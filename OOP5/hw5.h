#ifndef HW5_H_
#define HW5_H_

#include <type_traits>
#include <iostream>
using namespace std;
struct Type
{

	//add your implementation here

};

/*
template <class T>
class OOP_Polymorphic
{

	 friend T; //only the actual type can register this class at the CASTS data structure.

private:
	 void Register_Inheritence(const Type *base);

public:

	 static const Type *Get_Type();
	 virtual const Type *My_Type();
};

*/

class CASTS
{

public:

	template<typename Dst, typename Src>
	static Dst new_static_cast(Src src);
	/*
	template<typename Dst, typename Src>
	static Dst new_dynamic_cast(Src src);

	static int Inherits_From(const Type *derived, const Type *base);*/
};






template<typename Dst, typename Src>
static Dst CASTS::new_static_cast(Src src)
{

	constexpr static bool b = (((is_pointerCASTS<Dst>::value && is_pointerCASTS<Src>::value) ||
		(is_refCASTS<Dst>::value && is_refCASTS<Src>::value)) &&
		std::is_convertible<Dst, Src>::value);

	Dst res = IF<b, Dst, Src>::castAux(src);
	
	return res;



}


template<typename T>
struct is_pointerCASTS {
	static const bool value = false;
};

template<typename T>
struct is_pointerCASTS <T*> {
	static const bool value = true;
};
template<typename T>
struct is_refCASTS {
	static const bool value = false;
};

template<typename T>
struct is_refCASTS <T&> {
	static const bool value = true;
};


template <bool b, typename Dst, typename Src>
struct IF {
public:
	static	Dst castAux(Src src) {
		return src;
	}
};
template <typename Dst, typename Src>
struct IF<true, Dst, Src> {
public:
	static Dst castAux(Src src)
	{
		return reinterpret_cast<Dst> (src);
	}
};

#endif
