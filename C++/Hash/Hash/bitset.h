#pragma once
#include<vector>

namespace yzhzc
{
	class bitset
	{
	public:
		bitset(size_t N)
		{
			_bits.resize(N / 32 + 1, 0);
			_num = 0;
		}

		void set(size_t x)
		{
			size_t index = x / 32;		//ӳ���ĸ�����
			size_t pos = x % 32;		//ӳ�������ڵ�λ��

			_bits[index] |= (1 << pos);		//����1��1��ȫ0Ϊ0
			_num++;
		}

		void reset(size_t x)
		{
			size_t index = x / 32;		//ӳ���ĸ�����
			size_t pos = x % 32;		//ӳ�������ڵ�λ��

			_bits[index] &= ~(1 << pos);		//����0��0��ȫ1Ϊ1
			_num--;
		}

		bool test(size_t x)
		{
			size_t index = x / 32;		//ӳ���ĸ�����
			size_t pos = x % 32;

			return _bits[index] & (1 << pos);
		}
	private:
		std::vector<int>_bits;
		size_t _num;
	};

	void test_bitset()
	{
		bitset bs(20);
		bs.set(1);
		bs.set(10);
		bs.set(11);

		for (size_t i = 0; i < 20; ++i)
		{
			cout << i << " " << bs.test(i);
			cout << endl;
		}
	}

}