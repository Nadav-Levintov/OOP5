#include "hw5.h"

class A {};
class B : public A {};

int main() {
	A a();
	CASTS::new_static_cast<B*>(a);
	return 0;
}