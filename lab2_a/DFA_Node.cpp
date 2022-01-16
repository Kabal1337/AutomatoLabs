#include "DFA_Node.h"

DFA_Node::DFA_Node(DFA_node_type type, std::vector<int> positions)
{
	this->positions = positions;
	this->type_accept = false;
	this->type_normal = false;
	this->type_start = false;
	if(type == dfa_accepting)
		this->type_accept = true;
	if (type == dfa_start)
		this->type_start = true;
	if (type == dfa_normal)
		this->type_normal = true;
	this->isChecked = false;
}

void DFA_Node::sort_pos()
{
	for (int i = 0; i < positions.size(); i++)
	{
		for (int j = positions.size() - 1; j > i; j--)
		{
			if (positions[j-1] > positions[j])
			{
				int temp = positions[j - 1];
				positions[j- 1] = positions[j];
				positions[j] = temp;
			}
		}
	}
}

void DFA_Node::make_link(DFA_Node* to, std::string tr)
{
	this->links[tr] = to;
}
