#include <iostream>

int main()
{
	const int Count = 10;
	int Massive[Count] = { 8, 10, 45, 2, 15, 3, 9, 22, 29, 11 };
	int Min = 0;
	int Move = 0;

	for (int i = 0; i < Count; i++)
	{
		std::cout << Massive[i] << " ";
	}
	std::cout << "\n";

	for (int i = 0; i < Count; i++)
	{
		Min = i; 
		for (int j = i + 1; j < Count; j++)
		{
			if (Massive[j] < Massive[Min])
			{
				Min = j;
			}
		}
		if (i != Min)
		{
			Move = Massive[i];
			Massive[i] = Massive[Min];
			Massive[Min] = Move;
		}
	}

	for (int i = 0; i < Count; i++)
	{
		std::cout << Massive[i] << " ";
	}
	std::cout << "\n";
}