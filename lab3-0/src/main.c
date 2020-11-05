#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void quicksort(long long int *mass,long long int first,long long int end)
{
	if(end-first==0)//end-first==1||
	{
		
	}else
	{
		long long int i=first,ii=end-1;
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
			long long int t;
			t=mass[i];
			mass[i]=mass[ii];
			mass[ii]=t;
			i+=1;
			ii-=1;
		}
		if(mass[ii]>mass[end])
		{
			long long int t;
			t=mass[ii];
			mass[ii]=mass[end];
			mass[end]=t;
		}
		if(mass[i]>mass[end])
		{
			long long int t;
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
	if(fscanf(ptrfile,"%lld%c",&size,&delet)==0)
	{
		
	}
	long long int *mass=(long long int*)malloc(sizeof(long long int)*size);
	for(long long int i=0;i<size;i++)
	{
		if(fscanf(ptrfile,"%lld%c",mass+i,&delet)==0)
		{
		    
		}
	}
	quicksort(mass,0,size-1);
	for(long long int i=0;i<size;i++)
	{
		printf("%lld%s",mass[i]," ");
	}
	free(mass);
	fclose(ptrfile);
	return 0;
}
