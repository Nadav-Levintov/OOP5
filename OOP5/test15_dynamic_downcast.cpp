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
	int x;
	B() : x(1) { POLY(B)::Register_Inheritence(A::Get_Type()); }
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
	B* b = new C();
	A* a = CASTS::new_dynamic_cast<A*>(b);
	b = CASTS::new_dynamic_cast<B*>(a);
	assert(b->x == 1);
	return 0;
}