#ifndef HW5_H_
#define HW5_H_

#include <type_traits>
#include <iostream>
using namespace std;

static int typeCounter = 0;

template<typename T>
struct typeID {
	 int value = -1;
	int get_value()
	{
		return value;
	}
	void set_value()
	{
		value = typeCounter++;
	}

};


struct Type 
{
	int id;
	Type(int i) :id(i) {}
	bool operator==(const Type& t)
	{
		return (id==t.id);
	}

};





template <class T>
class OOP_Polymorphic
{

	friend T; //only the actual type can register this class at the CASTS data structure.

private:
	void Register_Inheritence(const Type *base);

public:
	OOP_Polymorphic() {
		if (typeID<T>::get_value() == -1)
		{
			typeID<T>::set_value();
		}

	}
	static const Type *Get_Type();
	virtual const Type *My_Type();
};

template<class T>
static const Type* OOP_Polymorphic<T>::Get_Type()
{
	if (typeID<T>::get_value() == -1)
		return NULL;
	
	return Type(typeID<T>::get_value());
}

template<class T>
virtual const Type* OOP_Polymorphic<T>::My_Type()
{

	return this.Get_Type();
}


class CASTS
{

public:

	template<typename Dst, typename Src>
	static Dst new_static_cast(Src src);

	template<typename Dst, typename Src>
	static Dst new_dynamic_cast(Src src);

	static int Inherits_From(const Type *derived, const Type *base);
};

template<typename Dst, typename Src>
static Dst CASTS::new_dynamic_cast(Src src)
{
	constexpr static bool b = (((is_pointerCASTS<Dst>::value && is_pointerCASTS<Src>::value) ||
		(is_refCASTS<Dst>::value && is_refCASTS<Src>::value)));

	static_assert(b, "illegal dynamic convert");
	if (std::is_convertible<Dst, Src>::value)
	{
		return new_static_cast<Dst, Src>(src);
	}


}




template<typename Dst, typename Src>
static Dst CASTS::new_static_cast(Src src)
{

	constexpr static bool b = (((is_pointerCASTS<Dst>::value && is_pointerCASTS<Src>::value) ||
		(is_refCASTS<Dst>::value && is_refCASTS<Src>::value)) &&
		std::is_convertible<Dst, Src>::value);


	static_assert(b || std::is_convertible<Dst, Src>::value || std::is_convertible<Src, Dst>::value, "illegal static convert");
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
