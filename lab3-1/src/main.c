#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void swapper(int *mass,int first,int second)
{
	int a=mass[first];
	mass[first]=mass[second];
	mass[second]=a;
}

void heap(int *mass,int *size,int index)
{
	int largest=index;
	int l=2*index+1;
	int r=2*index+2;
	if(l<(*size)&&mass[l]>mass[index])
	{
		largest=l;
	}
	if(r<(*size)&&mass[r]>mass[index])
	{
		largest=r;
	}
	if(largest!=index)
	{
		swapper(mass,largest,index);
		heap(mass,size,largest);
	}
}

void heapsort(int *mass, int size)
{
	for(int i=size-1;i>-1;i--)
	{
		heap(mass,&size,i);
	}
	for(int i=size-1;i>-1;i--)
	{
		swapper(mass,0,i);
		heap(mass,&i,0);
	}
}

void printer_mass(int *mass,int size)
{
	for(int i=0;i<size;i++)
	{
		printf("%d%c",mass[i],' ');
	}
}

int main()
{
	int size;
	char deleter;
	if(scanf("%d%c",&size,&deleter)==0)
	{
	    
	}
	int *massive=(int*)malloc(sizeof(int)*size);
	for(int i=0;i<size;i++)
	{
		if(scanf("%d%c",massive+i,&deleter)==0)
		{
		    
		}
	}
	heapsort(massive,size);
	printer_mass(massive,size);
	free(massive);
	return 0;
}
