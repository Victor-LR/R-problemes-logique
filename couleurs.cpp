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

class Tuple4 {
public:
	Object *object[4];

	Tuple4(Object *a, Object *b, Object *c, Object *d) {
		 object[0] = a;
		 object[1] = b;
		 object[2] = c;
		 object[3] = d;
	}

	Object& x1() {
		return *object[0];
	}
	Object& x2() {
		return *object[1];
	}
	Object& x3() {
		return *object[2];
	}
	Object& x4() {
		return *object[3];
	}
	Object *operator[](int n) {
 		return object[n];
	}
	friend ostream& operator <<(ostream &out, Tuple4 &obj) {
 		out << "(" << obj[0] -> value << "," <<obj[1] -> value << "," <<obj[2] -> value << "," <<obj[3] -> value << ")";
		return out;}

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

list<Tuple2> voisins;

list<Tuple4> coloriage;

void coloriage_deduce1(){
	for(auto t1 : voisins){
		for(auto t2 : voisins){
			for(auto t3 : voisins){
				for(auto t4 : voisins){
					for(auto t5 : voisins){
							if(t1.x1() != t2.x1()) continue;
							if(t1.x2() != t3.x1()) continue;
							if(t1.x2() != t4.x1()) continue;
							if(t3.x1() != t4.x1()) continue;
							if(t3.x2() != t5.x1()) continue;
							if(t2.x2() != t4.x2()) continue;
							if(t2.x2() != t5.x2()) continue;
							if(t4.x2() != t5.x2()) continue;
								coloriage.push_back(Tuple4(t1[0],t1[1],t3[1],t2[1]));
					}
				}
			}
		}
	}
}
void deduction(){
	voisins.push_back(Tuple2(new Value("rouge"),new Value("vert")));
	voisins.push_back(Tuple2(new Value("rouge"),new Value("bleu")));
	voisins.push_back(Tuple2(new Value("vert"),new Value("rouge")));
	voisins.push_back(Tuple2(new Value("vert"),new Value("bleu")));
	voisins.push_back(Tuple2(new Value("bleu"),new Value("rouge")));
	voisins.push_back(Tuple2(new Value("bleu"),new Value("vert")));
	cout << "Listes des prédicats : "<< endl;
	cout <<"voisins =\n" << voisins << endl;

	cout << "Déductions pour toutes les règles :"<< endl;
	coloriage_deduce1();
	cout <<"coloriage =\n" << coloriage << endl;
}

int main(int argc, char **argv){
	deduction();
};

