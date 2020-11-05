#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void quicksort(long int *mass,long int first,long int end)
{
	
	if(end-first==0)//end-first==1||
	{
		
	}else
	{
	
		long pivot=mass[(first+end)/2];
		long int i=first,ii=end;
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
			long int t;
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
	long int size;
	if(fscanf(ptrfile,"%ld%c",&size,&delet)==0)
	{
		
	}
	long int *mass=(long int*)malloc(sizeof(long int) * size);
	//int counter=1;
	for(long int i=0;i<size;i++)
	{
		if(fscanf(ptrfile,"%ld%c",&mass[i],&delet)==0)
		{
		    
		}
		/*
		if(mass[i]<mass[i-1]&&i>=1)
		{
			
		}else
		{
			counter=1;
		}
		*/
	}
	/*
	if(counter==1)
	{
	*/
		quicksort(mass,0,size-1);
	//}
	FILE* ptrfile2=fopen("out.txt","w");
	for(long int i=0;i<size;i++)
	{
		fprintf(ptrfile2,"%ld%s",mass[i]," ");
	}
	free(mass);
	fclose(ptrfile);
	fclose(ptrfile2);
	return 0;
}
