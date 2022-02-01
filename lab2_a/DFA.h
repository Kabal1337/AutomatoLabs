#pragma once
#include <vector>
#include "DFA_Node.h"
#include "Syntax_Tree.h"
enum Operation_Type
{
	Cross, Diff
};
class DFA
{
public:
	DFA(Syntax_Tree* tree);
	DFA();
	void node_process(DFA_Node* node, Syntax_Tree* tree);
	std::vector<std::string> alth;
	DFA_Node get_enter_node();
	DFA_Node get_exit_node();
	DFA* DFA_mul(DFA* dfa, Operation_Type type);
	void add_node(DFA_Node* node);
	bool check_string(std::string str, Syntax_Tree* tree);
	void draw_dfa_graph(std::string file_name);
	void add_to_group(DFA_Node* node, Syntax_Tree* tree, char ch);
	void drawing(DFA_Node* node, std::ofstream* out);
	void min_group(std::map<int, DFA_Node*>* group, std::map<int, std::map<int, DFA_Node*>>* pi_groups, std::vector<std::string>* alth);
	std::string search();
	std::vector<DFA_Node*> get_nodes();
	void make_link_for_mul(DFA_Node* cur_node, DFA* dfa_mul);
	void minimization();
	void draw_dfa_graph_mul(std::string file_name);
private:
	void del_mul_no_links(DFA* dfa_mul);
	DFA_Node* enter_node;
	DFA_Node* exit_node;
	std::vector<DFA_Node*> nodes;
	void drawing_mul(DFA_Node* node, std::ofstream* out);
	void cross();
	void diff();
	void set_exit_node(Syntax_Tree* tree);
	std::map <std::string, std::string> catch_groups;
	std::string search_str;
};