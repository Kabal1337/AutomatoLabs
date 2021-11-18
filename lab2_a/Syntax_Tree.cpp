#include "Syntax_Tree.h"

Syntax_Tree::Syntax_Tree(std::string string)
{
	int first_index;
	int last_index;
	
	
	std::string str = "(" + string + ")";
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
			
			if (str[i] != '.' && str[i] != '?' && str[i] != '|' && str[i] != '%' && str[i]!=' ')
			{
				std::vector<int> temp;
				temp.push_back(i);
				std::string temp1;
				temp1.push_back(str[i]);
				creat_node(temp1, temp, a_node);
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
				i += 2;

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
			if(check_node(i))
			{
			
				if (check_node(i + 1))
				{
					if (nodes[i + 1]->type == a_node)
					{
						std::vector<int> temp;
						temp.push_back(-i);
						temp.push_back(i + 1);
						creat_node("cat", temp, cat_node);
						str[i] = ' ';
						add_child(-i, i);
						add_child(-i, i + 1);
					}

				}
				else
				{
					int j = i+1;
					while (j <= last_index)
					{
						if (check_node(j + 1)) 
						{
							if (nodes[j + 1]->type == a_node)
							{
								std::vector<int> temp;
								temp.push_back(-i);
								temp.push_back(j + 1);
								creat_node("cat", temp, cat_node);
								str[i] = ' ';
								add_child(-i, i);
								add_child(-i, j + 1);
							}
							break;
						}

						j++;
					}
				}
			}
			else
			if (check_bracket(i)) 
			{
				if (brackets[i].second == Open)
				{
					while (1)
					{
						if (check_bracket(i))
							if (brackets[i].second == Close) break;
						i++;
					}
				}
				if (check_node(i + 1))
				{
					if (nodes[i + 1]->type == a_node)
					{
						std::vector<int> temp;
						temp.push_back(-i);
						temp.push_back(i + 1);
						creat_node("cat", temp, cat_node);
						str[i] = ' ';
						add_child(-i, i);
						add_child(-i, i + 1);
					}

				}
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
			}
		}
		str[first_index-1] = ' ';
		str[last_index+1] = ' ';
	}
	while (last_index != 0 && first_index != 0);
		
	this->root = _get_root();
	
	
}

Syntax_Node* Syntax_Tree::_get_node(int index)
{
	return nodes[index];
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
			if (brackets[real_child_index].second == Open)
			{
				real_child_index++;

			}
			else real_child_index--;
		}
		else
		while (check_node(real_child_index))
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
	
	nodes[indexes[0]] = temp;
	
}
bool Syntax_Tree::check_node(int index)
{
	if (nodes.find(index) == nodes.end()) {
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