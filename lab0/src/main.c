#include <stdio.h>
#include <stdlib.h>

int main()
{
	long long int a, b,indx=0,tochka=0,tochka1=0,numeral,part1=0,part2=0,step=1,part1_size=0,p1=0;
	char X[13];
	if (scanf("%lld", &a) != 1) 
	{
	    exit(0);
	}
	if (scanf("%lld", &b) != 1)
	{
		exit(0);
	}
	if (scanf("%s", X) != 1)
	{
		exit(0);
	}
	if(a<2||a>16||b<2||b>16)
	{
	    printf("%s", "bad input");
		exit(0);
	}
	for (; indx < 13 &&X[indx]!=0; indx++)
	{
	    numeral=-1;
		(X[indx] - '.' == 0) ? (tochka = 1, numeral=0) : ((X[indx] - '0' >= 0 && X[indx] - '9' <= 0) ? numeral = X[indx] - '0' : ((X[indx] - 'A' >= 0 && X[indx] - 'F' <= 0) ? numeral = X[indx] - 'A' + 10 : ((X[indx] - 'a' >= 0 && X[indx] - 'f' <= 0) ? numeral = X[indx] - 'a' + 10 : (-1))));
		if (numeral != -1)
		{
		    if(numeral<0||numeral>a-1)
		    {
		        printf("%s", "bad input");
			    exit(0);
		    }
		    if(tochka==0)
		    {
		        part1 = numeral + part1 * a;
		    }else
		    {
		        if(tochka==1)
		        {
		            p1+=1;
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
		               tochka1+=1;
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
	if(p1>1)
	{
	    printf("%s", "bad input");
		exit(0);
	}
	long long int copy_part1=part1;
	while (copy_part1 != 0)
	{
		copy_part1 /= b;
		part1_size += 1;
	}
	if(indx>0&&part1_size==0)
	{
	    part1_size=1;
	}
	long long int symbol, symb;
	char part1_end[part1_size], part2_end[30];
	for(long long int i=0;i<part1_size;i++)
	{
	    part1_end[i]=0;
	}
	for(long long int i=0;i<30;i++)
	{
	    part2_end[i]=0;
	}
	for (long long int i=0; i<part1_size; (part1/=b),i++)
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
	for(long long int i=0;i<30;i++)
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
	long long int r=0;
	for(long long int i=part1_size-1;i>-1;i--)
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
	long long int y=0;
	for(long long int i=29;i>-1;i--)
	{
	    if(part2_end[i]!='0')
	    {
	        y=i+1;
	        break;
	    }
	}
	if(tochka1!=0&&tochka==2)
	{
	    printf("%s",".");
	}
	if(y>12||(y==0&&tochka1!=0))
	{
	    y=12;
	}
	for(long long int i=0;i<y;i++)
	{
	    if(tochka==2)
	    {
	        printf("%c",part2_end[i]);
	    }
	}
	return 0;
}
