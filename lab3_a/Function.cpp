#include "Function.h"

Function::Function(Variable* return_var, std::string name, int start_i)
{
	this->return_var = return_var;
	this->name = name;
	this->start_i = start_i;
	
}

void Function::add_var(Variable* variable)
{
	this->scope[variable->get_name()] = variable;
}

void Function::add_arg(Variable* variable)
{
	this->scope[variable->get_name()] = variable;
	this->args.push_back(&(this->scope[variable->get_name()]));
}

Variable* Function::get_var(std::string var_name)
{
	return this->scope[var_name];
}

std::string Function::get_fun_name()
{
	return this->name;
}

var_type Function::get_ret_type()
{
	return this->return_var->get_type();
}

Variable* Function::get_return_var()
{
	return this->return_var;
}

int Function::get_start_i()
{
	return this->start_i;
}

int Function::get_args_size()
{
	return this->args.size();
}

void Function::set_arg(int index, int value)
{
	Variable** ptr_tmp = this->args[index];
	Integer* tmp = dynamic_cast<Integer*>(*ptr_tmp);
	if (tmp == nullptr) throw (std::string)("The argument type does not match the parameter");
	tmp->set_value(value);
}





Function* Function::make_copy()
{
	Function* new_foo = new Function(this->return_var, this->name, this->start_i);
	
	for (int i = 0; i < this->args.size(); i++)
	{
		new_foo->add_arg(*this->args[i]);
	}
	
	return new_foo;
}


