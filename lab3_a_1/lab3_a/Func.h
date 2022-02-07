#pragma once
#include "Var.h"
#include <string>
#include <map>
#include "Integer.h"
#include <vector>
#include "String.h"
#include <stack>
class Func
{
public:
	Func(std::string name, var_type var_type, int body_index);
	void add_arg(Var* variable);
	int get_body_index();
	void add_variable(Var* var, std::string name);
	Var* get_variable(std::string var_name);
	Var* get_return_var();
	Var* get_return_var_ptr();
private:
	std::string name;
	int body_index;
	Var* return_var;
	Var* return_var_ptr;
	std::map<std::string, Var*> variables;
	std::vector<Var*> args;
	std::stack<Func*> func_stack;
};

