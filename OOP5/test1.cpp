#include "hw5.h"

class A {};
class B :public A {};
class C {};
int main() {
	A* b = new B();
	B* b2 = CASTS::new_static_cast<B*>(b);
	A aa = CASTS::new_static_cast<A>(*b2);
	A* a = new A();
	b2 = CASTS::new_static_cast<B*>(a); //works, but result is not safe
	C* c = CASTS::new_static_cast<C*>(a); //doesn't COMPILE
	return 0;
}
