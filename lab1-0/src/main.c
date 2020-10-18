#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main()
{
    char a[17], b[1000];
    int table[16];
    char table_w[16];
    FILE* ptrfile=fopen("in.txt","r");
    if(fgets(a,18,ptrfile)==0)
    {
    	printf("%d%s",0," ");
    	return 0;
	}
	if(fgets(b,999,ptrfile)==0)
    {
    	printf("%d%s",0," ");
    	return 0;
	}
    //gets(a);
    //gets(b);
    //printf("%d%s%d%c", strlen(a)," ", strlen(b),'\n');
    int counter = 0, a_size = strlen(a), b_size = strlen(b), table_size = 0;
    /*
    for(int i=0;i<a_size;i++)
    {
    	printf("%c%s",a[i],"-");
	}
	printf("%s","()");
	for(int i=0;i<b_size;i++)
	{
		printf("%c%s",b[i],"-");
	}
	*/
    for (int i = 0; i < a_size-2; i++)
    {
    	//printf("%d%s",a[i]," ");
         counter = 0;
         for (int ii = 0; ii < table_size; ii++)
         {
                if (a[i] == table_w[ii])
                {
                    table[ii] = a_size - i - 2;
                    counter = 1;
                    break;
                }
         }
         if (counter == 0)
         {
                table_w[table_size] = a[i];
                table[table_size] = a_size - i - 2;
                table_size += 1;
         }
    }
    int location = a_size - 2;
    /*
    for (int i = 0; i < table_size; i++)
    {
        printf("%c%d%s", table_w[i], table[i]," ");
    }
    */
    while (location < b_size)
    {
        printf("%d%s", location+1, " ");
        //printf("%c%s%c", b[location], " ", a[a_size - 1]);
        if (b[location] == a[a_size - 2])
        {
            int location_copy = location - 1,popp=1;
            for (int i = a_size - 3; i > -1; i--)
            {
                printf("%d%s", location_copy + 1," ");
                //printf("%c%s%c", b[location_copy], " ", a[i]);
                if (b[location_copy] == a[i])
                {
                    popp += 1;
                    location_copy -= 1;
                }
                else
                {
                    int l = 0;
                    for (int ii = 0; ii < table_size; ii++)
                    {
                        if (table_w[ii] == a[a_size - 2])
                        {
                            location += table[ii];
                            l = 1;
                            break;
                        }
                    }
                    if (l != 1)
                    {
                        location += a_size-1;
                    }
                    break;
                }
            }
            if (popp == a_size-1)
            {
                int olp = 0;
                for (int i = 0; i < table_size; i++)
                {
                    if(table_w[i] == a[a_size - 2])
                    {
                    	olp=1;
                        location += table[i];
                        break;
					}
                }
                if (olp != 1)
                {
                    location += a_size-1;
                }
            }
        }
        else
        {
            int q = 0;
            for (int i = 0; i < table_size; i++)
            {
                if (table_w[i] == b[location])
                {
                    location += table[i];
                    q = 1;
                    break;
                }
                
            }
            if (q != 1)
            {
                location += a_size-1;
            }
        }
    }
    return 0;
}
