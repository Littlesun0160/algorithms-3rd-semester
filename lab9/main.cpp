#include <iostream>

void heapify(int mass[], int n, int i)
{
    int largest = i;
    int left = 2 * i + 1; 
    int rigth = 2 * i + 2;

    if (left < n && mass[left] > mass[largest])
    {
        largest = left;
    }
    if (rigth < n && mass[rigth] > mass[largest])
    {
        largest = rigth;
    }

    if (largest != i)
    {
        std::swap(mass[i], mass[largest]);
        heapify(mass, n, largest);
    }
}

void Sort(int mass[], int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
    {
        heapify(mass, n, i);
    }
   
    for (int i = n - 1; i >= 0; i--)
    {
        std::swap(mass[0], mass[i]);
        heapify(mass, i, 0);
    }
}

int main()
{
    int Massive[] = { 10,20,13,8,2,18 };
    int Count = sizeof(Massive) / sizeof(Massive[0]);

    for (int i = 0; i < Count; ++i)
    {
        std::cout << Massive[i] << " ";
    }
    std::cout << "\n";

    Sort(Massive, Count);

    for (int i = 0; i < Count; ++i)
    {
        std::cout << Massive[i] << " ";
    }
    std::cout << "\n";
}