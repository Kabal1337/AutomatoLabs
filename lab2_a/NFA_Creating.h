#pragma once
#include <list>
#include <map>
#include <fstream>
#include "Syntax_Tree.h"
#include "NFA_Component.h"

class NFA_Creating
{
public:
	NFA_Creating(std::string regex);

	void draw_nfa_graph(std::string file_name);
	void draw_syntax_tree(std::string file_name);

	NFA_Node* get_start();
	NFA_Node* get_recieve();

	std::map<std::string, int> get_abc();
private:
	Syntax_Tree* stree;
	int nfa_nodes_id;
	NFA_Node* start;
	NFA_Node* recieve;
	std::list<NFA_Component*> graphs;
	std::map<std::string, int> abc;
	void build(Syntax_Node* node);
	void create_graph(Syntax_Node* node);

	void drawing(NFA_Node* node, std::ofstream* out);
	NFA_Component* find_graph(int index);
};