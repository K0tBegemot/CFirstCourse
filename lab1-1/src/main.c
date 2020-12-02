#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int counter=0;
void Rob_Carp(char*, char*, int, int);
int hash(char*, int, int);

int main()
{
    char a[18], b[1000];
    FILE* ptrfile = fopen("in.txt", "r");
    if (fgets(a, 18, ptrfile)==0)
    {
    	fclose(ptrfile);
    	return 0;
	}
	int a_size = strlen(a)-1;
	printf("%d%c", hash(a, 0, a_size), ' ');
	while (fgets(b, 1000, ptrfile) != 0)
	{
		int b_size = strlen(b);
		if (b[b_size-1] == '\n')
		{
			Rabin_Karp(a, b, a_size, b_size);
		}else
		{
			Rabin_Karp(a, b, a_size, b_size);
			break;
		}
	}
	fclose(ptrfile);
    return 0;
}

void Rabin_Karp(char* a, char* b, int a_size, int b_size)
{
    int hashstr = hash(b, 0, a_size);
    int hashsubstr = hash(a, 0, a_size);
    for (int i = 0; i < b_size - a_size+1; i++)
    {
        if (hashstr == hashsubstr)
        {
            for (int ii = i; ii < i + a_size; ii++)
            {
                printf("%d%c", counter+ii + 1, ' ');
                if(a[ii-i] != b[ii])
                {
                	break;
                }
            }
        }
        hashstr = hash(b, i+1, a_size);
    }
    counter += (b_size);
}

int hash(char* aa, int firstel, int a_size)
{
    int hasher = 0;
    for (int i = firstel; i < firstel + a_size; i++)
    {
    	int k = 0;
    	if((int)aa[i] < 0)
    	{
    		k = 193 + (int)aa[i];
		}else
		{
			k = (int)aa[i];
		}
        hasher += ((k % 3) * pow(3, (i - firstel)));
    }
    return hasher;
}
