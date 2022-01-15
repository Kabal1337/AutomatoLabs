#pragma once
#include <vector>
#include "DFA_Node.h"
#include "Syntax_Tree.h"
class DFA
{
public:
	DFA(Syntax_Tree* tree);
	void node_process(DFA_Node* node, Syntax_Tree* tree);
	std::vector<std::string> alth;
	DFA_Node* enter_node;
	DFA_Node* exit_node;
	
	void add_node(DFA_Node* node);
	bool check_string(std::string str, Syntax_Tree* tree);
	void draw_dfa_graph(std::string file_name);
	void add_to_group(DFA_Node* node, Syntax_Tree* tree, char ch);
	void drawing(DFA_Node* node, std::ofstream* out);
	
	std::vector<DFA_Node*> nodes;
private:
	void set_exit_node(Syntax_Tree* tree);
	std::map <std::string, std::string> catch_groups;
};