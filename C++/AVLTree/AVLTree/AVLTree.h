#pragma once
#include<iostream>

using namespace std;

template<class K, class V>
struct AVLTreeNode
{
	AVLTreeNode<K, V>* _left;
	AVLTreeNode<K, V>* _right;
	AVLTreeNode<K, V>* _parent;
	int _bf;	//ƽ������
	pair<K, V> _kv;

	AVLTreeNode(const pair<K, V> kv)
		:_left(nullptr)
		,_right(nullptr)
		,_parent(nullptr)
		,_bf(0)
		,_kv(kv)
	{}
};

template <class K,class V>
class AVLTree
{
	typedef AVLTreeNode<K, V> Node;
public:
	//����
	bool Insert(const pair<K, V>& kv)
	{
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

		//����ƽ������
		while (parent)
		{
			if (cur == parent->_right)
				parent->_bf++;
			else
				parent->_bf--;

			if (parent->_bf == 0)
			{
				break;

			}
			else if (parent->_bf == 1 || parent->_bf == -1)
			{
				//�߶ȱ仯�ˣ���Ҫ���ϸ���
				cur = parent;
				parent = parent->_parent;
			}
			else if (parent->_bf == 2 || parent->_bf == -2)
			{
				//��ƽ���ˣ���ת����
				if (parent->_bf == 2)
				{
					if (cur->_bf == 1)
					{
						RotateL(parent);
					}
					else if(cur->_bf == -1)
					{
						RotateRL(parent);
					}
				}
				else if(parent->_bf == -2)
				{
					if (cur->_bf == -1)
					{
						RotateR(parent);
					}
					else if (cur->_bf == 1)
					{
						RotateLR(parent);
					}
				}
				//��ת���ȫ��ƽ�⣬����ѭ��
				break;
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
			subR->_parent =  nullptr;
		}
		else
		{
			subR->_parent = pparent;
			if (parent == pparent->_left)
				pparent->_left = subR;
			else
				pparent->_right = subR;
		}

		//ƽ�����Ӹ�λ
		parent->_bf = 0;
		subR->_bf = 0;
	}

	//������ڵ㳬��������������
	void RotateRL(Node* parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;
		int bf = subRL->_bf;
		RotateR(subR);
		RotateL(parent);
		if (bf == -1)
		{
			parent->_bf = 0;
			subR->_bf = 1;
			subRL->_bf = 0;
		}
		else if (bf == 1)
		{
			parent->_bf = -1;
			subR->_bf = 0;
			subRL->_bf = 0;
		}
		else
		{
			parent->_bf = 0;
			subR->_bf = 0;
			subRL->_bf = 0;
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

		//ƽ�����Ӹ�λ
		parent->_bf = 0;
		subL->_bf = 0;
	}

	//�����ҽڵ㳬��������������
	void RotateLR(Node* parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;
		int bf = subLR->_bf;
		RotateL(subL);
		RotateR(parent);
		if (bf == -1)
		{
			parent->_bf = 1;
			subL->_bf = 0;
			subLR->_bf = 0;
		}
		else if (bf == 1)
		{
			parent->_bf = 0;
			subL->_bf = -1;
			subLR->_bf = 0;
		}
		else
		{
			parent->_bf = 0;
			subL->_bf = 0;
			subLR->_bf = 0;
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

	int Hight(Node* root)
	{
		if (root == nullptr)
			return 0;

		int leftHight = Hight(root->_left);
		int rightHight = Hight(root->_right);

		return max(leftHight, rightHight) + 1;
	}

	bool _IsBalance(Node* root)
	{
		if (root == nullptr)
			return true;

		int leftHight = Hight(root->_left);
		int rightHight = Hight(root->_right);

		return abs(leftHight - rightHight) < 2 && _IsBalance(root->_left) && _IsBalance(root->_right);
	}

	//�ж��Ƿ�Ϊƽ�������
	bool IsBalance()
	{
		return _IsBalance(_root);
	}

	//ɾ���ڵ�
	bool Erase(const K& key)
	{
		//�����ڵ��λ��
		Node* parent = nullptr;
		Node* cur = _root;
		while (cur)
		{
			if (cur->_kv.first < key)
			{
				parent = cur;
				cur = cur->_right;
			}
			else if (cur->_kv.first > key)
			{
				parent = cur;
				cur = cur->_left;
			}
			else
			{
				//�ҵ�λ�÷����ɾ��
				if (cur->_left == nullptr)
				{
					//ɾ���ڵ����Ϊ��
					if (parent->_left == cur)
					{
						parent->_left = cur->_right;
						parent->_bf++;
					}
					else
					{
						parent->_right = cur->_right;
						parent->_bf--;
					}

					if(cur->_right)
						cur->_right->_parent = parent;

					delete cur;
				}
				else if (cur->_right == nullptr)
				{
					//ɾ���ڵ��ұ�Ϊ��
					if (parent->_left == cur)
					{
						parent->_left = cur->_left;
						parent->_bf++;
					}
					else
					{
						parent->_right = cur->_left;
						parent->_bf--;
					}

					if (cur->_left)
						cur->_left->_parent = parent;

					delete cur;
				}
				else
				{
					//ɾ���ڵ����߶���Ϊ��
					//��ɾ���ڵ��ұ�������С���Ľڵ㣬����������ڵ㣬ȥ���ɾ���ڵ�
					Node* rightMin = cur->_right;
					Node* rightMinParent = rightMin->_parent;
					while (rightMin->_left)
					{
						rightMinParent = rightMin;
						rightMin = rightMin->_left;
					}

					//����ڵ���ɾ���ڵ㽻������
					cur->_kv = rightMin->_kv;

					//��������ڵ���ұߵĽڵ��븸�ڵ������
					if (rightMin == rightMinParent->_left)
					{
						rightMinParent->_left = rightMin->_right;
						parent = rightMinParent;
						parent->_bf++;
					}
					else
					{
						//���ڵ����ɾ���ڵ�����
						rightMinParent->_right = rightMin->_right;
						parent = rightMinParent;
						parent->_bf--;
					}
					delete rightMin;
				}
				while (parent)
				{
					if (parent->_bf == 0)
					{
						//�����߶ȼ�С�ˣ����ϸ���ƽ������
						cur = parent;
						parent = parent->_parent;

						if (cur == parent->_left)
							parent->_bf++;
						else
							parent->_bf--;
					}
					else if (parent->_bf == 1 || parent->_bf == -1)
					{
						break;
					}
					else if (parent->_bf == 2 || parent->_bf == -2)
					{
						if (parent->_bf == -2)
						{
							//�������������ҵ���
							RotateR(parent);
						}
						else if (parent->_bf == 2)
						{
							//����������������
							RotateL(parent);
						}
						break;
					}
				}
				return true;
			}
		}
		return false;
	}

private:
	Node* _root = nullptr;
};










































