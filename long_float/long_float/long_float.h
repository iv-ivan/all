#include<vector>
#include<iostream>
#include<string>

using namespace std;

class long_float {
	private:
		vector <char> num;
		int man;
		bool sign;
	public:
		friend ostream& operator << (ostream&, const long_float&);
		friend istream& operator >> (istream&, long_float&);
		friend void convert (long_float&, string);
		long_float ();
		long_float (string);
		long_float (const long_float&);
		long_float (const float&);
		//long_float operator + (long_float);
		/*long_float operator - (long_float);
		long_float operator * (long_float);
		long_float operator / (long_float);*/
		long_float& operator = (const long_float&);
		long_float& operator = (const float&);
};