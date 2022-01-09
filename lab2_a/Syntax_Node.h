#pragma once

#include <list>
#include <string>
#include <vector>
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
enum sign_type
{
	a_node, cat_node, klyn_node, opart_node, or_node, eps_node
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
	bool Nullable;
	std::vector<int> First;
	std::vector<int> Last;
private:

};