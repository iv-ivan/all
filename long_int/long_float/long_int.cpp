#include<vector>
#include<iostream>
#include<string>

using namespace std;

const int osn = 1000;
const int osn_log = 3;
int stepen[3]={1,10,100/*,1000,10000,100000,1000000,10000000,100000000*/};
class long_int {
	private:
		vector <int> num;
		bool sign;
		
		//карацуба
		friend void operator *= (int, long_int&);
		friend long_int kar(long_int&,long_int&);
		friend long_int karkar(long_int&,long_int&);
		friend long_int& sdv (int m, long_int& k);
		//
		friend void convert_from_i (long_int&, const int&);
		friend void convert_from_str (long_int&, const string&);

		friend bool operator == (const long_int&, const long_int&);
		friend bool operator < (const long_int&, const long_int&);
		friend bool operator > (const long_int&, const long_int&);
		friend bool operator != (const long_int&, const long_int&);
		friend bool operator <= (const long_int&, const long_int&);
		friend bool operator >= (const long_int&, const long_int&);

		friend ostream& operator << (ostream&, const long_int&);
		friend istream& operator >> (istream&, long_int&);
		
		friend long_int operator + (const long_int&, const long_int&);
		
		friend long_int operator - (const long_int&, const long_int&);

		friend long_int operator * (const long_int&, const int&);
		friend long_int operator * (const int&, const long_int&);
		friend long_int operator * (const long_int&, const long_int&);

		friend long_int operator / (const long_int&, const long_int&);

		friend long_int operator % (const long_int&, const long_int&);

		friend long_int operator - (const long_int&);

	public:
		long_int ();
		long_int (const int&);

		long_int (const long_int&);
		
		long_int& operator = (const long_int&);
};

int ABS_MOD(int x){
	if(x>=0) return x; else return -x;
}

char my_itoa (const char& c) {
	switch (c) {
		case 0 : return '0';
			break;
		case 1 : return '1';
			break;
		case 2 : return '2';
			break;
		case 3 : return '3';
			break;
		case 4 : return '4';
			break;
		case 5 : return '5';
			break;
		case 6 : return '6';
			break;
		case 7 : return '7';
			break;
		case 8 : return '8';
			break;
		case 9 : return '9';
			break;
		default : cout << "ERROR";
			break;
	}
}
char my_atoi (const char& c) {
	switch (c) {
		case '0' : return 0;
			break;
		case '1' : return 1;
			break;
		case '2' : return 2;
			break;
		case '3' : return 3;
			break;
		case '4' : return 4;
			break;
		case '5' : return 5;
			break;
		case '6' : return 6;
			break;
		case '7' : return 7;
			break;
		case '8' : return 8;
			break;
		case '9' : return 9;
			break;
		default : cout << "ERROR";
			return 0;
			break;
	}
}
void itostr(string& str, const int& a) {
	int x=ABS_MOD(a);
	string t="";
	if(a<0) {
		str.push_back('-');
	}
	while(x>0) {
		t.push_back(my_itoa(char(x % 10)));
		x /= 10;
	}
	for(int i = t.length() - 1; i>=0;--i) {
		str.push_back(t[i]);
	}
}
void convert_from_i (long_int& x, const int& a){
	x.sign = (a>=0);
	if ((a < osn) && (a > - osn)) {
		x.num.erase(x.num.begin(), x.num.end());
		x.num.push_back(ABS_MOD(a));
	} else {
		string temp;
		itostr(temp,a);
		convert_from_str (x, temp);
	}
}
void convert_from_str (long_int& x, const string& temp) {
	x.num.erase(x.num.begin(), x.num.end());
	if(temp[0] == '-') {
		x.sign = 0;
		int m = 0;
		int c = 0;
		for (int i =  temp.length () - 1; i >= 1; --i) {
			if (m < osn_log) {
				c = stepen[m] * ((int) my_atoi (temp[i])) + c;
				++m;
			}
			if (m == osn_log) {
				x.num.push_back (c);
				m = 0;
				c = 0;
			}
		}
		if (m > 0) {
			x.num.push_back (c);
		}
	} else {
		x.sign = 1;
		int m = 0;
		int c = 0;
		for (int i = temp.length () - 1; i >=0; --i) {
			if (m < osn_log) {
				c = stepen[m] * ((int) my_atoi (temp[i])) + c;
				++m;
			}
			if (m == osn_log) {
				x.num.push_back (c);
				m = 0;
				c = 0;
			}
		}
		if (m > 0) {
			x.num.push_back (c);
		}
	}
}

