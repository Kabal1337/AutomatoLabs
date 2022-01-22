#pragma once
#include "Variables/Variable.h"
#include "Variables/Integer.h"
#include "Variables/String.h"
#include <vector>
#include <map>

class Function
{
public:
	Function(Variable* return_var, std::string name, int start_i);
	
	void add_var(Variable* variable);
	void add_arg(Variable* variable);
	Variable* get_var(std::string var_name);
	std::string get_fun_name();
	
	int get_start_i();
	int get_args_size();

	void set_arg(int index, int value); //Устанавливает значение аргумента при вызвове функции
	
	var_type get_ret_type();
	Variable* get_return_var();

	

	Function* make_copy();

	
	
private:
	std::string name;
	std::vector<Variable**> args;
	std::map<std::string, Variable*> scope;

	Variable* return_var; //Переменная функции, содержащая в себе возвращаемое значение
	

	

	int start_i;
};
