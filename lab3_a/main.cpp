#include <iostream>
#include <vector>
#include <regex>

#include "Variables/Variable.h"
#include "Variables/Integer.h"
#include "Variables/String.h"
#include "Variables/Pointer.h"
#include "Variables/Array.h"

#include "Interpreter.h"
#include "Calculator/ST_Calculator.h"



using namespace std;


int main()
{
	
	//Тест с рекурсией
	//Interpreter ntrptr("recursive_test.txt", "labyrinth.txt");
	//Тест с математическим выражением
	//Interpreter ntrptr("math_test.txt", "labyrinth.txt");
	//Тест с конкатенацией строк
	//Interpreter ntrptr("str_test.txt", "labyrinth.txt");
	Interpreter ntrptr("array_test.txt", "labyrinth.txt");

    return 0;
}