bool operator == (const long_int& x, const long_int& y) {
	if ((x.num.size() == y.num.size()) && (x.num.size() == 1) && (x.num[x.num.size() - 1] == 0) && (y.num[y.num.size() - 1] == 0)) {
		return 1;
	}

	if ((x.sign == y.sign) && (x.num == y.num)) {
		return 1;
	} else {
		return 0;
	}
}	
bool operator < (const long_int& x, const long_int& y) {
	if (x == y) {
		return 0;
	}

	if (x.sign > y.sign) {
		return 0;
	}

	if (x.sign < y.sign) {
		return 1;
	}

	if (x.num.size() < y.num.size()) {
		if (x.sign == 1) {
			return 1;
		} else {
			return 0;
		}
	}

	if (x.num.size() > y.num.size()) {
		if (x.sign == 1) {
			return 0;
		} else {
			return 1;
		}
	}

	for (int i = (int) x.num.size() - 1; i >= 0; --i) {
		if (x.num[i] < y.num[i]) {
			if(x.sign == 1) {
				return 1;
			} else {
				return 0;
			}
		}
		if (x.num[i] > y.num[i]) {
			if(x.sign == 0) {
				return 1;
			} else {
				return 0;
			}
		}
	}
	return 0;
}
bool operator > (const long_int& x, const long_int& y) {
	return (y < x);
}
bool operator != (const long_int& x, const long_int& y) {
	return !(x == y);
}
bool operator <= (const long_int& x, const long_int& y) {
	return (x < y) || (x == y);
}
bool operator >= (const long_int& x, const long_int& y) {
	return y <= x;
}

ostream& operator << (ostream& ostr, const long_int& x) {
	if ((x.sign == 0) && !((x.num.size() == 1) && (x.num[x.num.size() - 1] == 0))) {
		ostr << '-';
	}
	if ((x.num.size() == 1) && (x.num[x.num.size() - 1] == 0)) {
		ostr << '0';
		return ostr;
	}
	for (int i = (int) x.num.size () - 1; i >= 0; --i) {
		if (i < (int) x.num.size () - 1) {
			int q = -1;
			int w = x.num[i];
			while (w > 0) {
				++q;
				w = w / 10;
			}
			for (int j = 0; j < osn_log - 1 - q; ++j){
				ostr << '0';
			}
		}
		if (x.num[i] !=  0) {
			ostr << x.num[i];				
		}
	}
	
	return (ostr);
}
istream& operator >> (istream& istr, long_int& x) {
	string temp;
	istr >> temp;
	convert_from_str (x, temp);
	return (istr);
}

long_int::long_int () {
	sign = 1;
	num.erase (num.begin (), num.end ());
}
long_int::long_int (const int& x) {
	convert_from_i (*this,x);
}

long_int::long_int (const long_int& x) {
	sign = x.sign;
	num = x.num;
}

long_int& long_int::operator = (const long_int& x) {
	if (&x == this) {
		return *this;
	} else {
		sign = x.sign;
		num = x.num;
		return *this;
	}
}

long_int operator - (const long_int& x) {
	long_int y (x);
	y.sign = ! (y.sign);
	return y;
}

long_int operator + (const long_int& x, const long_int& y) {
	if (x.sign == 0) {
		if (y.sign == 0) {
			return - ((- x) + (- y));
		} else {
			return - ((- x) - y);
		}
	} else {
		if (y.sign == 0) {
			return x - (- y);
		} else {
			long_int c(x);
			int carry = 0;
			for (size_t i = 0; (i < y.num.size ()) || (i < c.num.size()) || carry; ++i) {
				if (i == c.num.size ()) {
					c.num.push_back(0);
				}
				if (i < y.num.size()){
					c.num[i] += carry + y.num[i];
				} else {
					c.num[i] += carry;
				}
				if (c.num[i] >= osn) {
					c.num[i] -= osn;
					carry = 1;
				} else {
					carry = 0;
				}
			}
			return c;
		}
	}
}

