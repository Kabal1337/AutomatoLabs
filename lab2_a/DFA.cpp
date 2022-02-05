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
	minimization();
}

DFA::DFA()
{

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

DFA_Node DFA::get_enter_node()
{
	return *enter_node;
}

DFA_Node DFA::get_exit_node()
{
	return *exit_node;
}

DFA* DFA::DFA_mul(DFA* dfa, Operation_Type type)
{

	DFA* dfa_mul = new DFA();
	
	for (int i = 0; i < alth.size(); i++)
	{
		for (int j = 0; j < dfa->alth.size(); j++)
		{
			if (alth[i] == dfa->alth[j])
			{
				dfa_mul->alth.push_back(alth[i]);
			}
		}
	}
	for (int i = 0; i < nodes.size(); i++)
	{
		for (int j = 0; j < dfa->nodes.size(); j++)
		{
			DFA_Node* node = new DFA_Node(nodes[i], dfa->nodes[j]);
			node->id = dfa_mul->nodes.size();
			dfa_mul->nodes.push_back(node);
		
		}
	}
	for (int i = 0; i < dfa_mul->nodes.size(); i++)
	{
		if (dfa_mul->nodes[i]->get_node1()->type_start && dfa_mul->nodes[i]->get_node2()->type_start)
		{
			dfa_mul->nodes[i]->type_start = true;
			dfa_mul->enter_node = dfa_mul->nodes[i];
		}
	}
	
	for (int i = 0; i < alth.size(); i++)
	{
		make_link_for_mul(dfa_mul->enter_node, dfa_mul);
	}
	del_mul_no_links(dfa_mul);
	/*for (int i = 0; i < dfa_mul->nodes.size(); i++)
	{
		for (int j = 0; j < alth.size(); j++)
		{
			if (dfa_mul->nodes[i]->get_node1()->links.count(alth[j]) != 0 && dfa_mul->nodes[i]->get_node2()->links.count(alth[j]) != 0)
			{


				DFA_Node* t_node1 = dfa_mul->nodes[i]->get_node1()->links[alth[j]];
				DFA_Node* t_node2 = dfa_mul->nodes[i]->get_node2()->links[alth[j]];
				for (int k = 0; k < dfa_mul->nodes.size(); k++)
				{
					if (dfa_mul->nodes[k]->get_node1() == t_node1 && dfa_mul->nodes[k]->get_node2() == t_node2)
					{
						dfa_mul->nodes[i]->make_link(dfa_mul->nodes[k], alth[j]);
					}
				}
			}
		}

	}*/
	if(type == Cross)
		dfa_mul->cross();
	if(type == Diff)
		dfa_mul->diff();
	return dfa_mul;
}
void DFA::del_mul_no_links(DFA* dfa_mul)
{
	for (auto it = dfa_mul->nodes.begin(); it != dfa_mul->nodes.end(); it++)
	{
		if ((*it)->links.size() == 0)
		{
			dfa_mul->nodes.erase(it);
			del_mul_no_links(dfa_mul);
			break;
		}
		
	}
}
void DFA::make_link_for_mul(DFA_Node* cur_node, DFA* dfa_mul)
{
	if(cur_node->links.size() == 0)
		for (int j = 0; j < alth.size(); j++)
		{
			if (cur_node->get_node1()->links.count(alth[j]) != 0 && cur_node->get_node2()->links.count(alth[j]) != 0)
			{


				DFA_Node* t_node1 = cur_node->get_node1()->links[alth[j]];
				DFA_Node* t_node2 = cur_node->get_node2()->links[alth[j]];
				for (int k = 0; k < dfa_mul->nodes.size(); k++)
				{
					if (dfa_mul->nodes[k]->get_node1() == t_node1 && dfa_mul->nodes[k]->get_node2() == t_node2)
					{
						cur_node->make_link(dfa_mul->nodes[k], alth[j]);
						DFA_Node* cur_node_t = dfa_mul->nodes[k];
						make_link_for_mul(cur_node_t, dfa_mul);
					}
				}
			}
			
		}

	
}
void DFA::draw_dfa_graph_mul(std::string file_name)
{
	if (this->enter_node == nullptr) return;

	std::ofstream* out = new std::ofstream(file_name);
	*out << "digraph G {" << std::endl;

	*out << "\"";
	/*for (int i = 0; i < enter_node->positions.size(); i++)
	{
		*out << enter_node->positions[i] << ",";
	}*/
	if (enter_node->get_node1() != NULL && enter_node->get_node2() != NULL)
		*out << enter_node->get_node1()->id << "," << enter_node->get_node2()->id;
	*out << "id:" << enter_node->id;
	*out << "\"" << " [label=\"";
	/*for (int i = 0; i < enter_node->positions.size(); i++)
	{
		*out << enter_node->positions[i] << ",";
	}*/
	if (enter_node->get_node1() != NULL && enter_node->get_node2() != NULL)
		*out << enter_node->get_node1()->id << "," << enter_node->get_node2()->id;
	*out << "id:" << enter_node->id;
	if (!enter_node->type_accept)
		*out << "\\nstart\"];" << std::endl;
	else
		*out << "\\nstart, accepting\"];" << std::endl;
	for (int i = 0; i < nodes.size(); i++)
	{

		if (nodes[i]->type_accept && !nodes[i]->type_start)
		{
			*out << "\"";
			if (nodes[i]->get_node1() != NULL && nodes[i]->get_node2() != NULL)
				*out << nodes[i]->get_node1()->id << "," << nodes[i]->get_node2()->id;
			*out << "id:" << nodes[i]->id;

			*out << "\"" << " [label=\"";
			if (nodes[i]->get_node1() != NULL && nodes[i]->get_node2() != NULL)
				*out << nodes[i]->get_node1()->id << "," << nodes[i]->get_node2()->id;
			*out << "id:" << nodes[i]->id;
			*out << "\\naccepting\"];" << std::endl;
		}
	}
	drawing_mul(this->enter_node, out);
	for (int i = 0; i < nodes.size(); i++)
	{
		nodes[i]->isChecked = false;
	}
	*out << "}";
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
	bool not_accepted = false;
	DFA_Node* cur_ptr = enter_node;
	for (int i = 0; i < str.size(); i++)
	{
		if (cur_ptr->type_accept) was_in_accept = true;
		std::string temp_char;
		if (i + 2 < str.size())
		{
			if (str[i] == '.' && str[i + 1] == '.' && str[i + 2] == '.')
			{
				temp_char.push_back(str[i]);
				temp_char.push_back(str[i + 1]);
				temp_char.push_back(str[i + 2]);
				i = i + 2;
			}
			else temp_char.push_back(str[i]);
		}
		else
		temp_char.push_back(str[i]);
		if (cur_ptr->links.count(temp_char) == 0)
		{
			if (!was_in_accept) search_str.clear();
			cur_ptr = enter_node;
			not_accepted = true;
		}
		else if (cur_ptr->links[temp_char]->positions.size() == 0)
		{
			if (!was_in_accept) search_str.clear();
			cur_ptr = enter_node;
			not_accepted = true;
		}
		else
		{
			if(!not_accepted)
			for (int j = 0; j < temp_char.size(); j++)
			{
				add_to_group(cur_ptr, tree, temp_char[j]);
			}
			
			if(!was_in_accept)
			for (int j = 0; j < temp_char.size(); j++)
			{
					search_str.push_back(temp_char[j]);
			}
			
			cur_ptr = cur_ptr->links[temp_char];
		}
		
		
	}
	if(!not_accepted)
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

void DFA::minimization()
{
	//минимизация дфа
	std::map<int, std::map<int, DFA_Node*>> pi_groups; //массив групп, в которых хрянятся узлы дфа
	std::map<int, DFA_Node*> accept; //принимающие
	std::map<int, DFA_Node*> not_accept; //не принимающие
	for (int i = 0; i < nodes.size(); i++)
	{
		if (nodes[i]->type_accept == true)
			accept[nodes[i]->id] = nodes[i];
		else
		{
			not_accept[nodes[i]->id] = nodes[i];
		}
	}
	std::map<int, DFA_Node*>* accept_ptr;
	std::map<int, DFA_Node*>* not_accept_ptr;
	accept_ptr = &accept;
	not_accept_ptr = &not_accept;
	pi_groups[pi_groups.size()] = accept;
	pi_groups[pi_groups.size()] = not_accept;
	
	min_group(accept_ptr, &pi_groups, &alth);
	min_group(not_accept_ptr, &pi_groups, &alth);
	//формирование нового нода
	
	for (auto it = pi_groups.begin(); it != pi_groups.end(); it++)
	{
		//создаем новый нод, удаляя старые из группы, у которой больше одного нода
		if (it->second.size() > 1)
		{
			int node_id_new = it->second.begin()->first;
			bool acc = false;
			bool start = false;
			std::vector<int> positions;
			for (auto it_n = it->second.begin(); it_n != it->second.end(); it_n++)
			{
				if (it_n->second->type_accept)
					acc = it_n->second->type_accept;

				if (it_n->second->type_start)
					start = it_n->second->type_start;

				for (int i = 0; i < it_n->second->positions.size(); i++)
				{
					bool have_this_pos = false;
					for (int j = 0; j < positions.size(); j++)
					{
						if (positions[j] == it_n->second->positions[i]) have_this_pos = true;
					}
					if (!have_this_pos) positions.push_back(it_n->second->positions[i]);

				}
			}
			DFA_Node* new_general_node = new DFA_Node(dfa_normal, positions);
			new_general_node->sort_pos();
			
			for (auto it_all_groups = pi_groups.begin(); it_all_groups != pi_groups.end(); it_all_groups++)
			{
				//добавление связей нодам, не относящимся к новому ноду
				if (it_all_groups->first != it->first)
				{
					for (auto it_all_groups_n = it_all_groups->second.begin(); it_all_groups_n != it_all_groups->second.end(); it_all_groups_n++)
					{
						for (auto it_link = it_all_groups_n->second->links.begin(); it_link != it_all_groups_n->second->links.end(); it_link++)
						{
							for (auto it_n = it->second.begin(); it_n != it->second.end(); it_n++)
							{
								if (it_link->second == it_n->second)
								{
									it_link->second = new_general_node;
								}
							}
							
						}
					}
				}
				//добавление связей новому ноду
				else
				{
					for (auto it_l = it->second.begin()->second->links.begin(); it_l != it->second.begin()->second->links.end(); it_l++)
					{
						bool in_our_groop = false;
						for (auto it_n = it->second.begin(); it_n != it->second.end(); it_n++)
						{	
							if (it_n->second->id == it_l->second->id)
							{
								in_our_groop = true;
								new_general_node->links[it_l->first] = new_general_node;
								break;
							}
							
						}
						if (!in_our_groop) new_general_node->links[it_l->first] = it_l->second;
					}
					//new_general_node->links = it->second.begin()->second->links;
					
				}
			}
			
			//удаление старых нодов
			int new_node_id = it->second.begin()->second->id;
			
			for (auto it_n = it->second.begin(); it_n != it->second.end(); it_n++)
			{
				for (int j = 0; j < nodes.size(); j++)
				{
					if (it_n->first == nodes[j]->id)
					{
						nodes.erase(nodes.begin()+j);
					}
				}
			}
			new_general_node->id = new_node_id;
			new_general_node->type_accept = acc;
			new_general_node->type_start = start;
			nodes.push_back(new_general_node);
		}
	}
}

void DFA::drawing_mul(DFA_Node* node, std::ofstream* out)
{
	if (node->isChecked) return;

	for (auto it = node->links.begin(); it != node->links.end(); it++)
	{
		*out << "\"";
		/*for (int i = 0; i < node->positions.size(); i++)
		{
			*out << node->positions[i] << ",";
		}*/
		if (node->get_node1() != NULL && node->get_node2() != NULL)
			*out << node->get_node1()->id << "," << node->get_node2()->id;
		*out << "id:" << node->id;
		*out << "\"" << " -> " << " \"";
		/*for (int i = 0; i < (*it).second->positions.size(); i++)
		{

			*out << (*it).second->positions[i] << ",";
		}*/
		if (it->second->get_node1() != NULL && it->second->get_node2() != NULL)
			*out << it->second->get_node1()->id << "," << it->second->get_node2()->id;
		*out << "id:" << it->second->id;
		*out << "\" "

			<< "[label=\"" << (*it).first << "\"];" << std::endl;
	}
	node->isChecked = true;

	for (auto it = node->links.begin(); it != node->links.end(); it++)
	{
		drawing_mul((*it).second, out);
	}
}

void DFA::cross()
{
	for (int i = 0; i < nodes.size(); i++)
	{
		if (nodes[i]->get_node1()->type_accept && nodes[i]->get_node2()->type_accept)
		{
			nodes[i]->type_accept = true;
		}
	}
}

void DFA::diff()
{
	for (int i = 0; i < nodes.size(); i++)
	{
		if (nodes[i]->get_node1()->type_accept && !nodes[i]->get_node2()->type_accept)
		{
			nodes[i]->type_accept = true;
		}
	}
}

std::string DFA::search()
{
	return search_str;
}

std::vector<DFA_Node*> DFA::get_nodes()
{
	return nodes;
}



void DFA::min_group(std::map<int, DFA_Node*>* group, std::map<int, std::map<int, DFA_Node*>>* pi_groups, std::vector<std::string>* alth)
{
	if (group->size() > 1)
	{
		for (int i = 0; i < alth->size(); i++) //проверяем по каждому знаку алфавита
		{
			std::map<int, std::pair<int, int>> node_trans; //переход из нода в нод по этой букве. pair: 1: группа нода, 2: сам нод
			for (auto it_n = group->begin(); it_n != group->end(); it_n++)
			{
				
				std::pair<int, int> p_temp;
				
				p_temp.second = it_n->second->links[alth->at(i)]->id;
				
				node_trans[it_n->first] = p_temp;
			}
			for (auto it_node_tr = node_trans.begin(); it_node_tr != node_trans.end(); it_node_tr++) //заполняем информацию в какую группу происхлдит переход нодов при данном знаке алфавита 
			{
				for (auto it_groups = pi_groups->begin(); it_groups != pi_groups->end(); it_groups++)
				{
					for (auto it_groups_n = it_groups->second.begin(); it_groups_n != it_groups->second.end(); it_groups_n++)
					{
						if (it_groups_n->first == it_node_tr->second.second) it_node_tr->second.first = it_groups->first;
					}
				}
			}
			std::map<int, std::map<int, DFA_Node*>> new_groups;
			for (auto it_node_tr = node_trans.begin(); it_node_tr != node_trans.end(); it_node_tr++)
			{
				if (new_groups.count(it_node_tr->second.first) == 0)
				{
					std::map<int, DFA_Node*> new_group;
					new_group[it_node_tr->first] = (*group)[it_node_tr->first];
					new_groups[it_node_tr->second.first] = new_group;
				}
				else
				{
					new_groups[it_node_tr->second.first][it_node_tr->first] = (*group)[it_node_tr->first];
				}
			}
			if (new_groups.size() > 1)
			{
				for (auto it_groups = pi_groups->begin(); it_groups != pi_groups->end(); it_groups++)
				{
					if (it_groups->second == *group)
					{
						pi_groups->at(it_groups->first) = new_groups[new_groups.begin()->first];
						auto it_new_gr = new_groups.begin();
						for (it_new_gr++; it_new_gr != new_groups.end(); it_new_gr++)
						{
							(*pi_groups)[pi_groups->size()] = it_new_gr->second;
							
						}
						for (auto it_new_gr = new_groups.begin(); it_new_gr != new_groups.end(); it_new_gr++)
						{
							min_group(&it_new_gr->second, pi_groups, alth);
						}
						break;
					}
				}
				break;
			}
		}
	}
	//std::vector<std::map<int, DFA_Node*>> new_groups;
	//for (auto temp_it = temp.begin(); temp_it != temp.end(); temp_it++)
	//{
	//	bool added_to_gr = false;
	//	if (new_groups.size() == 0) 
	//	{
	//		std::map<int, DFA_Node*> temp_group;
	//		temp_group[temp_it->first] = nodes[temp_it->first];
	//		new_groups.push_back(temp_group);
	//	}
	//	else
	//	{
	//		for (int j = 0; j < new_groups.size(); j++)
	//		{
	//			int group_id = -1; //id группы, к которой относится новая группа(new_group)
	//			for (auto it1 = pi_groups->begin(); it1 != pi_groups->end(); it1++)
	//			{
	//				for (auto it2 = it1->second.begin(); it2 != it1->second.end(); it2++)
	//				{
	//					if (new_groups[j].begin()->second->id == it2->first) //смотрим к какой группе относится первый элемент новой группы
	//					{
	//						group_id = it1->first;	
	//					}
	//				}

	//			}

	//			for (auto it = pi_groups->at(group_id).begin(); it != pi_groups->at(group_id).end(); it++)
	//			{
	//				if (it->first == temp_it->second)
	//				{
	//					new_groups[j][temp_it->first] = nodes[temp_it->first];	//добавляем нод в новую группу
	//					added_to_gr = true;
	//				}
	//			}
	//			if (added_to_gr) break;


	//		}
	//		if (added_to_gr == false) //если так и не добавили, то создаем новую 
	//		{
	//			std::map<int, DFA_Node*> temp_group;
	//			temp_group[temp_it->second] = nodes[temp_it->second];
	//			new_groups.push_back(temp_group);
	//		}
	//	}
	//	
	//}
	//if (new_groups.size() > 1) //если групп больше двух, то разбиваем обрабатываемую группу
	//{
	//	for (auto it = pi_groups->begin(); it != pi_groups->end(); it++)
	//	{
	//		if (it->second == *group) pi_groups->erase(it);
	//		for (int j = 0; j < new_groups.size(); j++)
	//		{
	//			pi_groups->at(pi_groups->size()) = new_groups[j];
	//			min_group(&pi_groups->at(pi_groups->size()-1), pi_groups, alth);
	//		}
	//	}
	//	
	//}
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
