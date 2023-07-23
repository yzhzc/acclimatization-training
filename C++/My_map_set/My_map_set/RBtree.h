#pragma once
#include<iostream>
using namespace std;



enum Colour
{
	BLACK,
	RED,
};


template<class T>
struct RBTreeNode
{
	RBTreeNode<T>* _left;
	RBTreeNode<T>* _right;
	RBTreeNode<T>* _parent;

	T _data;

	Colour _col;

	RBTreeNode(const T& data)
		:_left(nullptr)
		,_right(nullptr)
		,_parent(nullptr)
		,_data(data)
		,_col(BLACK)
	{}
};

template<class T>
class __TreeIterator
{
	typedef RBTreeNode<T> Node;
	
	Node* _node;

public:

	__TreeIterator(Node* node)
		:_node(node)
	{}

	typedef __TreeIterator<T> Self;

	T& operator*()
	{
		return _node->_data;
	}

	T* operator->()
	{
		return &_node->_data;
	}

	Self& operator++()
	{
		if (_node->_right)
		{
			Node* subLft = _node->_right;
			while (subLft->_left)
			{
				subLft = subLft->_left;
			}
			_node = subLft;
		}
		else
		{
			Node* cur = _node;
			Node* parent = cur->_parent;
			while (parent && cur == parent->_right)
			{
				cur = cur->_parent;
				parent = parent->_parent;
			}
			_node = parent;
		}
		return *this;
	}

	Self& operator--()
	{

	}

	bool operator!=(const Self& s)
	{
		return _node != s._node;
	}
};


//T接收的有可能是单个类型，也可能是pair<K, V>
template<class T, class KOfT>
class RBTree
{
	typedef RBTreeNode<T> Node;
	
public:
	typedef __TreeIterator<T> iterator;
	iterator begin()
	{
		Node* cur = _root;
		while (cur && cur->_left)
		{
			cur = cur->_left;
		}

		return iterator(cur);
	}

	iterator end()
	{
		return iterator(nullptr);
	}

	bool Insert(const T& data)
	{
		//按搜索树的规则进行插入
		//空树的情况
		if (_root == nullptr)
		{
			_root = new Node(data);
			return true;
		}

		//搜索节点的位置

		KOfT koft;		//生成传过来的结构体内，结构体内有仿函数
		Node* parent = nullptr;
		Node* cur = _root;
		while (cur)
		{
			if (koft(cur->_data) < koft(data))
			{
				parent = cur;
				cur = cur->_right;
			}
			else if (koft(cur->_data) > koft(data))
			{
				parent = cur;
				cur = cur->_left;
			}
			else
			{
				return false;
			}
		}

		//接入新节点，上下链接
		cur = new Node(data);
		cur->_parent = parent;
		if (koft(parent->_data) < koft(data))
			parent->_right = cur;
		else
			parent->_left = cur;

		//新增节点是红
		cur->_col = RED;
		while (parent && parent->_col == RED)
		{
			//红黑色条件看叔叔
			Node* grandfather = parent->_parent;
			//parent在左边
			if(grandfather->_left == parent)
			{
				Node* uncle = grandfather->_right;
				//情况1：uncle存在，且为红
				if (uncle && uncle->_col == RED)
				{
					parent->_col = uncle->_col = BLACK;
					if (grandfather != _root)
						grandfather->_col = RED;

					//继续向上处理
					cur = grandfather;
					parent = cur->_parent;
				}
				//情况3:uncle存在，且为黑
				//        或者
				//情况2：uncle不存在
				else
				{
					//左右折
					if (cur == parent->_right)
					{
						RotateL(parent);
						swap(parent, cur);
					}
					RotateR(grandfather);
					grandfather->_col = RED;
					parent->_col = BLACK;

					break;
				}
			}
			else
			{
				//parent在右边
				Node* uncle = grandfather->_left;
				//情况1：uncle存在，且为红
				if (uncle && uncle->_col == RED)
				{
					parent->_col = uncle->_col = BLACK;
					if (grandfather != _root)
						grandfather->_col = RED;

					//继续向上处理
					cur = grandfather;
					parent = cur->_parent;
				}
				//情况3:uncle存在，且为黑
				//        或者
				//情况2：uncle不存在
				else
				{
					//右左折
					if (cur == parent->_left)
					{
						RotateR(parent);
						swap(parent, cur);
					}
					RotateL(grandfather);
					grandfather->_col = RED;
					parent->_col = BLACK;

					break;
				}
			}
		}
		return true;
	}

	//右树右节点超出向左旋转
	void RotateL(Node* parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;
		Node* pparent = parent->_parent;

		//将右树左节点插下接到parent右边
		parent->_right = subRL;
		if (subRL)
			subRL->_parent = parent;

		//将parent插下接到右树左边
		subR->_left = parent;
		parent->_parent = subR;

		//判断parent的parent与subR的链接
		if (_root == parent)
		{
			_root = subR;
			subR->_parent = nullptr;
		}
		else
		{
			subR->_parent = pparent;
			if (parent == pparent->_left)
				pparent->_left = subR;
			else
				pparent->_right = subR;
		}
	}

	//左树左节点超出向右旋转
	void RotateR(Node* parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;
		Node* pparent = parent->_parent;

		//将左树右节点插下接到parent左边
		parent->_left = subLR;
		if (subLR)
			subLR->_parent = parent;

		//将parent插下接到左树右边
		subL->_right = parent;
		parent->_parent = subL;

		//判断parent的parent与subL的链接
		if (_root == parent)
		{
			_root = subL;
			subL->_parent = nullptr;
		}
		else
		{
			subL->_parent = pparent;
			if (parent == pparent->_left)
				pparent->_left = subL;
			else
				pparent->_right = subL;
		}
	}

	//c++的递归方式
	void _InOrder(Node* root)
	{
		if (root == nullptr)
			return;

		_InOrder(root->_left);
		cout << root->_kv.first << " " << root->_kv.second << endl;
		_InOrder(root->_right);
	}
	//中序打印二叉树
	void InOrder()
	{
		_InOrder(_root);
		cout << endl;
	}

	Node* Find(const T& key)
	{
		KOfT koft;
		Node* cur = _root;
		Node* parent = nullptr;
		while (cur)
		{
			if (koft(cur->_data) < koft(key))
			{
				parent = cur;
				cur = cur->_right;
			}
			else if (koft(cur->_data) > koft(key))
			{
				parent = cur;
				cur = cur->_left;
			}
			else
			{
				return cur;
			}
		}

		return nullptr;
	}
private:
	Node* _root = nullptr;
};


