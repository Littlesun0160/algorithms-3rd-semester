#include <iostream>
#include <cmath>

int main()
{
	setlocale(LC_ALL, "rus");
	std::cout << "¬ведите переменную х\n";
	int X;
	std::cin >> X;

	for (int i = 0; pow(3, i) <= X; i++)
	{
		for (int j = 0; pow(5, j) <= X; j++)
		{
			for (int k = 0; pow(7, k) <= X; k++)
			{
				if ((pow(3, i) * pow(5, j) * pow(7, k)) <= X)
				{
					std::cout << pow(3, i) * pow(5, j) * pow(7, k) << " ";
				}
			}
		}
	}
}