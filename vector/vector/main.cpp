#include<iostream>
#include"vector.h"
using namespace std;

int main() {
	myvector::vector<bool> t;
	for(int i = 0; i < 93; ++i) {
		//cout<<':'<<i % 2<<endl;
		t.push_back((i) % 4);
		//bool m = t[i];
		//cout<<t[0]<<endl;
		cout<<t[i]<<endl;
	}
	/*t[0] = 1;
	cout<<t[0];
	cout<<'!'<<endl;
	cout<< t[9088];*/
	myvector::vector<bool> tt;
	tt = t;
	for(int i = 0; i < 93; ++i) {
		//tt[i] = 1;
		cout<<tt[i]<<endl;
	}
	return 0;
}