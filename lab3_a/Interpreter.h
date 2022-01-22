#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <regex>
#include <stack>


#include "Function.h"
#include "Variables/Variable.h"
#include "Variables/String.h"
#include "Variables/Pointer.h"


class Interpreter
{
public:
	
	Interpreter(std::string robocode_file);

private:
	//В этом стеке находится номер позиции в коде, к которой необходимо вернуться в случае встречи return, finish или начала программы
	std::stack<int> call_stack;
	//В этом стеке хранятся контексты вызываемых функций
	std::stack<Function*> context_stack;

	std::vector<std::string> code;
	std::map<std::string, Function*> functions;
	

	

	void _build();
	
};