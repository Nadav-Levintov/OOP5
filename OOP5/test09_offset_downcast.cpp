#include "hw5.h"
#include <assert.h>
using namespace std;

class A { public: int x; A() : x(1) {}; };
class B  { public: int x; B() : x(2) {}; virtual ~B() {}; };
class C : public A, public B  { public: int x; C() : x(3) {}; };

int main() {
	A* a = new C();
	C* c =CASTS::new_static_cast<C*>(a);
	assert(c->x == 3);
	assert(CASTS::new_static_cast<C*>((B*)c)->x == 3);
	return 0;
}
