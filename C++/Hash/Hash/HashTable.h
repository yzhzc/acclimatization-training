#pragma once
#include<vector>
#include<iostream>



using namespace std;



//开散列
namespace OPEN_HASH
{
	template<class T>
	struct HashNode
	{
		T _data;
		HashNode<T>* _next;

		HashNode(const T& data)
			:_data(data)
			,_next(nullptr)
		{}
	};


	//前置声明，让迭代器找到这个类型
	template<class K, class T, class KeyOfT, class Hash>
	class HashTable;


	//迭代器
	template<class K, class T, class KeyOfT, class Hash>
	struct __HashTableIterator
	{
		typedef HashTable<K, T, KeyOfT, Hash> HT;
		typedef __HashTableIterator<K, T, KeyOfT, Hash> Self;
		typedef HashNode<T> Node;

		Node* _node;
		HT* _pht;

		__HashTableIterator(Node* node, HT* pht)
			:_node(node)
			,_pht(pht)
		{}

		T& operator*()
		{
			return _node->_data;
		}

		T* operator->()
		{
			return &_node->_data;
		}

		Self operator++()
		{
			if (_node->_next != nullptr)
			{
				_node = _node->_next;
			}
			else
			{
				KeyOfT koft;
				size_t i = _pht->HashFunc(koft(_node->_data)) % _pht->_tables.size();
				++i;
				for (; i < _pht->_tables.size(); ++i)
				{
					Node* cur = _pht->_tables[i];
					if(cur)
					{
						_node = cur;
						return *this;
					}
				}

				_node = nullptr;
			}

			return *this;
		}

		bool operator!=(const Self& s)
		{
			return _node != s._node;
		}
	};


	template<class K>
	struct _Hash
	{
		const K& operator()(const K& key)
		{
			return key;
		}
	};

	//模板的特化关于string
	template<>
	struct _Hash<string>
	{
		size_t& operator()(const string& key)
		{
			size_t hash = 0;
			for (size_t i = 0; i < key.size(); ++i)
			{
				hash += 131;
				hash += key[i];
			}

			return hash;
		}
	};

	//模板参数写法
	//template<class K>
	//struct _HashString
	//{
	//	size_t& operator()(const string& key)
	//	{
	//		size_t hash = 0;
	//		for (size_t i = 0; i < key.size(); ++i)
	//		{
	//			hash += 131;
	//			hash += key[i];
	//		}

	//		return hash;
	//	}
	//};


	template<class K,class T, class KeyOfT, class Hash>
	class HashTable
	{
		typedef HashNode<T> Node;
	public:
		friend struct __HashTableIterator<K, T, KeyOfT, Hash>;

		typedef __HashTableIterator<K, T, KeyOfT, Hash> iterator;

		~HashTable()
		{
			Clear();
		}

		void Clear()
		{
			for (size_t i = 0; i < _tables.size(); ++i)
			{
				Node* cur = _tables[i];
				while (cur)
				{
					Node* next = cur->_next;
					delete cur;
					cur = next;
				}

				_tables[i] = nullptr;
			}

		}

		iterator begin()
		{
			for (size_t i = 0; i < _tables.size(); ++i)
			{
				if (_tables[i])
				{
					return iterator(_tables[i], this);
				}
			}

			return end();
		}

		iterator end()
		{
			return iterator(nullptr, this);
		}

		//返回一个码值
		size_t HashFunc(const K& key)
		{
			return hash(key);
		}

		pair<iterator, bool> Insert(const T& data)
		{
			//负载因子为1时增容
			if (_tables.size() == _num)
			{
				vector<Node*> newtables;
				size_t newsize = _tables.size() == 0 ? 10 : _tables.size() * 2;
				newtables.resize(newsize);
				for (size_t i = 0; i < _tables.size(); ++i)
				{
					Node* cur = _tables[i];
					while (cur)
					{
						Node* next = cur->_next;
						//计算在新表中的位置
						size_t index = hash(koft(cur->_data)) % newtables.size();
						//将新表该位置的数据接到该节点后方
						cur->_next = newtables[index];
						//头插到新表该位置
						newtables[index] = cur;

						//该集合的下一个数据
						cur = next;
					}

					//旧表各节点置空
					_tables[i] = nullptr;
				}

				//新表交换给旧表，自动析构新表
				_tables.swap(newtables);
			}

			size_t index = hash(koft(data)) % _tables.size();

			//查找在不在表中
			Node* cur = _tables[index];
			while (cur)
			{
				if (koft(cur->_data) == koft(data))
				{
					return make_pair(iterator(cur, this),false);
				}
				else
				{
					cur = cur->_next;
				}
			}

			//头插链表
			Node* newnode = new Node(data);
			newnode->_next = _tables[index];
			_tables[index] = newnode;
			++_num;

			return make_pair(iterator(newnode, this), true);

		}


