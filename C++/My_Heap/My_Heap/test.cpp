#include"priority_queue.h"
#include<iostream>

using namespace yzhzc;

int main()
{
	priority_queue<int> pq;
	
	pq.push(1);
	pq.push(8);
	pq.push(4);
	pq.push(9);
	pq.push(6);
	pq.push(7);

	while (!pq.empty())
	{
		std::cout << pq.top();
		pq.pop();
	}
	

	return 0;
}