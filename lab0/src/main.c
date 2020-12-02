#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	long long int = 0, tochka = 0, treq = 0, part1 = 0, part2 = 0, step = 1, part1_size = 0, p1=0;
	int a, b;
	char X[14], j;
	FILE* ptrfile = fopen("in.txt", "r");
	if (fscanf(ptrfile, "%d%d%c%13s", &a, &b, &j, X) != 3)
	{
	    printf("bad input\n");
	    fclose ptrfile;
	    return 0;
	}
	/*
	if (fscanf(ptrfile, "%d", &a) == 0)
	{
	    printf("%s","bad input");
	    fclose(ptrfile);
		return 0;
	}
	if (fscanf(ptrfile, "%d", &b) == 0)
	{
	    printf("%s","bad input");
	    fclose(ptrfile);
		return 0;
	}
	if(fscanf(ptrfile,"%c",&j)==0)
	{
	    printf("%s","bad input");
	    fclose(ptrfile);
		return 0;
	}
	if (fgets(X,14,ptrfile)==0)
	{
	    printf("%s","bad input");
	    fclose(ptrfile);
		return 0;
	}
	*/
	if (a < 2 || a > 16 || b < 2 || b > 16)
	{
	    printf("bad input\n");
	    fclose(ptrfile);
		return 0;
	}
	int xSize = strlen(X);
	for (indx=0; indx <xSize; indx++)
	{
	    if(X[indx] != '\n')
	    {
	        int numeral = -1;
		if(X[indx] == '.')
		{
			tochka=1;
			numeral=0;
		}else
		{
			if('0' <= X[indx] && X[indx] <= '9')
			{
				numeral = X[indx] - '0';
			}else
			{
				if(X[indx] - 'A' >= 0 && X[indx] - 'F' <= 0)
				{
					numeral = X[indx] - 'A' + 10;
				}else
				{
					if(X[indx] - 'a' >= 0 && X[indx] - 'f' <= 0)
					{
						numeral = X[indx] - 'a' + 10;
					}else
					{
						numeral=(-1);
					}
				}
			}
		}
		if (numeral != -1)
		{
		    if(numeral < 0 || numeral > a-1)
		    {
		        printf("%s", "bad input");
		        fclose(ptrfile);
			    return 0;
		    }
		    if(tochka == 0)
		    {
		        part1 = numeral + part1 * a;
		    }else
		    {
		        if(tochka == 1)
		        {
		            p1+=1;
		            if(indx == 0)
		            {
		                printf("%s", "bad input");
		                fclose(ptrfile);
			            return 0;
		            }else
		            {
		                if(X[indx+1] == 0)
		                {
		                    printf("%s", "bad input");
		                    fclose(ptrfile);
			                return 0;
		                }
		            }
		            tochka = 2;
				    continue;
		        }else
		        {
		            if(tochka == 2)
		            {
		               treq += 1;
		               part2 = part2 * a + numeral;
				       step *= a; 
		            }
		        }
		    }
			
		}
		else
		{
			printf("%s", "bad input");
			fclose(ptrfile);
			return 0;
		}
	    }
	}
	if(p1>1)
	{
	    printf("%s", "bad input");
	    fclose(ptrfile);
		return 0;
	}
	long long int copy_part1=part1, copy_part2=part2;
	if(part1 == 0 && part2 == 0 && tochka == 2)
	{
		printf("%s","bad input");
		return 0;
	}
	while (copy_part1 != 0)
	{
		copy_part1 /= b;
		part1_size += 1;
	}
	if(indx > 0 && part1_size == 0)
	{
	    part1_size=1;
	}
	long long int symbol, symb;
	char part1_end[part1_size], part2_end[15];
	for (long long int i=0; i<part1_size; (part1/=b),i++)
	{
		symbol = part1 % b;
		if (symbol <= 9)
		{
			symb = (char)((int)'0' + (int)symbol);
		}
		else
		{
			symb = (char)((int)'a' + (int)symbol - 10);
		}
		part1_end[i] = symb;
	}
	for(long long int i=0; i<15; i++)
	{
			symbol = (part2*b)/step;
	    if (symbol <= 9)
		{
			symb = (char)((int)'0' + (int)symbol);
		}
		else
		{
			symb = (char)((int)'a' + (int)symbol - 10);
		}
		part2_end[i] = symb;
		part2 = part2*b - symbol*step;
	}
	for(long long int i = part1_size-1; i>-1; i--)
	{
	    printf("%c", part1_end[i]);
	}
	if(tochka == 2 && copy_part2 != 0)
	{
		printf("%c", '.');
		for(long long int i=0; i<12; ++)
		{
			if(part2_end[i] != '-')
			{
				printf("%c", part2_end[i]);
			}
		}
	}
	fclose(ptrfile);
	return 0;
}
