#ifndef VECTOR
#define VECTOR

#include<cstdlib>
#include<new>
#include<iostream>

namespace myvector {
	template <typename T> class vector {
		private:
			int capacity;//����������� �� ������ ������
			int size;//���������� ���������
			T* array;//��������� �� ��������
			void grow ();//��������� capacity � 2 ����
	
		public:
			T& operator [] (const int&);//����� �������� ��������
			T operator [] (const int&) const;//����� �������� ��������
			vector& operator = (const vector<T>&);//������������
			vector ();//����������� �� ���������
			vector (const vector<T>&);//����������� �����������
			void push_back (const T&);//�������� ������� � �����
			~vector ();//����������
			bool operator ==(const vector<T>&) const;//�������� �� ���������
	};

	//----------------����������--------------------------------
	template <typename T> vector<T>::vector () {
		array = (T*) new char[100 * sizeof (T)];
		capacity = 100;
		size = 0;
	}
	
	template <typename T> vector<T>::vector (const vector<T>& y) {
		array = (T*) new char [y.size * sizeof (T)];
		for (int i = 0; i < y.size; ++i) {
			new (array + i) T (y.array[i]);
		}
		size = y.size;
		capacity = y.capacity;
	}

	template <typename T> void vector<T>::push_back (const T& object) {
		if(size == capacity) {
			grow();
		}

		new (array + size) T (object);
		++size;
	}
		
	template <typename T> void vector<T>::grow () {
		T* array0 = (T*) ::operator new (2 * capacity * sizeof(T));
		for (int i = 0; i < size; ++i) {
			new (array0 + i) T (array[i]);
		}
		delete[] array;
		capacity = 2 * capacity;
		array = array0;
	}
	
	template <typename T> T& vector<T>::operator [](const int& i) {
		return *(array + i);
	}

	template <typename T> T vector<T>::operator [](const int& i) const{
		return *(array + i);
	}

	template <typename T> vector<T>& vector<T>::operator = (const vector<T>& y) {
		T* array0 = (T*) ::operator new (y.capacity * sizeof(T));
		for (int i = 0; i < y.size; ++i) {
			new (array0 + i) T (y.array[i]);
		}
		delete[] array;
		size = y.size;
		capacity = y.capacity;
		array = array0;
		return *this;
	}

	template <typename T> vector<T>::~vector() {
		delete[] array;
	}

	template <typename T> bool vector<T>::operator == (const vector<T>& y) const {
		if(y.size != this->size) {
			return 0;
		}
		for (int i = 0; i < y.size; ++i) {
			if(x[i] != y[i]) {
				return 0;
			}
		}
		return 1;
	}
//-----------------------------------------------------------------------------------------------
	//----------------bool--------------------
	class bool_eq {
		public:
			unsigned char* ptr;
			int in;
	};//��� ������������

	template <> class vector<bool> {
		private:
			int capacity;//����������� �� ������ ������
			int size;//���������� ���������
			unsigned char* array;//��������� �� ��������
			void grow();//��������� capacity � 2 ����
			bool_eq eq;//��� ������������

			friend std::ostream& operator << (std::ostream&, const vector<bool>&);//����� ������ ��������

		public:
			vector<bool>& operator = (const vector<bool>&);//������������
			vector ();//����������� �� ���������
			vector (const vector<bool>&);//����������� �����������
			void push_back(const bool&);//�������� ������� � �����
			bool operator [](const int&) const;//����� �������� ��������
			vector& operator [](const int&);//����� �������� ��������
			void operator = (const bool&);//�������� � ��� �� �����-�� ����� ��������
			bool operator == (const vector<bool>&) const;//����� ��?
			~vector();//����������
	};
	
	std::ostream& operator << (std::ostream& out, const vector<bool>& my) {//����� ������ ��������
		unsigned char ptr =  *my.eq.ptr;
		for(int j = 0; j < 7 - my.eq.in; ++j) {
			ptr >>= 1;
		}
		out << ptr % 2;
		return out;
	}

	vector<bool>& vector<bool>::operator = (const vector<bool>& y) {
		unsigned char* array0 = new unsigned char[(y.capacity - 1) / 8 + 1];
		if (y.size >= 1) {
			for (int i = 0; i <= (y.size - 1) / 8; ++i) {
				new (array0 + i) unsigned char (y.array[i]);
	
			}
		}
		delete[] array;
		size = y.size;
		capacity = y.capacity;
		array = array0;
		return (*this);
	}

	vector<bool>::vector (const vector& y) {
		array = new unsigned char[(y.capacity - 1) / 8 + 1];
		if (y.size >= 1) {
			for (int i = 0; i <= (y.size - 1) / 8; ++i) {
				new (array + i) unsigned char (y.array[i]);
			}
		}
		size = y.size;
		capacity = y.capacity;
	}

	vector<bool>::vector() {
		array = new unsigned char[100];
		for(int i = 0; i< 100; ++i) {
			array[i] = 0;
		}
		capacity = 800;
		size = 0;
	}
		
	void vector<bool>::push_back(const bool& object) {
		if(size == capacity) {
			grow();
		}
		*(array + size / 8) += (((unsigned char) object) % 2) << (7 - size % 8);
		++size;
	}
		
	void vector<bool>::grow() {
		unsigned char* array0 = new unsigned char[(2 * capacity - 1) / 8 + 1];
		for(int i = 0; i <= (capacity - 1) / 8; ++i) {
			array0[i]= array[i];
		}
		for(int i = (capacity - 1) / 8 + 1; i <= (2 * capacity - 1) / 8; ++i) {
			array0[i]= 0;
		}
		delete[] array;
		capacity = 2 * capacity;
		array = array0;
	}
		
	bool vector<bool>::operator [](const int& i) const {
		unsigned char t = *(array + i / 8);
		t >>= (i % 8);
		return (bool) (t % 2);
	}
	
	vector<bool>& vector<bool>::operator [](const int& i) {
		int in = i % 8;
		eq.ptr = (array + i / 8);
		eq.in = in;
		return *(this);
	}
	
	void vector<bool>::operator = (const bool& object) {
		unsigned char *ptr = eq.ptr;
		int y = 1;
		y = y & ((unsigned char) object);
		if (y == 0) {
			for(int j = 0; j < 7 - eq.in; ++j) {
				y <<= 1;
				y += 1;
			}
			for(int j = 0; j < eq.in; ++j) {
				y += (1 << (7 - j));
			}
			*ptr = (*ptr) & (y);
		} else {
			for(int j = 0; j < 7 - eq.in; ++j) {
				y <<= 1;
			}
			*ptr = (*ptr) | (y);
		}
	}
	
	vector<bool>::~vector() {
		delete[] array;
	}

	bool vector<bool>::operator == (const vector<bool>& y) const {
		if(y.size != this->size) {
			return 0;
		}
		for (int i = 0; i < y.size; ++i) {
			bool t = (*this)[i];
			if(t != y[i]) {
				return 0;
			}
		}
		return 1;
	}
}
#endif