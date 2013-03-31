#include"abonent.h"
ostream& operator << (ostream& ostr, const call& a) {
	ostr<<"to "<<a.n<<" at "<<a.date<<"Duration "<<a.duration<<endl;
	return ostr;
}

call::call():n(0),date(),duration() {
}
call::call(int q,const myDateTime& w,int e):n(q),date(w),duration(e)  {
}
call::call(const call& a):n(a.n),date(a.date),duration(a.duration){
}

void call::operator =(const call& a) {
	n=a.n;
	date=a.date;
	duration = a.duration;
}
myDateTime call::get_date() {
	return date;
}

int call::get_n() {
	return n;
}

int call::get_duration() {
	return duration;
}
//------------------------------------
ostream& operator << (ostream& ostr, const call_obj& a) {
	const call* p = &a;
	ostr<<*p;
	return ostr;
}
call_obj::call_obj():call() {
	to_first=NULL;
	to_last=NULL;
}
call_obj::call_obj(const call& a):call(a) {
	to_first=NULL;
	to_last=NULL;
}

void call_obj::set_to_first(call_obj* a) {
	to_first = a;
}
void call_obj::set_to_last(call_obj* a) {
	to_last = a;
}
call_obj* call_obj::get_to_last() {
	return to_last;
}
call_obj* call_obj::get_to_first() {
	return to_first;
}
//--------------------------
call_list::call_list() {
	first = NULL;
	last = NULL;
}

call_list::call_list(const call_list& a) {
	call_list::iterator i = a.begin();
	while(!(i == a.end())) {
		add(*i);
		++i;
	}
}

void call_list::operator = (const call_list& a) {
	if(first != NULL) {
		call_list::iterator j = begin();
		while(!(j == end())) {
			call_list::iterator i(j);
			++j;
			delete (i.Elem);
		}
	}
	call_list::iterator i = a.begin();
	while(!(i ==a.end())) {
		add(*i);
		++i;
	}
}

call_list::~call_list() {
	call_list::iterator j = begin();
	while(!(j == end())) {
		call_list::iterator i(j);
		++j;
		delete (i.Elem);
	}
}

void call_list::add(const call& a) {
	call_obj* p = new call_obj;
	*p=a;
	if(first == NULL) {
		first = p;
		last = p;
	} else {
		(*last).set_to_last(p);
		(*p).set_to_first(last);
		(*p).set_to_last(NULL);
		last = p;
	}
}

call_list::iterator call_list::begin() const {
	return iterator(first);
}
call_list::iterator call_list::end() const {
	return iterator(last);
}

//private:*call_obj Elem;
call_list::iterator::iterator() {
	Elem = NULL;
}

call_list::iterator::iterator(call_obj* a){
	Elem = a;
}
		
call_list::iterator& call_list::iterator::operator ++() {
	this->Elem = (this->Elem)->get_to_last();
	return *this;
}

call_list::iterator& call_list::iterator::operator --() {
	this->Elem = (this->Elem)->get_to_first();
	return *this;
}

call call_list::iterator::operator *() {
	call* p = this->Elem;
	return *p;
}

bool call_list::iterator::operator ==(const call_list::iterator& a) {
	if(this->Elem != a.Elem) {
		return 0;
	} else {
		return 1;
	}
}
//----------------
Abonent::Abonent(): history(){
	n = 0;
	balance = 0;
}
Abonent::Abonent(int i): history(){
	n = i;
	balance = 0;
}

Abonent::Abonent(const Abonent& a) {
	n=a.n;
	balance = a.balance;
	history = a.history;
}

Abonent& Abonent::operator = (const Abonent& a) {
	n=a.n;
	balance = a.balance;
	history = a.history;
	return *this;
}


int Abonent::get_n() {
	return n;
}

int Abonent::get_balance() {
	return balance;
}
void Abonent::set_balance(int i){
	balance = i;
}

int main(){
	Abonent(a);
	call x(1,2,3);
	call y(23,65,2);
	a.history.add(x);
	a.history.add(y);
	cout<<*(a.history.begin())<<' '<<*(a.history.end())<<' '<<*(++a.history.begin())<<' '<<*(--a.history.end());
	return 0;
}