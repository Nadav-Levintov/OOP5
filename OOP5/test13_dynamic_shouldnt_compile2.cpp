#include "hw5.h"
#include <assert.h>

class A {

};
class B : public A {
};


int main() {
	A* a =new B();
	CASTS::new_dynamic_cast<B*>(a);

	return 0;
}