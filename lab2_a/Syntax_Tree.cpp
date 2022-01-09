#include "Syntax_Tree.h"

Syntax_Tree::Syntax_Tree(std::string string)
{
	int first_index;
	int last_index;
	
	
	std::string str = "(" + string + "#" + ")";
	add_cat_str(str);
	
	do
	{
		first_index = 0;
		last_index = 0;

		for (int i = 0; i < str.length(); i++)
		{
			

			if (str[i] == '(')
			{
				first_index = i+1;
			}
			if (str[i] == ')')
			{
				last_index = i-1;
				break;
			}
		}
		if (first_index == 0 && last_index == 0) break;
		str[first_index-1] = ' ';
		str[last_index+1] = ' ';
		add_brackets(first_index - 1, last_index + 1);

		for (int i = first_index; i <= last_index; i++)
		{
			
			if (str[i] != '.' && str[i] != '?' && str[i] != '|' && str[i] != '%' && str[i]!=' ' && str[i] != '#' && str[i] != '@')
			{
				std::vector<int> temp;
				temp.push_back(i);
				std::string temp1;
				temp1.push_back(str[i]);
				creat_node(temp1, temp, a_node);
				_get_node(i)->Nullable = false;
				
				str[i] = ' ';

			}
			else
				if ((str[i] == '.') && (str[i + 1] == '.') && (str[i + 2] == '.')) i += 2;
				else
			if ((str[i] == '.') && ((str[i + 1] != '.') || (str[i + 2] != '.')))
			{
				std::vector<int> temp;
				temp.push_back(i);
				creat_node(".", temp, a_node);
				_get_node(i)->Nullable = false;
				
				str[i] = ' ';
			}
			if (str[i] == '#')
			{
				std::vector<int> temp;
				temp.push_back(i);
				std::string temp1;
				temp1.push_back(str[i]);
				creat_node(temp1, temp, eps_node);
				_get_node(i)->Nullable = false;
				
				str[i] = ' ';
			}
		}


		for (int i = first_index; i <= last_index; i++)
		{
			if ((str[i] == '.') && (str[i + 1] == '.') && (str[i + 2] == '.'))
			{
				std::vector<int> temp;
				temp.push_back(i);
				temp.push_back(i + 1);
				temp.push_back(i + 2);
				creat_node("...", temp, klyn_node);
				str[i] = ' ';
				str[i + 1] = ' ';
				str[i + 2] = ' ';
				add_child(i, i - 1);
				_get_node(i)->Nullable = true;
				int real_child_index = i - 1;
				
					_get_node(i)->First = _get_node(i)->left_ptr->First;
					_get_node(i)->Last = _get_node(i)->left_ptr->Last;
				
				i += 2;
			}
		}
		for (int i = first_index; i <= last_index; i++)
		{
			if (str[i] == '|')
			{
				std::vector<int> temp;
				temp.push_back(i);
				creat_node("|", temp, or_node);
				str[i] = ' ';
				add_child(i, i - 1);
				add_child(i, i + 1);
				_get_node(i)->Nullable = _get_node(i)->left_ptr->Nullable || _get_node(i)->right_ptr->Nullable;
				for (int j = 0; j < _get_node(i)->left_ptr->First.size(); j++)
				{
					_get_node(i)->First.push_back(_get_node(i)->left_ptr->First[j]);
				}

				for (int j = 0; j < _get_node(i)->right_ptr->First.size(); j++)
				{
					_get_node(i)->First.push_back(_get_node(i)->right_ptr->First[j]);
				}
				for (int j = 0; j < _get_node(i)->right_ptr->Last.size(); j++)
				{
					_get_node(i)->Last.push_back(_get_node(i)->right_ptr->Last[j]);
				}

				for (int j = 0; j < _get_node(i)->left_ptr->Last.size(); j++)
				{
					_get_node(i)->Last.push_back(_get_node(i)->left_ptr->Last[j]);
				}
			}
		}
		for (int i = first_index; i <= last_index; i++)
		{
			if (str[i] == '?')
			{
				std::vector<int> temp;
				temp.push_back(i);
				creat_node("?", temp, opart_node);
				str[i] = ' ';
				add_child(i, i - 1);
			}
		}
		for (int i = first_index; i <= last_index; i++)
		{
			if (str[i] == '@')
			{
				std::vector<int> temp;
				temp.push_back(i);
				creat_node("cat", temp, cat_node);
				str[i] = ' ';
				add_child(i, i - 1);
				add_child(i, i + 1);
				for (int j = 0; j < _get_node(i)->left_ptr->First.size(); j++)
				{
					_get_node(i)->First.push_back(_get_node(i)->left_ptr->First[j]);
				}
				if (_get_node(i)->left_ptr->Nullable == true)
					for (int j = 0; j < _get_node(i)->right_ptr->First.size(); j++)
					{
						_get_node(i)->First.push_back(_get_node(i)->right_ptr->First[j]);
					}
				for (int j = 0; j < _get_node(i)->right_ptr->Last.size(); j++)
				{
					_get_node(i)->Last.push_back(_get_node(i)->right_ptr->Last[j]);
				}
				if (_get_node(i)->right_ptr->Nullable == true)
					for (int j = 0; j < _get_node(i)->left_ptr->Last.size(); j++)
					{
						_get_node(i)->Last.push_back(_get_node(i)->left_ptr->Last[j]);
					}
			}
			//if(check_node(i))
			//{
			//
			//	if (check_node(i + 1))
			//	{
			//		if (nodes[i + 1]->type == a_node)
			//		{
			//			std::vector<int> temp;
			//			temp.push_back(-i);
			//			temp.push_back(i + 1);
			//			creat_node("cat", temp, cat_node);
			//			str[i] = ' ';
			//			add_child(-i, i);
			//			add_child(-i, i + 1);
			//			_get_node(-i)->Nullable = _get_node(-i)->left_ptr->Nullable && _get_node(-i)->right_ptr->Nullable;
			//			for (int j = 0; j < _get_node(-i)->left_ptr->First.size(); j++)
			//			{
			//				_get_node(-i)->First.push_back(_get_node(-i)->left_ptr->First[j]);
			//			}
			//			if (_get_node(-i)->left_ptr->Nullable == true)
			//				for (int j = 0; j < _get_node(-i)->right_ptr->First.size(); j++)
			//				{
			//					_get_node(-i)->First.push_back(_get_node(-i)->right_ptr->First[j]);
			//				}
			//			for (int j = 0; j < _get_node(-i)->right_ptr->Last.size(); j++)
			//			{
			//				_get_node(-i)->Last.push_back(_get_node(-i)->right_ptr->Last[j]);
			//			}
			//			if (_get_node(-i)->right_ptr->Nullable == true)
			//				for (int j = 0; j < _get_node(-i)->left_ptr->Last.size(); j++)
			//				{
			//					_get_node(-i)->Last.push_back(_get_node(-i)->left_ptr->Last[j]);
			//				}

			//		}

			//	}
			//	/*else
			//	{
			//		int j = i+1;
			//		while (j <= last_index)
			//		{
			//			if (check_node(j + 1)) 
			//			{
			//				if (nodes[j + 1]->type == a_node)
			//				{
			//					std::vector<int> temp;
			//					temp.push_back(-i);
			//					temp.push_back(j + 1);
			//					creat_node("cat", temp, cat_node);
			//					str[i] = ' ';
			//					add_child(-i, i);
			//					add_child(-i, j + 1);
			//					_get_node(-i)->Nullable = _get_node(-i)->left_ptr->Nullable && _get_node(-i)->right_ptr->Nullable;
			//					for (int j = 0; j < _get_node(-i)->left_ptr->First.size(); j++)
			//					{
			//						_get_node(-i)->First.push_back(_get_node(-i)->left_ptr->First[j]);
			//					}
			//					if (_get_node(-i)->left_ptr->Nullable == true)
			//						for (int j = 0; j < _get_node(-i)->right_ptr->First.size(); j++)
			//						{
			//							_get_node(-i)->First.push_back(_get_node(-i)->right_ptr->First[j]);
			//						}
			//					for (int j = 0; j < _get_node(-i)->right_ptr->Last.size(); j++)
			//					{
			//						_get_node(-i)->Last.push_back(_get_node(-i)->right_ptr->Last[j]);
			//					}
			//					if (_get_node(-i)->right_ptr->Nullable == true)
			//						for (int j = 0; j < _get_node(-i)->left_ptr->Last.size(); j++)
			//						{
			//							_get_node(-i)->Last.push_back(_get_node(-i)->left_ptr->Last[j]);
			//						}
			//				}
			//				break;
			//			}

			//			j++;
			//		}
			//	}*/
			//}
			//else
			//if (check_bracket(i)) 
			//{
			//	if (brackets[i].second == Close)
			//	{

			//		
			//		if (check_node(i + 1))
			//		{
			//			if (nodes[i + 1]->type == a_node)
			//			{
			//				std::vector<int> temp;
			//				temp.push_back(-i);
			//				temp.push_back(i + 1);
			//				creat_node("cat", temp, cat_node);
			//				str[i] = ' ';
			//				add_child(-i, i);
			//				add_child(-i, i + 1);
			//				_get_node(-i)->Nullable = _get_node(-i)->left_ptr->Nullable && _get_node(-i)->right_ptr->Nullable;
			//				for (int j = 0; j < _get_node(-i)->left_ptr->First.size(); j++)
			//				{
			//					_get_node(-i)->First.push_back(_get_node(-i)->left_ptr->First[j]);
			//				}
			//				if (_get_node(-i)->left_ptr->Nullable == true)
			//					for (int j = 0; j < _get_node(-i)->right_ptr->First.size(); j++)
			//					{
			//						_get_node(-i)->First.push_back(_get_node(-i)->right_ptr->First[j]);
			//					}
			//				for (int j = 0; j < _get_node(-i)->right_ptr->Last.size(); j++)
			//				{
			//					_get_node(-i)->Last.push_back(_get_node(-i)->right_ptr->Last[j]);
			//				}
			//				if (_get_node(-i)->right_ptr->Nullable == true)
			//					for (int j = 0; j < _get_node(-i)->left_ptr->Last.size(); j++)
			//					{
			//						_get_node(-i)->Last.push_back(_get_node(-i)->left_ptr->Last[j]);
			//					}
			//			}

			//		}
			//	}
			//}
			

		}

		
		str[first_index-1] = ' ';
		str[last_index+1] = ' ';
	}
	while (last_index != 0 && first_index != 0);
		
	this->root = _get_root();
	creat_FP();
	/*for (auto it = nodes.begin(); it != nodes.end(); ++it)
	{
		
		if (it->second->type == cat_node)
		{
			it->second->Nullable = it->second->left_ptr->Nullable && it->second->right_ptr->Nullable;
			if (it->second->left_ptr->Nullable == true)
			{
				for (int i = 0; i < it->second->left_ptr->First.size(); i++)
				{
					it->second->First.push_back(it->second->left_ptr->First[i]);
				}
				for (int i = 0; i < it->second->right_ptr->First.size(); i++)
				{
					it->second->First.push_back(it->second->right_ptr->First[i]);
				}
				
			}
			else it->second->First = it->second->left_ptr->First;
			
			if (it->second->left_ptr->Nullable == true)
			{
				for (int i = 0; i < it->second->left_ptr->Last.size(); i++)
				{
					it->second->Last.push_back(it->second->left_ptr->Last[i]);
				}
				for (int i = 0; i < it->second->right_ptr->Last.size(); i++)
				{
					it->second->Last.push_back(it->second->right_ptr->Last[i]);
				}
			}
			else it->second->Last = it->second->left_ptr->Last;
		}
		if (it->second->type == or_node)
		{
			it->second->Nullable = it->second->left_ptr->Nullable || it->second->right_ptr->Nullable;

			for (int i = 0; i < it->second->left_ptr->First.size(); i++)
			{
				it->second->First.push_back(it->second->left_ptr->First[i]);
			}
			for (int i = 0; i < it->second->right_ptr->First.size(); i++)
			{
				it->second->First.push_back(it->second->right_ptr->First[i]);
			}

			for (int i = 0; i < it->second->left_ptr->Last.size(); i++)
			{
				it->second->Last.push_back(it->second->left_ptr->Last[i]);
			}
			for (int i = 0; i < it->second->right_ptr->Last.size(); i++)
			{
				it->second->Last.push_back(it->second->right_ptr->Last[i]);
			}
		}
		if (it->second->type == klyn_node)
		{
			it->second->Nullable = true;
			it->second->First = it->second->left_ptr->First;
			it->second->Last = it->second->left_ptr->Last;
		}
	}*/
	
}

