#pragma once
#include <vector>
#include "DFA_Node.h"
#include "DFA.h"
class DFA_to_reg
{
public:
	DFA_to_reg(DFA* dfa);
	std::string K_path(int i, int j, int k);
	std::string regex;
private:
	std::map <int, DFA_Node*> nodes;
};