long_int operator - (const long_int& x, const long_int& y) {
	if (x.sign == 0) {
		if (y.sign == 0) {
			return - ((- x) - (- y));
		} else {
			return - ((- x) + y);
		}
	} else {
		if (y.sign == 0) {
			return x + (- y);
		} else {
			if (x >= y) {
				long_int c(x);
				int carry = 0;
				for (size_t i = 0; (i < y.num.size ()) || (i < c.num.size()) || carry; ++i) {
					if (i < y.num.size()){
						c.num[i] -= carry + y.num[i];
					} else {
						c.num[i] -= carry;
					}
					if (c.num[i] < 0) {
						c.num[i] += osn;
						carry = 1;
					} else {
						carry = 0;
					}
				}
				while(c.num.back() == 0 && c.num.size() > 1) {
					c.num.pop_back();
				}
				return c;
			} else {
				return - (y - x);
			}
		}
	}
}

long_int operator * (const int& y, const long_int& a) {
	return a * y;
}
long_int operator * (const long_int& a, const int& y) {
	if ((y < osn) && (y > -osn)) {
		if (y < 0) {
			if (a.sign == 0) {
				return (- a) * (- y);
			} else{
				return - (a * (- y));
			}
		} else {
			if (a.sign == 1) {
				long_int c(a);
				int carry = 0;
				for (size_t i = 0; (i < c.num.size ()) || carry; ++i) {
					//cout<<i<<endl;
					if (i == c.num.size()) {
						c.num.push_back(carry);
						carry = 0;
					} else {
						int a = c.num[i] * y + carry;
						if (a >= osn) {
							carry = (a / osn);
							c.num[i] = (a - osn * carry);
						} else {
							c.num[i] = a;
							carry = 0;
						}
					}
				}
				while(c.num.back() == 0 && c.num.size() > 1) {
					c.num.pop_back();
				}
				return c;
			} else {
				return - ( (- a) * y );
			}
		}
	} else {
		long_int c;
		convert_from_i (c, y);
		return a * c;
	}
}
long_int operator * (const long_int& x, const long_int& y) {
	if (y.sign == 0) {
		if (x.sign == 0) {
			return (- x) * (- y);
		} else{
			return - (x * (- y));
		}
	} else {
		if (x.sign == 1) {
			long_int q;
			for (int i = 0; i < (int) x.num.size() + (int) y.num.size(); ++i) {
				q.num.push_back(0);
			}
			for (int i = 0; i < (int) x.num.size(); ++i) {
				int carry = 0;
				for (int j = 0; (j < (int) y.num.size()) || carry; ++j) {
					if (j < (int) y.num.size()) {
						int a = x.num[i] * y.num[j] + q.num[i+j] + carry;
						if(a >= osn) {
							carry = (a / osn);
							q.num[i+j] = (a - osn * carry);
						} else {
							q.num[i+j] = a;
							carry = 0;
						}
					} else {
						int a = q.num[i+j] + carry;
						if(a >= osn) {
							carry = (a / osn);
							q.num[i+j] = ( a - osn * carry);
						} else {
							q.num[i+j] =  a;
							carry = 0;
						}
					}
				}
			}
			while(q.num.back() == 0 && q.num.size() > 1) {
					q.num.pop_back();
				}
			return q;
		} else {
			return -((- x) * y);
		}
	}
}


