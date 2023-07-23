#pragma once
#include<iostream>
using namespace std;



enum Colour
{
	BLACK,
	RED,
};


template<class K,class V>
struct RBTreeNode
{
	RBTreeNode<K, V>* _left;
	RBTreeNode<K, V>* _right;
	RBTreeNode<K, V>* _parent;

	std::pair<K, V> _kv;

	Colour _col;

	RBTreeNode(const std::pair<K, V> kv)
		:_left(nullptr)
		,_right(nullptr)
		,_parent(nullptr)
		,_kv(kv)
		,_col(BLACK)
	{}
};

template<class K, class V>
class RBTree
{
	typedef RBTreeNode<K, V> Node;
public:

	bool Insert(const std::pair<K, V>& kv)
	{
		//按搜索树的规则进行插入
		//空树的情况
		if (_root == nullptr)
		{
			_root = new Node(kv);
			return true;
		}

		//搜索节点的位置
		Node* parent = nullptr;
		Node* cur = _root;
		while (cur)
		{
			if (cur->_kv.first < kv.first)
			{
				parent = cur;
				cur = cur->_right;
			}
			else if (cur->_kv.first > kv.first)
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
		cur = new Node(kv);
		cur->_parent = parent;
		if (parent->_kv.first < kv.first)
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
private:
	Node* _root = nullptr;
};


