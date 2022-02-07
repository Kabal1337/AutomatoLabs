#include "Integer.h"

Integer::Integer(std::string name, int value)
{
	this->value = value;
	this->name = name;
	this->mut = false;
	this->type = Integer_t;
}

Integer::Integer(std::string name)
{
	this->value = value;
	this->mut = true;
	this->type = Integer_t;
}

var_type Integer::get_type()
{
	return this->type;
}

std::string Integer::get_name()
{
	return this->name;
}

int Integer::get_value()
{
	return this->value;
}

void Integer::set_value(int value)
{
	this->value = value;
}
