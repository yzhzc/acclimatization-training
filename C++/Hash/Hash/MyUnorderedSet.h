#pragma once
#include"HashTable.h"

using namespace OPEN_HASH;

namespace yzhzc
{
	template<class K, class Hash = _Hash<K>>
	class unordered_set
	{
		struct SapKOfT
		{
			const K& operator()(const K& key)
			{
				return key;
			}
		};

	public:

		typedef typename __HashTableIterator<K, K, SapKOfT, Hash> iterator;

		pair<iterator, bool> Insert(const K& k)
		{
			return _ht.Insert(k);
		}

		iterator begin()
		{
			return _ht.begin();
		}

		iterator end()
		{
			return _ht.end();
		}


	private:
		HashTable <K, K, SapKOfT, Hash> _ht;
	};


	void TestHashTable_set()
	{
		unordered_set<int> ht;
		ht.Insert(4);
		ht.Insert(14);
		ht.Insert(24);
		ht.Insert(5);
		ht.Insert(15);
		ht.Insert(25);
		ht.Insert(6);
		ht.Insert(16);
		ht.Insert(26);
		ht.Insert(36);
		ht.Insert(1);
		ht.Insert(2);
		ht.Insert(3);
		ht.Insert(9);
		ht.Insert(7);

		unordered_set<int>::iterator it = ht.begin();

		while (it != ht.end())
		{
			cout << *it << " ";
			++it;
		}
		cout << endl;
	}
}