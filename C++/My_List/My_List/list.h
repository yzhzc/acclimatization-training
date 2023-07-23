#pragma once


namespace My_List
{
	//链表结构
	template<class T>
	struct __list_node
	{
		__list_node<T>* _next;
		__list_node<T>* _prev;
		T _data;

		//构造
		__list_node(const T x = T())
			:_data(x)
			,_next(nullptr)
			,_prev(nullptr)
		{}
	};

	//迭代器指针结构
	template<class T, class Ref, class Ptr>
	struct __list_iterator
	{
		//迭代器类型为链表节点地址
		typedef __list_node<T> Node;
		typedef __list_iterator<T, Ref, Ptr> Self;//T, T&,T*
		Node* _node;

		//构造
		__list_iterator(Node* node)
			:_node(node)
		{}

		Ref operator*()
		{
			return _node->_data;
		}

		//前置++
		Self& operator++()
		{
			_node = _node->_next;
			return *this;
		}

		//后置++
		Self operator++(int)
		{
			Self tmp(*this);
			++(*this);

			return tmp;
		}

		//前置--
		Self& operator--()
		{
			_node = _node->_prev;
			return *this;
		}

		//后置--
		Self operator--(int)
		{
			Self tmp(*this);
			--(*this);

			return tmp;
		}

		bool operator!=(const Self& it)
		{
			return _node != it._node;
		}

		bool operator==(const Self& it)
		{
			return _node == it._node;
		}

		//->
		Ptr operator->()
		{
			return &_node->_data;
		}

	};


	template<class T>
	class list
	{
		typedef __list_node<T> Node;
	public:
		typedef __list_iterator<T, T&, T*> iterator;
		typedef __list_iterator<T, const T&, const T*> const_iterator;

		//构造
		list()
		{
			_head = new Node;
			_head->_next = _head;
			_head->_prev = _head;
		}

		//拷贝构造
		list(const list<T>& l1)
		{
			_head = new Node;
			_head->_next = _head;
			_head->_prev = _head;

			for (auto& e : l1)
			{
				push_back(e);
			}
		}

		~list()
		{
			clear();
			delete[] _head;
			_head = nullptr;
		}

		list<T>& operator=(list<T>& l1)
		{
			//if (this != &l1)
			//{
			//	clear();
			//	for (auto& e : l1)
			//	{
			//		push_back(e);
			//	}
			//}

			std::swap(_head, l1._head);
			
			return *this;
		}

		//清除所有数据
		void clear()
		{
			iterator it = begin();
			while (it != end())
			{
				erase(it++);
			}
		}

		//删除中间节点
		void erase(iterator pos)
		{
			assert(pos != end());
			Node* tmp = pos._node->_prev;
			tmp->_next = pos._node->_next;
			pos._node->_next->_prev = tmp;
			delete[] pos._node;
			pos._node = nullptr;
		}

		iterator begin()
		{
			return iterator(_head->_next);
		}

		iterator end()
		{
			return iterator(_head);
		}

		const_iterator begin() const
		{
			return const_iterator(_head->_next);
		}

		const_iterator end() const
		{
			return const_iterator(_head);
		}


		//尾插
		iterator push_back(const T& x)
		{
			return insert(_head, x);
		}

		//中间插入
		iterator insert(iterator pos, const T& x)
		{
			Node* cur = pos._node;
			Node* prev = cur->_prev;
			Node* newnode = new Node(x);
			prev->_next = newnode;
			newnode->_next = cur;
			cur->_prev = newnode;
			newnode->_prev = prev;

			return newnode;
		}

		//尾删
		void pop_back()
		{
			erase(--end());
		}

		//头删
		void pop_front()
		{
			erase(begin());
		}

		
	private:
		Node* _head;
	};







}