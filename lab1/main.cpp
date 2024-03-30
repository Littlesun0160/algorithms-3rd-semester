#include <iostream>
#include <stack>

int main()
{
	setlocale(LC_ALL, "rus");
	std::cout << "Введите строку\n";
	std::stack <char> stek;

	std::string Text;
	std::cin >> Text;
	std::string Open = "{[("; std::string Close = "}])";

	bool flag = false; 
	for (int i = 0; i < Text.length(); i++)
	{
		if (Open.find(Text[i])!=-1)
		{
			stek.push(Text[i]);
		}
		else if (!stek.empty())
		{
			if (Close.find(Text[i]) != -1 and (Open.find(stek.top()) == Close.find(Text[i])))
			{
				stek.pop();
			}
			else
			{
				std::cout << "Строка не существует\n";
				flag = true;
				break;
			}
		}
		else
		{
			std::cout << "Строка не существует\n";
			flag = true;
			break;
		}
	}

	if (stek.empty())
	{
		std::cout << "Строка существует\n";
	}
	else if (!flag)
	{
		std::cout << "Строка не существует\n";
	}
}