#include <iostream>
#include <vector>

void Sort(std::vector<int>& Numbers, int SizeNumbers)
{
	double ratio = 1.247;
	int step = SizeNumbers/1.247; // ��� ����������

	while (step >= 1)
	{
		for (int i = 0; i + step < SizeNumbers; i++)
		{
			if (Numbers[i] > Numbers[i + step])
			{
				std::swap(Numbers[i], Numbers[i + step]);
			}
		}
		step /= ratio;
	}
}

int main()
{
	setlocale(LC_ALL, "rus");
	std::vector<int> Numbers;
	int SizeNumbers;
	std::cout << "������� ����� �������\n";
	std::cin >> SizeNumbers;
	std::cout << "������� �������� �������\n";
	for (int i = 0; i < SizeNumbers; i++)
	{
		int Num;
		std::cin >> Num;
		Numbers.push_back(Num);
	}

	Sort(Numbers, SizeNumbers);
	for (int i = 0; i < SizeNumbers; i++)
	{
		std::cout << "���������: " << Numbers[i] << " ";
	}
	std::cout << "\n";
}