#pragma once
#include<iostream>
using namespace std;




class Date
{
public:
	//获取每个月对应的天数
	int GetMonthDay(int year, int month) const;
	//初始化
	Date(int year = 0, int month = 1, int day = 1);
	//拷贝构造
	Date(const Date& d);

	bool operator<(const Date& d) const;

	bool operator==(const Date& d) const;

	Date& operator=(const Date& d);

	//复用
	bool operator<=(const Date& d);

	bool operator>(const Date& d);

	bool operator>=(const Date& d);

	bool operator!=(const Date& d);

	Date operator+(int day) const;

	Date& operator+=(int day);

	Date operator-(int day) const;

	Date& operator-=(int day);
	//前置++
	Date& operator++();
	//后置++
	Date operator++(int);
	//前置--
	Date& operator--();
	//后置--
	Date operator--(int);

	int operator-(const Date& d) const;

	void Print();

private:
	int _year;
	int _month;
	int _day;
};