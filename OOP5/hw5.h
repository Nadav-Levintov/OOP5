#ifndef HW5_H_
#define HW5_H_

#include <type_traits>
#include <iostream>
#include <map>
#include <set>

using namespace std;

static int typeCounter = 0;

struct typeID {
	int value = -1;
	int get_value()
	{
		return value;
	}
	void set_value()
	{
		if (value == -1) {
			value = typeCounter++;
		}
	}

};


struct Type
{
	int id;
	Type() {
		id = -1;
	}
	Type(int i) :id(i) {}
	Type(const Type& t) {
		id = t.id;
	}

	void setID(int i)
	{
		id = i;
	}
	bool operator==(const Type& t);

	bool operator<(const Type& t);

	bool operator>(const Type& t);
	Type& operator=(const Type& t)
	{
		id = t.id;
		return *this;
	}

};



bool Type::operator==(const Type& t)
{
	return (id == t.id);
}
bool Type::operator<(const Type& t)
{
	return (id < t.id);
}

bool Type::operator>(const Type& t)
{
	return (id > t.id);
}


bool operator<(const Type& t1, const Type& t2)
{
	return (t1.id < t2.id);
}

bool operator>(const Type& t1, const Type& t2)
{
	return (t1.id > t2.id);
}

bool operator==(const Type& t1, const Type& t2)
{
	return (t1.id == t2.id);
}



template <class T>
class OOP_Polymorphic
{
	static typeID id;
	int vId;
	static Type staticT;
	Type t;
	friend T; //only the actual type can register this class at the CASTS data structure.

private:
	void Register_Inheritence(const Type *base);
	static set<Type> handeldParents;
public:
	OOP_Polymorphic() {
		id.set_value();
		vId = id.get_value();
		staticT.setID(id.get_value());
		t.setID(id.get_value());
	}

	static const Type *Get_Type()
	{
		if (id.get_value() == -1)
			return NULL;

		return &staticT;
	}
	virtual const Type *My_Type()
	{

		return &t;
	}
};
template<typename T>
set<Type> OOP_Polymorphic<T>::handeldParents;

template <class T>
typeID OOP_Polymorphic<T>::id;
template <class T>
Type OOP_Polymorphic<T>::staticT;

template<typename T>
void OOP_Polymorphic<T>::Register_Inheritence(const Type *base)
{


	Type currentT = *(this->My_Type());
	map<Type, map<Type, int>>::iterator it = CASTS::typesMap.find(currentT);
	if (base == NULL)
	{


		if (it == CASTS::typesMap.end())
		{
			map<Type, int> parentsMap;
			pair<Type, map<Type, int>> baseP(currentT, parentsMap);
			CASTS::typesMap.insert(baseP);


		}
		return;
	}

	if (handeldParents.find(*base) != handeldParents.end())
	{
		return;
	}
	handeldParents.insert(*base);
	
	CASTS::addToMap(*(this->My_Type()), *base);


}




class CASTS
{

public:

	static map<Type, map<Type, int>> typesMap;

	template<typename Dst, typename Src>
	static Dst new_static_cast(Src src);

	template<typename Dst, typename Src>
	static Dst new_dynamic_cast(Src src);

	static int Inherits_From(const Type *derived, const Type *base)
	{
		map<Type, map<Type, int>>::iterator it1 = CASTS::typesMap.find(*derived);
		if (it1 == CASTS::typesMap.end())
		{
			return 0;
		}

		map<Type, int>::iterator it2 = (*it1).second.find(*base);
		if (it2 == (*it1).second.end())
		{
			return 0;
		}

		return (*it2).second;
	}


