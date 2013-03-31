#include"matrix.h"

int main(){
	matrix<float, 3, 3> A;
	for(int i = 0; i < 3; ++i) {
		for(int j = 0; j < 3; ++j) {
			cin>>A[i][j];
			//A[i][j] = i + 3*j;
		}
	}
	matrix<float, 3, 3> B(A);
	//int n;
	//cin>>n;
	cout<<B<<endl;
	cout<<A.invert();
	return 0;
}