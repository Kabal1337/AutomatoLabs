#pragma once
#include <string>
#include "Var.h"
class Integer : virtual public Var
{
public:
	Integer(std::string name, int value);
	Integer(std::string name);
	var_type get_type() override;
	std::string get_name() override;
	int get_value();
	void set_value(int value);
private:
	int value;
	std::string name;
	bool mut;
	var_type type;
};
