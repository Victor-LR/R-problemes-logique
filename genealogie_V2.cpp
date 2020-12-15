#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <list>
using namespace std;

template<class Tuple>
ostream& operator <<(ostream &out,list<Tuple> &c) {
	for(auto e : c) {
		out << "\t" << e << endl;
	}
	out << endl;
	return out;
}

class Object {
public:
	string value;

	Object() {
	}

	Object(string v): value(v) {
	}

	virtual ~Object() {
	}

	virtual int compare(const Object & obj) = 0;

	friend bool operator==(const Object& obj1, const Object& obj2) {
		return const_cast<Object &>(obj1).compare(obj2) == 0;
	}

	friend bool operator!=(const Object& obj1, const Object& obj2) {
		return const_cast<Object &>(obj1).compare(obj2) != 0;
	}

};

class Variable : public Object {
public:
	Variable(string name) : Object(name){ }

	int compare(const Object & obj) {
		return 0;
	}

};

class Value : public Object {
public:
	Value(string identifier) : Object(identifier){}

	int compare(const Object & obj) {
		Value * val = dynamic_cast<Value *>(&const_cast<Object &>(obj));
		if(val == nullptr) {
			return 0;
		} else {
			if (value == val->value) return 0;
			return 1;
		}
		return 0;
	}

};

class Tuple2 {
public:
	Object *object[2];

	Tuple2(Object *a, Object *b) {
		 object[0] = a;
		 object[1] = b;
	}

	Object& x1() {
		return *object[0];
	}
	Object& x2() {
		return *object[1];
	}
	Object *operator[](int n) {
 		return object[n];
	}
	friend ostream& operator <<(ostream &out, Tuple2 &obj) {
 		out << "(" << obj[0] -> value << "," <<obj[1] -> value << ")";
		return out;}

};

list<Tuple2> pere;
list<Tuple2> frere;

list<Tuple2> grand_pere;
list<Tuple2> oncle;

void grand_pere_deduce1(){
	for(auto t1 : pere){
		for(auto t2 : pere){
				if(t1.x2() != t2.x1()) continue;
					grand_pere.push_back(Tuple2(t1[0],t2[1]));
		}
	}
}
void oncle_deduce1(){
	for(auto t1 : frere){
		for(auto t2 : pere){
				if(t1.x2() != t2.x1()) continue;
					oncle.push_back(Tuple2(t1[0],t2[1]));
		}
	}
}
void deduction(){
	pere.push_back(Tuple2(new Value("roger"),new Value("michel")));
	pere.push_back(Tuple2(new Value("michel"),new Value("jean")));
	pere.push_back(Tuple2(new Value("michel"),new Value("mathieu")));
	pere.push_back(Tuple2(new Value("jean"),new Value("sarah")));
	pere.push_back(Tuple2(new Value("jean"),new Value("xavier")));
	frere.push_back(Tuple2(new Value("roger"),new Value("stephane")));
	frere.push_back(Tuple2(new Value("jean"),new Value("mathieu")));
	cout << "Listes des prédicats : "<< endl;
	cout <<"pere =\n" << pere << endl;
	cout <<"frere =\n" << frere << endl;

	cout << "Déductions pour toutes les règles :"<< endl;
	grand_pere_deduce1();
	cout <<"grand_pere =\n" << grand_pere << endl;
	oncle_deduce1();
	cout <<"oncle =\n" << oncle << endl;
}

int main(int argc, char **argv){
	deduction();
};

