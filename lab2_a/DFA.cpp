#include "DFA.h"

DFA::DFA(Syntax_Tree* tree)
{
	enter_node = nullptr;
	exit_node = nullptr;
	DFA_Node* start_node = new DFA_Node(dfa_start, tree->_get_root()->First);
	enter_node = start_node;
	add_node(start_node);
	alth = *tree->get_alth();
	node_process(enter_node, tree);
	
	set_exit_node(tree);
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
			node_new->sort_pos();
			bool uniq_node = true;
			for (int l = 0; l < nodes.size(); l++)
			{
				if (nodes[l]->positions == node_new->positions)
				{
					uniq_node = false;
					node->make_link(nodes[l], alth[i]);
					
					break;
				}
			}
			if (uniq_node)
			{
				
				node->make_link(node_new, alth[i]);
				add_node(node_new);
				node_process(node_new, tree);
			}
		}
		else
		{
			bool have_empty = false;
			for (int j = 0; j < nodes.size(); j++)
			{
				if (nodes[j]->positions.size() == 0)
				{
					have_empty = true;
					node->make_link(nodes[j], alth[i]);
				}
			}
			if (!have_empty)
			{
				node->make_link(node_new, alth[i]);
				
				for (int j = 0; j < alth.size(); j++)
				{
					node_new->make_link(node_new, alth[j]);
				}
				nodes, add_node(node_new);
			}
		}
	}
	
}

void DFA::add_node(DFA_Node* node)
{
	node->id = nodes.size();
	this->nodes.push_back(node);
}

bool DFA::check_string(std::string str, Syntax_Tree* tree)
{
	search_str.clear();
	bool was_in_accept = false;
	DFA_Node* cur_ptr = enter_node;
	for (int i = 0; i < str.size(); i++)
	{
		if (cur_ptr->type_accept) was_in_accept = true;
		std::string temp_char;
		temp_char.push_back(str[i]);
		if (cur_ptr->links[temp_char] == NULL) 
			return false;
		else if (cur_ptr->links[temp_char]->positions.size() == NULL) 
			return false;
		else
		{
			add_to_group(cur_ptr, tree, str[i]);
			if(!was_in_accept)
			search_str.push_back(str[i]);
			cur_ptr = cur_ptr->links[temp_char];
		}
		
		
	}
	if(cur_ptr->type_accept == true)
		return true;
	else
	{
		return false;
	}
}
void DFA::add_to_group(DFA_Node* node, Syntax_Tree* tree, char ch)
{
	for (auto it = tree->groups.begin(); it != tree->groups.end(); it++)
	{
		for (int j = 0; j < node->positions.size(); j++)
		{
		
			if (node->positions[j] >= it->second.first && node->positions[j] <= it->second.second && tree->str[node->positions[j]] == ch)
			{
				if (catch_groups[it->first].empty())
				{
					std::string temp;
					temp.push_back(ch);
					catch_groups[it->first] = temp;
					break;
				}
				else
				{
					catch_groups[it->first].push_back(ch);
					break;
				}
			}
		}

	}
	
}

void DFA::draw_dfa_graph(std::string file_name)
{
	if (this->enter_node == nullptr) return;

	std::ofstream* out = new std::ofstream(file_name);
	*out << "digraph G {" << std::endl;

	*out << "\"";
	for (int i = 0; i < enter_node->positions.size(); i++)
	{
		*out << enter_node->positions[i] << ",";
	}
	*out << " id:" << enter_node->id << "; ";
	*out << "\"" << " [label=\"";
		for (int i = 0; i < enter_node->positions.size(); i++)
		{
			*out << enter_node->positions[i] << ",";
		}
		*out << " id:" << enter_node->id << "; ";
		if(!enter_node->type_accept)
			*out << "\\nstart\"];" << std::endl;
		else
			*out << "\\nstart, accepting\"];" << std::endl;
	for (int i = 0; i < nodes.size(); i++)
	{

		if (nodes[i]->type_accept && !nodes[i]->type_start)
		{
			*out << "\"";
			for (int j = 0; j < nodes[i]->positions.size(); j++)
			{
				*out << nodes[i]->positions[j] << ",";
			}
			*out << " id:" << nodes[i]->id << "; ";
			*out << "\"" << " [label=\"";
			for (int j = 0; j < nodes[i]->positions.size(); j++)
			{
				*out << nodes[i]->positions[j] << ",";
			}
			*out << " id:" << nodes[i]->id << "; ";
			*out << "\\naccepting\"];" << std::endl;
		}
	}
	/**out << "\"";
	for (int i = 0; i < exit_node->positions.size(); i++)
	{
		*out << exit_node->positions[i] << ",";
	}

	*out << "\"" << " [label=\"";
	for (int i = 0; i < exit_node->positions.size(); i++)
	{
		*out << exit_node->positions[i] << ",";
	}
	*out << "\\naccepting\"];" << std::endl;*/

	drawing(this->enter_node, out);

	*out << "}";
}



void DFA::drawing(DFA_Node* node, std::ofstream* out)
{
	if (node->isChecked) return;

	for (auto it = node->links.begin(); it != node->links.end(); it++)
	{
		*out << "\"";
		for (int i = 0; i < node->positions.size(); i++)
		{
			*out << node->positions[i] << ",";
		}
		*out << " id:" << node->id << "; ";
		*out << "\"" << " -> " << " \"";
		for (int i = 0; i < (*it).second->positions.size(); i++)
		{
			
			*out << (*it).second->positions[i] <<",";
		}
		*out << " id:" << (*it).second->id << "; ";
		*out << "\" "
			
			<< "[label=\""<<(*it).first << "\"];" << std::endl;
	}
	node->isChecked = true;

	for (auto it = node->links.begin(); it != node->links.end(); it++)
	{
		drawing((*it).second, out);
	}
}

std::string DFA::search()
{
	return search_str;
}

void DFA::set_exit_node(Syntax_Tree* tree)
{
	for (int i = 0; i < nodes.size(); i++)
	{
		for (int j = 0; j < nodes[i]->positions.size(); j++)
		{
			if (tree->nodes[nodes[i]->positions[j]]->sign == "#")
			{
				exit_node = nodes[i];
				exit_node->type_accept = true;
				
			}
		}
	}
}
