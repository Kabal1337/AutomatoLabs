// lab2_a.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <map>
#include <string>
#include "Syntax_Tree.h"
#include "NFA_Creating.h"
#include "DFA.h"
#include "DFA_to_reg.h"
#include "DFA_mul.h"
int main()
{
    std::string reg1 = "(abc...)(a|b|c)...";
    std::string reg2 = "abcd...";
    Syntax_Tree* tree1 = new Syntax_Tree(reg1);
    Syntax_Tree* tree2 = new Syntax_Tree(reg2);
    //tree1->draw_syntax_tree("test1.txt");
    tree1->draw_syntax_tree("Syntax_tree.txt");
    DFA* dfa1 = new DFA(tree1);
    DFA* dfa2 = new DFA(tree2);
    dfa1->draw_dfa_graph("dfa1.txt");
    dfa2->draw_dfa_graph("dfa2.txt");
    DFA* dfa_mul = dfa1->DFA_mul(dfa2, Diff);
    if (dfa1->check_string("mephiaababmephi", tree1))
    {
        std::cout << "string accepted" << std::endl;
    }
   else std::cout << "string not accepted" << std::endl;
    std::cout<<dfa1->search();
     DFA_to_reg to_reg(dfa1);
    std::ofstream* out = new std::ofstream("regex_inv.txt");
    *out << to_reg.regex;
    Syntax_Tree* tree_reg = new Syntax_Tree(to_reg.regex);
    DFA* dfa_reg = new DFA(tree_reg);
    dfa_reg->draw_dfa_graph("dfa_reg.txt");
   // DFA_mul* dfa_mul = new DFA_mul(dfa1, dfa2, Diff);
    dfa_mul->draw_dfa_graph_mul("dfa_mul.txt");
    dfa_mul->minimization();
    dfa_mul->draw_dfa_graph_mul("dfa_mul_min.txt");
    return 0;
    
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
