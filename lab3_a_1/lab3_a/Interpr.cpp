#include "Interpr.h"


Interpr::Interpr(std::string code_file)
{

	std::ifstream file(code_file);
	if (!file.is_open()) throw (std::string)("File not found!");

	std::string temp;
	while (getline(file, temp))
	{
		this->code.push_back(temp);
	}
	try
	{
		take_funcs();
		perform_body();
	}
	catch (const std::string& exeption)
	{
		std::cerr << exeption.c_str();
	}
}

void Interpr::take_funcs()
{
	//проверяет закрыты ли все start/finish
	std::stack<std::string> sf_stack;

	std::cmatch cap_gr;
	std::string type("int|string");
	std::string name("[a-zA-Z][a-zA-Z0-9]*");
	std::regex regex_func("(" + type + ")[ ](" + name + ")[(]((" + type + ")[ ](" + name + ")([,][ ]?(" + type + ")[ ](" + name + "))*)?[)]"); //1 группа - тип функции, 4 - имя функции, 5 - аргументы
	std::regex regex_start("start");
	std::regex regex_finish("finish");
	std::regex regex_return("return[ ]((" + name + ")|(.*))[;]");
	for (int i = 0; i < code.size(); i++)
	{
		if (regex_match(code[i].c_str(), cap_gr, regex_func))
		{
			if (this->functions[cap_gr[2]] != nullptr) throw ("Function '" + cap_gr[4].str() + "' alredy exists, at line: " + std::to_string(i + 1));
			if (code[i + 1] != "start") throw ("Expected 'start', at line: " + std::to_string(i + 1));
			sf_stack.push("finish");
			Func* function = nullptr;
			if (cap_gr[1] == "int")
			{
				function = new Func(cap_gr[2], Integer_t, i + 2);
			}
			else if (cap_gr[1] == "string")
			{
				function = new Func(cap_gr[2], String_t, i + 2);
			}
			//параметры функции
			if (cap_gr[3].length() != 0)
			{
				std::string value = cap_gr[3];
				static const std::regex rdelim{ ", " };
				std::vector<std::string> args{
						std::sregex_token_iterator(value.begin(), value.end(), rdelim, -1),
						std::sregex_token_iterator()
				};

				std::cmatch arg_cg;
				std::regex regex_arg("(" + type + ")[ ](" + name + ")"); //1 группа - type , 4 группа - name
				for (int j = 0; j < args.size(); j++)
				{
					regex_match(args[j].c_str(), arg_cg, regex_arg);

					if (arg_cg[2].length() != 0 && arg_cg[3].length() != 0)
					{

					}
					else
					{
						if (cap_gr[1] == "int")
						{
							function->add_arg(new Integer(arg_cg[4]));
						}
						else if (cap_gr[1] == "string")
						{
							function->add_arg(new String(arg_cg[4]));
						}
					}
				}
			}
			this->functions[cap_gr[2]] = function;

			//если была встечена функция main, то отправляем ее в стек позиции, с нее начнется выполнение кода.
			if (cap_gr[2] == "main") this->pos_stack.push(this->functions["main"]->get_body_index());

			i++;
			continue;
			
		}
		if (regex_match(code[i].c_str(), regex_start))
		{
			sf_stack.push("finish");
			continue;
		}

		if (regex_match(code[i].c_str(), regex_finish))
		{
			if (!sf_stack.empty() && sf_stack.top() != "finish") throw ("Expected '" + sf_stack.top() + "', at line: " + std::to_string(i + 1));
			if (sf_stack.empty()) throw ("Unexpected 'finish' met, at line: " + std::to_string(i + 1));
			sf_stack.pop();
			continue;
		}

	}

	if (!sf_stack.empty()) throw "Error '" + sf_stack.top() + "' expected";
	if (this->pos_stack.empty()) throw (std::string)("The 'main' function was not met");

	
}