long_int operator / (const long_int& x, const long_int& y) {

	if (y == 0) {
		cout << "error";
		return 0;
	}

	if (x == 0) {
		return 0;
	}

	if (x.sign == 0 || y.sign == 0) {
		return 0;
	}
	
	if (x.num.size() < y.num.size()) {
		return 0;
	}

	if (x < y) {
		return 0;
	}

	long_int rez_inv;
	rez_inv.num.erase(rez_inv.num.begin(), rez_inv.num.end());
	int ptr = (int) x.num.size() - (int) y.num.size();
	long_int q;
	q.num.erase(q.num.begin(), q.num.end());
	for (int i = 0; i < (int) y.num.size(); ++i) {
		q.num.push_back(x.num[ptr + i]);
	}
	int p = 0;
	while (q >= 0) {
		q = q - y;
		++ p;
	}
	if (ptr == 0) {
		//cout<<'!';
		return p - 1;
	} else {
		if(p > 1) {
			rez_inv.num.push_back(p - 1);
		}
		q = q + y;
	}
	//cout<<q<<'!';
	while(ptr > 0) {
		--ptr;
		p = 0;
		if(q != 0) {
			q.num.insert(q.num.begin(), x.num[ptr]);
		} else {
			q.sign = 1;
			q.num[0] = x.num[ptr];
		}
		//cout<<'!'<<q<<'!\n';
		while (q >= 0) {
			q = q - y;
			++ p;
		}
		rez_inv.num.push_back(p - 1);
		q = q + y;
	}
	long_int rez;
	rez.num.erase(rez.num.begin(), rez.num.end());
	for(int u = (int) rez_inv.num.size() - 1; u >= 0; --u) {
		rez.num.push_back ( rez_inv.num[u]);
	}
	return rez;
}

long_int operator % (const long_int& x, const long_int& y) {
	return x - y * (x / y);
}

//карацуба
long_int& sdv (int m, long_int& k) {
	if(m==0) {
		return k;
	}
	long_int x(k);
	k.num.erase(k.num.begin(), k.num.end());
	for(int i=0;i<m;++i) {
		k.num.push_back(0);
	}
	for(int i=0;i<(int)x.num.size();++i) {
		k.num.push_back(x.num[i]);
	}
	return k;
}

long_int kar (long_int& x, long_int& y) {
	//cout<<x<<' '<<y<<'!'<<endl;
	if (x.num.size() == 1) {
		long_int c;
		c.num.push_back(x.num[0]*y.num[0]);
		if(c.num[0] >= osn) {
	c.num.push_back(c.num[0] / osn);
			c.num[0] = c.num[0] % osn;
		}
		if(y.sign != x.sign){
			c.sign = 0;
		}else{
			c.sign=1;
		}
		return c;
	} else {
		long_int k1, k2, k3, k4;
		for(int i=0;i < (int)x.num.size() / 2; ++i) {
			k1.num.push_back(x.num[i]);
			k3.num.push_back(y.num[i]);
		}
		for(int i = (int)x.num.size() / 2; i < (int)x.num.size(); ++i) {
			k2.num.push_back(x.num[i]);
			k4.num.push_back(y.num[i]);
		}
		return kar(k1,k3) + sdv(x.num.size() / 2, karkar(k1+k2,k3+k4)-kar(k1,k3)-kar(k2,k4)) + sdv(2*(x.num.size()/2),kar(k2,k4));
	}
}
long_int karkar(long_int& x, long_int& y) {
	if(y.num.size() > x.num.size()) {
		return karkar(y, x);
	} else {
		if(x.num.size() == y.num.size()){
			return kar(x, y);
		} else {
			long_int k;
			long_int c(x);
			//cout<<y.num.size()<<' '<<x.num.size()<<'!'<<endl;
			for(int i = (int)y.num.size(); i < (int)x.num.size(); ++i){
				k.num.push_back(x.num[i]);
				c.num.pop_back();
			}
			//cout<<k<<' '<<c<<endl;
			//cout<<kar(c,y)<<' '<<sdv(y.num.size(),karkar(k,y))<<endl;
			return kar(c, y) + sdv(y.num.size(), karkar(k, y));
		}
	}
}
int main() {
	long_int x;
	long_int y;
	cin >> x >> y;
	/*long_int y = 1;
	for (int i = 1; i <= x; i++) {
		y = i * y;
		
	}*/
	cout<<karkar(y,x);
	return 0;
}