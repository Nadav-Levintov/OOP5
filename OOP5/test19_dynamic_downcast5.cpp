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

class B : public POLY(B) {
public:
	B() { POLY(B)::Register_Inheritence(NULL); }
	GENERATE_MYTYPE(B)
};

class C : public A, public B, public POLY(C) {
public:
	C(){
		POLY(C)::Register_Inheritence(POLY(A)::Get_Type());
		POLY(C)::Register_Inheritence(POLY(B)::Get_Type());
	}
	GENERATE_MYTYPE(C)
};

int main() {
	A a = A();
	C c();
	A& a_ref = a;
	try {
		CASTS::new_dynamic_cast<C&, A&>(a_ref);
		assert(false);
	}
	catch (...) {

	}
	return 0;
}