#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void swap(int *mass, int first, int second)
{
	int a = mass[first];
	mass[first] = mass[second];
	mass[second] = a;
}

void make_heap(int *mass, int *size, int index)
{
	int largest = index;
	int l = 2 * index + 1;
	int r = 2 * index + 2;
	if(l < (*size) && mass[l] > mass[largest])
	{
		largest = l;
	}
	if(r < (*size) && mass[r] > mass[largest])
	{
		largest = r;
	}
	if(largest != index)
	{
		swap(mass, largest, index);
		heap(mass, size, largest);
	}
}

void print_arr(int *mass, int size)
{
	for(int i=0; i < size; i++)
	{
		printf("%d%c", mass[i], ' ');
	}
}

void heapsort(int *mass, int size)
{
	for(int i = size - 1; i > -1; i--)
	{
		make_heap(mass, &size, i);
	}
	for(int i = size - 1; i>-1; i--)
	{
		swap(mass, 0, i);
		make_heap(mass, &i, 0);
	}
}

int main()
{
	int size;
	char deleter;
	if(scanf("%d%c", &size, &deleter) == 0)
	{
		
	}
	int *massive = (int*)malloc(sizeof(int) * size);
	for(int i=0; i<size; i++)
	{
		if(scanf("%d%c", massive+i, &deleter) == 0)
		{
			
		}
	}
	heapsort(massive, size);
	print_arr(massive, size);
	free(massive);
	return 0;
}
