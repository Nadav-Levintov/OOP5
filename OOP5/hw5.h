#ifndef HW5_H_
#define HW5_H_


struct Type
{

	//add your implementation here

};


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



class CASTS
{

public:

     template<typename Dst, typename Src>
     static Dst new_static_cast(Src src);

     template<typename Dst, typename Src>
     static Dst new_dynamic_cast(Src src);

     static int Inherits_From(const Type *derived, const Type *base);
};


#endif
