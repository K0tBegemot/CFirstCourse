#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int counter = 0;
void Rabin_Karp(int *, int *, int, int, int *);
void remakeHash(int *, int *, int, int, int *);
int hash(int *, int, int);

int main()
{
    char a[18], b[1000];
    FILE *ptrfile = fopen("in.txt", "r");
    if (fgets(a, 18, ptrfile) == 0)
    {
        fclose(ptrfile);
        return 0;
    }
    int aSize = strlen(a) - 1;
    int constRemHash = 1;
    for (int i = 0; i < aSize - 1; i++)
    {
        constRemHash *= 3;
    }
    int c[18], d[1000];
    for (int i = 0; i < 18; i++)
    {
        c[i] = (unsigned char)(a[i]);
    }
    printf("%d ", hash(c, 0, aSize));
    while (fgets(b, 1000, ptrfile) != 0)
    {
        int bSize = strlen(b);
        for (int i = 0; i < bSize; i++)
        {
            d[i] = (unsigned char)(b[i]);
        }
        Rabin_Karp(c, d, aSize, bSize, &constRemHash);
        if (b[bSize - 1] != '\n')
        {
            break;
        }
    }
    fclose(ptrfile);
    return 0;
}

void Rabin_Karp(int *a, int *b, int aSize, int bSize, int *constRemHash)
{
    int hashstr = hash(b, 0, aSize);
    int hashsubstr = hash(a, 0, aSize);
    for (int i = 0; i < bSize - aSize + 1; i++)
    {
        if (hashstr == hashsubstr)
        {
            for (int ii = i; ii < i + aSize; ii++)
            {
                printf("%d ", counter + ii + 1);
                if (a[ii - i] != b[ii])
                {
                    break;
                }
            }
        }
        remakeHash(&hashstr, b, i, aSize, constRemHash);
    }
    counter += (bSize);
}

void remakeHash(int *hashstr, int *a, int min, int aSize, int *constRemHash)
{
    int first, second;
    first = a[min];
    second = a[min + aSize];
    *hashstr -= (first % 3);
    *hashstr /= 3;
    *hashstr += (second % 3) * (*constRemHash);
}

int hash(int *a, int firstel, int aSize)
{
    int hasher = 0;
    for (int i = firstel; i < firstel + aSize; i++)
    {
        int constCount = 1;
        for (int o = 0; o < i - firstel; o++)
        {
            constCount *= 3;
        }
        hasher += ((a[i] % 3) * constCount);
    }
    return hasher;
}
