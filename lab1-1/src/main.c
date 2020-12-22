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
    int a_size = strlen(a) - 1;
    int constRemHash = 1;
    for (int i = 0; i < a_size - 1; i++)
    {
        constRemHash *= 3;
    }
    int c[18], d[1000];
    for (int i = 0; i < 18; i++)
    {
        c[i] = (unsigned char)(a[i]);
    }
    printf("%d ", hash(c, 0, a_size));
    while (fgets(b, 1000, ptrfile) != 0)
    {
        int b_size = strlen(b);
        for (int i = 0; i < b_size; i++)
        {
            d[i] = (unsigned char)(b[i]);
        }
        Rabin_Karp(c, d, a_size, b_size, &constRemHash);
        if (b[b_size - 1] != '\n')
        {
            break;
        }
    }
    fclose(ptrfile);
    return 0;
}

void Rabin_Karp(int *a, int *b, int a_size, int b_size, int *constRemHash)
{
    int hashstr = hash(b, 0, a_size);
    int hashsubstr = hash(a, 0, a_size);
    for (int i = 0; i < b_size - a_size + 1; i++)
    {
        if (hashstr == hashsubstr)
        {
            for (int ii = i; ii < i + a_size; ii++)
            {
                printf("%d ", counter + ii + 1);
                if (a[ii - i] != b[ii])
                {
                    break;
                }
            }
        }
        remakeHash(&hashstr, b, i, a_size, constRemHash);
    }
    counter += (b_size);
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

int hash(int *a, int firstel, int a_size)
{
    int hasher = 0;
    for (int i = firstel; i < firstel + a_size; i++)
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
