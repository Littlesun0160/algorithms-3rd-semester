#include <iostream>

int main()
{
	const int Count = 15;
	int Massive[Count] = { 5, 9, 10, 35, 27, 1, 11, 8, 17, 39, 24, 28, 74, 3, 14 };

	for (int i = 0; i < Count; i++)
	{
		std::cout << Massive[i] << '\t';
	}
	std::cout << "\n";
	int Move = 0; 
	int NewMove;

	for (int i = 1; i < Count; i++)
	{
		Move = Massive[i]; 
		NewMove = i;
		for (int j = i - 1; j >= 0 && Massive[j] > Move; j--)
		{
			NewMove = j;
			Massive[j + 1] = Massive[j];
		}
		Massive[NewMove] = Move;
	}

	for (int i = 0; i < Count; i++)
	{
		std::cout << Massive[i] << '\t';
	}
	std::cout << "\n";
}