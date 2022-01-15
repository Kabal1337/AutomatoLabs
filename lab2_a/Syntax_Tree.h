#pragma once
#include <list>
#include <string>
#include <iostream>
#include <fstream>
#include "Syntax_Node.h"
#include <map>

enum bracket_type
{
	Open, Close
};

class Syntax_Tree
{
public:
	Syntax_Tree(std::string string);
	Syntax_Node* _get_root();
	Syntax_Node* _get_node(int index);
	void add_cat_str(std::string &str);
	bool check_bracket(int index);
	void draw_syntax_tree(std::string file_name);
	void creat_FP();
	
	std::vector<std::string> *get_alth();
	std::map <int, Syntax_Node*> nodes;
	std::map <int, std::vector<int>> FP;
	std::map <std::string, std::pair<int, int>> groups;
	std::string str;
private:
	
	void add_child(int parent_index, int child_index);
	void creat_node(std::string sign, std::vector<int> indexes, sign_type type);
	bool check_node(int index);
	void add_brackets(int open, int close);
	void process_opart(std::string *str);
	void find_repeat(std::string* str);
	void catch_groups(std::string& str);
	std::map<int, std::pair<int, bracket_type>> brackets;
	Syntax_Node* root;
	
	//Syntax_Node* std::vector<>





};