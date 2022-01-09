#include "DFA.h"

DFA::DFA(Syntax_Tree* tree)
{
	enter_node = nullptr;
	exit_node = nullptr;
	DFA_Node* start_node = new DFA_Node(dfa_start, tree->_get_root()->First);
	enter_node = start_node;
	add_node(start_node);
	alth = *tree->get_alth();
	
	
}

void DFA::node_process(DFA_Node* node, Syntax_Tree* tree)
{
	for (int i = 0; i < alth.size(); i++)
	{
		std::vector<int> temp_pos;
		DFA_Node* node_new = new DFA_Node(dfa_normal, temp_pos);
		bool accept_new_node = false;
		for (int j = 0; j < node->positions.size(); j++)
		{
			
			if (alth[i] == tree->nodes[node->positions[j]]->sign)
			{
				accept_new_node = true;
				if (node_new->positions.size() == 0) node_new->positions = tree->FP[node->positions[j]];
				else 
				{
					for (int k = 0; k < tree->FP[node->positions[j]].size(); k++)
					{
						bool same = false;
						for (int m = 0; m < node_new->positions.size(); m++)
						{
							if (tree->FP[node->positions[j]][k] == node_new->positions[m]) same = true;
						}
						if (same == false) node_new->positions.push_back(tree->FP[node->positions[j]][k]);
					}
				}
				
			}
			
		}
		if (accept_new_node)
		{
			
			node->make_link(node_new, alth[i]);
			add_node(node_new);
			node_process(node_new, tree);
			
		}
	}
}

void DFA::add_node(DFA_Node* node)
{
	this->nodes.push_back(node);
}
