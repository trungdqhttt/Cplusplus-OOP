#pragma once
#include<iostream>
#include<fstream>
#include<iomanip>
using namespace std;



class CDate
{
private:
	int day;
	int month;
	int year;
	static const int MonthsInYear[13];
	static const int DaysInMonth[13];
	bool isLeapYear(int year) { // Check leap year
		return (year % 100) ? (year % 4 == 0) : (year % 400 == 0);
	}
public:
	CDate() {
		day = month = year = 0;
	}
	void setDate(int d, int m, int y) {
		day = d;
		month = m;
		year = y;
	}
	void setDay(int d) {
		day = d;
	}
	void setMonth(int m) {
		month = m;
	}
	void setYear(int y) {
		year = y;
	}
	friend ostream& operator << (ostream&, const CDate);
	friend istream& operator >> (istream&, CDate&);
	int countLeapYears();
	int operator -(CDate); // TimeSpan
	CDate operator + (int); // Cộng với một giá trị ngày bất kỳ
	CDate operator - (int); // Trừ cho một giá trị ngày bất kỳ
	CDate operator ++ (); 
	CDate operator ++ (int);  
	CDate operator -- ();
	CDate operator -- (int);
	~CDate() {};
};

void Menu(CDate, CDate);



