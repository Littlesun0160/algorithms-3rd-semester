#include <iostream>
#include <stack>
#include <vector>
#include <string>

double Result(std::string MathExpression)
{
	std::stack <int> MathNum;
	std::stack <char> MathOper;
	std::string Operations = "*/+-="; std::string Staples = "()";
	
	std::string Number;  //Строка для определения одного числа
	int CountOfStaples = 0;

	for (int i = 0; i < (MathExpression.length()-1); i++)
	{
		if (isdigit(MathExpression[i]))
		{
			Number.push_back(MathExpression[i]);
		}
		if (!(Number.empty()) && Operations.find(MathExpression[i+1]) != std::string::npos) //Если мы нашли операцию
		{
			MathNum.push(std::stod(Number));
			Number.clear();
		}
		else if (Staples.find(MathExpression[i]) != std::string::npos || Operations.find(MathExpression[i]) != std::string::npos)
		{
			if (MathOper.empty()) //Если нашли операцию или скобки, то смотрим, каким символом является данный
			{
				MathOper.push(MathExpression[i]);
				continue;
			}
			switch (MathExpression[i])
			{
			case '(':
				CountOfStaples += 1;
				MathOper.push('('); //Скобку просто добавляем в стек операций
				break;
			case '+':
			case '-':
				if (Operations.find(MathOper.top()) != std::string::npos)
				{
					double Second = MathNum.top();
					MathNum.pop();
					double First = MathNum.top();
					MathNum.pop();
					switch (MathOper.top())
					{
					case '*':
						MathNum.push(First * Second);
						break;
					case '/':
						if (Second == 0)
						{
							throw std::exception("Деление на ноль!");
						}
						MathNum.push(First / Second);
						break;
					case '+':
						MathNum.push(First + Second);
						break;
					case '-':
						MathNum.push(First - Second);
						break;
					}
					MathOper.pop();
				}
				break;
			case ')':
			{
				CountOfStaples -= 1;
				if (Operations.find(MathExpression[i - 1]) != std::string::npos)
				{
					throw std::exception("Ошибка! Выражение введено неверно\n");
				}
				double Second = MathNum.top();
				MathNum.pop();
				double First = MathNum.top();
				MathNum.pop();
				switch (MathOper.top())
				{
				case '*':
					MathNum.push(First * Second);
					break;
				case '/':
					if (Second == 0)
					{
						throw std::exception("Деление на ноль!");
					}
					MathNum.push(First / Second);
					break;
				case '+':
					MathNum.push(First + Second);
					break;
				case '-':
					MathNum.push(First - Second);
					break;
				}
				MathOper.pop();
				break;
			}

			case '*':
			case '/':
				if (MathOper.top() == '/' || MathOper.top() == '*') {
					double Second = MathNum.top();
					MathNum.pop();
					double First = MathNum.top();
					MathNum.pop();
					switch (MathOper.top()) {
					case '*':
						MathNum.push(First * Second);
						break;
					case '/':
						if (Second == 0) {
							throw std::exception("Деление на ноль!");
						}
						MathNum.push(First / Second);
						break;
					}
					MathOper.pop();
					break;
				}
			}
			if (MathExpression[i] != '(' && MathExpression[i] != ')')
			{
				MathOper.push(MathExpression[i]);
			}
		}
		else
		{
			std::cout << "Ошибка! Выражение введено неверно\n";
			break;
		}
	}
	for (int i = MathExpression.size() - 2; i >= 0; i--) 
	{
		if (Operations.find(MathExpression[i]) != std::string::npos)
		{
			double Second = MathNum.top();
			MathNum.pop();
			double First = MathNum.top();
			MathNum.pop();
			if (MathOper.top() == '(')
			{
				MathOper.pop();
				i--;
			}
			switch (MathOper.top())
			{
			case '*':
				MathNum.push(First * Second);
				break;
			case '/':
				if (Second == 0)
				{
					throw std::exception("Деление на ноль!");
				}
				MathNum.push(First / Second);
				break;
			case '+':
				MathNum.push(First + Second);
				break;
			case '-':
				MathNum.push(First - Second);
				break;
			}
			MathOper.pop();
		}
		if (CountOfStaples != 0 || MathExpression[MathExpression.length() - 1] != '=')
		{
			std::cout << "Ошибка! Выражение введено неверно\n";
			exit(0);
		}
		}
	return MathNum.top();

}
int main()
{
	setlocale(LC_ALL, "rus");
	std::cout << "Введите математическое выражение\n";
	std::string MathExpression;
	std::cin >> MathExpression;
	std:: cout << Result(MathExpression);
	


	
}