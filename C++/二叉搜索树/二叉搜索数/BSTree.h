#pragma once
#include<iostream>


using namespace std;

template<class T>
struct BTreeNode
{
	T _key;
	BTreeNode<T>* _left;
	BTreeNode<T>* _right;

	BTreeNode(const T& key)
		:_left(nullptr)
		, _right(nullptr)
		, _key(key)
	{}
};

template<class T>
class BSTree
{
	typedef BTreeNode<T> Node;
public:

	//����ڵ�
	bool Insert(const T& key)
	{
		if (_root == nullptr)
		{
			_root = new Node(key);
			return true;
		}

		Node* parent = nullptr;
		Node* cur = _root;
		while (cur)
		{
			if (cur->_key < key)
			{
				parent = cur;
				cur = cur->_right;
			}
			else if (cur->_key > key)
			{
				parent = cur;
				cur = cur->_left;
			}
			else
			{
				return false;
			}
		}

		cur = new Node(key);
		if (cur->_key > parent->_key)
		{
			parent->_right = cur;
		}
		else
		{
			parent->_left = cur;
		}

		return true;
	}

	//c++�ĵݹ鷽ʽ
	void _InOrder(Node* root)
	{
		if (root == nullptr)
			return;

		_InOrder(root->_left);
		cout << root->_key << " ";
		_InOrder(root->_right);
	}
	//�����ӡ������
	void InOrder()
	{
		_InOrder(_root);
		cout << endl;
	}

	//����
	bool Find(const T& key)
	{
		Node* cur = _root;
		while (cur)
		{
			if (cur->_key < key)
			{
				cur = cur->_right;
			}
			else if (cur->_key > key)
			{
				cur = cur->_left;
			}
			else
			{
				return true;
			}
		}

		return false;
	}

	//ɾ��
	bool Erase(const T& key)
	{
		Node* cur = _root;
		Node* parent = nullptr;
		while (cur)
		{
			//��������ڵ�
			if (cur->_key < key)
			{
				parent = cur;
				cur = cur->_right;
			}
			else if (cur->_key > key)
			{
				parent = cur;
				cur = cur->_left;
			}
			else
			{
				//ɾ���Ľڵ������֧
				if (cur->_left == nullptr)
				{
					if (parent->_left == cur)
					{
						parent->_left = cur->_right;
					}
					else if (parent->_right == cur)
					{
						parent->_right = cur->_right;
					}

					delete cur;
				}
				//ɾ���Ľڵ����ҷ�֧
				else if (cur->_right == nullptr)
				{
					if (parent->_left == cur)
					{
						parent->_left = cur->_left;
					}
					else if (parent->_right == cur)
					{
						parent->_right = cur->_left;
					}

					delete cur;
				}
				//ɾ���Ľڵ����Ҷ��з�֧
				else
				{
					Node* rightMin = cur->_right;
					Node* rightMinParent = cur;
					//��ɾ���ڵ��ұ�������С���Ľڵ㣬����������ڵ㣬ȥ���ɾ���ڵ�
					while (rightMin->_left)
					{
						rightMinParent = rightMin;
						rightMin = rightMin->_left;
					}
					cur->_key = rightMin->_key;

					if (rightMin == rightMinParent->_left)
					{
						rightMinParent->_left = rightMin->_right;
					}
					else
					{
						//���ڵ����ɾ���ڵ�����
						rightMinParent->_right = rightMin->_right;
					}
					
					delete rightMin;
				}

				return true;
			}
		}
		return false;
	}
private:
	Node* _root = nullptr;
};
