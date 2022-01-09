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
	DFA_node_type type;

	bool isChecked;
	

	void make_link(DFA_Node* to, std::string tr);
	std::vector<int> positions;
	std::map<std::string, DFA_Node*> links;

private:
};