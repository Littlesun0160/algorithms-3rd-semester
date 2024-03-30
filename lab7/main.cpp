#include <iostream>

void ShellSort(int n, int mass[])
{
	int InterCount;
	int Inter;
	for (int Step = n / 2; Step > 0; Step /= 2)
	{
		for (int i = Step; i < n; i++)
		{
			Inter = mass[i];
			for (int j = i; j >= 0; j -= Step)
			{
				InterCount = j;
				if (Inter < mass[j - Step])
				{
					mass[j] = mass[j - Step];
				}
				else
				{
					break;
				}
			}
			mass[InterCount] = Inter;
		}
	}
}

int main()
{
	const int Count = 10;
	int Massive[Count] = {40, 5, 25, 1, 20, 16, 28, 19, 22, 11};
	for (int i = 0; i < Count; i++)
	{
		std::cout << Massive[i] << " ";
	}
	std::cout << "\n";

	ShellSort(Count, Massive);

	for (int i = 0; i < Count; i++)
	{
		std::cout << Massive[i] << " ";
	}
	std::cout << "\n";
}