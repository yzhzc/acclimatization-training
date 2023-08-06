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
		int _dsti;	// Ŀ�����±�
		const W _w;	// Ȩֵ
		Node* _next;

		Node(int dsti, const W& w)
			:_dsti(dsti)
			, _w(w)
			, _next(nullptr)
		{}
	};

	struct Edge
	{
		size_t _srci;	// Ŀ�����±�
		size_t _dsti;
		W _w;	// Ȩֵ

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
			_vertexs.push_back(a[i]);	//�����������
			_indexMap[a[i]] = i;	//�洢��Ӧ�±�
		}
		_matrix.resize(n);
		for (size_t i = 0; i < _matrix.size(); i++)
		{
			_matrix[i].resize(n, MAX_W);
		}
	}

	~Graph()
	{}

	//��ȡĿ���Ӧ���±�
	size_t GetVertexIndex(const V& v)
	{
		auto it = _indexMap.find(v);
		if (it != _indexMap.end())
			return it->second;

		throw invalid_argument("���㲻����");	//��Ч�����쳣

		return -1;
	}

	//��ӱ�ֵ(��,��,ֵ)
	void AddEdge(const V& src, const V& dst, const W& w)
	{
		size_t srci = GetVertexIndex(src);
		size_t dsti = GetVertexIndex(dst);

		//ά���ڽӱ�
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
		vector<bool> visited(n, false);	//�������

		q.push(srci);
		visited[srci] = true;
		int levelSize = 1;
		
		while (!q.empty())
		{
			//����һ��һ���
			for (size_t i = 0; i < levelSize; ++i)
			{
				size_t front = q.front();
				q.pop();
				cout << front << ":" << _vertexs[front] << endl;
				//��front������ڽӶ��������
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
		vector<bool> visited(_vertexs.size(), false);	//�������
		_DFS(srci, visited);
	}

	//����һ����С������
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
		//С������
		priority_queue<Edge, vector<Edge>, greater<Edge>> minque;
		//�ߵ�Ȩֵ���
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
			//�ж��Ƿ񹹳ɻ�
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

	//����һ����С������
	W Prim(Self& minTree, const W& src)
	{
		//��ʼ��
		size_t n = _vertexs.size();
		size_t srci = GetVertexIndex(src);
		minTree._vertexs = _vertexs;
		minTree._indexMap = _indexMap;
		minTree._matrix.resize(n);
		for (size_t i = 0; i < n; ++i)
		{
			minTree._matrix[i].resize(n, MAX_W);
		}
		vector<bool> X(n, false);	//����־λ
		vector<bool> Y(n, true);	//�յ��־λ
		X[srci] = true;
		Y[srci] = false;

		priority_queue<Edge, vector<Edge>, greater<Edge>> minque;
		//��һ��������Χ�����
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
			//���X�����������������
			if (X[min._dsti])
				continue;

			minTree._AddEdge(min._srci, min._dsti, min._w);
			X[min._dsti] = true;
			Y[min._dsti] = false;

			++size;
			totalW += min._w;
			if (size == n - 1)
				return totalW;

			//�¶�����Χ�����,�ų���X�������ظ��ı�
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
	vector<V> _vertexs;	//����ļ���
	map<V, int> _indexMap; //����ӳ���±�
	vector<vector<W>> _matrix; //�ڽӾ���
	vector<Node*> _tables;	//�ڽӱ�
};