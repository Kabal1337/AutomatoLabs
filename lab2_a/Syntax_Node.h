#pragma once

#include <list>
#include <string>
#include <vector>
enum sign_type
{
	a_node, cat_node, klyn_node, opart_node, or_node
};
class Syntax_Node
{
public:
	Syntax_Node(std::string sign, std::vector<int> indexes, sign_type type);
	bool isChecked;

	std::string sign;
	std::vector<int> indexes;
	Syntax_Node* parent_ptr;
	Syntax_Node* left_ptr;
	Syntax_Node* right_ptr;
	sign_type type;
private:

};