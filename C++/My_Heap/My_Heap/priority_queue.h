#pragma once
#include<functional>
#include<vector>
#include<queue>


namespace yzhzc
{
	template<class T, class Container = std::vector<T>, class Comapre = std::less<T>>
	class priority_queue
	{
	public:
		void push(const T& x)
		{
			_con.push_back(x);
			AdjustUp(_con.size() - 1);
		}

		void pop()
		{
			std::swap(_con[0], _con[_con.size() - 1]);
			_con.pop_back();
			AdjustDown(0);
		}

		T& top()
		{
			return _con.front();
		}

		size_t size()
		{
			return _con.size();
		}

		bool empty()
		{
			return _con.empty();
		}

		void AdjustUp(int child)
		{
			Comapre com;
			int parent = (child - 1) / 2;
			while (parent >= 0)
			{
				if (com(_con[parent], _con[child]))
				{
					std::swap(_con[child], _con[parent]);
					child = parent;
					parent = (child - 1) / 2;
				}
				else
				{
					break;
				}
			}
		}

		void AdjustDown(int parent)
		{
			Comapre com;
			int child = parent * 2 + 1;
			while (child<_con.size())
			{
				if (child + 1 < _con.size() && com(_con[child], _con[child + 1]))
				{
					child++;
				}
				if (com(_con[parent], _con[child]))
				{
					std::swap(_con[child], _con[parent]);
					parent = child;
					child = parent * 2 + 1;
				}
				else
				{
					break;
				}
			}
		}
	private:
		Container _con;
	};
}