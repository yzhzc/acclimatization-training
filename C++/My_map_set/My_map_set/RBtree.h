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


//T���յ��п����ǵ������ͣ�Ҳ������pair<K, V>
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
		//���������Ĺ�����в���
		//���������
		if (_root == nullptr)
		{
			_root = new Node(data);
			return true;
		}

		//�����ڵ��λ��

		KOfT koft;		//���ɴ������Ľṹ���ڣ��ṹ�����зº���
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

		//�����½ڵ㣬��������
		cur = new Node(data);
		cur->_parent = parent;
		if (koft(parent->_data) < koft(data))
			parent->_right = cur;
		else
			parent->_left = cur;

		//�����ڵ��Ǻ�
		cur->_col = RED;
		while (parent && parent->_col == RED)
		{
			//���ɫ����������
			Node* grandfather = parent->_parent;
			//parent�����
			if(grandfather->_left == parent)
			{
				Node* uncle = grandfather->_right;
				//���1��uncle���ڣ���Ϊ��
				if (uncle && uncle->_col == RED)
				{
					parent->_col = uncle->_col = BLACK;
					if (grandfather != _root)
						grandfather->_col = RED;

					//�������ϴ���
					cur = grandfather;
					parent = cur->_parent;
				}
				//���3:uncle���ڣ���Ϊ��
				//        ����
				//���2��uncle������
				else
				{
					//������
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
				//parent���ұ�
				Node* uncle = grandfather->_left;
				//���1��uncle���ڣ���Ϊ��
				if (uncle && uncle->_col == RED)
				{
					parent->_col = uncle->_col = BLACK;
					if (grandfather != _root)
						grandfather->_col = RED;

					//�������ϴ���
					cur = grandfather;
					parent = cur->_parent;
				}
				//���3:uncle���ڣ���Ϊ��
				//        ����
				//���2��uncle������
				else
				{
					//������
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

	//�����ҽڵ㳬��������ת
	void RotateL(Node* parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;
		Node* pparent = parent->_parent;

		//��������ڵ���½ӵ�parent�ұ�
		parent->_right = subRL;
		if (subRL)
			subRL->_parent = parent;

		//��parent���½ӵ��������
		subR->_left = parent;
		parent->_parent = subR;

		//�ж�parent��parent��subR������
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

	//������ڵ㳬��������ת
	void RotateR(Node* parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;
		Node* pparent = parent->_parent;

		//�������ҽڵ���½ӵ�parent���
		parent->_left = subLR;
		if (subLR)
			subLR->_parent = parent;

		//��parent���½ӵ������ұ�
		subL->_right = parent;
		parent->_parent = subL;

		//�ж�parent��parent��subL������
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

	//c++�ĵݹ鷽ʽ
	void _InOrder(Node* root)
	{
		if (root == nullptr)
			return;

		_InOrder(root->_left);
		cout << root->_kv.first << " " << root->_kv.second << endl;
		_InOrder(root->_right);
	}
	//�����ӡ������
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