		//查找
		Node* Find(const K& key)
		{
			size_t index = HashFunc(key) % _tables.size();
			Node* cur = _tables[index];
			while (cur)
			{
				if (koft(cur->_data) == HashFunc(key))
				{
					return cur;
				}
				else
				{
					cur = cur->_next;
				}
			}

			return nullptr;
		}


		//删除
		bool Erase(const K& key)
		{
			size_t index = HashFunc(key) % _tables.size();
			Node* prev = nullptr;
			Node* cur = _tables[index];
			while (cur)
			{
				if (koft(cur->_data) == HashFunc(key))
				{
					if (cur = _tables[index])
					{
						_tables[index] = cur->_next;
					}
					else
					{
						prev->_next = cur->_next;
					}
					delete cur;

					return true;
				}
				else
				{
					prev = cur;
					cur = cur->_next;
				}
			}

			return false;
		}
	private:
		vector<Node*> _tables;
		size_t _num = 0;	//存了几个有效数据
		KeyOfT koft;
		Hash hash;
	};
}







//闭散列
namespace CLOSE_HASH
{
	enum State
	{
		EMPTY,	//空
		EXITS,	//出口
		DELETE	//删除
	};


	template<class T>
	struct HashData
	{
		T _data;
		State _state;
	};


	//unordered_set<K>       -> HashTable<K, K>
	//unordered_map<K, V>    -> HashTable<K, pair<K,V>>
	template<class K, class T, class KeyOfT>
	class HashTable
	{
	public:
		//插入
		bool Insert(const T& d)
		{
			//负载因子
			if (_tables.empty() || ((_num * 10) / _tables.size()) >= 7)
			{
				//增容原始写法
				//vector<HashData<T>> newtables;
				//size_t newsize = _tables.size() == 0 ? 10 : _tables.size() * 2;
				//newtables.resize(newsize);
				//for (size_t i = 0; i < _tables.size(); ++i)
				//{
				//	if (_tables[i]._state == EXITS)
				//	{
				//		//重新计算在新表中的映射位置
				//		size_t index = koft(_tables[i]._data) % newtables.size();
				//		//插入到新表中
				//		while (newtables[index]._state == EXITS)
				//		{
				//			++index;
				//			if (index == _tables.size())
				//			{
				//				index = 0;
				//			}
				//		}

				//		newtables[index] = _tables[i];
				//	}
				//}
				////新数据交换到原始vector，自动析构newtables
				//_tables.swap(newtables);


				//新写法
				//创建一个新哈希表
				HashTable<K, T, KeyOfT> newht;

				//新哈希表增容
				size_t newsize = _tables.size() == 0 ? 10 : _tables.size() * 2;
				newht._tables.resize(newsize);

				for (size_t i = 0; i < _tables.size(); ++i)
				{
					if (_tables[i]._state == EXITS)
					{
						//将旧哈希表内容插到新表
						newht.Insert(koft(_tables[i]._data));
					}
				}

				_tables.swap(newht._tables);
			}

			////线性探测
			////计算d中的key在表中映射位置
			//size_t index = koft(d) % _tables.size();
			//while (_tables[index]._state == EXITS)
			//{
			//	if (koft(_tables[index]._data) == koft(d))
			//	{
			//		return false;
			//	}
			//	++index;
			//	if (index == _tables.size())
			//	{
			//		index = 0;
			//	}
			//}

			//_tables[index]._data = d;
			//_tables[index]._state = EXITS;
			//_num++;


			//二次探测
			//计算d中的key在表中映射位置
			size_t start = koft(d) % _tables.size();
			size_t index = start;
			int i = 1;
			while (_tables[index]._state == EXITS)
			{
				if (koft(_tables[index]._data) == koft(d))
				{
					return false;
				}
				index = start + i * i;
				++i;
				index %= _tables.size();
			}

			_tables[index]._data = d;
			_tables[index]._state = EXITS;
			_num++;
		}


		//查找
		HashData<T>* Find(const K& key)
		{
			size_t index = key % _tables.size();
			while (_tables[index]._st - 5ate != EMPTY)
			{
				//找到这个值的位置
				if (koft(_tables[index]._data) == key)
				{
					if (_tables[index]._state == EXITS)
					{
						return &_tables[index];
					}
					//这个值被删除了
					else if (_tables[index]._state == DELETE)
					{
						return nullptr;
					}
				}
				//向后走
				++index;
				if (index == _tables.size())
				{
					index = 0;
				}
			}

			return nullptr;
		}


		bool Erase(const K& key)
		{
			HashData<T>* ret = Find(key);
			if (ret)
			{
				ret->_state = DELETE;
				_num--;
				return true;
			}
			else
			{
				return false;
			}
		}


	private:
		vector<HashData<T>> _tables;
		size_t _num = 0;	//存了几个有效数据
		KeyOfT koft;
	};
}









