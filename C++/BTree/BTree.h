#pragma once

using namespace std;

template<class K, size_t M>
struct BTreeNode
{
	K _keys[M];	// 权值
	BTreeNode<K, M>* _subs[M + 1];	// 字节点
	size_t _n;	// 实际存储的关键字数量
	BTreeNode<K, M>* _parent;

	BTreeNode()
	{
		for (size_t i = 0; i < M; ++i)
		{
			_keys[i] = K();
			_subs[i] = nullptr;
		}
		_subs[M] = nullptr;
		_n = 0;
		_parent = nullptr;
	}
};


//如果数据是存在磁盘中,K是磁盘地址
template<class K, size_t M>
class BTree
{
	typedef BTreeNode<K, M> Node;
public:

	//查找关键字位置
	pair<Node*, int> Find(const K& key)
	{
		Node* cur = _root;
		Node* parent = nullptr;
		size_t i = 0;
		
		while (cur)
		{
			while (i < cur->_n)	//如果大于所有关键字则进入最后一个节点
			{
				if (key < cur->_keys[i])	//小于关键字进入子节点
					break;
				else if (key > cur->_keys[i])	//大于关键字则判断下一个关键字
					++i;
				else
					return make_pair(cur, i);
			}
			parent = cur;
			cur = cur->_subs[i];
		}
		return make_pair(parent, -1);
	}

	void Insterkey(Node* node, const K& key, Node* child)
	{
		int end = node->_n - 1;
		while (end >= 0)
		{
			// 将数据后移给key腾出对应位置
			if (key < node->_keys[end])
			{
				node->_keys[end + 1] = ->_keys[end];
				node->_subs[end + 2] = node->_subs[end + 1];
				end--;
			}
			else
			{
				break;
			}
		}
		node->_keys[end + 1] = key;
		node->_subs[end + 2] = child;
		if (child)
			child->_parent = node;

		node->_n++;
	}

	bool Insert(const K& key)
	{
		if (_root == nullptr)
		{
			_root = new Node;
			_root->_keys[0] = key;
			_root->_n++;

			return true;
		}

		// key已经存在，不允许插入
		pair<Node*, int> ret = Find(key);
		if (ret.second >= 0)
			return false;

		// 如果没有找到，find顺便带回parent节点
		// 循环每次往cur插入 newkey和child
		Node* cur = ret.first;
		K newKey = key;
		Node* child = nullptr;
		while (1)
		{
			InsertKey(cur, newKey, child);
			// 满了就要分裂
			// 没有满，插入就结束
			if (cur->_n < M)
			{
				return true;
			}
			else
			{
				// 分裂一半[mid+1, M-1]给兄弟
				size_t mid = M / 2;
				Node* brother = new Node;
				size_t j = 0;
				size_t i = 0;
				for (i = mid + 1; i <= M - 1; ++i)
				{
					// 分裂拷贝key和key的左孩子
					brother->_keys[j] = cur->_keys[i];
					brother->_subs[j] = cur->_subs[i];

					// 将拷贝走的叶子节点对应的parent修改为brother
					if (cur->_subs[i])
						cur->_subs[i]->_parent = brother;

					// 重置已经拷贝走的数据
					cur->_keys[i] = K();
					cur->_subs[i] = nullptr;

					++j;
				}
				// 处理最后一位M位置的_subs
				brother->_subs[j] = cur->_subs[i];
				if (cur->_subs[i])
					cur->_subs[i]->_parent = brother;

				cur->_subs[i] = nullptr;

				// 修改兄弟节点的关键字数量
				brother->_n = j;
				cur->_n -= (brother->_n + 1);

				// 取出中位数key插入上层parent中
				K midKey = cur->_keys[mid];
				cur->_keys[mid] = K();

				// 说明刚刚分裂是根节点
				if (cur->_parent == nullptr)
				{
					_root = new Node;
					_root->_keys[0] = midKey;
					_root->_subs[0] = cur;
					_root->_subs[1] = brother;
					_root->_n = 1;

					cur->_parent = _root;
					brother->_parent = _root;
					break;
				}
				else
				{
					// 转换成往parent->parent 去插入parent->[mid] 和 brother
					newKey = midKey;

					child = brother;
					cur = cur->_parent;
				}
			}
		}
		return true;
	}

private:
	Node* _root = nullptr;
};
