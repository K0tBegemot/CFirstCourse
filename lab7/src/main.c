#include <stdio.h>
#include <stdlib.h>

//struct BitFlag

struct BitSet
{
    char *bitset;
    int length;
    int width;
    int type; // 0 - symmetrical; 1 - unsymmetrical;
};

struct BitSet *CreateBitSet(int length, int width, int type)
{
    if (length == 0 || width == 0)
    {
        printf("Invalid length or value field. Bitset not created");
        return 0;
    }
    struct BitSet *created = (struct BitSet *)malloc(sizeof(struct BitSet));
    created->bitset = 0;
    int size = length * width;
    int summ;
    switch (type)
    {
    case 0:
        created->bitset = (char *)calloc((size / 8 + (size % 8 ? 1 : 0)), sizeof(char));
        break;
    case 1:
        summ = ((width - 1) * width / 2);
        created->bitset = (char *)calloc(((size - summ) / 8 + ((size - summ) % 8 ? 1 : 0)), sizeof(char));
        break;
    default:
        printf("Invalid type field. Bitset not created");
        free(created);
        return 0;
    }
    created->length = length;
    created->width = width;
    created->type = type;
    return created;
}

int WriteBit(struct BitSet *created, int x, int y, int bit)
{
    int returnValue=0;
    switch (created->type)
    {
    case 0:
        if (x + 1 > created->width || y + 1 > created->length)
        {
            printf("Invalid coordinate fields. Bit not writed");
            return 0;
        }
        int shift = (created->length) * (x) + y;
        char *tVar = (created->bitset) + (shift) / 8;
        if ((*tVar & (1 << (8 - (shift % 8) - 1))) != 0)
        {
            if (bit == 0)
            {
                *tVar = (*tVar ^ (1 << (8 - (shift % 8) - 1)));
            }
        }
        else
        {
            if (bit == 1)
            {
                *tVar = (*tVar ^ (1 << (8 - (shift % 8) - 1)));
            }
        }
        returnValue = 1;
        break;
    case 1:

        break;
    default:
        printf("Invalid type field. Bad BitSet. Bit not writed");
        return 0;
    }
    return returnValue;
}

int ReadBit(struct BitSet *created, int x, int y)
{
    int returnValue = 2;
    switch (created->type)
    {
    case 0:
        if (x + 1 > created->width || y + 1 > created->length)
        {
            printf("Invalid coordinate fields. Bit not readed");
            return 2;
        }
        int shift = (created->length) * (x) + y;
        char *tVar = (created->bitset) + (shift) / 8;
        if ((*tVar & (1 << (8 - (shift % 8) - 1))) != 0)
        {
            returnValue = 1;
        }
        else
        {
            returnValue = 0;
        }
        break;
    case 1:

        break;
    default:
        printf("Invalid type field. Bad BitSet. Bit not readed");
        return 2;
    }
    return returnValue;
}

int TopologicSort(struct BitSet *a, int *colorArray, int *finishStack, int *finishStackInd, int *numberOfBlackTops, int whiteTop, int n)
{
    if (colorArray[whiteTop] == 0)
    {
        colorArray[whiteTop] = 1;
    }
    else
    {
        if (colorArray[whiteTop] == 1)
        {
            return 1;
        }
        else
        {
            if (colorArray[whiteTop] == 2)
            {
                return 0;
            }
        }
    }
    for (int i = n-1; i >-1; i--)
    {
        if ((ReadBit(a, whiteTop, i) == 1) && (i != whiteTop))
        {
            if (TopologicSort(a, colorArray, finishStack, finishStackInd, numberOfBlackTops, i, n))
            {
                return 1;
            }
        }
    }
    colorArray[whiteTop] = 2;
    *numberOfBlackTops += 1;
    finishStack[*finishStackInd] = whiteTop + 1;
    *finishStackInd += 1;
    return 0;
}

int main()
{
    int n, m;
    if (scanf("%d", &n) == 0)
    {
        printf("bad number of vertices");
        return 0;
    }
    struct BitSet *a = CreateBitSet(n, n, 0);
    if (scanf("%d", &m) == 0)
    {
        printf("bad number of lines");
        return 0;
    }
    int *colorArray = (int *)calloc(n, sizeof(int));
    int f, s;
    int exceptions = 0, counter = 0;

    for (int i = 0; i < m; i++)
    {
        if (scanf("%d%d", &f, &s) < 2)
        {
            break;
        }
        counter += 1;
        if (f == s)
        {
            exceptions = 1;
            break;
        }
        else
        {
            if ((f < 1 || f > n) || (s < 1 || s > n))
            {
                exceptions = 2;
            }
        }
        WriteBit(a, f - 1, s - 1, 1);
    }
    if (counter < m)
    {
        exceptions = 1;
    }
    if (n < 0 || n > 2000)
    {
        printf("bad number of vertices");
        return 0;
    }
    else
    {
        if (m < 0 || m > (n * (n - 1)) / 2)
        {
            printf("bad number of edges");
            return 0;
        }
        else
        {
            if (exceptions == 1)
            {
                printf("bad number of lines");
                return 0;
            }
            else
            {
                if (exceptions == 2)
                {
                    printf("bad vertex");
                    return 0;
                }
            }
        }
    }
    /*
    for(int i=0;i<n;i++)
    {
    	for(int ii=0;ii<n;ii++)
    	{
    		printf("%d ", ReadBit(a,i,ii));
		}
		printf("\n");
	}
	*/
    int numberOfWhiteTops = n;
    int *finishStack = malloc(sizeof(int) * n);
    int finishStackInd = 0;
    while (numberOfWhiteTops > 0)
    {
        int numberOfBlackTops = 0, whiteTop = 0;
        for (int i = 0; i < n; i++)
        {
            if (colorArray[i] == 0)
            {
                whiteTop = i;
                break;
            }
        }
        if (TopologicSort(a, colorArray, finishStack, &finishStackInd, &numberOfBlackTops, whiteTop, n))
        {
            printf("impossible to sort");
            return 0;
        }
        numberOfWhiteTops -= numberOfBlackTops;
    }
    for (int i = n - 1; i > -1; i--)
    {
        printf("%d", finishStack[i]);
    }
}
