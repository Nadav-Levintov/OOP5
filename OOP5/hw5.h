#ifndef HW5_H_
#define HW5_H_

#include <type_traits>
#include <iostream>
#include <map>
#include <set>

using namespace std;
/*static counter for Type uniqe ID*/
static int typeCounter = 0;
/*Type would have a static typeID member*/
struct typeID {
	int value = -1;
	int get_value();
	void set_value();

};

/*A type woyld be creatd using the static TypeId*/
struct Type
{
	int id;
	
	Type();

	Type(int i) :id(i) {}
	
	Type(const Type& t);

	void setID(int i);
	
	bool operator==(const Type& t);

	bool operator<(const Type& t);

	bool operator>(const Type& t);
	Type& operator=(const Type& t);

};



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

	static set<Type> handeldParents;//would be used to prevent registering parents more then once.

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

/*initialize the static members of OOP_Polymorphic<T>*/
template<typename T>
set<Type> OOP_Polymorphic<T>::handeldParents;
template <class T>
typeID OOP_Polymorphic<T>::id;
template <class T>
Type OOP_Polymorphic<T>::staticT;

template<typename T>
void OOP_Polymorphic<T>::Register_Inheritence(const Type *base)
{

	Type currentT = *(this->My_Type()); //get My Type
	map<Type, map<Type, int>>::iterator it = CASTS::typesMap.find(currentT); //find the map that is relevent to me in the CASTS DS.
	if (base == NULL)
	{
		/*if registering OOP_Polymorphic<T>*/
		if (it == CASTS::typesMap.end())
		{
			/*if this is the first time registering me to the CASTS DS*/
			map<Type, int> parentsMap;
			pair<Type, map<Type, int>> baseP(currentT, parentsMap);
			CASTS::typesMap.insert(baseP);
		}
		return;
	}

	if (handeldParents.find(*base) != handeldParents.end())
	{
		/*if this parent was allready inserted to the map, do nothing*/
		return;
	}

	handeldParents.insert(*base);//insert parent to the set of the parents that were handeld.

	CASTS::addToMap(*(this->My_Type()), *base);//add the parent and all of his inheretence to the map in the CASTS DS.

}




class CASTS
{

public:

	static map<Type, map<Type, int>> typesMap;//the static DS to control the number of times objects inheret from each other.

	template<typename Dst, typename Src>
	static Dst new_static_cast(Src src);

	template<typename Dst, typename Src>
	static Dst new_dynamic_cast(Src src);

	static int Inherits_From(const Type *derived, const Type *base)
	{
		map<Type, map<Type, int>>::iterator it1 = CASTS::typesMap.find(*derived);
		if (it1 == CASTS::typesMap.end())
		{
			/*derived was never initiated or was never registerd.*/
			return 0;
		}

		map<Type, int>::iterator it2 = (*it1).second.find(*base);
		if (it2 == (*it1).second.end())
		{
			/*base was never initiated or was never registerd.*/
			return 0;
		}

		return (*it2).second; //the number of times base inheretes from derived using the CASTS DS
	}


