#pragma once
#include<iostream>

using namespace std;

template<class K, class V>
struct AVLTreeNode
{
	AVLTreeNode<K, V>* _left;
	AVLTreeNode<K, V>* _right;
	AVLTreeNode<K, V>* _parent;
	int _bf;	//平衡因子
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
	//插入
	bool Insert(const pair<K, V>& kv)
	{
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

		//更新平衡因子
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
				//高度变化了，需要向上更新
				cur = parent;
				parent = parent->_parent;
			}
			else if (parent->_bf == 2 || parent->_bf == -2)
			{
				//不平衡了，旋转处理
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
				//旋转完就全部平衡，跳出循环
				break;
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

		//平衡因子复位
		parent->_bf = 0;
		subR->_bf = 0;
	}

	//右树左节点超出，右旋再左旋
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

		//平衡因子复位
		parent->_bf = 0;
		subL->_bf = 0;
	}

	//左树右节点超出，左旋再右旋
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

	//判断是否为平衡二叉树
	bool IsBalance()
	{
		return _IsBalance(_root);
	}

	//删除节点
	bool Erase(const K& key)
	{
		//搜索节点的位置
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
				//找到位置分情况删除
				if (cur->_left == nullptr)
				{
					//删除节点左边为空
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
					//删除节点右边为空
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
					//删除节点俩边都不为空
					//找删除节点右边最左（最小）的节点，或者左边最大节点，去替代删除节点
					Node* rightMin = cur->_right;
					Node* rightMinParent = rightMin->_parent;
					while (rightMin->_left)
					{
						rightMinParent = rightMin;
						rightMin = rightMin->_left;
					}

					//最左节点与删除节点交换数据
					cur->_kv = rightMin->_kv;

					//处理最左节点的右边的节点与父节点的链接
					if (rightMin == rightMinParent->_left)
					{
						rightMinParent->_left = rightMin->_right;
						parent = rightMinParent;
						parent->_bf++;
					}
					else
					{
						//父节点就是删除节点的情况
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
						//子树高度减小了，向上更新平衡因子
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
							//左子树超出，右单旋
							RotateR(parent);
						}
						else if (parent->_bf == 2)
						{
							//右子树超出，左单旋
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










































