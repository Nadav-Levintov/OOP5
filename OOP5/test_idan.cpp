#include "hw5.h"
#include <iostream>
#include <cassert>

using namespace std;

class A {};
class B : public A {};

class Base : public OOP_Polymorphic<Base> {
public:
  Base() {
      Register_Inheritence(NULL); // we don't register
                                  // "OOPPolymorphic" as a parent
  }
  const Type *My_Type() const {
      return OOP_Polymorphic<Base>::Get_Type();
  }
};
class Derived : public Base, public OOP_Polymorphic<Derived> {
public:
  Derived() {
      OOP_Polymorphic<Derived>::Register_Inheritence(Base::Get_Type());
  }
  const Type *My_Type() const {
      return OOP_Polymorphic<Derived>::Get_Type();
  }
  const Type *My_Type() {
      return OOP_Polymorphic<Derived>::Get_Type();
  }
  virtual void f() {
      cout << "Derived Successfully" << endl;
  }
};

void static_test() {
  A* ap = new B();
  const A* apc = ap;
  B* bp = new B();
  const B* bpc = bp;
  A a = A();
  const A ac = a;
  B b = B();
  const B bc = b;
  A& ar = b;
  const A& arc = ar;
  B& br = b;
  const B& brc = br;

  CASTS::new_static_cast<B*, A*>(ap);
  CASTS::new_static_cast<A*, B*>(bp);
  CASTS::new_static_cast<A, B>(b);
  CASTS::new_static_cast<B&, A&>(ar);
  CASTS::new_static_cast<A&, B&>(br);

  CASTS::new_static_cast<const B*, A*>(ap);
   CASTS::new_static_cast<const A*, B*>(bp);
   CASTS::new_static_cast<const A, B>(b);
   CASTS::new_static_cast<const B&, A&>(ar);
   CASTS::new_static_cast<const A&, B&>(br);

   CASTS::new_static_cast<const B*, const A*>(apc);
   CASTS::new_static_cast<const A*, const B*>(bpc);
   CASTS::new_static_cast<const A, const B>(bc);
   CASTS::new_static_cast<const B&, const A&>(arc);
   CASTS::new_static_cast<const A&, const B&>(brc);

   
  //CASTS::new_static_cast<A, const B>(bc); // idan thought it doesnt work but it does
  
  // EACH LINE HERE SHOULD RAISE "illegal static convert" AND NOT COMPILE!
//  CASTS::new_static_cast<B*,  const A*>(apc);
  //CASTS::new_static_cast<A*, const B*>(bpc);

 // CASTS::new_static_cast<B&, const A&>(arc);
  //CASTS::new_static_cast<A&, const B&>(brc);
  
}

void dynamic_test() {
  Base* ap = new Derived();
  const Base* apc = ap;
  Derived* bp = new Derived();
  const Derived* bpc = bp;
  Base a = Base();
  const Base ac = a;
  Derived b = Derived();
  const Derived bc = b;
  Base& ar = b;
  const Base& arc = ar;
  Derived& br = b;
  const Derived& brc = br;

  CASTS::new_dynamic_cast<Derived*, Base*>(ap);
  CASTS::new_dynamic_cast<Base*, Derived*>(bp);
  CASTS::new_dynamic_cast<Derived&, Base&>(ar);
  CASTS::new_dynamic_cast<Base&, Derived&>(br);

  //CASTS::new_dynamic_cast<const Derived*, Base*>(ap);
  //CASTS::new_dynamic_cast<const Base*, Derived*>(bp);

  //CASTS::new_dynamic_cast<const Derived&, Base&>(ar);
  //CASTS::new_dynamic_cast<const Base&, Derived&>(br);

  //CASTS::new_dynamic_cast<const Derived*, const Base*>(apc);
  //CASTS::new_dynamic_cast<const Base*, const Derived*>(bpc);

  //CASTS::new_dynamic_cast<const Derived&, const Base&>(arc);
  //CASTS::new_dynamic_cast<const Base&, const Derived&>(brc);



  //CASTS::new_dynamic_cast<Derived*, const Base*>(apc) == nullptr ? "" : throw(-1);
  //CASTS::new_dynamic_cast<Base*, const Derived*>(bpc) == nullptr ? "" : throw(-1);
  /*
  not good:
  CASTS::new_dynamic_cast<Derived&, const Base&>(arc);
  CASTS::new_dynamic_cast<Base&, const Derived&>(brc);

  this are not pointers and refrence
  CASTS::new_dynamic_cast<Base, const Derived>(bc);
 */
  //CASTS::new_dynamic_cast<Base, Derived>(b);
  /*CASTS::new_dynamic_cast<const Base, Derived>(b);
  CASTS::new_dynamic_cast<const Base, const Derived>(bc);
  */
}

int main() {
  static_test();
  dynamic_test();
}