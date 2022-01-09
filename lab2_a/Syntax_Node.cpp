#include "Syntax_Node.h"

Syntax_Node::Syntax_Node(std::string sign, std::vector<int> indexes, sign_type type)
{	
	this->isChecked = false;
	this->sign = sign;
	this->indexes = indexes;
	this->type = type;
	this->parent_ptr = nullptr;
	this->left_ptr = nullptr;
	this->right_ptr = nullptr;
	this->Nullable = false;
	
	/*if(type == a_node) this->Nullable = false;
	if (type == eps_node) this->Nullable = true;
	if (type == klyn_node) this->Nullable = true;*/

}
