#ifndef _ABONENT
#define _ABONENT
#include"datetime.h"
#include<iostream>
using namespace std;
class call {
private:
	unsigned int n;
	myDateTime date;
	unsigned int duration;

	friend ostream& operator << (ostream&, const call&);
public:
	call();
	call(int,const myDateTime&,int);

	call(const call&);

	void operator =(const call&);
	myDateTime get_date();
	int get_n();
	int get_duration();
};

class call_obj: public call {
private:
	call_obj* to_first;
	call_obj* to_last;
	friend ostream& operator << (ostream&, const call_obj&);
public:
	call_obj();
	call_obj(const call&);

	void set_to_first(call_obj*);
	void set_to_last(call_obj*);
	call_obj* get_to_first();
	call_obj* get_to_last();
};

class call_list {
private:
	call_obj* first;
	call_obj* last;
public:
	call_list();
	call_list(const call_list&);

	void operator = (const call_list&);

	~call_list();

	void add(const call&);

	class iterator {
	private:
		call_obj* Elem;
	public:
		friend class call_list;
		iterator();
		iterator(call_obj*);
		
		iterator& operator ++();
		iterator& operator --();
		call operator *();
		bool operator ==(const iterator&);
	};

	iterator begin() const;
	iterator end() const;
};

class Abonent {
	int n;
	int balance;
public:
	call_list history;

	Abonent();
	Abonent(int);
	Abonent(const Abonent&);
	Abonent& operator =(const Abonent&);
	
	int get_n();
	int get_balance();
	void set_balance(int);
};
#endif