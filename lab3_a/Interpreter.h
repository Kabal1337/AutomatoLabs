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
	/*
	* ������ �������������� ������� � ���������� ���� �������: 
	* Collect (�������� ���������� � ��������)
	* �
	* Built (��������� ��� ������ �������)
	*/
	Interpreter(std::string robocode_file);

private:
	//� ���� ����� ��������� ����� ������� � ����, � ������� ���������� ��������� � ������ ������� return, finish ��� ������ ���������
	std::stack<int> call_stack;
	//� ���� ����� �������� ��������� ���������� �������
	std::stack<Function*> context_stack;

	std::vector<std::string> code;
	std::map<std::string, Function*> functions;
	

	

	void _collect();
	
};