#pragma once
#include<vector>
#include<iostream>



using namespace std;



//��ɢ��
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


	//ǰ���������õ������ҵ��������
	template<class K, class T, class KeyOfT, class Hash>
	class HashTable;


	//������
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

	//ģ����ػ�����string
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

	//ģ�����д��
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

		//����һ����ֵ
		size_t HashFunc(const K& key)
		{
			return hash(key);
		}

		pair<iterator, bool> Insert(const T& data)
		{
			//��������Ϊ1ʱ����
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
						//�������±��е�λ��
						size_t index = hash(koft(cur->_data)) % newtables.size();
						//���±��λ�õ����ݽӵ��ýڵ��
						cur->_next = newtables[index];
						//ͷ�嵽�±��λ��
						newtables[index] = cur;

						//�ü��ϵ���һ������
						cur = next;
					}

					//�ɱ���ڵ��ÿ�
					_tables[i] = nullptr;
				}

				//�±������ɱ��Զ������±�
				_tables.swap(newtables);
			}

			size_t index = hash(koft(data)) % _tables.size();

			//�����ڲ��ڱ���
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

			//ͷ������
			Node* newnode = new Node(data);
			newnode->_next = _tables[index];
			_tables[index] = newnode;
			++_num;

			return make_pair(iterator(newnode, this), true);

		}


		//����
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


		//ɾ��
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
		size_t _num = 0;	//���˼�����Ч����
		KeyOfT koft;
		Hash hash;
	};
}







//��ɢ��
namespace CLOSE_HASH
{
	enum State
	{
		EMPTY,	//��
		EXITS,	//����
		DELETE	//ɾ��
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
		//����
		bool Insert(const T& d)
		{
			//��������
			if (_tables.empty() || ((_num * 10) / _tables.size()) >= 7)
			{
				//����ԭʼд��
				//vector<HashData<T>> newtables;
				//size_t newsize = _tables.size() == 0 ? 10 : _tables.size() * 2;
				//newtables.resize(newsize);
				//for (size_t i = 0; i < _tables.size(); ++i)
				//{
				//	if (_tables[i]._state == EXITS)
				//	{
				//		//���¼������±��е�ӳ��λ��
				//		size_t index = koft(_tables[i]._data) % newtables.size();
				//		//���뵽�±���
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
				////�����ݽ�����ԭʼvector���Զ�����newtables
				//_tables.swap(newtables);


				//��д��
				//����һ���¹�ϣ��
				HashTable<K, T, KeyOfT> newht;

				//�¹�ϣ������
				size_t newsize = _tables.size() == 0 ? 10 : _tables.size() * 2;
				newht._tables.resize(newsize);

				for (size_t i = 0; i < _tables.size(); ++i)
				{
					if (_tables[i]._state == EXITS)
					{
						//���ɹ�ϣ�����ݲ嵽�±�
						newht.Insert(koft(_tables[i]._data));
					}
				}

				_tables.swap(newht._tables);
			}

			////����̽��
			////����d�е�key�ڱ���ӳ��λ��
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


			//����̽��
			//����d�е�key�ڱ���ӳ��λ��
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


		//����
		HashData<T>* Find(const K& key)
		{
			size_t index = key % _tables.size();
			while (_tables[index]._st - 5ate != EMPTY)
			{
				//�ҵ����ֵ��λ��
				if (koft(_tables[index]._data) == key)
				{
					if (_tables[index]._state == EXITS)
					{
						return &_tables[index];
					}
					//���ֵ��ɾ����
					else if (_tables[index]._state == DELETE)
					{
						return nullptr;
					}
				}
				//�����
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
		size_t _num = 0;	//���˼�����Ч����
		KeyOfT koft;
	};
}









