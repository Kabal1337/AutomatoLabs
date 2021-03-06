#pragma once
#include <vector>
#include <map>
#include <string>
enum DFA_node_type
{
	dfa_start, dfa_accepting, dfa_normal
};
class DFA_Node
{
public:
	DFA_Node(DFA_node_type type, std::vector<int> positions);
	DFA_Node(DFA_Node* node1, DFA_Node* node2);
	bool type_accept;
	bool type_normal;
	bool type_start;
	int id;
	bool isChecked;
	void sort_pos();
	DFA_Node* get_node1();
	DFA_Node* get_node2();
	void make_link(DFA_Node* to, std::string tr);
	std::vector<int> positions;
	std::map<std::string, DFA_Node*> links;
	void set_node1(DFA_Node* node1);
	void set_node2(DFA_Node* node2);
private:
	DFA_Node* node1;
	DFA_Node* node2;
};