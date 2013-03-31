#include<vector>
#include<iostream>
#include<string>

using namespace std;

class long_int {
	private:
		vector <char> num;//������ ����� - ������ ������ ������ �� �������� � ��������
		bool sign;//���� 1=+, 0=-
		
		friend void convert (long_int&, const string&);//�� ������ � �����

		friend bool operator == (const long_int&, const long_int&);//���������
		friend bool operator < (const long_int&, const long_int&);//������
		friend bool operator > (const long_int&, const long_int&);//������
		friend bool operator != (const long_int&, const long_int&);//"��" ���������
		friend bool operator <= (const long_int&, const long_int&);//������ ��� =
		friend bool operator >= (const long_int&, const long_int&);//������ ��� =

		friend ostream& operator << (ostream&, const long_int&);//�����
		friend istream& operator >> (istream&, long_int&);//�����
		
		
		friend long_int operator + (const long_int&, const long_int&);//�������� � �������

		
		friend long_int operator - (const long_int&, const long_int&);//��������� �������

		friend long_int operator * (const long_int&, const int&);//��������� �� ��������
		friend long_int operator * (const int&, const long_int&);//��������� �� �������� �����
		friend long_int operator * (const long_int&, const long_int&);//��������� �������

		
		friend long_int operator / (const long_int&, const long_int&);//������� �������

		
		friend long_int operator % (const long_int&, const long_int&);//��������� ������� - �������

		friend long_int operator - (const long_int&);//������ ���� �����


	public:
		long_int ();//����������� �� ��������� = 0, �������������� ��� 0 � �������
		long_int (const string&);//����������� �� ������
		long_int (const int&);//����������� �� ����

		long_int (const long_int&);//����������� ����������� �� ������ �� �����
		
		long_int& operator = (const long_int&);//������������ ������ ����� �������
		long_int& operator = (const int&);//������������ ���� ������ ����
};