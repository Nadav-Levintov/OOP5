#include "hw5.h"
#include <assert.h>

#define GENERATE_MYTYPE(x) \
	const Type* My_Type() { return OOP_Polymorphic<x>::Get_Type(); }
#define POLY(x) \
	OOP_Polymorphic<x>

using namespace std;

class A : public POLY(A) {
public:
	A() { Register_Inheritence(NULL); }
	GENERATE_MYTYPE(A)
};

class B : public A, public POLY(B) {
public:
	B() { POLY(B)::Register_Inheritence(A::Get_Type()); }
	GENERATE_MYTYPE(B)
};


int main() {
	assert(POLY(A)::Get_Type() == NULL);
	A* a = new A();
	
	assert(POLY(B)::Get_Type() == NULL);
	assert(POLY(A)::Get_Type() == a->My_Type());
	B b = B(); 
	assert(!(POLY(A)::Get_Type() == b.My_Type()));
	A a2 = A();
	assert(a2.My_Type() == a->My_Type());


	return 0;
}
