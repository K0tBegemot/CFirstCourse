#include <cstdlib.h>
#include <cstdio>
#include <string.h>

void Rob_Carp(char*, char*, int, int);
int hash(char*, int, int);

int main()
{
    char a[17], b[1000];
    gets_s(a,16);
    gets_s(b, 999);
    int a_size = strlen(a), b_size = strlen(b);
    Rob_Carp(a, b, a_size, b_size);
    return 0;
}

void Rob_Carp(char* a, char* b, int a_size, int b_size)
{
    int hashstr = hash(b, 0, a_size);
    int hashsubstr = hash(a, 0, a_size);
    printf("%d%s", hashsubstr, " ");
    for (int i = 0; i < b_size - a_size+1; i++)
    {
        if (hashstr == hashsubstr)
        {
            for (int ii = i; ii < i + a_size; ii++)
            {
                printf("%d%s", ii + 1, " ");
            }
        }
        hashstr = hash(b, i+1, a_size);
    }
}

int hash(char* aa, int firstel, int a_size)
{
    int hasher = 0;
    //printf("%d%s%d%c", firstel, " ", a_size,'\n');
    for (int i = firstel; i < firstel + a_size; i++)
    {
        hasher += ((aa[i] % 3) * pow(3, (i-firstel)));
    }
    //printf("%d%c", hasher, '\n');
    return hasher;
}

