#pragma once
#include<vector>
#include<queue>
#include<map>
#include<functional>
#include"UnionFindSet.h"

using namespace std;

template<class V, class W, W MAX_W = INT_MAX, bool Direction = false>
class Graph
{
	typedef Graph<V, W, MAX_W, Direction> Self;

	struct Node
	{
		int _dsti;	// 目标点的下标
		const W _w;	// 权值
		Node* _next;

		Node(int dsti, const W& w)
			:_dsti(dsti)
			, _w(w)
			, _next(nullptr)
		{}
	};

	struct Edge
	{
		size_t _srci;	// 目标点的下标
		size_t _dsti;
		W _w;	// 权值

		Edge(size_t srci, size_t dsti, const W& w)
			:_srci(srci)
			, _dsti(dsti)
			, _w(w)
		{}

		bool operator>(const Edge& e) const
		{
			return _w > e._w;
		}
	};
public:
	Graph()
	{}

	Graph(const V* a, size_t n)
		:_tables(n, nullptr)
	{
		for (size_t i = 0; i < n; i++)
		{
			_vertexs.push_back(a[i]);	//数据依次入表
			_indexMap[a[i]] = i;	//存储对应下标
		}
		_matrix.resize(n);
		for (size_t i = 0; i < _matrix.size(); i++)
		{
			_matrix[i].resize(n, MAX_W);
		}
	}

	~Graph()
	{}

	//获取目标对应的下标
	size_t GetVertexIndex(const V& v)
	{
		auto it = _indexMap.find(v);
		if (it != _indexMap.end())
			return it->second;

		throw invalid_argument("顶点不存在");	//无效参数异常

		return -1;
	}

	//添加边值(行,列,值)
	void AddEdge(const V& src, const V& dst, const W& w)
	{
		size_t srci = GetVertexIndex(src);
		size_t dsti = GetVertexIndex(dst);

		//维护邻接表
		Node* eg = new Node(dsti, w);
		eg->_next = _tables[srci];
		_tables[srci] = eg;

		if (Direction == false)
		{
			Node* eg = new Node(srci, w);
			eg->_next = _tables[dsti];
			_tables[dsti] = eg;
		}

		_AddEdge(srci, dsti, w);
	}

	void _AddEdge(size_t srci, size_t dsti, const W& w)
	{
		_matrix[srci][dsti] = w;
		if (Direction == false)
		{
			_matrix[dsti][srci] = w;
		}
	}

	void BFS(const V& src)
	{
		size_t n = _vertexs.size();
		size_t srci = GetVertexIndex(src);
		queue<size_t> q;
		vector<bool> visited(n, false);	//标记数组

		q.push(srci);
		visited[srci] = true;
		int levelSize = 1;
		
		while (!q.empty())
		{
			//控制一层一层出
			for (size_t i = 0; i < levelSize; ++i)
			{
				size_t front = q.front();
				q.pop();
				cout << front << ":" << _vertexs[front] << endl;
				//把front顶点的邻接顶点入队列
				for (size_t i = 0; i < n; i++)
				{
					if (_matrix[front][i] != MAX_W && visited[i] == false)
					{
						q.push(i);
						visited[i] = true;
					}
				}
			}
			cout << endl;
			levelSize = q.size();
		}
		cout << endl;
	}

	void _DFS(const size_t srci, vector<bool>& visited)
	{
		cout << srci << ":" << _vertexs[srci] << endl;
		visited[srci] = true;
		for (size_t i = 0; i < _vertexs.size(); i++)
		{
			if (_matrix[srci][i] != MAX_W && visited[i] == false)
			{
				_DFS(i, visited);
			}
		}
	}

	void DFS(const V& src)
	{
		size_t srci = GetVertexIndex(src);
		vector<bool> visited(_vertexs.size(), false);	//标记数组
		_DFS(srci, visited);
	}

