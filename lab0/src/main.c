#include <stdio.h>
#include <stdlib.h>

int main()
{
	long int a, b,indx=0,tochka=0,numeral,part1=0,part2=0,step=1,part1_size=0;
	char X[13];
	if (scanf("%ld", &a) != 1) 
	{
	exit(0);
	}
	if (scanf("%ld", &b) != 1)
	{
		exit(0);
	}
	if (scanf("%s", X) != 1)
	{
		exit(0);
	}
	for (; indx < 13 &&X[indx]!=0; indx++)
	{
	    numeral=-1;
		(X[indx] - '.' == 0) ? (tochka = 1, numeral=0) : ((X[indx] - '0' >= 0 && X[indx] - '9' <= 0) ? numeral = X[indx] - '0' : ((X[indx] - 'A' >= 0 && X[indx] - 'F' <= 0) ? numeral = X[indx] - 'A' + 10 : ((X[indx] - 'a' >= 0 && X[indx] - 'f' <= 0) ? numeral = X[indx] - 'a' + 10 : (-1))));
		if (numeral != -1)
		{
		    if(tochka==0)
		    {
		        part1 = numeral + part1 * a;
		    }else
		    {
		        if(tochka==1)
		        {
		            if(indx==0)
		            {
		                printf("%s", "bad input");
			            exit(0);
		            }else
		            {
		                if(X[indx+1]==0)
		                {
		                    printf("%s", "bad input");
			                exit(0);
		                }
		            }
		            tochka = 2;
				    continue;
		        }else
		        {
		            if(tochka==2)
		            {
		               part2 = part2 * a + numeral;
				       step *= a; 
		            }
		        }
		    }
			
		}
		else
		{
			printf("%s", "bad input");
			exit(0);
		}
	}
	long int copy_part1=part1;
	while (copy_part1 != 0)
	{
		copy_part1 /= b;
		part1_size += 1;
	}
	if(indx>0&&part1_size==0)
	{
	    part1_size=1;
	}
	int symbol, symb;
	char part1_end[part1_size], part2_end[12];
	for(int i=0;i<part1_size;i++)
	{
	    part1_end[i]=0;
	}
	for(int i=0;i<12;i++)
	{
	    part2_end[i]=0;
	}
	for (int i=0; i<part1_size; (part1/=b),i++)
	{
		symbol = part1 % b;
		if (symbol <= 9)
		{
			symb = '0' + symbol;
		}
		else
		{
			symb = 'A' + symbol - 10;
		}
		part1_end[i] = symb;
	}
	for(int i=0;i<12;i++)
	{
	    symbol =(part2*b)/step;
	    if (symbol <= 9)
		{
			symb = '0' + symbol;
		}
		else
		{
			symb = 'A' + symbol - 10;
		}
		part2_end[i] = symb;
		part2=part2*b-symbol*step;
	}
	long int r=0;
	for(int i=part1_size-1;i>-1;i--)
	{
	    if(part1_end[i]!=0)
	    {
	        r=1;
	    }
	    if(r==1)
	    {
	        printf("%c",part1_end[i]);
	    }
	}
	long int y=0;
	for(int i=11;i>-1;i--)
	{
	    if(part2_end[i]!='0')
	    {
	        y=i+1;
	        break;
	    }
	}
	if(y>0&&tochka==2)
	{
	    printf("%s",".");
	}
	for(int i=0;i<y;i++)
	{
	    printf("%c",part2_end[i]);
	}
	return 0;
}
