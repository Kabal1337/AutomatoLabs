#pragma once
#include "String.h"
#include "Var.h"
#include <string>
class String : virtual public Var
{
public:
	String(std::string name);
	String(std::string name, std::string value);
	var_type get_type() override;
	std::string get_name() override;
	std::string get_value();
	void set_value(std::string str);
private:
	std::string name;
	std::string value;
	bool mut;
	var_type type;
	
};
