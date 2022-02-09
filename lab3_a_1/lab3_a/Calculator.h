#pragma once
#include <string>
#include <map>
#include "Calc_Node.h"
#include <vector>
class Calculator
{
public:
	Calculator(std::string expression);
	void add_brackets(int open, int close);

private:
	std::map<int, Calc_Node> nodes;
	std::vector<std::pair<int, bracket_type>> brackets;
};

