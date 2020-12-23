#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void constructTables(char *a, int *table, char *tableW, long long int aSize, long long int *tableSize)
{
    for (int i = 0; i < aSize - 2; i++)
    {
        long long int counter = 0;
        for (int ii = 0; ii < *tableSize; ii++)
        {
            if (a[i] == tableW[ii])
            {
                table[ii] = aSize - i - 2;
                counter = 1;
                break;
            }
        }
        if (counter == 0)
        {
            tableW[*tableSize] = a[i];
            table[*tableSize] = aSize - i - 2;
            *tableSize += 1;
        }
    }
}

void changeTable(char *c, int cSize, int tableSize, long long int *location, char *tableW, int *table, long long int *gerb, int aSize)
{
    int q = 0;
    for (int i = 0; i < tableSize; i++)
    {
        if (tableW[i] == c[*location])
        {
            *location += table[i];
            q = 1;
            if (*location >= cSize)
            {
                *gerb += cSize;
            }
            break;
        }
    }
    if (q != 1)
    {
        *location += aSize - 1;
        if (*location >= cSize)
        {
            *gerb += cSize;
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
    long long int aSize = strlen(a);
    long long int tableSize = 0;
    constructTables(a, table, tableW, aSize, &tableSize);
    FILE *ptrfile2 = fopen("out.txt", "w");
    long long int gerb = 0;
    while (fgets(c, 97, ptrfile) != 0)
    {
        int cSize = strlen(c);
        if (cSize == 0)
        {
            break;
        }
        else
        {
            long long int location = aSize - 2;
            while (location < cSize)
            {
                fprintf(ptrfile2, "%lld%s", location + 1 + gerb, " ");
                if (c[location] == a[aSize - 2])
                {
                    long long int locationCopy = location - 1, popp = 1;
                    for (int i = aSize - 3; i > -1; i--)
                    {
                        fprintf(ptrfile2, "%lld%s", locationCopy + 1 + gerb, " ");
                        if (c[locationCopy] == a[i])
                        {
                            popp += 1;
                            locationCopy -= 1;
                        }
                        else
                        {
                            changeTable(c, cSize, tableSize, &location, tableW, table, &gerb, aSize);
                            break;
                        }
                    }
                    if (popp == aSize - 1)
                    {
                        changeTable(c, cSize, tableSize, &location, tableW, table, &gerb, aSize);
                    }
                }
                else
                {
                    changeTable(c, cSize, tableSize, &location, tableW, table, &gerb, aSize);
                }
            }
        }
    }
    fclose(ptrfile);
    fclose(ptrfile2);
    return 0;
}
