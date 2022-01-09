#include "DFA_Node.h"

DFA_Node::DFA_Node(DFA_node_type type, std::vector<int> positions)
{
	this->positions = positions;
	this->type = type;
	this->isChecked = false;
}

void DFA_Node::make_link(DFA_Node* to, std::string tr)
{
	this->links[tr] = to;
}
