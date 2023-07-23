#pragma once
#include"HashTable.h"

using namespace OPEN_HASH;

namespace yzhzc
{
	template<class K,class V, class Hash = _Hash<K>>
	class unordered_map
	{
		struct MapKOfT
		{
			const K& operator()(const pair<K, V>& kv)
			{
				return kv.first;
			}
		};

	public:

		typedef __HashTableIterator<K, pair<K, V>, MapKOfT, Hash> iterator;

		pair<iterator, bool> Insert(const pair<K, V>& kv)
		{
			return _ht.Insert(kv);
		}

		iterator begin()
		{
			return _ht.begin();
		}

		iterator end()
		{
			return _ht.end();
		}

		V& operator[](const K& key)
		{
			pair<iterator, bool> ret = _ht.Insert(make_pair(key, V()));
			return ret.first->second;
		}

	private:
		HashTable <K, pair<K, V>, MapKOfT, Hash> _ht;
	};

	void TestHashTable_map()
	{
		unordered_map<string, string> ht;
		ht.Insert(make_pair("sort", "ÅÅÐò"));
		ht.Insert(make_pair("left", "×ó"));
		ht.Insert(make_pair("right", "ÓÒ"));
		ht["left"] = "zuo";
		ht["1111"];

		unordered_map<string, string>::iterator it = ht.begin();


		while (it != ht.end())
		{
			cout << it->first << " " << it->second;
			cout << endl;

			++it;
		}
		cout << endl;
	}





}