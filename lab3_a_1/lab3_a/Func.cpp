#include "Func.h"


Func::Func(std::string name, var_type var_type_return, int body_index)
{
	this->name = name;
	if (var_type_return == Integer_t)
	{
		return_var = new Integer("return");
	}
	else if(var_type_return == String_t)
	{
		return_var = new String("return");
	}
	this->body_index = body_index;
	this->return_var_ptr = nullptr;
	
}

void Func::add_arg(Var* variable)
{
	this->variables[variable->get_name()] = variable;
	this->args.push_back(variable);
}

int Func::get_body_index()
{
	return this->body_index;
}

void Func::add_variable(Var* var, std::string name)
{
	variables[name] = var;
}

Var* Func::get_variable(std::string var_name)
{
	return variables[var_name];
}

Var* Func::get_return_var()
{
	return return_var;
}

Var* Func::get_return_var_ptr()
{
	return return_var_ptr;
}
