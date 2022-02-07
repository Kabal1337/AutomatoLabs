#pragma once
#include <stack>
#include <string>
#include <map>
#include "Func.h"
#include <vector>
#include <fstream>
#include <regex>
#include <iostream>
#include "String.h"
class Interpr
{
public:
	Interpr(std::string code_file);

private:
	Func* cur_func;
	int cur_index;
	std::map<std::string, Func*> functions;
	//считываемый код
	std::vector<std::string> code;
	//собирает информацию о функциях и смотрит закрыты ли start/finish
	void take_funcs();
	//выполняет код в теле функции
	void perform_body();
	std::stack<int> pos_stack;
	std::stack<Func*> func_stack;
};


