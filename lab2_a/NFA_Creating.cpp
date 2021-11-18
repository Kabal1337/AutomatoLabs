#include "NFA_Creating.h"

NFA_Creating::NFA_Creating(std::string regex)
{
	this->start = nullptr;
	this->recieve = nullptr;
	this->nfa_nodes_id = 0;

	this->stree = new Syntax_Tree(regex);
	build(this->stree->_get_root());
}

void NFA_Creating::build(Syntax_Node* node)
{
	if (this->stree->_get_root()->isChecked == true) return;

	if (node->left_ptr == nullptr && node->right_ptr == nullptr)
	{
		++(this->abc)[node->sign];

		create_graph(node);
		node->isChecked = true;

		build(node->parent_ptr);
	}

	if (node->left_ptr != nullptr && node->right_ptr != nullptr)
	{
		if (node->left_ptr->isChecked && node->right_ptr->isChecked)
		{
			create_graph(node);
			node->isChecked = true;

			build(node->parent_ptr);
		}

		if (!node->left_ptr->isChecked) build(node->left_ptr);
		if (!node->right_ptr->isChecked) build(node->right_ptr);
	}

	if (node->left_ptr != nullptr && node->right_ptr == nullptr)
	{
		if (node->left_ptr->isChecked)
		{
			create_graph(node);
			node->isChecked = true;

			build(node->parent_ptr);
		}
		else build(node->left_ptr);
	}
}

void NFA_Creating::create_graph(Syntax_Node* node)
{
	NFA_Component* new_comp;

	NFA_Node* node_A;
	NFA_Node* node_B;

	NFA_Component* comp_A;
	NFA_Component* comp_B;

	switch (node->type)
	{
	case a_node:
		new_comp = new NFA_Component(node->indexes[0]);

		node_A = new NFA_Node(nfa_start, this->nfa_nodes_id++);
		node_B = new NFA_Node(nfa_accepting, this->nfa_nodes_id++);

		
		
		node_A->make_link(node_B, node->sign);
		

		new_comp->add_node(node_A);
		new_comp->add_node(node_B);

		new_comp->enter_node = node_A;
		new_comp->exit_node = node_B;

		this->start = node_A;
		this->recieve = node_B;
		this->graphs.push_back(new_comp);
		break;
	case or_node:
		new_comp = new NFA_Component(node->indexes[0]);

		node_A = new NFA_Node(nfa_start, this->nfa_nodes_id++);
		node_B = new NFA_Node(nfa_accepting, this->nfa_nodes_id++);

		comp_A = find_graph(node->left_ptr->indexes[0]);
		comp_B = find_graph(node->right_ptr->indexes[0]);

		comp_A->enter_node->type = nfa_normal;
		comp_A->exit_node->type = nfa_normal;
		comp_B->enter_node->type = nfa_normal;
		comp_B->exit_node->type = nfa_normal;

		node_A->make_link(comp_A->enter_node, "eps");
		node_A->make_link(comp_B->enter_node, "eps");

		comp_A->exit_node->make_link(node_B, "eps");
		comp_B->exit_node->make_link(node_B, "eps");

		new_comp->enter_node = node_A;
		new_comp->exit_node = node_B;

		this->start = node_A;
		this->recieve = node_B;
		this->graphs.push_back(new_comp);
		break;
	case cat_node:
		new_comp = new NFA_Component(node->indexes[0]);

		comp_A = find_graph(node->left_ptr->indexes[0]);
		comp_B = find_graph(node->right_ptr->indexes[0]);

		comp_A->enter_node->type = nfa_start;
		comp_A->exit_node->type = nfa_normal;
		comp_B->enter_node->type = nfa_normal;
		comp_B->exit_node->type = nfa_accepting;

		comp_A->exit_node->links = comp_B->enter_node->links;
		comp_B->delete_node(comp_B->enter_node);
		comp_B->enter_node = nullptr;

		new_comp->enter_node = comp_A->enter_node;
		new_comp->exit_node = comp_B->exit_node;

		this->start = comp_A->enter_node;
		this->recieve = comp_B->exit_node;
		this->graphs.push_back(new_comp);
		break;
	case klyn_node:
		new_comp = new NFA_Component(node->indexes[0]);

		node_A = new NFA_Node(nfa_start, this->nfa_nodes_id++);
		node_B = new NFA_Node(nfa_accepting, this->nfa_nodes_id++);

		comp_A = find_graph(node->left_ptr->indexes[0]);

		comp_A->enter_node->type = nfa_normal;
		comp_A->exit_node->type = nfa_normal;

		node_A->make_link(comp_A->enter_node, "eps");
		comp_A->exit_node->make_link(node_B, "eps");
		comp_A->exit_node->make_link(comp_A->enter_node, "eps");
		
		new_comp->enter_node = node_A;
		new_comp->exit_node = node_B;
		new_comp->enter_node->make_link(new_comp->exit_node, "eps");
		this->start = node_A;
		this->recieve = node_B;
		this->graphs.push_back(new_comp);
		break;
	default:
		throw("there is no such type!");
		break;
	}
}



void NFA_Creating::draw_syntax_tree(std::string file_name)
{
	this->stree->draw_syntax_tree(file_name);
}

NFA_Node* NFA_Creating::get_start()
{
	return this->start;
}

NFA_Node* NFA_Creating::get_recieve()
{
	return this->recieve;
}

std::map<std::string, int> NFA_Creating::get_abc()
{
	return this->abc;
}

void NFA_Creating::draw_nfa_graph(std::string file_name)
{
	if (this->start == nullptr) return;

	std::ofstream* out = new std::ofstream(file_name);
	*out << "digraph G {" << std::endl;

	*out << this->start->id << " [label=\"" << this->start->id << "\\nstart\"];" << std::endl;
	*out << this->recieve->id << " [label=\"" << this->recieve->id << "\\nrecieve\"];" << std::endl;

	drawing(this->start, out);

	*out << "}";
}

void NFA_Creating::drawing(NFA_Node* node, std::ofstream* out)
{
	if (node->isChecked) return;

	for (auto it = node->links.begin(); it != node->links.end(); it++)
	{
		*out << node->id << " -> " << (*it).first->id << "[label=\"" << (*it).second << "\"];" << std::endl;
	}
	node->isChecked = true;

	for (auto it = node->links.begin(); it != node->links.end(); it++)
	{
		drawing((*it).first, out);
	}
}

NFA_Component* NFA_Creating::find_graph(int index)
{
	for (auto it = this->graphs.begin(); it != this->graphs.end(); it++)
	{
		if ((*it)->index == index) return (*it);
	}

	return nullptr;
}