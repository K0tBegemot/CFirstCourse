#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int makeRearrangement(char *a, int size)
{
    int counter = 0;
    int s = 0;
    for (int i = size - 1; i > 0; i--)
    {
        if (a[i] > a[i - 1])
        {
            s = i;
            counter += 1;
            break;
        }
    }
    if (counter == 0)
    {
        return -1;
    }
    char minn = a[s];
    int minnIndex = s;
    for (int i = s + 1; i < size; i++)
    {
        if (a[i] < minn && a[i] > a[s - 1])
        {
            minn = a[i];
            minnIndex = i;
        }
    }
    char u;
    u = a[s - 1];
    a[s - 1] = minn;
    a[minnIndex] = u;
    return s;
}

void swap(char *b, int r, int aSize)
{
    //bubbleSortElementsInThePermutationAfterTheEnlargedElement
    for (int i = 0; i < r; i++)
    {
        for (int ii = r; ii < aSize - 1; ii++)
        {
            if (b[ii] > b[ii + 1])
            {
                char c = b[ii];
                b[ii] = b[ii + 1];
                b[ii + 1] = c;
            }
        }
    }
}

void printOnePermutation(char *b, int aSize)
{
    for (int ii = 0; ii < aSize; ii++)
    {
        printf("%d", b[ii]-'0');
    }
    printf("\n");
}

int main()
{
    char a[100];
    int count1[10], size;
    FILE *ptrfile = fopen("in.txt", "r");
    if (fgets(a, 100, ptrfile) == 0)
    {
        printf("%s", "bad input");
        fclose(ptrfile);
        return 0;
    }
    if (fscanf(ptrfile, "%d", &size) == 0)
    {
        printf("%s", "bad input");
        fclose(ptrfile);
        return 0;
    }
    int aSize = strlen(a) - 1;
    for (int i = 0; i < 10; i++)
    {
        count1[i] = 0;
    }
    for (int i = 0; i < aSize; i++)
    {
        if ((a[i]>='0') && (a[i]<='9'))
        {
            count1[a[i] - '0'] += 1;
            if (count1[a[i] - '0'] > 1)
            {
                printf("%s", "bad input");
                return 0;
            }
        }
        else
        {
            printf("%s", "bad input");
            return 0;
        }
    }
    for (int i = 0; i < size; i++)
    {
        int r = makeRearrangement(a, aSize);
        if (r == -1)
        {
            return 0;
        }
        swap(a, r, aSize);
        printOnePermutation(a, aSize);
    }
    fclose(ptrfile);
    return 0;
}
