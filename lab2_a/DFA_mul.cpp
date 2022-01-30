#include "DFA_mul.h"

DFA_mul::DFA_mul(DFA* dfa1, DFA* dfa2, Operation_Type type)
{
	for (int i = 0; i < dfa1->nodes.size(); i++)
	{
		for (int j = 0; j < dfa2->nodes.size(); j++)
		{
			DFA_mul_node* node = new DFA_mul_node(dfa1->nodes[i], dfa2->nodes[j]);
			
			nodes.push_back(node);
		}
	}
	for (int i = 0; i < nodes.size(); i++)
	{
		if (nodes[i]->get_node1()->type_start && nodes[i]->get_node2()->type_start)
		{
			nodes[i]->start = true;
			enter_node = nodes[i];
		}
	}
	for (int i = 0; i < nodes.size(); i++)
	{
		for (int j = 0; j < dfa1->alth.size(); j++)
		{
			if (nodes[i]->get_node1()->links[dfa1->alth[j]] != NULL && nodes[i]->get_node2()->links[dfa1->alth[j]] != NULL) 
			{


				DFA_Node* t_node1 = nodes[i]->get_node1()->links[dfa1->alth[j]];
				DFA_Node* t_node2 = nodes[i]->get_node2()->links[dfa1->alth[j]];
				for (int k = 0; k < nodes.size(); k++)
				{
					if (nodes[k]->get_node1() == t_node1 && nodes[k]->get_node2() == t_node2)
					{
						nodes[i]->make_link(nodes[k], dfa1->alth[j]);
					}
				}
			}
		}
	
	}
	if (type == Cross) cross();
	if (type == Diff) diff();
}

std::vector<DFA_mul_node*> DFA_mul::get_nodes()
{
	return nodes;
}

void DFA_mul::draw_dfa_graph(std::string file_name)
{
	if (this->enter_node == nullptr) return;

	std::ofstream* out = new std::ofstream(file_name);
	*out << "digraph G {" << std::endl;

	*out << "\"";
	/*for (int i = 0; i < enter_node->positions.size(); i++)
	{
		*out << enter_node->positions[i] << ",";
	}*/
	*out << enter_node->get_node1()->id << "," << enter_node->get_node2()->id;
	*out << "\"" << " [label=\"";
	/*for (int i = 0; i < enter_node->positions.size(); i++)
	{
		*out << enter_node->positions[i] << ",";
	}*/
	*out << enter_node->get_node1()->id << "," << enter_node->get_node2()->id;
	if (!enter_node->accepting)
		*out << "\\nstart\"];" << std::endl;
	else
		*out << "\\nstart, accepting\"];" << std::endl;
	for (int i = 0; i < nodes.size(); i++)
	{

		if (nodes[i]->accepting && !nodes[i]->start)
		{
			*out << "\"";
			*out << nodes[i]->get_node1()->id << "," << nodes[i]->get_node2()->id;

			*out << "\"" << " [label=\"";
			*out << nodes[i]->get_node1()->id << "," << nodes[i]->get_node2()->id;
			*out << "\\naccepting\"];" << std::endl;
		}
	}
	drawing(this->enter_node, out);

	*out << "}";
}

void DFA_mul::drawing(DFA_mul_node* node, std::ofstream* out)
{
	if (node->isChecked) return;

	for (auto it = node->get_links()->begin(); it != node->get_links()->end(); it++)
	{
		*out << "\"";
		/*for (int i = 0; i < node->positions.size(); i++)
		{
			*out << node->positions[i] << ",";
		}*/
		*out << node->get_node1()->id << "," << node->get_node2()->id;
		
		*out << "\"" << " -> " << " \"";
		/*for (int i = 0; i < (*it).second->positions.size(); i++)
		{

			*out << (*it).second->positions[i] << ",";
		}*/
		*out << it->second->get_node1()->id << "," << it->second->get_node2()->id;
		*out << "\" "

			<< "[label=\"" << (*it).first << "\"];" << std::endl;
	}
	node->isChecked = true;

	for (auto it = node->get_links()->begin(); it != node->get_links()->end(); it++)
	{
		drawing((*it).second, out);
	}
}



void DFA_mul::cross()
{
	for (int i = 0; i < nodes.size(); i++)
	{
		if (nodes[i]->get_node1()->type_accept && nodes[i]->get_node2()->type_accept)
		{
			nodes[i]->accepting = true;
		}
	}
}

void DFA_mul::diff()
{
	for (int i = 0; i < nodes.size(); i++)
	{
		if (nodes[i]->get_node1()->type_accept && !nodes[i]->get_node2()->type_accept)
		{
			nodes[i]->accepting = true;
		}
	}
}

