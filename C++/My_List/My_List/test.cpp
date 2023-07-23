#include<iostream>
#include<cassert>
#include"list.h"


using namespace My_List;


typedef struct Date
{
	int _year = 0;
	int _month = 1;
	int _day = 0;
}Date;


void print_list(const list<int>& l1)
{
	list<int>::const_iterator it = l1.begin();
	while (it != l1.end())
	{
		std::cout << *it<<std::endl;
		++it;

	}
}

int main()
{
	//list<Date> l1;
	//l1.push_back(Date());
	//l1.push_back(Date());
	//l1.push_back(Date());



	//list<Date>::iterator it = l1.begin();
	//l1.erase(it);
	//it = l1.begin();
	//while (it != l1.end())
	//{
	//	std::cout << it->_year;
	//	//"it->" = _node->date的地址
	//	//"_node->date的地址"->_year
	//	//it->->_year,编译器优化减少了一个->
	//	
	//	it++;
	//}

	list<int> l1;
	l1.push_back(1);
	l1.push_back(2);
	l1.push_back(3);
	l1.push_back(4);
	l1.push_back(5);


	list<int>::iterator it = l1.begin();
	it++;
	l1.insert(it, 9);
	it++;
	it++;
	l1.erase(it);
	l1.pop_back();

	print_list(l1);
	list<int> l2(l1);
	print_list(l2);

	list<int> l3;
	l3 = l1;
	l3.push_back(8);
	print_list(l3);



	return 0;
}