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

	//插入节点
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

	//c++的递归方式
	void _InOrder(Node* root)
	{
		if (root == nullptr)
			return;

		_InOrder(root->_left);
		cout << root->_key << " ";
		_InOrder(root->_right);
	}
	//中序打印二叉树
	void InOrder()
	{
		_InOrder(_root);
		cout << endl;
	}

	//查找
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

	//删除
	bool Erase(const T& key)
	{
		Node* cur = _root;
		Node* parent = nullptr;
		while (cur)
		{
			//搜索这个节点
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
				//删除的节点无左分支
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
				//删除的节点无右分支
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
				//删除的节点左右都有分支
				else
				{
					Node* rightMin = cur->_right;
					Node* rightMinParent = cur;
					//找删除节点右边最左（最小）的节点，或者左边最大节点，去替代删除节点
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
						//父节点就是删除节点的情况
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
