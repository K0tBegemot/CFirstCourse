#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void constructTables(char *a, int *table, char *tableW, long long int a_size, long long int *table_size)
{
    for (int i = 0; i < a_size - 2; i++)
    {
        long long int counter = 0;
        for (int ii = 0; ii < *table_size; ii++)
        {
            if (a[i] == tableW[ii])
            {
                table[ii] = a_size - i - 2;
                counter = 1;
                break;
            }
        }
        if (counter == 0)
        {
            tableW[*table_size] = a[i];
            table[*table_size] = a_size - i - 2;
            *table_size += 1;
        }
    }
}

void changeTable(char *c, int size_c, int table_size, long long int *location, char *tableW, int *table, long long int *gerb, int a_size)
{
    int q = 0;
    for (int i = 0; i < table_size; i++)
    {
        if (tableW[i] == c[*location])
        {
            *location += table[i];
            q = 1;
            if (*location >= size_c)
            {
                *gerb += size_c;
            }
            break;
        }
    }
    if (q != 1)
    {
        *location += a_size - 1;
        if (*location >= size_c)
        {
            *gerb += size_c;
        }
    }
}

int main()
{
    char a[18], c[97];
    int table[16];
    char tableW[16];
    FILE *ptrfile = fopen("in.txt", "r");
    if (fgets(a, 18, ptrfile) == 0)
    {
        fclose(ptrfile);
        return 0;
    }
    long long int a_size = strlen(a);
    long long int table_size = 0;
    constructTables(a, table, tableW, a_size, &table_size);
    FILE *ptrfile2 = fopen("out.txt", "w");
    long long int gerb = 0;
    while (fgets(c, 97, ptrfile) != 0)
    {
        int size_c = strlen(c);
        if (size_c == 0)
        {
            break;
        }
        else
        {
            long long int location = a_size - 2;
            while (location < size_c)
            {
                fprintf(ptrfile2, "%lld%s", location + 1 + gerb, " ");
                if (c[location] == a[a_size - 2])
                {
                    long long int location_copy = location - 1, popp = 1;
                    for (int i = a_size - 3; i > -1; i--)
                    {
                        fprintf(ptrfile2, "%lld%s", location_copy + 1 + gerb, " ");
                        if (c[location_copy] == a[i])
                        {
                            popp += 1;
                            location_copy -= 1;
                        }
                        else
                        {
                            changeTable(c, size_c, table_size, &location, tableW, table, &gerb, a_size);
                            break;
                        }
                    }
                    if (popp == a_size - 1)
                    {
                        changeTable(c, size_c, table_size, &location, tableW, table, &gerb, a_size);
                    }
                }
                else
                {
                    changeTable(c, size_c, table_size, &location, tableW, table, &gerb, a_size);
                }
            }
        }
    }
    fclose(ptrfile);
    fclose(ptrfile2);
    return 0;
}
