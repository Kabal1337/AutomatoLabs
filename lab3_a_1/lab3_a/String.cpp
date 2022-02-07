#include "String.h"


String::String(std::string name)
{
	this->name = name;
	this->type = String_t;
	this->mut = true;
}

String::String(std::string name, std::string value)
{
	this->name = name;
	this->type = String_t;
	this->mut = true;
	this->value = value;
}

var_type String::get_type()
{
	return type;
}

std::string String::get_name()
{
	return name;
}

std::string String::get_value()
{
	return this->value;
}

void String::set_value(std::string str)
{
	this->value = str;
}


