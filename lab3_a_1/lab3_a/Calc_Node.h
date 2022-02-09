#pragma once
#include <string>
#include "Var.h"
enum calc_node_type
{
	leaf_node, mul_node, div_node, mod_node, plus_node, sub_node, 
	eq_node, greater_node, less_node
};
enum bracket_type
{
	bracket_open, bracket_close, bracket_error
};

class Calc_Node
{
public:
	Calc_Node();
	Calc_Node(char sign, int index, std::string value, calc_node_type type);
	std::string get_value();
	std::string name;
	char sign;
	Var* var;
	int index;
	calc_node_type node_type;
	Calc_Node* parent_ptr;
	Calc_Node* left_child;
	Calc_Node* right_child;
	bool is_checked;
private:



};