	static void addToMap(const Type &d, const  Type &b)
	{

		if (CASTS::typesMap.find(d) == CASTS::typesMap.end())
		{
			/*if derived is not in the CASTS DB insert it.*/
			map<Type, int> newMap;
			pair<Type, map<Type, int>> newPair2(d, newMap);
			CASTS::typesMap.insert(newPair2);
		}


		map<Type, map<Type, int>>::iterator it = CASTS::typesMap.find(d); //get the map relevent to the derived from the DS in CASTS(it's there for sure).
		map<Type, int> myMap = (*it).second;//get the map from the pair.
		if (myMap.find(b) == myMap.end())
		{
			/*base is not in my map, insert it with 1 value*/
			pair<Type, int> newPair(b, 1);
			myMap.insert(newPair);
		}
		else
		{
			/*base IS in my map allready, increase the times I inhereted from it.*/
			pair<Type, int> oldPair = *myMap.find(b);
			oldPair.second++;
			myMap.erase(b);
			myMap.insert(oldPair);
		}
		map<Type, int> &parentMap = (*(CASTS::typesMap.find(b))).second;//get the map of base in order to retrive it's inharetence.
		for each (pair<Type, int> p in parentMap)
		{
			/*for each type in the parent map add it if didn't exsist in my map or update the relevant entry.*/
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
		/*push the updated map to the CASTS DS*/
		pair<Type, map<Type, int>> updatePair(d, myMap);
		CASTS::typesMap.erase(d);
		CASTS::typesMap.insert(updatePair);
		return;
	}

};

map<Type, map<Type, int>> CASTS::typesMap; //initialize the static CASTS DS.

template<typename Dst, typename Src>
static Dst CASTS::new_dynamic_cast(Src src)
{
	constexpr static bool b = (((is_pointerCASTS<Dst>::value && is_pointerCASTS<Src>::value) ||
		(is_refCASTS<Dst>::value && is_refCASTS<Src>::value)));
	/*check if both Types are pointers or ref*/
	static_assert(b, "illegal dynamic convert");
	/*check if cast could be done during compilation*/
	if (std::is_convertible<Src, Dst>::value)
	{
		return new_static_cast<Dst, Src>(src);
	}
	/*check both Types inherent from OOP_Polymorphic.*/
	constexpr static bool b2 = (std::is_convertible<extractType<Src>::RET, OOP_Polymorphic<extractType<Src>::RET>>::value) && (std::is_convertible<extractType<Dst>::RET, OOP_Polymorphic<extractType<Dst>::RET>>::value);
	static_assert(b2, "illegal dynamic convert");

	Type dyn = createType<Src>::create(src);//get the dynamic type of src
	Type staSrc = *(OOP_Polymorphic<extractType<Src>::RET>::Get_Type());//get the static type of Src.


	if ((!(dyn == staSrc) && (CASTS::Inherits_From(&dyn, &staSrc) == 0)) || ((OOP_Polymorphic<extractType<Dst>::RET>::Get_Type()) == 0))
	{
		/*if dyn is not Src or does not inherent from it and check if Dst was never inisiated*/
		return errorDynamic<Dst, is_pointerCASTS<Src>::value>::errorReturn();
	}

	Type staDst = *(OOP_Polymorphic<extractType<Dst>::RET>::Get_Type());//get the Dst type

	if ((CASTS::Inherits_From(&staDst, &staSrc) == 1))//check if Dst inherets exacly once from Src
	{
		if ((CASTS::Inherits_From(&dyn, &staDst) > 0) || dyn == staDst)//if the dynamic type is equal to dst or kind of dst cast.
		{
			return (Dst)src;
		}
		else {
			return errorDynamic<Dst, is_pointerCASTS<Src>::value>::errorReturn();
		}
	}

	return errorDynamic<Dst, is_pointerCASTS<Src>::value>::errorReturn();//if for some reason got here, return error.

}


template<typename Dst, typename Src>
static Dst CASTS::new_static_cast(Src src)
{
/*check if static cast is legal*/
	constexpr static bool b = (((is_pointerCASTS<Dst>::value && is_pointerCASTS<Src>::value) ||
		(is_refCASTS<Dst>::value && is_refCASTS<Src>::value)) &&
		!(is_constCASTS<Src>::value && !is_constCASTS<Src>::value) &&
		std::is_convertible<Dst, Src>::value);
	
	static_assert(b || std::is_convertible<Dst, Src>::value || std::is_convertible<Src, Dst>::value, "illegal static convert");
	/*call the relevant static cast template*/
	Dst res = IF<b, Dst, Src>::castAux(src);

	return res;
	
}



/*Template Specialization:*/

/*This is used to either return nullptr or throw exception according to PTR or Ref types in dynamic cast*/
template<typename T, bool b>
struct errorDynamic {
	static T errorReturn()
	{
		return nullptr;
	}

};

template<typename T>
struct errorDynamic<T, false> {
	static T errorReturn()
	{
		throw std::bad_cast();

		return extractType<T>::RET();
	}

};

/*check if T is Pointer*/
template<typename T>
struct is_pointerCASTS {
	static const bool value = false;
};

template<typename T>
struct is_pointerCASTS <T*> {
	static const bool value = true;
};

/*check if T is ref*/
template<typename T>
struct is_refCASTS {
	static const bool value = false;
};

template<typename T>
struct is_refCASTS <T&> {
	static const bool value = true;
};

/*check if T is const*/
template<typename T>
struct is_constCASTS {
	static const bool value = false;
};

template<typename T>
struct is_constCASTS <const T> {
	static const bool value = true;
};

/*extract the type itself (with out * or &)*/
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

/*create the Static Type */
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

/*Static cast based on the template*/
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
		return (Dst)src;
	}
};

#endif
