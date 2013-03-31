#ifndef _MATRIX
#define _MATRIX

#include<iostream>

using namespace std;

template<typename T, int N, int M> class matrix {
	private:
		T* cells;
		template<typename T0, int N0, int M0>

		friend ostream& operator << (ostream&, const matrix<T0,N0,M0>&);
	public:
		matrix();
		matrix(const matrix&);
		~matrix();
		template<typename T0, int N0, int M0> 
		matrix<T,N,M>& operator = (const matrix<T0,N0,M0>&);
		void change(const int&, const int&);
		T* operator [](const int&) const;
		T det () const;
		T trace () const;
		matrix<T, N, M> invert();
		matrix<T, M, N> transpose();
};

template<typename T, int N, int M> matrix<T,N,M> operator +(const matrix<T,N,M>& A, const matrix<T,N,M>& B) {
	matrix<T,N,M> X;
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j) {
			X[i][j] = A[i][j] + B[i][j];
		}
	}
	return X;
}

template<typename T, int N, int M> matrix<T,N,M> operator -(const matrix<T,N,M>& A, const matrix<T,N,M>& B) {
	matrix<T,N,M> X;
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j) {
			X[i][j] = A[i][j] - B[i][j];
		}
	}
	return X;
}

template<typename T, int N, int M> matrix<T,N,N> operator *(const matrix<T,N,M>& A, const matrix<T,M,N>& B) {
	matrix<T,N,N> X;
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			T qw = 0;
			for (int q = 0; q < M; ++q) {
				qw = qw + A[i][q]*B[q][j];
			}
			X[i][j] = qw;
		}
	}
	return X;
}

template <typename T0, int N0, int M0> ostream& operator <<(ostream& out,const matrix<T0,N0,M0>& A) {
	for (int i = 0; i < N0; ++i) {
		for (int j = 0; j < M0; ++j) {
			out<<A[i][j]<<' ';
		}
		out<<endl;
	}
	return out;
}

template <typename T, int N, int M> matrix<T,N,M>::matrix() {
	cells = new T [N*M];
	for(int i = 0; i < N; ++i) {
		for(int j = 0;j < M; ++j) {
				cells[i*M + j] = 0;
			}
	}
}

template <typename T, int N, int M> matrix<T,N,M>::matrix(const matrix<T,N,M>& A) {
	cells = new T [N*M];
	for(int i = 0; i < N; ++i) {
		for(int j = 0;j < M; ++j) {
			cells[i*M + j] = A[i][j];
		}
	}
}

template <typename T, int N, int M> matrix<T,N,M>::~matrix() {
	delete[] cells;
}

template<typename T, int N, int M> 
template<typename T0, int N0, int M0> 
matrix<T,N,M>& matrix<T,N,M>::operator = (const matrix<T0,N0,M0>& A) {
	if((N != N0)||(M != M0)) {
		cout<<"error";
		return *this;
	} else {
		for(int i = 0; i < N; ++i) {
			for(int j = 0;j < M; ++j) {
				cells[i*M + j] = A[i][j];
			}
		}
		return *this;
	}
}

template<typename T, int N, int M> T* matrix<T,N,M>::operator [](const int& i) const {
	return cells + i*M;
}

template<typename T, int N, int M> void matrix<T,N,M>::change (const int& x, const int& y) {
	for (int j = 0; j < M; ++j) {
		T temp = (*this)[x][j];
		(*this)[x][j] = (*this)[y][j];
		(*this)[y][j] = temp;
	}
}

template<typename T, int N, int M> T matrix<T,N,M>::det () const {
	if(N != M) {
		cout<<"error";
		return 0;
	} else {
		matrix<T,N,M> X(*this);
		T koef = 1;
		for (int j = 0; j < M; ++j) {
			int i = 0;
			do {
				if(i == N) {
					break;
				}
				bool flag = 1;

				if(X[i][j] != 0) {
					if(j > 0){
						for(int q = 0; q < j; ++q) {
							if(X[i][q] != 0) {
								flag = 0;
								break;
							}
						}
					} else { break;}
					if(flag) { 
						break;
					} else { 
						++i;
						continue;
					}
				} else {
					++i;
				}
			} while(1);

			if (i == N) {
				return 0;
			} else {
				for (int q = 0; q < N; ++q) {
					if (X[q][j] == 0 || i == q) {
						continue;
					} else {
						T h = X[q][j] / X[i][j];
						for (int l = 0; l < M; ++l) {
							if (l == j) {
								X[q][j] = 0;
								continue;
							}
							X[q][l] = X[q][l] - X[i][l] * h;
						}
					}
				}
			}
		}
		T deter = 1;
		int schet = 0;
		for (int i = 0; i < N; ++i) {
			for (int j = 0; j < M; ++j) {
				if (X[i][j] != 0) {
					deter *= X[i][j];
					schet += i + j;
				}
			}
		}
		if(schet % 2 == 0) {
			return deter;
		} else {
			return -(deter);
		}
	}
}

template <typename T, int N, int M> matrix<T, M, N> matrix<T,N,M>::transpose() {
	matrix<T,M,N> X;
	for (int i = 0; i < N; ++i) {
		for (int  j = 0; j < M; ++j) {
			X[j][i] = (*this)[i][j];
		}
	}
	return X;
}

template <typename T, int N, int M> matrix<T, N, M> matrix<T,N,M>::invert() {
	if(M != N) {
		cout<<"error";
		return *this;
	} else {
		matrix<T, N, 2*M> X;
		for(int i = 0; i < N; ++i) {
			for(int j = 0; j < M; ++j) {
				X[i][j] = (*this)[i][j];
			}
			for(int j = M; j < 2*M; ++j) {
				X[i][j] = 0;
			}
			X[i][M + i] = 1;
		}

		for (int j = 0; j < M; ++j) {
			int i = 0;
			do {
				if(i == N) {
					break;
				}
				bool flag = 1;

				if(X[i][j] != 0) {
					if(j > 0){
						for(int q = 0; q < j; ++q) {
							if(X[i][q] != 0) {
								flag = 0;
								break;
							}
						}
					} else { break;}
					if(flag) { 
						break;
					} else { 
						++i;
						continue;
					}
				} else {
					++i;
				}
			} while(1);

			if (i == N) {
				cout<<"don't exist"<<endl;
				return (*this);
			} else {
				for (int q = 0; q < N; ++q) {
					if (X[q][j] == 0 || i == q) {
						continue;
					} else {
						T h = X[q][j] / X[i][j];
						for (int l = 0; l < 2*M; ++l) {
							if (l == j) {
								X[q][j] = 0;
								continue;
							}
							X[q][l] = X[q][l] - X[i][l] * h;
						}
					}
				}
			}
		}
		int schet = 0;
		for (int j = 0; j < M; ++j) {
			for (int i = 0; i < N; ++i) {
				if (X[i][j] != 0) {
					X.change(schet, i);
					
					T temp=X[schet][j];
					for(int q = 0; q < 2*M; ++q) {
						X[schet][q] /= temp;
					}
					++schet;
				}
			}
		}
		matrix<T,N,M> L;
		for(int i = 0; i < N; ++i) {
			for(int j = M; j < 2*M; ++j) {
				L[i][j - M] = X[i][j];
			}
		}
		return L;
	}
}

template<typename T, int N, int M>
T matrix<T,N,M>::trace () const {
	if (N != M) {
		cout<<"error";
		return 0;
	} else {
		T tr = 0;
		for (int i = 0; i < N; ++i) {
			tr += (*this)[i][i];
		}
		return tr;
	}
}
#endif