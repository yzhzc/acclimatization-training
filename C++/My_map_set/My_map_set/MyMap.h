#pragma once
#include"RBtree.h"

namespace yzhzc
{
	template<class K, class V>
	class map
	{
		struct MapKeyOfT
		{
			const K& operator()(const pair<K,V>& kv) 
			{
				return kv.first;
			}
		};

	public:

		typedef typename RBTree<pair<K, V>, MapKeyOfT>::iterator iterator;

		iterator begin()
		{
			return _t.begin();
		}

		iterator end()
		{
			return _t.end();
		}

		//≤Â»Î
		bool Insert(const pair<K, V>& kv)
		{
			return _t.Insert(kv);
		}
	private:
		RBTree<pair<K, V>, MapKeyOfT> _t;
	};




}











