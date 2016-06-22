#include "hw5.h"

class A {};
class B : public A  {};

int main() {
	A* a = new A();
	CASTS::new_static_cast<B&,A*>(a);
	return 0;
}