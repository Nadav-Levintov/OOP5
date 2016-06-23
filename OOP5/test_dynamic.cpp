#include "hw5.h"

class Base : public OOP_Polymorphic<Base> {
public:
	Base() {
		Register_Inheritence(NULL); // we don't register
									// "OOPPolymorphic" as a parent
	}
	const Type *My_Type() {
		return OOP_Polymorphic<Base>::Get_Type();
	}
};
class Derived : public Base, public OOP_Polymorphic<Derived> {
public:
	Derived() {
		OOP_Polymorphic<Derived>::Register_Inheritence(
			OOP_Polymorphic<Base>::Get_Type());
	}
	const Type *My_Type() {
		return OOP_Polymorphic<Derived>::Get_Type();
	}
	virtual void f() {
		cout << "Derived Successfully" << endl;
	}
};
int main() {
	Base* b = new Derived();
	Derived* d = CASTS::new_dynamic_cast<Derived*>(b);
	d->f(); //prints 'Derived Successfully'
	return 0;
}