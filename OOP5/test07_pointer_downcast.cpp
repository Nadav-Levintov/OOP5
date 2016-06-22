#include "hw5.h"
#include <assert.h>
using namespace std;

class A { public: int x; A() : x(1) {}; };
class B : public A  { public: int x; B() : x(2) {}; };
class C : public B  { public: int x; C() : x(3) {}; };

int main() {
	int x;
	A* a = new A();
	CASTS::new_static_cast<C*>(a);
	a = new B();
	x = CASTS::new_static_cast<B*>(a)->x;
	assert(x == 2);
	return 0;
}