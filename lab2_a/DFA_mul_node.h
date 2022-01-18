#pragma once
#include "DFA_Node.h"
class DFA_mul_node
{
public:
	DFA_mul_node(DFA_Node* node1, DFA_Node* node2);
	bool accepting;
	bool start;
	DFA_Node* get_node1();
	DFA_Node* get_node2();
	std::map<std::string, DFA_mul_node*>* get_links();
	void make_link(DFA_mul_node* to, std::string tr);
	bool isChecked;
private:

	DFA_Node* node1;
	DFA_Node* node2;
	std::map<std::string, DFA_mul_node*> links;
};



