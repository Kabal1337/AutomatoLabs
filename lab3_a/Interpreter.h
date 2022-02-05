#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <regex>
#include <stack>

#include "Calculator/ST_Calculator.h"
#include "Function.h"
#include "Variables/Variable.h"
#include "Variables/String.h"
#include "Variables/Array.h"


class Interpreter
{
public:
	/*
	* ������ �������������� ������� � ���������� ���� �������: 
	* take_func (�������� ���������� � ��������) �
	* perform_body (��������� ��� ������ �������)
	*/
	Interpreter(std::string robocode_file, std::string labyrinth_file);

private:
	//� ���� ����� ��������� ����� ������� � ����, � ������� ���������� ��������� � ������ ������� return, finish ��� ������ ���������
	std::stack<int> pos_stack;
	//� ���� ����� �������� ��������� ���������� �������
	std::stack<Function*> context_stack;

	std::vector<std::string> code;
	std::map<std::string, Function*> functions;
	

	

	void take_funcs();
	void perform_body();
};