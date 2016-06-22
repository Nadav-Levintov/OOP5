#include "hw5.h"
#include <assert.h>
using namespace std;

class A { public: int x; A() : x(1) {}; };
class B : public A  { public: int x; B() : x(2) {}; };
class C : public B  { public: int x; C() : x(3) {}; };

int main() {
	int x;
	A a = A();
	A& a_ref = a;
	CASTS::new_static_cast<C&,A&>(a_ref);
	B b = B();
	A& b_ref = b;
	x = CASTS::new_static_cast<B&,A&>(b_ref).x;
	assert(x == 2);
	return 0;
}