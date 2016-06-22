#include "hw5.h"
#include <assert.h>
using namespace std;

class A { public: int x; A() : x(1) {}; };
class B : public A  { public: int x; B() : x(2) {}; };
class C : public B  { public: int x; C() : x(3) {}; };

int main() {
	int x;
	C c = C();
	x = CASTS::new_static_cast<A>(c).x;
	assert(x == 1);
	x = CASTS::new_static_cast<B>(c).x;
	assert(x == 2);
	x = CASTS::new_static_cast<C>(c).x;
	assert(x == 3);
	return 0;
}