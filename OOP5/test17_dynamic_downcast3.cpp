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
	A* a = new A();
	B* b = CASTS::new_dynamic_cast<B*>(a);
	assert(b == NULL);
	A& a_ref = *a;
	try {
		CASTS::new_dynamic_cast<B& , A&>(a_ref);
		assert(false);
	}
	catch (std::bad_cast& b) {
		cout << b.what() << endl;
	}
	catch (exception& e) {
		cout << e.what() << endl;
	}
	return 0;
}
