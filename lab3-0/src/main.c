#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void quicksort(long long int *mass,long long int first,long long int end)
{
	
	if(end-first==0)//end-first==1||
	{
		
	}else
	{
	
		long long pivot=mass[(first+end)/2];
		long long int i=first,ii=end;
		while(i<=ii)
		{
			while(mass[i]<pivot)
			{
				i+=1;
			}
			while(mass[ii]>pivot)
			{
				ii-=1;
			}
			if(i<=ii)
			{
			long long int t;
			t=mass[i];
			mass[i]=mass[ii];
			mass[ii]=t;
			i+=1;
			ii-=1;
			}
		}
        /*
		for(int iii=0;iii<200;iii++)
		{
			printf("%d%c",mass[iii],' ');
		}
		printf("%c",'\n');
		*/
		if (first < ii)
		{
			quicksort(mass, first, ii);
		}
        if (i < end)
        {
        	quicksort(mass, i, end);
		}
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
	int minimal,counter=0;
	FILE* ptrfile2=fopen("out.txt","w");
	for(long long int i=0;i<size;i++)
	{
		if(fscanf(ptrfile,"%lld%c",mass+i,&delet)==0)
		{
		    
		}
		if(i==0)
		{
			minimal=mass[i];
		}
		if(mass[i]>=mass[i-1]&&counter==0&&i!=0)
		{
			
		}else
		{
			counter=1;
		}
	}
	if(counter==1)
	{
		quicksort(mass,0,size-1);
	}
	for(long long int i=0;i<size;i++)
	{
		fprintf(ptrfile2,"%d%s",mass[i]," ");
	}
	free(mass);
	fclose(ptrfile);
	fclose(ptrfile2);
	return 0;
}
