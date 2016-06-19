//
// Created by ophir on 17/06/16.
//


#include "hw5.h"

/*classes/types*/

class A1 {};
class B1 : public A1 {};

class A2 {};
class B2 : public A2 {};
class C2 : public B2 {};

class A3 {};
class B3 {};
class C3 : public A3, public B3 {};

class A4 {};
class B4 {};
class C4 : public A4, public B4 {};
class D4 : public C4 {};

class E {};

class V_base1 { virtual void f(); };
class V_der11 : public V_base1 {};
class V_der12 : public V_der11 {};


/*should all be okay*/

void test_case1_ptr_downcast() {


    A1* a1 = new A1();
    B1* b1 = CASTS::new_static_cast<B1*>(a1);
    delete a1;
	
    A2* a2 = new A2();
    B2* b2 = new B2();
    C2* c21 = CASTS::new_static_cast<C2*>(a2);
    C2* c22 = CASTS::new_static_cast<C2*>(b2);
    delete a2;
    delete b2;

    A3* a3 = new A3();
    B3* b3 = new B3();
    C3* c31 = CASTS::new_static_cast<C3*>(a3);
    C3* c32 = CASTS::new_static_cast<C3*>(b3);
    delete a3;
    delete b3;

    A4* a4 = new A4();
    B4* b4 = new B4();
    D4* d41 = CASTS::new_static_cast<D4*>(a4);
    D4* d42 = CASTS::new_static_cast<D4*>(b4);
    C4* c4 = new C4();
    D4* d43 = CASTS::new_static_cast<D4*>(c4);
    delete a4;
    delete b4;
    delete c4;
	
}

void test_case1_ptr_upcast() {
	
    B1* b11 = new B1();
    A1* a1 = CASTS::new_static_cast<A1*>(b11);

    C2* c2 = new C2();
    B2* b2 = CASTS::new_static_cast<B2*>(c2);
    A2* a2 = CASTS::new_static_cast<A2*>(b2);

    C3* c3 = new C3();
    A3* a3 = CASTS::new_static_cast<A3*>(c3);
    B3* b3 = CASTS::new_static_cast<B3*>(c3);

    D4* d4 = new D4();
    A4* a41 = CASTS::new_static_cast<A4*>(d4);
    B4* b41 = CASTS::new_static_cast<B4*>(d4);
    C4* c4 = CASTS::new_static_cast<C4*>(d4);
    A4* a42 = CASTS::new_static_cast<A4*>(c4);
    B4* b42 = CASTS::new_static_cast<B4*>(c4);
	
}

void test_case1_ref_downcast() {


    A1 a1;
    A1& a1ref = a1;
    B1& b1 = CASTS::new_static_cast<B1&, A1&>(a1ref);

    A2 a2;
    A2& a2ref = a2;
    B2 b2;
    B2& b2ref = b2;
    C2& c21 = CASTS::new_static_cast<C2&, A2&>(a2ref);
    C2& c22 = CASTS::new_static_cast<C2&, B2&>(b2ref);

    A3 a3;
    A3& a3ref = a3;
    B3 b3;
    B3& b3ref = b3;
    C3& c31 = CASTS::new_static_cast<C3&, A3&>(a3ref);
    C3& c32 = CASTS::new_static_cast<C3&, B3&>(b3ref);

    A4 a4;
    A4& a4ref = a4;
    B4 b4;
    B4& b4ref = b4;
    D4& d41 = CASTS::new_static_cast<D4&, A4&>(a4ref);
    D4& d42 = CASTS::new_static_cast<D4&, B4&>(b4ref);
    C4 c4;
    C4& c4ref = c4;
    D4& d43 = CASTS::new_static_cast<D4&, C4&>(c4ref);
}


void test_case3() {

    int a = CASTS::new_static_cast<int>(5.2);
    double b = CASTS::new_static_cast<double>(4);
    char c = CASTS::new_static_cast<char>(65);
}

void test_mix_should_not_compile() {
    /*expected "illegal static convert" message*/

    /*test each one*/

    /*A1* a1 = new A1();
    E* e1 = CASTS::new_static_cast<E*>(a1);
    delete a1;*/

    /*A1* a12 = new A1();
    int* i1 = CASTS::new_static_cast<int*>(a12);
    delete a12;*/

    /*A1* a13 = new A1();
    B1** b1 = CASTS::new_static_cast<B1**>(a13);
    delete a13;*/

    /*A1* a14 = new A1();
    B1* b2 = CASTS::new_static_cast<B1*>(&a14);
    delete a14;*/
	/*
    A1* a15 = new A1();
    A1*& a16 = a15;
    B1** b3 = CASTS::new_static_cast<B1**>(a16);
    delete a15;*/

    /*A1*** a17;
    B1** b4 = CASTS::new_static_cast<B1**>(a17);*/

    /*V_base1* v1 = new V_base1();
    V_der11* vd1 = CASTS::new_static_cast<V_der11*>(v1);
    V_der12* vd2 = CASTS::new_static_cast<V_der12*>(v1);
    delete v1;*/
	/*
    A1* a18;
    B1** b5 = CASTS::new_static_cast<B1**>(&a18);*/
	/*
    A1** a19;
   B1*** b6 = CASTS::new_static_cast<B1***>(&a19);
   */
/*
   B1** b11;
    A1** A20 = CASTS::new_static_cast<A1**>(b11);*/
}

int main()
{
	return 0;
}



