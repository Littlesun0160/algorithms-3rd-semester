#include <iostream>
#include <algorithm>
using namespace std;

int partition(int mass[], int start, int end)
{
    int pivot = mass[end];
    int pIndex = start;

    for (int i = start; i < end; i++)
    {
        if (mass[i] <= pivot)
        {
            swap(mass[i], mass[pIndex]);
            pIndex++;
        }
    }

    swap(mass[pIndex], mass[end]);
    return pIndex;  //индекс опорного элемента
}

void Sort(int mass[], int start, int end)
{
    if (start >= end) 
    {
        return;
    }

    int pivot = partition(mass, start, end);
    Sort(mass, start, pivot - 1);
    Sort(mass, pivot + 1, end);
}


int main()
{
    int Massive[] = { 56, 239, 13, 139, 91, 223, 22, 38, 83, 102, 33, 126, 6 };
    const int Count = sizeof(Massive) / sizeof(Massive[0]);
    
    for (int i = 0; i < Count; i++)
    {
        std::cout << Massive[i] << " ";
    }
    std::cout << "\n";

    Sort(Massive, 0, Count - 1);

    for (int i = 0; i < Count; i++)
    {
        std::cout << Massive[i] << " ";
    }
    std::cout << "\n";

}