	//制造一颗最小生成树
	W Kruskal(Self& minTree)
	{
		size_t n = _vertexs.size();
		minTree._vertexs = _vertexs;
		minTree._indexMap = _indexMap;
		minTree._matrix.resize(n);
		for (size_t i = 0; i < n; ++i)
		{
			minTree._matrix[i].resize(n, MAX_W);
		}
		//小堆升序
		priority_queue<Edge, vector<Edge>, greater<Edge>> minque;
		//边的权值入堆
		for (size_t i = 0; i < n; ++i)
		{
			for (size_t j = 0; j < n; ++j)
			{
				if (i < j && _matrix[i][j] != MAX_W)
				{
					minque.push(Edge(i, j, _matrix[i][j]));
				}
			}
		}
		int size = 0;
		W totalW = W();
		UnionFindSet ufs(n);
		while (!minque.empty())
		{
			Edge min = minque.top();
			minque.pop();
			//判断是否构成环
			if (!ufs.InSet(min._srci, min._dsti))
			{
				minTree._AddEdge(min._srci, min._dsti, min._w);
				ufs.Union(min._srci, min._dsti);
				++size;
				totalW += min._w;
			}
			if (size == n - 1)
				return totalW;
		}
		return W();
	}

	//制造一颗最小生成树
	W Prim(Self& minTree, const W& src)
	{
		//初始化
		size_t n = _vertexs.size();
		size_t srci = GetVertexIndex(src);
		minTree._vertexs = _vertexs;
		minTree._indexMap = _indexMap;
		minTree._matrix.resize(n);
		for (size_t i = 0; i < n; ++i)
		{
			minTree._matrix[i].resize(n, MAX_W);
		}
		vector<bool> X(n, false);	//起点标志位
		vector<bool> Y(n, true);	//终点标志位
		X[srci] = true;
		Y[srci] = false;

		priority_queue<Edge, vector<Edge>, greater<Edge>> minque;
		//第一个顶点周围边入堆
		for (size_t i = 0; i < n; ++i)
		{
			if (_matrix[srci][i] != MAX_W)
				minque.push(Edge(srci, i, _matrix[srci][i]));
		}
		int size = 0;
		W totalW = W();
		while (!minque.empty())
		{
			Edge min = minque.top();
			minque.pop();
			//如果X中有这个顶点则跳过
			if (X[min._dsti])
				continue;

			minTree._AddEdge(min._srci, min._dsti, min._w);
			X[min._dsti] = true;
			Y[min._dsti] = false;

			++size;
			totalW += min._w;
			if (size == n - 1)
				return totalW;

			//新顶点周围边入堆,排除与X集合中重复的边
			for (size_t i = 0; i < n; ++i)
			{
				if (_matrix[min._dsti][i] != MAX_W && Y[i])
					minque.push(Edge(min._dsti, i, _matrix[min._dsti][i]));
			}
		}
		return W();
	}

	void Print()
	{
		for (size_t i = 0; i < _vertexs.size(); ++i)
			cout << "[" << i << "]" << "->" << _vertexs[i] << endl;

		cout << endl;
		cout << "  ";
		for (size_t i = 0; i < _matrix.size(); i++)
			cout << i << " ";

		cout << endl;
		for (size_t i = 0; i < _matrix.size(); i++)
		{
			cout << i << " ";
			for (size_t j = 0; j < _matrix.size(); j++)
			{
				if (_matrix[i][j] == INT_MAX)
					cout << "*" << " ";
				else
					cout << _matrix[i][j] << " ";
			}
			cout << endl;
		}
		cout << endl;

		for (int i = 0; i < _tables.size(); i++)
		{
			Node* prev = _tables[i];
			cout << i;
			while (prev)
			{
				cout << "->" << prev->_dsti << "(" << prev->_w << ")";
				prev = prev->_next;
			}
			cout << endl;
		}
		cout << endl;
	}

private:
	vector<V> _vertexs;	//顶点的集合
	map<V, int> _indexMap; //顶点映射下标
	vector<vector<W>> _matrix; //邻接矩阵
	vector<Node*> _tables;	//邻接表
};