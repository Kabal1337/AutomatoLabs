#include "DFA_mul_node.h"
DFA_mul_node::DFA_mul_node(DFA_Node* node1, DFA_Node* node2)
{
	this->node1 = node1;
	this->node2 = node2;
	accepting = false;
	start = false;
	isChecked = false;
}

DFA_Node* DFA_mul_node::get_node1()
{
	return node1;
}

DFA_Node* DFA_mul_node::get_node2()
{
	return node2;
}

std::map<std::string, DFA_mul_node*>* DFA_mul_node::get_links()
{
	return &links;
}

void DFA_mul_node::make_link(DFA_mul_node* to, std::string tr)
{
	links[tr] = to;
}
