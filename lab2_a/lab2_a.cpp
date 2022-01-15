﻿// lab2_a.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <map>
#include <string>
#include "Syntax_Tree.h"
#include "NFA_Creating.h"
#include "DFA.h"
int main()
{
    std::string reg = "<anime>(ANI...M?(<sosi>(E|H)))";
    Syntax_Tree* tree = new Syntax_Tree(reg);
    
    tree->draw_syntax_tree("test1.txt");
    DFA* dfa = new DFA(tree);
    
    dfa->draw_dfa_graph("test3.txt");
    if (dfa->check_string("ANIIIIME", tree))
    {
        std::cout << "string accepted";
    }
    else std::cout << "string not accepted";
    //NFA_Creating* nfa = new NFA_Creating(reg);
    //nfa->draw_syntax_tree("test1.txt");
    //nfa->draw_nfa_graph("test2.txt");
    
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
