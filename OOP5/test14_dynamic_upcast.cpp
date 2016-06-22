#include "hw5.h"
#include <assert.h>

class A {

};
class B : public A {
};


int main() {
	B* b = new B();
	A* a =CASTS::new_dynamic_cast<A*>(b);

	return 0;
}
