#pragma once
#include"RBtree.h"

namespace yzhzc
{
	template<class K>
	class set
	{
		struct SetKeyOfT
		{
			const K& operator()(const K& k)
			{
				return k;
			}
		};

	public:

		typedef typename RBTree<K, SetKeyOfT>::iterator iterator;

		iterator begin()
		{
			return _t.begin();
		}

		iterator end()
		{
			return _t.end();
		}

		//≤Â»Î
		bool set_Insert(const K& k)
		{
			return _t.Insert(k);
		}
	private:
		RBTree<K, SetKeyOfT> _t;
	};
}














