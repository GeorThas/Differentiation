#include "DiffParser.h"
#include "Differentiation.h"
#include <map>
#include <iostream>

std::string DiffParser(std::vector<Token>& arguments)
{

	std::string diff; //Ïðîèçâîäíàÿ
	std::map<std::string, std::string> DiffsList; //Ñïèñîê óæå âû÷èñëåííûõ ôóíêöèé è èõ ïðîèçâîäíûõ
	std::vector<std::string> operations = { "(", "+", "-", "*", "/", "^", ")", "(", "()","sin", "cos",  "tan", "ctg" };

	try {

		while (arguments.size() > 1)
		{
			std::string firstOper = "";
			int firstOperIndex = arguments.size();
			for (auto& str : operations)
			{
				int indexOf = 0;
				for (indexOf = 0; indexOf < arguments.size(); indexOf += 1)
					if (arguments[indexOf].getStr() == str)
						break;

				if (indexOf > 0 && indexOf < firstOperIndex)
				{
					firstOperIndex = indexOf;
					firstOper = str;
				}
			}

			std::string f1 = "", f2 = "", df1 = "", df2 = "", oper = "", expression = "";

			if (arguments[firstOperIndex].getType() == Token::FUNCTION) //Îáðàáîòêà ôóíêöèé
			{
				int ComposeIndex = firstOperIndex;

				f1 = arguments[ComposeIndex].getStr();
				df1 = Differentiation::Diff(f1, DiffsList);
				f2 = arguments[ComposeIndex - 1].getStr();
				df2 = Differentiation::Diff(f2, DiffsList);
				oper = "Compose";
				expression = f1 + "(" + f2 + ")";
				diff = Differentiation::Diff(f1, df1, f2, df2, oper);

				arguments[ComposeIndex].setStr(expression);
				arguments.erase(arguments.begin() + ComposeIndex - 1);
			}
			else //Îáðàáîòêà áèíàðíûõ îïåðàöèé
			{
				f1 = arguments[firstOperIndex - 2].getStr();
				df1 = Differentiation::Diff(f1, DiffsList);
				f2 = arguments[firstOperIndex - 1].getStr();
				df2 = Differentiation::Diff(f2, DiffsList);
				oper = arguments[firstOperIndex].getStr();
				expression = f1 + oper + f2;
				diff = Differentiation::Diff(f1, df1, f2, df2, oper);

				arguments.erase(arguments.begin() + firstOperIndex);
				arguments.erase(arguments.begin() + firstOperIndex - 1);
				arguments[firstOperIndex - 2].setStr(expression);
			} // ÍÅÎÁÕÎÄÈÌÎ ÄÎÁÀÂÈÒÜ ÎÁÐÀÁÎÒ×ÈÊ ÓÍÀÐÍÛÕ ÎÏÅÐÀÖÈÉ!!!

			if (!DiffsList.contains(expression))
			{
				DiffsList.insert({ expression, diff });
			}
		}
		return diff;
	}
	catch (std::exception& e)
	{
		//exit(-1);
		return "DiffError";
	}

}
