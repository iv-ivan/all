#include"datetime.h"
using namespace std;

myDateTime::myDateTime () {
	year = 0;
	month = 0;
	day = 0;
	h = 0;
	m = 0;
	s = 0;
}

void set_month_date(myDateTime& a, time_t t, int* arr) {
	long long x = 0;
	int j = 0;
	while(x < t) {
		x += arr[j]*24*3600;
		++j;
	}
	if (x == t) {
		a.month = j + 1;
		a.day = 1;
		a.h = 0;
		a.m = 0;
		a.s = 0;
	} else {
		x = t - x + arr[j-1]*24*3600;
		a.month = j;
		a.day = x / (24*3600) + 1;
		x = x % (24*3600);
		a.h = x / 3600;
		x -= a.h*3600;
		a.m = x / 60;
		x -= a.m*60;
		a.s = x;
	}
}

void convert_from_unix_positive(myDateTime& a, int _year, time_t unix) {
	long long t = 0;
	while (t < unix) {
		if((_year % 400 == 0)||((_year % 4 == 0) && (_year % 100 != 0))) {
			t = t + 31622400;
		} else {
			t = t + 31536000;
		}
		++_year;
	}
	if(t == unix) {
		a.year = _year;
		a.month = 1;
		a.day = 1;
		a.h = 0;
		a.m = 0;
		a.s = 0;
	} else {
		--_year;
		if((_year % 400 == 0)||((_year % 4 == 0) && (_year % 100 != 0))) {
			t = t - 31622400;
			a.year = _year;

			t = unix - t;
			int arr[12] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
			set_month_date(a, t, arr);
		} else {
			t = t - 31536000;
			a.year = _year;

			t = unix - t;
			int arr[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
			set_month_date(a, t, arr);
		}
	}
}

myDateTime::myDateTime (time_t unix) {
	if(unix>=0){
		int _year = 1970;
		convert_from_unix_positive(*this,_year,unix);
	} else {
		int y_year = 1970;
		time_t tt = 0;
		while (tt > unix) {
			--y_year;
			if((y_year % 400 == 0)||((y_year % 4 == 0) && (y_year % 100 != 0))) {
				tt = tt - 31622400;
			} else {
				tt = tt - 31536000;
			}
		}
		unix = unix - tt;
		int _year = y_year;
		convert_from_unix_positive(*this,_year,unix);
	}
}
		
myDateTime::myDateTime (int _year, int _month, int _day, int _h, int _m, int _s):year(_year),month(_month),day(_day),h(_h),m(_m),s(_s){
}

myDateTime::myDateTime (int _year, int _month, int _day): year(_year), month(_month),day(_day),h(0),m(0),s(0){
}

string return_day_p(const myDateTime& a, int* arr, int d) {
	for(int j = 1; j < a.month; ++j) {
				d += arr[j-1];
			}
			d+= a.day;
			d -=31+28+29;
			switch(d % 7) {
			case 0: return "Fri";break;
			case 1: return "Sat";break;
			case 2: return "Sun";break;
			case 3: return "Mon";break;
			case 4: return "Tue";break;
			case 5: return "Wed";break;
			case 6: return "Thu";break;
			}
}
string return_day_n(const myDateTime& a, int* arr, int d) {
	for(int j = 1; j < a.month; ++j) {
				d -= arr[j-1];
			}
			d-= a.day;
			d +=31+28+29;
			switch(d % 7) {
			case 0: return "Fri";break;
			case 1: return "Thu";break;
			case 2: return "Wed";break;
			case 3: return "Tue";break;
			case 4: return "Mon";break;
			case 5: return "Sun";break;
			case 6: return "Sat";break;
			}
}

string myDateTime::week_day() const {
	if(year>=2013 && month >= 3 && day >= 29) {
		int d = 0;
		for(int i = 2013; i < this->year;++i) {
			if((i % 400 == 0)||((i % 4 == 0) && (i % 100 != 0))) {
				d = d + 366;
			} else {
				d = d + 365;
			}	
		}
		if((this->year % 400 == 0)||((this->year % 4 == 0) && (this->year % 100 != 0))) {
			int arr[12] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
			return return_day_p(*this, arr, d);
		} else {
			int arr[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
			return return_day_p(*this, arr, d);
		}
	} else {
		int d = 0;
		for(int i = this->year; i < 2013;++i) {
			if((i % 400 == 0)||((i % 4 == 0) && (i % 100 != 0))) {
				d = d + 366;
			} else {
				d = d + 365;
			}	
		}
		if((this->year % 400 == 0)||((this->year % 4 == 0) && (this->year % 100 != 0))) {
			int arr[12] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
			return return_day_p(*this, arr, d);
		} else {
			int arr[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
			return return_day_p(*this, arr, d);
		}
	}
}

static myDateTime now() {
	time_t timer;
	(time(&timer));
	myDateTime x(timer);
	return x;
}

bool operator > (const myDateTime& a, const myDateTime& b) {
	if(a.year > b.year) {
		return 1;
	}
	if(a.year < b.year) {
		return 0;
	}
	if(a.month > b.month) {
		return 1;
	}
	if(a.month < b.month) {
		return 0;
	}
	if(a.day > b.day) {
		return 1;
	}
	if(a.day < b.day) {
		return 0;
	}
	if(a.h > b.h) {
		return 1;
	}
	if(a.h < b.h) {
		return 0;
	}
	if(a.m > b.m) {
		return 1;
	}
	if(a.m > b.m) {
		return 0;
	}
	if(a.s > b.s) {
		return 1;
	}
	if(a.s < b.s) {
		return 0;
	}
	return 0;
}

bool operator == (const myDateTime& a, const myDateTime& b) {
	return (a.year == b.year && a.month == b.month && a.day ==b.day && a.h == b.h && a.m == b.m && a.s == b.s);
}

bool operator < (const myDateTime& a, const myDateTime& b) {
	return b>a;
}

bool operator <= (const myDateTime& a, const myDateTime& b) {
	return (a<b)||(a==b);
}

bool operator >= (const myDateTime& a, const myDateTime& b) {
	return b<=a;
}
bool operator != (const myDateTime& a, const myDateTime& b) {
	return !(a==b);
}

ostream& operator <<(ostream& ostr, const myDateTime& a) {
	ostr<<a.day<<'.'<<a.month<<'.'<<a.year<<' '<<a.h<<':'<<a.m<<':'<<a.s<<endl;
	return ostr;
}

istream& operator >>(istream& istr, myDateTime& a) {
	int q,w,e,r,t,y;
	istr>>q>>w>>e>>r>>t>>y;
	a.year = e;
	a.month = w;
	a.day = q;
	a.h = r;
	a.m = t;
	a.s = y;
	return istr;
}

myDateTime myDateTime::operator +(const int& a) const {
	time_t x;
	x = (*this).convert_to_unix();
	myDateTime r(x+a);
	return r;
}
myDateTime myDateTime::operator -(const int& a) const {
	time_t x;
	x = (*this).convert_to_unix();
	myDateTime r(x-a);
	return r;
}

int return_n(int n,const myDateTime& a,int* arr) {
	for(int i = 1; i < a.month; ++i) {
				n += arr[i-1]*24*3600;
			}
			n+=(a.day - 1)*24*3600;
			n+=(a.h)*3600;
			n+=(a.m)*60;
			n+=a.s;
			return n;
}
time_t myDateTime::convert_to_unix()const {
	myDateTime x(1970,1,1,0,0,0);
	if((*this) >= x) {
		time_t n = 0;
		for(int j = 1970; j < this->year;++j) {
			if((j % 400 == 0)||((j % 4 == 0) && (j % 100 != 0))) {
				n = n + 31622400;
			} else {
				n = n + 31536000;
			}
		}
		if((this->year % 400 == 0)||((this->year % 4 == 0) && (this->year % 100 != 0))) {
			int arr[12] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
			return return_n(n,*this,arr);
		} else {
			int arr[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
			return return_n(n,*this,arr);
		}
	} else {
		time_t n = 0;
		int k = this->year;
		while(k < 1970) {
			if((k % 400 == 0)||((k % 4 == 0) && (k % 100 != 0))) {
				n = n - 31622400;
			} else {
				n = n - 31536000;
			}
			++k;
		}
		int arr[12] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
		return return_n(n,*this,arr);
	}
}

int main(){ time_t timer = -456532456;
//time(&timer);
myDateTime x(timer);
cout<<x<<' '<<x.week_day();
myDateTime y(2013,3,31,2,8,45);
cout<<y.convert_to_unix()<<endl;
cout<<y.week_day();
cout<<y+3600*24;
//cout<<myDateTime::now();
return 0;}