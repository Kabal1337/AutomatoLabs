
#include "NFA_Component.h"

NFA_Component::NFA_Component(int index)
{
	this->enter_node = nullptr;
	this->exit_node = nullptr;
	this->index = index;
}

void NFA_Component::add_node(NFA_Node* node)
{
	this->nodes.push_back(node);
}

void NFA_Component::delete_node(NFA_Node* node)
{
	for (auto it = this->nodes.begin(); it != this->nodes.end(); it++)
	{
		if ((*it) == node)
		{
			this->nodes.erase(it);
			break;
		}
	}
}