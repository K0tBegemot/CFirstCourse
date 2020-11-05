#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void quicksort(int *mass,int first,int end)
{
	if(end-first==0)//end-first==1||
	{
		
	}else
	{
		int i=first,ii=end-1;
		while(i<ii)
		{
			if(mass[i]<=mass[end])
			{
				i+=1;
				continue;
			}
			if(mass[ii]>=mass[end])
			{
				ii-=1;
				continue;
			}
			int t;
			t=mass[i];
			mass[i]=mass[ii];
			mass[ii]=t;
			i+=1;
			ii-=1;
		}
		if(mass[ii]>mass[end])
		{
			int t;
			t=mass[ii];
			mass[ii]=mass[end];
			mass[end]=t;
		}
		if(mass[i]>mass[end])
		{
			int t;
			t=mass[i];
			mass[i]=mass[end];
			mass[end]=t;
		}
		/*
		for(int iii=0;iii<15;iii++)
		{
			printf("%d%c",mass[iii],' ');
		}
		printf("%c",'\n');
		*/
		quicksort(mass,first,i);
		quicksort(mass,i+1,end);
	}
}

int main()
{
	FILE *ptrfile=fopen("in.txt","r");
	char delet;
	long long int size;
	if(fscanf(ptrfile,"%d%c",&size,&delet)==0)
	{
		
	}
	int *mass=(int*)malloc(sizeof(int)*size);
	for(int i=0;i<size;i++)
	{
		fscanf(ptrfile,"%d%c",mass+i,&delet);
	}
	quicksort(mass,0,size-1);
	for(int i=0;i<size;i++)
	{
		printf("%d%s",mass[i]," ");
	}
	return 0;
}
