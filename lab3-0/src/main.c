#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void quicksort(int *mass,int first,int end)
{
	
	if(end-first==0)//end-first==1||
	{
		
	}else
	{
	
		int pivot=mass[(first+end)/2];
		int i=first,ii=end;
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
			int t;
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
	int size;
	if(fscanf(ptrfile,"%d%c",&size,&delet)==0)
	{
		
	}
	int *mass=(int*)malloc(sizeof(int) * size);
	for(int i=0;i<size;i++)
	{
		if(fscanf(ptrfile,"%d%c",&mass[i],&delet)==0)
		{
		    
		}
	}
	quicksort(mass,0,size-1);
	FILE* ptrfile2=fopen("out.txt","w");
	for(int i=0;i<size;i++)
	{
		fprintf(ptrfile2,"%d%s",mass[i]," ");
	}
	free(mass);
	fclose(ptrfile);
	fclose(ptrfile2);
	return 0;
}
