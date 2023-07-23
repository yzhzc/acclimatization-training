#include"date.h"


int main()
{
	Date d1(2021, 2, 1);
	d1.Print();

	Date d2(2023, 7, 23);
	d2.Print();

	Date d3 = d1 + -20;
	d3.Print();
	d1.Print();

	cout << d2 - d1 << endl;
	return 0;
}


