#ifndef _myDateTime_
#define _myDateTime_
#include<string>
#include<iostream>
#include<time.h>
using namespace std;
class myDateTime {
	private:
		int year;
		int month;
		int day;
		int h;
		int m;
		int s;

		friend string return_day_n(const myDateTime&, int*, int);
		friend string return_day_p(const myDateTime&, int*, int);
		friend int return_n(int,const myDateTime&,int*);

		friend bool operator > (const myDateTime&, const myDateTime&);
		friend bool operator == (const myDateTime&, const myDateTime&);
		friend bool operator < (const myDateTime&, const myDateTime&);
		friend bool operator <= (const myDateTime&, const myDateTime&);
		friend bool operator >= (const myDateTime&, const myDateTime&);
		friend bool operator != (const myDateTime&, const myDateTime&);

		friend ostream& operator <<(ostream&, const myDateTime&);
		friend istream& operator >>(istream&, myDateTime&);

		friend void set_month_date(myDateTime&, time_t, int*);
		friend void convert_from_unix_positive(myDateTime&, int, time_t);
	public:
		myDateTime ();
		myDateTime (time_t unix);
		myDateTime (int _year, int _month, int _day, int _h, int _m, int _s);
		myDateTime (int _year, int _month, int _day);

		myDateTime operator +(const int&) const;
		myDateTime operator -(const int&) const;
		time_t convert_to_unix() const;

		string week_day() const;
		static myDateTime now();
};
#endif