Syntax_Node* Syntax_Tree::_get_node(int index)
{
	return nodes[index];
}

void Syntax_Tree::add_cat_str(std::string &str)
{
	for (int i = 0; i < str.size() - 1; i++)
	{
		if (str[i] != '?' && str[i] != '|' && str[i] != '%' && str[i] != ' ' && str[i] != '#' && str[i] != '@' && str[i] != '(')
		{	
			if (i + 2 < str.size() - 1)
				if (str[i] == '.' && str[i + 1] == '.' && str[i + 2] == '.') i += 2;
			if (str[i + 1] != '.' && str[i + 1] != '?' && str[i + 1] != '|' && str[i + 1] != '%' && str[i + 1] != ' ' && str[i+1] != '@' && str[i+1] != ')')
			{
				str.insert(i + 1, "@");
				add_cat_str(str);
				break;
			}
		}
	}
	
}




Syntax_Node* Syntax_Tree::_get_root()
{
	auto it = nodes.begin();
	Syntax_Node* temp = it->second;
		

	while (temp->parent_ptr != nullptr)
	{
		temp = temp->parent_ptr;
	}

	return temp;
}
void Syntax_Tree::add_child(int parent_index, int child_index)
{
	Syntax_Node* parent = _get_node(parent_index);
	int real_child_index = child_index;
	if (!check_node(real_child_index)) {
		if (check_bracket(real_child_index))
		{
			while (!check_node(real_child_index))
			{
				if (brackets[real_child_index].second == Open)
				{
					real_child_index++;

				}
				else real_child_index--;

			}
		}
		else
		while (!check_node(real_child_index))
		{
			real_child_index--;
		}
	}
	
		
	Syntax_Node* child = _get_node(real_child_index);
	while (child->parent_ptr != nullptr)
	{
		child = child->parent_ptr;
	}
	if (parent->left_ptr == nullptr)
	{
		parent->left_ptr = child;
	}
	else parent->right_ptr = child;

	child->parent_ptr = parent;
}
bool  Syntax_Tree::check_bracket(int index)
{
	if (brackets.find(index) == brackets.end()) {
		return false;
	}
	else return true;
}
void Syntax_Tree::creat_node(std::string sign, std::vector<int> indexes, sign_type type)
{
	Syntax_Node* temp = new Syntax_Node(sign, indexes, type);
	
	if (type == eps_node)
	{
		temp->Nullable = true;
		temp->First.push_back(indexes[0]);
		temp->Last.push_back(indexes[0]);
	}
	if (type == a_node)
	{
		temp->Nullable = false;
		temp->First.push_back(indexes[0]);
		temp->Last.push_back(indexes[0]);
	}
	nodes[indexes[0]] = temp;
	
}
bool Syntax_Tree::check_node(int index)
{
	if (nodes.find(index) == nodes.end()) 
	{
		return false;
	}
	else return true;
}
void Syntax_Tree::add_brackets(int open, int close)
{
	std::pair<int, bracket_type> t1 = { open, Open };
	std::pair<int, bracket_type> t2 = { close, Close };
	this->brackets[open] = t1;
	this->brackets[close] = t2;
}
void Syntax_Tree::draw_syntax_tree(std::string file_name)
{
	
	if (this->root == nullptr) return;
	std::ofstream* out = new std::ofstream(file_name);

	*out << "digraph G {" << std::endl;

	if ((this->root)->left_ptr == nullptr && (this->root)->right_ptr == nullptr)
	{
		*out << "\"" << "id:" << (this->root)->indexes[0] << " " << (this->root)->sign << "\"" << std::endl;
		*out << "}";
		return;
	}
	
	for (auto it = this->nodes.begin(); it != this->nodes.end(); it++)
	{
		if (it->second->left_ptr != nullptr)
		{
			*out << "\"" << "id:" << it->second->indexes[0] << " " << it->second->sign << "\"" << " -> " << "\"" << "id:" << it->second->left_ptr->indexes[0] << " " << it->second->left_ptr->sign << "\"" << std::endl;
		}
		if (it->second->right_ptr != nullptr)
		{
			*out << "\"" << "id:" << it->second->indexes[0] << " " << it->second->sign << "\"" << " -> " << "\"" << "id:" << it->second->right_ptr->indexes[0] << " " << it->second->right_ptr->sign << "\"" << std::endl;
		}
	}

	*out << "}";

}