void Interpr::perform_body()
{
	std::regex variable_op("([a-zA-Z][a-zA-Z0-9]*)"); 
	std::regex integer_op("(-?[0-9]+)|([a-zA-Z][a-zA-Z0-9]*)"); 
	std::regex string_op("[\"](.+)[\"]|([a-zA-Z][a-zA-Z0-9]*)"); 
	cur_index = pos_stack.top();
	this->pos_stack.pop();
	func_stack.push(functions["main"]);
	cur_func = func_stack.top();
	std::regex regex_variable_dec("((mutable)[ ])?(int|string)[ ]([a-zA-Z][a-zA-Z0-9]*)((;)|:=(.+);)"); //2 группа - mut, 3 - тип, 4 - имя переменной, 6 - только объявление, 7 - присвоение
	std::regex regex_variable_assig("([a-zA-Z][a-zA-Z0-9]*):=(([a-zA-Z][a-zA-Z0-9]*)|(.+));"); //1 - имя переменной, 3 - переменная, 4 - выражение
	std::regex regex_finish("finish");
	std::regex regex_return("return[ ]((-?[0-9]+)|[\"](.+)[\"]|([a-zA-Z][a-zA-Z0-9]*));"); 
	std::cmatch catch_group;
	while (1)
	{
		if (regex_match(code[cur_index].c_str(), catch_group, regex_variable_dec))
		{
			if (catch_group[3] == "int")
			{
				if (catch_group[2].length() == 0)
				{
					if (catch_group[6].length() != 0) throw (std::string)("Constant value not set, at line: " + std::to_string(cur_index + 1));
					std::cmatch temp_cg;
					std::string temp_group = catch_group[7];
					if (regex_match(temp_group.c_str(), temp_cg, integer_op)) //переменная или число
					{
						if (temp_cg[1].length() != 0) //число
						{
							cur_func->add_variable(new Integer(catch_group[4], std::stoi(temp_cg[1])), catch_group[4]);
						}
						else //перменная
						{
							Integer* var = dynamic_cast<Integer*>(cur_func->get_variable(temp_cg[2]));
							if (var == nullptr) throw (std::string)("Incompatible types, at line: " + std::to_string(cur_index + 1));

							cur_func->add_variable(new Integer(catch_group[4], var->get_value()), catch_group[4]);
						}
					
					}
					else //выражение
					{

					}
				}
				else //переменная 
				{
					std::cmatch temp_cg;
					std::string temp_group = catch_group[7];
					cur_func->add_variable(new Integer(catch_group[4]), catch_group[4]);
					if (catch_group[6].length() == 0)
					{
						std::cmatch temp_cg;
						if (regex_match(temp_group.c_str(), temp_cg, integer_op))
						{
							if (temp_cg[1].length() != 0) //число
							{
								dynamic_cast<Integer*>(cur_func->get_variable(catch_group[5]))->
									set_value(std::stoi(temp_cg[1]));
							}
							else//переменная
							{
								if(dynamic_cast<Integer*>(cur_func->get_variable(temp_cg[2])) == nullptr) 
									throw (std::string)("Unexpected type, at line: " + std::to_string(cur_index + 1));
								dynamic_cast<Integer*>(cur_func->get_variable(catch_group[4]))
									->set_value(dynamic_cast<Integer*>(cur_func->get_variable(temp_cg[2]))->get_value());
							}
						}
						else//выражение с переменными
						{

						}

					}
				}
			}
			else if (catch_group[3] == "string")
			{
				if (catch_group[2].length() == 0)//константа
				{
					if (catch_group[6].length() != 0) throw (std::string)("Constant was not set, at line " + std::to_string(cur_index + 1));
					std::string temp_group = catch_group[7];
					std::cmatch temp_cg;
					if (regex_match(temp_group.c_str(), temp_cg, string_op))
					{
						if (temp_cg[1].length() != 0)//строка
						{
							cur_func->add_variable(new String(catch_group[4], temp_cg[1]), catch_group[4]);

						}
						else //переменная
						{
							if (dynamic_cast<String*>(cur_func->get_variable(temp_cg[2])) == nullptr) throw 
								(std::string)("Unexpected type, at line: " + std::to_string(cur_index + 1));
							cur_func->add_variable(new String(catch_group[4],
								dynamic_cast<String*>(cur_func->get_variable(temp_cg[2]))->get_value()),
								catch_group[4]); //добавляем переменную в функцию
						}
					}
				}
				else //переменная с опц инициализацией
				{
					cur_func->add_variable(new String(catch_group[4]), catch_group[4]);
					if (catch_group[6].length() == 0)
					{
						std::cmatch temp_cg;
						std::string temp_group = catch_group[7];
						if (regex_match(temp_group.c_str(), temp_cg, string_op))
						{
							if (temp_cg[1].length() != 0)//строка
							{
								dynamic_cast<String*>(cur_func->get_variable(catch_group[4]))->set_value(temp_cg[1]);
							}
							else//переменная
							{
								if (dynamic_cast<String*>(cur_func->get_variable(temp_cg[2])) == nullptr)
									throw (std::string)("Unexpected type, at line: " + std::to_string(cur_index + 1));
								dynamic_cast<String*>(cur_func->get_variable(catch_group[4]))
									->set_value(dynamic_cast<String*>(cur_func->get_variable(temp_cg[2]))->get_value());
							}
						}
					}
	
				}

			}
			cur_index++;
			continue;
		}
		if (regex_match(code[cur_index].c_str(), catch_group, regex_return))
		{
			if(catch_group[2].length() != 0) //return числа
			{
				if (cur_func->get_return_var()->get_type() != Integer_t) 
					throw (std::string)("Unexpected type of return, at line: " + std::to_string(cur_index + 1));
				dynamic_cast<Integer*>(cur_func->get_return_var())->set_value(std::stoi(catch_group[2]));
			}
			else if (catch_group[3].length() != 0) //return string
			{
				if(cur_func->get_return_var()->get_type() != String_t) 
					throw (std::string)("Unexpected type of return, at line: " + std::to_string(cur_index + 1));
			}
			else //return переменной
			{
				if (cur_func->get_variable(catch_group[4]) == nullptr) throw 
					(std::string)("There is no such variable '" + catch_group[4].str() 
						+ "', at line: " + std::to_string(cur_index + 1));
				if (cur_func->get_return_var()->get_type() != cur_func->get_variable(catch_group[4])->get_type()) 
					throw (std::string)("The return type does not match the type of the function, at line: " 
						+ std::to_string(cur_index + 1));
				if (cur_func->get_variable(catch_group[4])->get_type() == Integer_t)
				{
					dynamic_cast<Integer*>(cur_func->get_return_var())->set_value(dynamic_cast<Integer*>(cur_func->get_variable(catch_group[4]))->get_value());
				}
				else if(cur_func->get_variable(catch_group[4])->get_type() == String_t)
				{
					dynamic_cast<String*>(cur_func->get_return_var())->set_value(dynamic_cast<String*>(cur_func->get_variable(catch_group[4]))->get_value());
				}
				else
				{
					throw (std::string)("This type is not supported for return, at line: " + std::to_string(cur_index + 1));
				}
				

			}

			if (cur_func->get_return_var_ptr() != nullptr)
			{
				switch (cur_func->get_return_var_ptr()->get_type())
				{
				case Integer_t:
					dynamic_cast<Integer*>(cur_func->get_return_var_ptr())->set_value(dynamic_cast<Integer*>(cur_func->get_return_var())->get_value());
					break;
				default:
					throw (std::string)("This type of beneficiary is not supported (yet?)");
					break;
				}
			}
			func_stack.pop();
			if (func_stack.empty()) break;
			cur_index = pos_stack.top();
			/*GI = pos_stack.top();
			while (!regex_match(code[GI - 1], fun_call_rx))
			{
				pos_stack.pop();
				GI = pos_stack.top();
			}*/
			pos_stack.pop();
			continue;


		}
		if (regex_match(code[cur_index].c_str(), regex_finish))
		{
			if (this->pos_stack.empty()) throw (std::string)("pos_stack was empty, at line: " + std::to_string(cur_index + 1));

			cur_index = this->pos_stack.top();
			this->pos_stack.pop();
			continue;
		}

		cur_index++;
	}
	if (this->functions["main"]->get_return_var()->get_type() == Integer_t)
	{
		std::cout << "Main returned: " << std::to_string(dynamic_cast<Integer*>(this->functions["main"]
			->get_return_var())->get_value()) << std::endl;
	}
	else if (this->functions["main"]->get_return_var()->get_type() == String_t)
	{
		std::cout << "Main returned \"" << dynamic_cast<String*>(this->functions["main"]
			->get_return_var())->get_value() << "\"" << std::endl;
	}
	else
		std::cout << "Unexpected return type from main" << std::endl;

}
