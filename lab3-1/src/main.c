#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void swap(int *arr, int i, int j)
{
    int a = arr[i];
    arr[i] = arr[j];
    arr[j] = a;
}

void shiftDown(int *arr, int size, int index)
{
    int largest = index;
    int l = 2 * index + 1;
    int r = 2 * index + 2;
    if (l < (size) && arr[l] > arr[largest])
    {
        largest = l;
    }
    if (r < (size) && arr[r] > arr[largest])
    {
        largest = r;
    }
    if (largest != index)
    {
        swap(arr, largest, index);
        shiftDown(arr, size, largest);
    }
}

void printArr(int *arr, int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
}

void heapSort(int *arr, int size)
{
    for (int i = size / 2 - 1; i >= 0; i--)
    {
        shiftDown(arr, size, i);
    }
    for (int i = size - 1; i >= 0; i--)
    {
        swap(arr, 0, i);
        shiftDown(arr, i, 0);
    }
}

int main()
{
    int size;
    char deleter;
    if (scanf("%d%c", &size, &deleter) == 0)
    {
    }
    int *array = (int *)malloc(sizeof(int) * size);
    for (int i = 0; i < size; i++)
    {
        if (scanf("%d%c", array + i, &deleter) == 0)
        {
        }
    }
    heapSort(array, size);
    printArr(array, size);
    free(array);
    return 0;
}