void Syntax_Tree::creat_FP()
{
	for (auto it = nodes.begin(); it != nodes.end(); it++)
	{
		if (it->second->type == a_node || it->second->type == eps_node)
		{
			std::vector<int> temp;
			FP[it->second->indexes[0]] = temp;
		}
	}
	for (auto it = nodes.begin(); it != nodes.end(); it++)
	{
		if (it->second->type == cat_node)
		{
			for (int i = 0; i < it->second->left_ptr->Last.size(); i++)
			{
				for (int j = 0; j < it->second->right_ptr->First.size(); j++)
				{
					FP[it->second->left_ptr->Last[i]].push_back(it->second->right_ptr->First[j]);
				}
				
			}
			
		}
		if (it->second->type == klyn_node)
		{
			for (int i = 0; i < it->second->left_ptr->Last.size(); i++)
			{
				for (int j = 0; j < it->second->left_ptr->First.size(); j++)
				{
					FP[it->second->left_ptr->Last[i]].push_back(it->second->left_ptr->First[j]);
				}

			}
		}
	}
}

std::vector<std::string>* Syntax_Tree::get_alth()
{
	std::vector<std::string> *alth = new std::vector<std::string>();
	for (auto it = nodes.begin(); it != nodes.end(); it++)
	{	
		
		
		if (it->second->type == a_node)
		{
			bool uniq = true;
			for (int i = 0; i < alth->size(); i++)
			{
				if (it->second->sign == (*alth)[i]) uniq = false;
			}
			if (uniq) alth->push_back(it->second->sign);
		}
	}
	return alth;
}
