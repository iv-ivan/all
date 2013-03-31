#include"long_float.h"
#include<cstdlib>
using namespace std;

ostream& operator << (ostream& ostr, const long_float& x) {
	if (x.sign == 0) {
		ostr << '-';
	}

	for (size_t i = 0; i < x.num.size (); ++i) {
		ostr << (int) x.num[i];
		if ((i == 0) && (i != x.num.size () - 1)) {
			ostr << '.';
		}					
	}

	ostr << 'E' << x.man;
	
	return (ostr);
}

char my_atoi (char& c) {
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
			break;
	}
}

/*char my_itoa (char& c) {
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
}*/

void convert (long_float& x, string temp) {
	int q = 0;
	bool flag = true;
	size_t i = 0;
	x.num.erase (x.num.begin(), x.num.end());
	if (temp[i] == '-') {
		x.sign = 0;
		++i;
	} else {
		x.sign = 1;
	}

	if (temp[i] == '0') {
		i += 2;
		if (i >= temp.size ()) {
			x.num.push_back (0);
			x.man = 0;
			return;
		}
		while (temp[i] == '0') {
			--q;
			++i;
		}
		while (i < temp.size ()) {
				x.num.push_back (my_atoi (temp[i]));
				++i;
		}
		x.man = q-1;
	} else {
		for(;i < temp.size (); ++i) {
			if (temp[i] != '.') {
				x.num.push_back (my_atoi(temp[i]));
				++q;
			} else {
				x.man = q-1;
				flag = false;
			}
		}
		if (flag) {
			x.man = q-1;
		}
	}
}

istream& operator >> (istream& istr, long_float& x) {
	x.num.erase (x.num.begin (), x.num.end ());

	string temp;
	istr >> temp;
	convert (x, temp);
	
	return (istr);
}

long_float::long_float () {
	man = 0;
	sign = true;
	num.push_back (0);
}

long_float::long_float (string s) {
	convert (*this, s);
}

long_float::long_float (const long_float& x) {
	man = x.man;
	sign = x.sign;
	num = x.num;
}

long_float& long_float::operator = (const long_float& x) {
	if (&x == this) {
		return *this;
	} else {
		man = x.man;
		sign = x.sign;
		num = x.num;
		return *this;
	}
}

long_float& short_to_long (float m) {
		char buffer[1000];
		sprintf(buffer, "%f", m);
		string temp = buffer;
		long_float* x = new long_float;
		convert (*x, temp);
		return *x;
}

long_float long_float::operator + (long_float y) {

}

int main(){
	long_float x;
	long_float y = "0.000134";
	long_float z(y); 
	cin >> x;
	float xx = 934.0042;
	//cout<<"float:"<<xx<<endl;
	long_float k = short_to_long (xx);
	cout << x << endl << y << endl << z << endl << k;
	return 0;
}