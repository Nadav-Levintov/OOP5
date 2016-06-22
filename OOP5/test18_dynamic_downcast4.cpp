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

int main() {
	A* a = new B();
	B* b = CASTS::new_dynamic_cast<B*>(a);
	assert(b->x == 1);
	assert(b->My_Type() == a->My_Type());
	return 0;
}