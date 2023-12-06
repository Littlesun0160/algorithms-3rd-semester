#include <iostream>
#include <vector>

using namespace std;

int GetMax(int mass[],const int n)
{
	int Max = mass[0];
	for (int i = 1; i < n; i++)
	{
		if (mass[i] > Max)
		{
			Max = mass[i];
		}
	}
	return Max;
}

void Sort(int mass[], int n, int exp)
{
	std::vector<int> output;
	int i, count[10] = { 0 };

	for (i = 0; i < n; i++)
	{
		count[(mass[i] / exp) % 10]++;
	}

	for (i = 1; i < 10; i++)
	{
		count[i] += count[i - 1];
	}

	for (int j = 0; j < n; j++)
	{
		output.push_back(int());
	}

	for (i = n - 1; i >= 0; i--) 
	{
		output[count[(mass[i] / exp) % 10] - 1] = mass[i];
		count[(mass[i] / exp) % 10]--;
	}

	for (i = 0; i < n; i++)
	{
		mass[i] = output.at(i);
	}
}

int main()
{
	int Massive[] = { 252, 91, 10, 2, 35, 8, 120, 111, 27, 85 };
	int Count = sizeof(Massive) / sizeof(Massive[0]);
	for (int i = 0; i < Count; i++)
	{
		std::cout << Massive[i] << " ";
	}
	std::cout << "\n";

	int Max = GetMax(Massive, Count);
	for (int i = 1; (Max / i) > 0; i *= 10)
	{
		Sort(Massive, Count, i);
	}

	for (int i = 0; i < Count; i++)
	{
		std::cout << Massive[i] << " ";
	}
	std::cout << "\n";
}