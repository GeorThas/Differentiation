#include <iostream>
#include "Tokenizator.h"
#include "Error.h"
#include "RevPolNot.h"
#include "Differentiation.h"
#include "DiffParser.h"
#include <list>

int main()
{
	std::vector<Token> tokensList, tokensListRPN;

	std::string expr = "4*x*cos(x)*sin(x)";
	std::cout << "Expression: " << expr << std::endl;

	try
	{
		tokenize(expr, tokensList); // Токенизация строки с выражением

		std::cout << GetTokensList(tokensList); // Вывод токенов
		
		ShuntingYard(tokensList, tokensListRPN); // 

		std::cout << "\n Reverse Polish Notation: ";
		for (auto& i : tokensListRPN)
			std::cout << i.getStr() << " ";
		std::cout << "\n";

		//std::cout << "Answer: " << countRPN(tokensListRPN) << "\n"; //???
		std::vector<Token> arguments = tokensListRPN;
		std::cout << "\n Derivative: " << DiffParser(arguments) << std::endl;

	}
	catch (Error& e)
	{
		std::cerr << e.what() << "\n";
		exit(-1);
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << '\n';
		exit(-1);
	}

	return 0;
}