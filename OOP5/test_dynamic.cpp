#include "hw5.h"
class Base : public OOP_Polymorphic<Base> {
public:  Base() {

	Register_Inheritence(NULL); // we don't register
								// "OOPPolymorphic" as a parent
}
};
class Derived : public Base, public OOP_Polymorphic<Derived> {
public:
	Derived() {
		OOP_Polymorphic<Derived>::Register_Inheritence(Base::Get_Type());
	}
	virtual void f() {
		cout << "Derived Successfully" << endl;
	}
};
int main() {
	Derived* d1 = new Derived();
	Base* b = d1;
	Derived* d = CASTS::new_dynamic_cast<Derived*>(b);
	d->f(); //prints 'Derived Successfuly'  
	return 0;
}