	static void addToMap(const Type &d, const  Type &b)
	{
		//map<Type, int>::iterator it;
		if (CASTS::typesMap.find(d) == CASTS::typesMap.end())
		{
			map<Type, int> newMap;
			pair<Type, map<Type, int>> newPair2(d, newMap);
			CASTS::typesMap.insert(newPair2);
		}


		map<Type, map<Type, int>>::iterator it = CASTS::typesMap.find(d);
		map<Type, int> myMap = (*it).second;
		if (myMap.find(b) == myMap.end())
		{
			pair<Type, int> newPair(b, 1);
			myMap.insert(newPair);
		}
		else
		{
			pair<Type, int> oldPair = *myMap.find(b);
			oldPair.second++;
			myMap.erase(b);
			myMap.insert(oldPair);
		}
		map<Type, int> &parentMap = (*(CASTS::typesMap.find(b))).second;
		for each (pair<Type, int> p in parentMap)
		{
			if (myMap.find(p.first) == myMap.end())
			{
				myMap.insert(p);
			}
			else
			{
				pair<Type, int> oldPair = *myMap.find(p.first);
				oldPair.second += p.second;
				myMap.erase(oldPair.first);
				myMap.insert(oldPair);
			}
		}
		pair<Type, map<Type, int>> updatePair(d, myMap);
		CASTS::typesMap.erase(d);
		CASTS::typesMap.insert(updatePair);
		return;
	}

};

map<Type, map<Type, int>> CASTS::typesMap;

template<typename Dst, typename Src>
static Dst CASTS::new_dynamic_cast(Src src)
{
	constexpr static bool b = (((is_pointerCASTS<Dst>::value && is_pointerCASTS<Src>::value) ||
		(is_refCASTS<Dst>::value && is_refCASTS<Src>::value)));

	static_assert(b, "illegal dynamic convert");
	
	if (std::is_convertible<Src, Dst>::value)
	{
		return new_static_cast<Dst, Src>(src);
	}

	constexpr static bool b2 = (std::is_convertible<extractType<Src>::RET, OOP_Polymorphic<extractType<Src>::RET>>::value) && (std::is_convertible<extractType<Dst>::RET, OOP_Polymorphic<extractType<Dst>::RET>>::value);
	static_assert(b2, "illegal dynamic convert");

	Type dyn = createType<Src>::create(src);
	Type staSrc = *(OOP_Polymorphic<extractType<Src>::RET>::Get_Type());


	if (!(dyn == staSrc) && (CASTS::Inherits_From(&dyn, &staSrc) == 0))
	{
		
		return errorDynamic<Dst, is_pointerCASTS<Src>::value>::errorReturn();
	}
	
	if ((OOP_Polymorphic<extractType<Dst>::RET>::Get_Type()) == 0)
	{
		return errorDynamic<Dst, is_pointerCASTS<Src>::value>::errorReturn();
	}

	Type staDst = *(OOP_Polymorphic<extractType<Dst>::RET>::Get_Type());
	
	if ((CASTS::Inherits_From(&staDst, &staSrc) == 1))
	{
		if ((CASTS::Inherits_From(&dyn, &staDst) > 0))
		{
			return (Dst)src;
		}
		else
			return errorDynamic<Dst, is_pointerCASTS<Src>::value>::errorReturn();
	}

	return errorDynamic<Dst, is_pointerCASTS<Src>::value>::errorReturn();


}
template<typename T,bool b>
struct errorDynamic {
	static T errorReturn()
	{
		return nullptr;
	}

};

template<typename T>
struct errorDynamic<T,false> {
	static T errorReturn()
	{
		throw std::bad_cast();

		return extractType<T>::RET();
	}

};







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



template<typename T>
struct extractType {
	typedef T RET;
};

template<typename T>
struct extractType <T&> {
	typedef T RET;
};

template<typename T>
struct extractType <T*> {
	typedef T RET;
};


template<typename T>
struct createType {
	static const Type create(T src) {
		return *(src.My_Type());
	}
};


template<typename T>
struct createType< T* > {
	static const Type create(T *src) {
		return *(src->My_Type());
	}
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
		//return reinterpret_cast<Dst> (src);
		return (Dst)src;
	}
};

#endif
