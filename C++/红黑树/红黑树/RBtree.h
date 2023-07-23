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
		//���������Ĺ�����в���
		//���������
		if (_root == nullptr)
		{
			_root = new Node(kv);
			return true;
		}

		//�����ڵ��λ��
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

		//�����½ڵ㣬��������
		cur = new Node(kv);
		cur->_parent = parent;
		if (parent->_kv.first < kv.first)
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
private:
	Node* _root = nullptr;
};


