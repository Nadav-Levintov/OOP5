#include "hw5.h"

class A {};
class B  {};

int main() {
	B b();
	CASTS::new_static_cast<A>(b);
	return 0;
}