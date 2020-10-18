#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main()
{
    char a[18],c[100];
    int table[16];
    char table_w[16];
    FILE* ptrfile=fopen("in.txt","r");
    if(fgets(a,18,ptrfile)==0)
    {
    	return 0;
	}
	long long int count=0,a_size = strlen(a);
    //printf("%d%s%d%c", strlen(a)," ", count,'\n');
    long long int counter = 0, table_size = 0;
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
	//if((b_size+1)%a_size==0)
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
    FILE* ptrfile2=fopen("out.txt","w");
    unsigned long long int gerb=0;
    while(fgets(c,100,ptrfile)!=0)
    {
    	int size_c=strlen(c);
    	if(size_c==0)
    	{
    		break;
		}else
		{
		    long long int location = a_size - 2;
    /*
    for (int i = 0; i < table_size; i++)
    {
        printf("%c%d%s", table_w[i], table[i]," ");
    }
    */
    while (location < size_c)
    {
        fprintf(ptrfile2,"%d%s", location+1+gerb, " ");
        //printf("%lld%s",location," ");
        if (c[location] == a[a_size - 2])
        {
            long long int location_copy = location - 1,popp=1;
            for (int i = a_size - 3; i > -1; i--)
            {
                fprintf(ptrfile2,"%d%s", location_copy + 1+gerb," ");
                //printf("%c%s%c", b[location_copy], " ", a[i]);
                if (c[location_copy] == a[i])
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
                            if(location>=size_c)
                            {
                                gerb+=size_c;	
							}
                            l = 1;
                            break;
                        }
                    }
                    if (l != 1)
                    {
                        location += a_size-1;
                        if(location>=size_c)
                        {
                        	gerb+=size_c;
						}
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
                        if(location>=size_c)
                        {
                        	gerb+=size_c;
						}
                        break;
					}
                }
                if (olp != 1)
                {
                    location += a_size-1;
                    if(location>=size_c)
                    {
                    	gerb+=size_c;
					}
                }
            }
        }
        else
        {
            int q = 0;
            for (int i = 0; i < table_size; i++)
            {
                if (table_w[i] == c[location])
                {
                    location += table[i];
                    q = 1;
                    if(location>=size_c)
                    {
                    	gerb+=size_c;
					}
                    break;
                }   
            }
            if (q != 1)
            {
                location += a_size-1;
                if(location>=size_c)
                    {
                    	gerb+=size_c;
					}
            }
        }
    }
		}
	}
    return 0;
}
