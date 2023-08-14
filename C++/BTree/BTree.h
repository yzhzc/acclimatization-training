#pragma once

using namespace std;

template<class K, size_t M>
struct BTreeNode
{
	K _keys[M];	// Ȩֵ
	BTreeNode<K, M>* _subs[M + 1];	// �ֽڵ�
	size_t _n;	// ʵ�ʴ洢�Ĺؼ�������
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


//��������Ǵ��ڴ�����,K�Ǵ��̵�ַ
template<class K, size_t M>
class BTree
{
	typedef BTreeNode<K, M> Node;
public:

	//���ҹؼ���λ��
	pair<Node*, int> Find(const K& key)
	{
		Node* cur = _root;
		Node* parent = nullptr;
		size_t i = 0;
		
		while (cur)
		{
			while (i < cur->_n)	//����������йؼ�����������һ���ڵ�
			{
				if (key < cur->_keys[i])	//С�ڹؼ��ֽ����ӽڵ�
					break;
				else if (key > cur->_keys[i])	//���ڹؼ������ж���һ���ؼ���
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
			// �����ݺ��Ƹ�key�ڳ���Ӧλ��
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

		// key�Ѿ����ڣ����������
		pair<Node*, int> ret = Find(key);
		if (ret.second >= 0)
			return false;

		// ���û���ҵ���find˳�����parent�ڵ�
		// ѭ��ÿ����cur���� newkey��child
		Node* cur = ret.first;
		K newKey = key;
		Node* child = nullptr;
		while (1)
		{
			InsertKey(cur, newKey, child);
			// ���˾�Ҫ����
			// û����������ͽ���
			if (cur->_n < M)
			{
				return true;
			}
			else
			{
				// ����һ��[mid+1, M-1]���ֵ�
				size_t mid = M / 2;
				Node* brother = new Node;
				size_t j = 0;
				size_t i = 0;
				for (i = mid + 1; i <= M - 1; ++i)
				{
					// ���ѿ���key��key������
					brother->_keys[j] = cur->_keys[i];
					brother->_subs[j] = cur->_subs[i];

					// �������ߵ�Ҷ�ӽڵ��Ӧ��parent�޸�Ϊbrother
					if (cur->_subs[i])
						cur->_subs[i]->_parent = brother;

					// �����Ѿ������ߵ�����
					cur->_keys[i] = K();
					cur->_subs[i] = nullptr;

					++j;
				}
				// �������һλMλ�õ�_subs
				brother->_subs[j] = cur->_subs[i];
				if (cur->_subs[i])
					cur->_subs[i]->_parent = brother;

				cur->_subs[i] = nullptr;

				// �޸��ֵܽڵ�Ĺؼ�������
				brother->_n = j;
				cur->_n -= (brother->_n + 1);

				// ȡ����λ��key�����ϲ�parent��
				K midKey = cur->_keys[mid];
				cur->_keys[mid] = K();

				// ˵���ոշ����Ǹ��ڵ�
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
					// ת������parent->parent ȥ����parent->[mid] �� brother
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
