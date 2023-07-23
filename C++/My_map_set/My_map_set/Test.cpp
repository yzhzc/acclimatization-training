#include"MyMap.h"
#include"MySet.h"

using namespace yzhzc;

int main()
{
	map<int, int> m;
	m.Insert(make_pair(1, 1));
	m.Insert(make_pair(2, 2));
	m.Insert(make_pair(3, 3));
	map<int,int>::iterator itm = m.begin();
	while (itm != m.end())
	{
		cout << itm->first << endl;
		++itm;
	}
	set<int> s;
	s.set_Insert(1);
	s.set_Insert(2);
	s.set_Insert(3);
	set<int>::iterator its = s.begin();
	while (its != s.end())
	{
		cout << *its << endl;
		++its;
	}

	return 0;
}