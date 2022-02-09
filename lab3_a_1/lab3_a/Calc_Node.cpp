#include "Calc_Node.h"

Calc_Node::Calc_Node()
{
	this->is_checked = false;
	this->parent_ptr = nullptr;
	this->left_child = nullptr;
	this->right_child = nullptr;
}

Calc_Node::Calc_Node(char sign, int index, std::string name, calc_node_type type)
{
	this->is_checked = false;
	this->sign = sign;
	this->index = index;
	this->node_type = type;
	this->parent_ptr = nullptr;
	this->left_child = nullptr;
	this->right_child = nullptr;
	this->name = name;
}

std::string Calc_Node::get_value()
{
	return name;
}
