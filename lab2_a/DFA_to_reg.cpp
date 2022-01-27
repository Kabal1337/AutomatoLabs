#include "DFA_to_reg.h"

DFA_to_reg::DFA_to_reg(DFA *dfa)
{	
	int j = 1;
	for (int i = 0; i < dfa->nodes.size(); i++)
	{
		this->nodes[j] = dfa->nodes[i];
		nodes[j]->id = j;
		j++;
	}
	
	for (int i = 1; i <= nodes.size(); i++)
	{
		
		if (nodes[i]->type_start == true)
		{
			
			for (int j = 1; j <= nodes.size(); j++)
			{
				if (nodes[j]->type_accept == true)
				{
					if (!regex.empty()) regex = regex + "|";
					regex = "(" + regex + K_path(i, j, nodes.size()) + ")";
				}
			}
			break;
		}
	}
}

std::string DFA_to_reg::K_path(int i, int j, int k)
{
	if (k == 0)
	{
		std::string reg;
		for (auto it = nodes[i]->links.begin(); it != nodes[i]->links.end(); it++)
		{
			if (it->second->id == nodes[j]->id) 
			{
				
					if (reg.size() == 0) reg.push_back(it->first[0]);
					else reg = reg + "|" + it->first[0];
					
				
			}
		}
		if (i == j)
		{
			if (!reg.empty())
				reg = "^|" + reg;
			else
				reg = "^";
		}
		//if (reg.size() > 1) reg = "(" + reg + ")";
		return reg;
	}
	else
	{
		std::string reg1 = K_path(i, j, k - 1);
		std::string reg2 = K_path(i, k, k - 1);
		std::string reg3 = K_path(k, k, k - 1);
		std::string reg4 = K_path(k, j, k - 1);
		std::string reg_f;
		if (!reg1.empty())
		{	
			//if (reg1.size() > 1) reg1 = "(" + reg1 + ")";
			reg_f = reg_f + reg1;
		}
		if (!reg2.empty() && !reg3.empty() && !reg4.empty())
		{
			//if (reg2 != "^" || reg3 != "^" || reg4 != "^")
			//{


				if (!reg_f.empty())
					reg_f = reg_f + "|";
				reg_f = reg_f + "(";
			//}
			//if (reg2 != "^")
			//{
				//if (reg2.size() > 1) reg2 = "(" + reg2 + ")";
				reg_f = reg_f + reg2;
			//}

			//if (reg3 != "^")
			//{
				reg_f = reg_f + "(" + "(" + reg3 + ")" + "..." + ")";
			//}
			//else reg_f = reg_f + reg3;
			//if (reg4 != "^")
			//{
				//if (reg4.size() > 1) reg4 = "(" + reg4 + ")";
				reg_f = reg_f + reg4;
			//}
			reg_f = reg_f + ")";
		}
		return (reg_f);
	}
		
	
}
