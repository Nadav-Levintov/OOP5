#include "hw5.h"

class A {};
class B  {};

int main() {
	A* a = new A();
	CASTS::new_static_cast<B*>(a);
	return 0;
}