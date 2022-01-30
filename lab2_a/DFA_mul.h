#pragma once
#include "DFA.h"
#include "DFA_mul_node.h"



class DFA_mul
{
public:
	DFA_mul(DFA* dfa1, DFA* dfa2, Operation_Type type);
	std::vector<DFA_mul_node*> get_nodes();
	void draw_dfa_graph(std::string file_name);
	void drawing(DFA_mul_node* node, std::ofstream* out);
	
	
private:

	std::vector<DFA_mul_node*> nodes;
	DFA_mul_node* enter_node;
	void cross();
	void diff();
	
};



