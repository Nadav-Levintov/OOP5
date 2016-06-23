#include "hw5.h"

int typeID::get_value()
{
	return value;
}

void typeID::set_value()
{
	if (value == -1) {
		value = typeCounter++;
	}
}

void Type::setID(int i)
{
	id = i;
}

Type::Type() {
	id = -1;
}

Type::Type(const Type& t) {
	id = t.id;
}

Type& Type::operator=(const Type& t)
{
	id = t.id;
	return *this;
}


/*Operators to be used to compare Types*/
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


