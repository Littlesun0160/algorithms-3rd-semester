#include <iostream>

void Merge(int mass[], int intmass[], int low, int mid, int high)
{
    int k = low, i = low, j = mid + 1;

    while (i <= mid && j <= high)
    {
        if (mass[i] <= mass[j]) 
        {
            intmass[k] = mass[i];
            k++; i++;
        }
        else 
        {
            intmass[k] = mass[j];
            k++; j++;
        }
    }

    while (i <= mid) 
    {
        intmass[k] = mass[i];
        k++; i++;
    }

    // Вторую половину копировать не нужно (поскольку остальные элементы
    // уже находятся на своем правильном месте во вспомогательном массиве)
    // копируем обратно в исходный массив, чтобы отразить порядок сортировки
    for (int i = low; i <= high; i++) 
    {
        mass[i] = intmass[i];
    }
}

void Sort(int mass[], int intmass[], int low, int high)
{
    if (high <= low) 
    { 
        return;
    }

    int mid = low + (high - low) / 2;
    Sort(mass, intmass, low, mid);
    Sort(mass, intmass, mid + 1, high);

    Merge(mass, intmass, low, mid, high);
}


int main(void)
{
    int Massive[] = { 2, 30, 5, 19, 102, 3, 35, 23, 19 };
    const int Count = sizeof(Massive) / sizeof(Massive[0]);
    int IntMassive[Count];

    for (int i = 0; i < Count; i++)
    {
        IntMassive[i] = Massive[i];
        std::cout << Massive[i] << " ";
    }
    std::cout << "\n";

    Sort(Massive, IntMassive, 0, Count - 1);

    for (int i = 0; i < Count; i++)
    {
        std::cout << Massive[i] << " ";
    }
    std::cout << "\n";
}
