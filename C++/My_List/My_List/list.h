#pragma once


namespace My_List
{
	//����ṹ
	template<class T>
	struct __list_node
	{
		__list_node<T>* _next;
		__list_node<T>* _prev;
		T _data;

		//����
		__list_node(const T x = T())
			:_data(x)
			,_next(nullptr)
			,_prev(nullptr)
		{}
	};

	//������ָ��ṹ
	template<class T, class Ref, class Ptr>
	struct __list_iterator
	{
		//����������Ϊ����ڵ��ַ
		typedef __list_node<T> Node;
		typedef __list_iterator<T, Ref, Ptr> Self;//T, T&,T*
		Node* _node;

		//����
		__list_iterator(Node* node)
			:_node(node)
		{}

		Ref operator*()
		{
			return _node->_data;
		}

		//ǰ��++
		Self& operator++()
		{
			_node = _node->_next;
			return *this;
		}

		//����++
		Self operator++(int)
		{
			Self tmp(*this);
			++(*this);

			return tmp;
		}

		//ǰ��--
		Self& operator--()
		{
			_node = _node->_prev;
			return *this;
		}

		//����--
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

		//����
		list()
		{
			_head = new Node;
			_head->_next = _head;
			_head->_prev = _head;
		}

		//��������
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

		//�����������
		void clear()
		{
			iterator it = begin();
			while (it != end())
			{
				erase(it++);
			}
		}

		//ɾ���м�ڵ�
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


		//β��
		iterator push_back(const T& x)
		{
			return insert(_head, x);
		}

		//�м����
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

		//βɾ
		void pop_back()
		{
			erase(--end());
		}

		//ͷɾ
		void pop_front()
		{
			erase(begin());
		}

		
	private:
		Node* _head;
	};







}