//timsort-like algorithm (without split-arrays of unconstant size)
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int minrun_global=0;
int Minrun(int);
void sdvig(int*, int, int);

int main()
{
	int size_m;
	FILE* ptrfile=fopen("in.txt","r");
	if(fscanf(ptrfile,"%d", &size_m)==0)
	{
		fclose(ptrfile);
		return 0;
	}
	int* ss =(int*)malloc(size_m*sizeof(int));
	for (int i = 0; i < size_m; i++)
	{
		if(fscanf(ptrfile,"%d", (ss+i))==0)
		{
			
		}
	}
	int minrun = Minrun(size_m);
	int per = (size_m / minrun);
	if (size_m % per > 0)
	{
		per += 1;
	}
	for (int i = 0; i < per; i++)
	{
		for (int ii = i * minrun; (ii < (i + 1) * minrun) && (ii < size_m); ii++)
		{
			for (int iii = i * minrun; iii < ii; iii++)
			{
				if (ss[iii] > ss[ii])
				{
					sdvig(ss, iii, ii);
				}
			}
		}
	}
	int step = 0;
	while (pow(2, step) < per)
	{
		step += 1;
	}
	//printf("%d%c", minrun, '\n');
	//printf("%d%c", step, '\n');
	/*
	for (int i = 0; i < size_m; i++)
	{
		printf("%d%s", ss[i], " ");
	}
	*/
	//printf("%c%s%c", '\n', "-----------------------------", '\n');
	int lil = 1;
	for (int i = 0; i < step-1; i++)// without changes: for (int i = 0; i < step; i++)
	{
		int minrun_copy = minrun * lil;
		minrun_global=minrun_copy;
		//printf("%d%c", minrun_copy,'\n');
		int for_c = size_m / minrun_copy;
		if (size_m % minrun_copy != 0)
		{
			for_c += 1;
		}
		if (for_c % 2 == 1)
		{
			for_c -= 1;
		}
		for (int mint = 0; mint < (for_c)*minrun_copy; mint += 2 * minrun_copy)
		{
			//printf("%c%d%c",'\n', mint%minrun_copy, '\n');
			int* timemass = (int*)malloc(minrun_copy*sizeof(int));
			for (int ii = 0; ii < minrun_copy; ii++)
			{
				timemass[ii] = ss[mint + ii];
				//printf("%d%s%d%c", timemass[ii], " ",ss[mint+ii],'\n');
			}
			//printf("%s%c","-----------", '\n');
			int index_of_timemass = 0, index_of_ss = mint + minrun_copy, index_of_sort_ss = mint, halop_counter_1 = 0, halop_counter_2 = 0;
			while (index_of_timemass < minrun_copy && index_of_ss < size_m && index_of_ss < mint + 2 * minrun_copy)
			{
				/*
				if (timemass[index_of_timemass] == 353 || ss[index_of_ss]==353)
				{
					printf("%d%s%d%s%d%s%d%c", timemass[index_of_timemass], " ", ss[index_of_ss]," ",index_of_timemass," ",index_of_ss, '\n');
				}
				*/
				if (timemass[index_of_timemass] < ss[index_of_ss])
				{
					ss[index_of_sort_ss] = timemass[index_of_timemass];
					index_of_sort_ss += 1;
					index_of_timemass += 1;
					if (halop_counter_2 == 0)
					{
						halop_counter_1 += 1;
					}
					else
					{
						halop_counter_1 = 0;
						halop_counter_2 = 0;
					}
				}
				else
				{
					if (timemass[index_of_timemass] > ss[index_of_ss])
					{
						ss[index_of_sort_ss] = ss[index_of_ss];
						index_of_sort_ss += 1;
						index_of_ss += 1;
						if (halop_counter_1 == 0)
						{
							halop_counter_2 += 1;
						}
						else
						{
							halop_counter_1 = 0;
							halop_counter_2 = 0;
						}
					}
					else
					{
						ss[index_of_sort_ss] = timemass[index_of_timemass];
						index_of_sort_ss += 1;
						index_of_timemass += 1;
					}
				}
				if (halop_counter_1 == 7)
				{
					int crypa = 1,otvet=index_of_timemass;
					int ii=index_of_timemass;
					while(ii<minrun_copy)
					{
						if (ii >= minrun_copy)
						{
							ii = minrun_copy - 1;
						}
						if (timemass[ii] < ss[index_of_ss])
						{
							if (ii == minrun_copy - 1)
							{
								otvet = ii;
								break;
							}
							else
							{
								ii += crypa;
								crypa *= 2;
							}
						}
						else
						{
							ii -= (crypa/2);
							otvet = ii;
							break;
						}
					}
					for (int ii = index_of_timemass; ii < otvet; ii++)
					{
						ss[index_of_sort_ss] = timemass[ii];
						index_of_sort_ss += 1;
						index_of_timemass += 1;
					}
					halop_counter_1 = 0;
					halop_counter_2 = 0;
				}
				else
				{
					if (halop_counter_2 == 7)
					{
						int crypa = 1, otvet = index_of_timemass;
						int ii=index_of_ss;
						while(ii < size_m && ii < mint + 2 * minrun_copy)
						{
							if (ii >= size_m)
							{
								ii = size_m - 1;
							}
							else
							{
								if (ii >= mint + 2 * minrun_copy)
								{
									ii = mint + 2 * minrun_copy - 1;
								}
							}
							if (ss[ii]<timemass[index_of_timemass])
							{
							    if (ii == size_m-1||ii==mint+2*minrun_copy)
							    {
								    otvet = ii;
								    break;
							    }else
								{
								    ii+=crypa;
								    crypa *= 2;
								}
							}
							else
							{
								ii -= (crypa/2);
								otvet = ii;
								break;
							}
						}
						for (int ii = index_of_ss; ii < otvet; ii++)
					    {
						    ss[index_of_sort_ss] = ss[ii];
						    index_of_sort_ss += 1;
						    index_of_ss += 1;
					    }
					        halop_counter_1 = 0;
					        halop_counter_2 = 0;
					}
				}
			}
			if (index_of_timemass < minrun_copy)
			{
				for (int ii = index_of_timemass; ii < minrun_copy; ii++)
				{
					ss[index_of_sort_ss] = timemass[index_of_timemass];
					index_of_sort_ss += 1;
					index_of_timemass += 1;
				}
			}
			if ((index_of_ss < mint + 2 * minrun_copy )&&( index_of_ss < size_m))
			{
				for (int ii = index_of_ss; ii < mint + 2 * minrun_copy && ii < size_m; ii++)
				{
					ss[index_of_sort_ss] = ss[index_of_ss];
					index_of_sort_ss += 1;
					index_of_ss += 1;
				}
			}
			free(timemass);
		}
		/*
		for (int iii = 0; iii < size_m; iii++)
		{
			printf("%d%s", ss[iii], " ");
		}
		printf("%c", '\n');
		*/
		lil *= 2;
	}
	//this part of application wasn't exist before my correction
	for(int ii=2*minrun_global;ii<size_m;ii++)
	{
		int coip=0;
		for(int i=0;i<2*minrun_global;i++)
	    {
			if(ss[i]>ss[ii])
			{
				sdvig(ss,i,ii);
				coip+=1;
			}
		}
		if(coip==0)
		{
			break;
		}  
	}
	//the end of this strange, but working, amazing, wonderful, brilliant and intelegent part
	for (int i = 0; i < size_m; i++)
	{
		printf("%d%s", ss[i], " ");
	}
	free(ss);
	fclose(ptrfile);
	return 0;
}

int Minrun(int size)
{
	int minrun = 0;
	while (size >= 64)
	{
		minrun |= size & 1;
		size >>= 1;
	}
	return (minrun + size);
}

void sdvig(int* ss, int first, int second)
{
	int q = ss[second];
	for (int i = second; i > first; i--)
	{
		ss[i] = ss[i - 1];
	}
	ss[first] = q;
}
