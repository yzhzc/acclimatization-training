#pragma once
#include"bitset.h"
#include<string>
namespace yzhzc
{
	struct HashStrl
	{
		size_t operator()(const std::string& str)
		{
			size_t hash = 0;
			for (size_t i = 0; i < str.size(); ++i)
			{
				hash *= 131;
				hash += str[i];
			}

			return hash;
			}
	};

	struct HashStr2
	{
		size_t operator()(const std::string& str)
		{
			size_t hash = 0;
			size_t magic = 63689;
			for (size_t i = 0; i < str.size(); ++i)
			{
				hash *= magic;
				hash += str[i];
				magic *= 378551;
			}

			return hash;
		}
	};

	struct HashStr3
	{
		size_t operator()(const std::string& str)
		{
			size_t hash = 5381;
			for (size_t i = 0; i < str.size(); ++i)
			{
				hash *= 131;
				hash += str[i];
				                                                
			}

			return hash;
		}
	};

	template
		<
		class K = std::string,
		class Hash1 = HashStrl,
		class Hash2 = HashStr2,
		class Hash3 = HashStr3
		>
	class bloomfilter
	{
	public:

		bloomfilter(size_t num)
			:_bs(num * 5)
			,_N(num * 5)
		{}

		void set(const K& key)
		{
			size_t index1 = Hash1()(key) % _N;
			size_t index2 = Hash2()(key) % _N;
			size_t index3 = Hash3()(key) % _N;

			_bs.set(index1);
			_bs.set(index2);
			_bs.set(index3);
		}

		bool test(const K& key)
		{
			size_t index1 = Hash1()(key) % _N;
			if (_bs.test(index1) == false)
				return false;

			size_t index2 = Hash2()(key) % _N;
			if (_bs.test(index2) == false)
				return false;

			size_t index3 = Hash3()(key) % _N;
			if (_bs.test(index3) == false)
				return false;

			return true;
		}
	private:
		bitset _bs;
		size_t _N;
	};

	void test_bloomfilter()
	{
		bloomfilter<std::string> bf(300);
		bf.set("abcd");
		bf.set("aadd");
		bf.set("bcad");

		cout << bf.test("abcd") << endl;
		cout << bf.test("aadd") << endl;
		cout << bf.test("abcd") << endl;
		cout << bf.test("cbad") << endl;
	}
}

