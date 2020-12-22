#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int counter = 0;
void Rabin_Karp(char *, char *, int, int, int *);
void remakeHash(int *, char *, int, int, int *);
int hash(char *, int, int);

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
    for (int i = 0; i < a_size; i++)
    {
        a[i] = (unsigned char)(a[i]);
    }
    printf("%d ", hash(a, 0, a_size));
    while (fgets(b, 1000, ptrfile) != 0)
    {
        int b_size = strlen(b);
        for (int i = 0; i < b_size; i++)
        {
            b[i] = (unsigned char)(b[i]);
        }
        Rabin_Karp(a, b, a_size, b_size, &constRemHash);
        if (b[b_size - 1] != '\n')
        {
            break;
        }
    }
    fclose(ptrfile);
    return 0;
}

void Rabin_Karp(char *a, char *b, int a_size, int b_size, int *constRemHash)
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

void remakeHash(int *hashstr, char *a, int min, int aSize, int *constRemHash)
{
    int first, second;
    first = (int)a[min];
    second = (int)a[min + aSize];
    *hashstr -= (first % 3);
    *hashstr /= 3;
    *hashstr += (second % 3) * (*constRemHash);
}

int hash(char *aa, int firstel, int a_size)
{
    int hasher = 0;
    for (int i = firstel; i < firstel + a_size; i++)
    {
        unsigned char k = 0;
        k = (unsigned char)aa[i];
        int constCount = 1;
        for (int o = 0; o < i - firstel; o++)
        {
            constCount *= 3;
        }
        hasher += ((k % 3) * constCount);
    }
    return hasher;
}
