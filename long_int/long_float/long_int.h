#include<vector>
#include<iostream>
#include<string>

using namespace std;

class long_int {
	private:
		vector <char> num;//вектор чаров - хранит каждый разряд от меньшего к большему
		bool sign;//знак 1=+, 0=-
		
		friend void convert (long_int&, const string&);//из строки в число

		friend bool operator == (const long_int&, const long_int&);//сравнение
		friend bool operator < (const long_int&, const long_int&);//меньше
		friend bool operator > (const long_int&, const long_int&);//больше
		friend bool operator != (const long_int&, const long_int&);//"не" сравнение
		friend bool operator <= (const long_int&, const long_int&);//меньше или =
		friend bool operator >= (const long_int&, const long_int&);//больше или =

		friend ostream& operator << (ostream&, const long_int&);//вывод
		friend istream& operator >> (istream&, long_int&);//вввод
		
		
		friend long_int operator + (const long_int&, const long_int&);//сложение с длинным

		
		friend long_int operator - (const long_int&, const long_int&);//вычитание длинных

		friend long_int operator * (const long_int&, const int&);//умножение на короткое
		friend long_int operator * (const int&, const long_int&);//умножение на короткое слева
		friend long_int operator * (const long_int&, const long_int&);//умножение длинных

		
		friend long_int operator / (const long_int&, const long_int&);//деление длинных

		
		friend long_int operator % (const long_int&, const long_int&);//умножение длинных - остаток

		friend long_int operator - (const long_int&);//меняет знак числа


	public:
		long_int ();//конструктор по умолчанию = 0, представляется как 0 в векторе
		long_int (const string&);//конструктор из строки
		long_int (const int&);//конструктор из инта

		long_int (const long_int&);//конструктор копирования из такого же числа
		
		long_int& operator = (const long_int&);//присваивание одного числа другому
		long_int& operator = (const int&);//присваивание инта нашему типу
};