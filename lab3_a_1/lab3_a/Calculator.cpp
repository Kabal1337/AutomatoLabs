#include "Calculator.h"
#include <regex>

Calculator::Calculator(std::string expression)
{
    std::regex sign("[*]|[/]|[%]|[+]|[-]|[=]|[>]|[<]|[(]|[)]");
    std::string parsed = "";
    std::string t_value = "";

    int arr_index = 0;
    for (int i = 0; i < expression.length(); i++)
    {
        /*if (expression[i] == '[')
        {
            arr_index = 1;
        }
        else if (reg[i] == ']')
        {
            arr_index = 0;
        }*/

        if (!regex_match(std::string(1, expression[i]), sign))
        {
            t_value += expression[i];
        }
        else
        {
            if (arr_index != 1)
            {
                if (t_value.size() != 0)
                { 
                    parsed += "!";
                    Calc_Node new_node('!', parsed.size() - 1, t_value, leaf_node);
                    this->nodes[parsed.size() - 1] = new_node;
                }
                parsed += std::string(1, expression[i]);
                t_value = "";
            }
            else
            {
                t_value += expression[i];
            }
        }
    }

    if (t_value.size() != 0)
    {
        parsed += "!";
        Calc_Node new_node('!', parsed.size() - 1, t_value, leaf_node);
        this->nodes[parsed.size() - 1] = new_node;
    }
    int first, last;

    do
    {
        first = -1;
        last = -1;

        for (int i = 0; i < parsed.length(); i++)
        {
            if (parsed[i] == '(')
            {
                first = i;
            }
            if (parsed[i] == ')')
            {
                last = i;
                break;
            }
        }

        if (first == -1 && last == -1) break;

        parsed[first] = ' ';
        parsed[last] = ' ';
        add_brackets(first, last);


        for (int i = first + 1; i < last; i++)
        {
            if (parsed[i] == '*')
            {
                create_node(parsed[i], i, mul_node);
                add_children(i, i - 1);
                add_children(i, i + 1);
                reg[i] = ' ';
            }
        }

        for (int i = first + 1; i < last; i++)
        {
            if (parsed[i] == '/')
            {
                create_node(parsed[i], i, div_node);
                add_children(i, i - 1);
                add_children(i, i + 1);
                parsed[i] = ' ';
            }
        }

        for (int i = first + 1; i < last; i++)
        {
            if (parsed[i] == '%')
            {
                create_node(parsed[i], i, mod_node);
                add_children(i, i - 1);
                add_children(i, i + 1);
                parsed[i] = ' ';
            }
        }

        for (int i = first + 1; i < last; i++)
        {
            if (parsed[i] == '+')
            {
                create_node(parsed[i], i, plus_node);
                add_children(i, i - 1);
                add_children(i, i + 1);
                reg[i] = ' ';
            }
        }

        for (int i = first + 1; i < last; i++)
        {
            if (parsed[i] == '-')
            {
                create_node(parsed[i], i, sub_node);
                add_children(i, i - 1);
                add_children(i, i + 1);
                parsed[i] = ' ';
            }
        }

        for (int i = first + 1; i < last; i++)
        {
            if (parsed[i] == '=')
            {
                create_node(parsed[i], i, eq_node);
                add_children(i, i - 1);
                add_children(i, i + 1);
                parsed[i] = ' ';
            }
        }

        for (int i = first + 1; i < last; i++)
        {
            if (parsed[i] == '>')
            {
                create_node(parsed[i], i, greater_node);
                add_children(i, i - 1);
                add_children(i, i + 1);
                parsed[i] = ' ';
            }
        }

        for (int i = first + 1; i < last; i++)
        {
            if (parsed[i] == '<')
            {
                create_node(parsed[i], i, less_node);
                add_children(i, i - 1);
                add_children(i, i + 1);
                parsed[i] = ' ';
            }
        }

    } while (first != -1 && last != -1);

}
void Calculator::add_brackets(int open, int close)
{
    std::pair<int, bracket_type> br1 = { open, bracket_open };
    std::pair<int, bracket_type> br2 = { close, bracket_close };
    this->brackets.push_back(br1);
    this->brackets.push_back(br2);
}