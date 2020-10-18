#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main()
{
    char a[18], b[4000],c[100];
    int table[16];
    char table_w[16];
    FILE* ptrfile=fopen("in.txt","r");
    if(fgets(a,18,ptrfile)==0)
    {
    	//printf("%d%s",0," ");
    	return 0;
	}
	long long int count=0,a_size = strlen(a);
	long long int pol=0,pol2=0;
	while(fgets(c,100,ptrfile)!=0)
    {
    	int size_c=strlen(c);
    	//printf("%d%s%d%c",a_size," ",size_c,'\n');
    	if(size_c==0)
    	{
    		break;
		}else
		{
				pol2+=1;
			if(c[size_c-1]=='\n')
			{
				//printf("%s","/");
				for(int i=0;i<size_c;i++)
    	        {
    	         	b[i+count]=c[i];
	        	}
	        	count+=size_c;
	        	if(a_size-2==size_c)
    	{
    		pol+=1;
		}
			}else
			{
				for(int i=0;i<size_c;i++)
          	    {
    	         	b[i+count]=c[i];
	        	}
	        	count+=size_c;
	        	if(a_size-1==size_c)
    	{
    		pol+=1;
		}
	        	break;
			}
		}
	}
	//printf("%d",pol2);
	if(pol2==pol&&pol!=0)
	{
		long int k=a_size-1;
		for(int i=0;i<pol2+1;i++)
		{
			//printf("%d%s",k," ");
			k+=a_size-1;
		}
		//printf("%d",pol);
		return 0;
	}
    //gets(a);
    //gets(b);
    //printf("%d%s%d%c", strlen(a)," ", count,'\n');
    long long int counter = 0, b_size = count, table_size = 0;
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
