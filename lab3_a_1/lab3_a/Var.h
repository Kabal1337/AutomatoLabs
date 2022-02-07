#pragma once
#include <string>

enum var_type
{
	Integer_t, String_t, Pointer_t, Array_t
};

class Var
{
public:
	
	virtual var_type get_type() = 0;
	virtual std::string get_name() = 0;
	
private:
	
};

