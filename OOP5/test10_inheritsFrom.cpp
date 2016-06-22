#include "hw5.h"
#include <assert.h>

#define GENERATE_MYTYPE(x) \
	const Type* My_Type() { return OOP_Polymorphic<x>::Get_Type(); }
#define POLY(x) \
	OOP_Polymorphic<x>

using namespace std;

class A : public POLY(A) {
public:
	A() {Register_Inheritence(NULL);}
	GENERATE_MYTYPE(A)
};

class B : public A, public POLY(B) {
public:
	B() { POLY(B)::Register_Inheritence(A::Get_Type()); }
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
	A();
	B();
	C();
	assert(CASTS::Inherits_From(POLY(A)::Get_Type(), POLY(A)::Get_Type()) == 0);
	assert(CASTS::Inherits_From(POLY(B)::Get_Type(), POLY(A)::Get_Type()) == 1);
	assert(CASTS::Inherits_From(POLY(C)::Get_Type(), POLY(A)::Get_Type()) == 2);
	assert(CASTS::Inherits_From(POLY(A)::Get_Type(), POLY(C)::Get_Type()) == 0);


	return 0;
}
