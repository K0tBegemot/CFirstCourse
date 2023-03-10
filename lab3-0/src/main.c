#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void quicksort(int *mass, int first, int last)
{
    if (last - first != 0)
    {
        int pivot = mass[(first + last) / 2];
        int i = first, ii = last;
        while (i <= ii)
        {
            while (mass[i] < pivot)
            {
                i += 1;
            }
            while (mass[ii] > pivot)
            {
                ii -= 1;
            }
            if (i <= ii)
            {
                int t;
                t = mass[i];
                mass[i] = mass[ii];
                mass[ii] = t;
                i += 1;
                ii -= 1;
            }
        }
        if (first < ii)
        {
            quicksort(mass, first, ii);
        }
        if (i < last)
        {
            quicksort(mass, i, last);
        }
    }
}

int main()
{
    FILE *ptrfile = fopen("in.txt", "r");
    int size;
    if (fscanf(ptrfile, "%d", &size) == 0)
    {
    }
    int *mass = (int *)malloc(sizeof(int) * size);
    for (int i = 0; i < size; i++)
    {
        if (fscanf(ptrfile, "%d", &mass[i]) == 0)
        {
        }
    }
    quicksort(mass, 0, size - 1);
    FILE *ptrfile2 = fopen("out.txt", "w");
    for (int i = 0; i < size; i++)
    {
        fprintf(ptrfile2, "%d ", mass[i]);
    }
    free(mass);
    fclose(ptrfile);
    fclose(ptrfile2);
    return 0;
}
