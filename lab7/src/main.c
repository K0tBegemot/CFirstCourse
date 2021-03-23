#include <stdio.h>
#include <stdlib.h>

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
        //printf("Invalid length or value field. Bitset not created");
        return 0;
    }
    struct BitSet *created = (struct BitSet *)malloc(sizeof(struct BitSet));
    created->bitset = 0;
    int size = length * width;
    int summ;
    switch (type)
    {
    case 0:
        created->bitset = (char *)calloc((size / 8 + ((size % 8) ? 1 : 0)), sizeof(char));
        break;
    case 1:
        summ = ((width - 1) * width / 2);
        created->bitset = (char *)calloc(((size - summ) / 8 + (((size - summ) % 8) ? 1 : 0)), sizeof(char));
        break;
    default:
        //printf("Invalid type field. Bitset not created");
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
    int returnValue = 0;
    if (created != 0)
    {
        switch (created->type)
        {
        case 0:
            if (x + 1 > created->width || y + 1 > created->length || x < 0 || y < 0)
            {
                //printf("Invalid coordinate fields. Bit not writed");
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
            //printf("Invalid type field. Bad BitSet. Bit not writed");
            return 0;
        }
    }
    return returnValue;
}

int ReadBit(struct BitSet *created, int x, int y)
{
    int returnValue = 2;
    if (created != 0)
    {
        switch (created->type)
        {
        case 0:
            if (x + 1 > created->width || y + 1 > created->length || x < 0 || y < 0)
            {
                //printf("Invalid coordinate fields. Bit not readed");
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
            //printf("Invalid type field. Bad BitSet. Bit not readed");
            return 2;
        }
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
    for (int i = n - 1; i > -1; i--)
    {
        if (ReadBit(a, whiteTop, i) == 1)
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

void FreeAll(FILE *fin, FILE *fout, int *colorArray, int *existOfEdge, int *finishStack, struct BitSet *a)
{
    fclose(fin);
    fclose(fout);
    if (colorArray)
    {
        free(colorArray);
    }
    if (existOfEdge)
    {
        free(existOfEdge);
    }
    if (finishStack)
    {
        free(finishStack);
    }
    if (a)
    {
        if (a->bitset)
        {
            free(a->bitset);
        }
        free(a);
    }
}

int main()
{
    FILE *fin = fopen("in.txt", "r");
    FILE *fout = fopen("out.txt", "w");
    int n, m;
    if (fscanf(fin, "%d", &n) == EOF)
    {
        fprintf(fout, "bad number of lines");
        FreeAll(fin,fout,0,0,0,0);
        return 0;
    }
    if (fscanf(fin, "%d", &m) == EOF)
    {
        fprintf(fout, "bad number of lines");
        FreeAll(fin,fout,0,0,0,0);
        return 0;
    }
    int *colorArray = (int *)calloc(n, sizeof(int));
    int *existOfEdge = (int *)calloc(n, sizeof(int));
    int f, s;
    int exceptions = 0, counter = 0;
    struct BitSet *a = CreateBitSet(n, n, 0);
    for (int i = 0; i < m; i++)
    {
        if (fscanf(fin, "%d%d", &f, &s) == EOF)
        {
            break;
        }
        counter += 1;
        if ((f < 1 || f > n) || (s < 1 || s > n))
        {
            exceptions = 2;
        }
        else
        {
            existOfEdge[f - 1] = 1;
            WriteBit(a, f - 1, s - 1, 1);
        }
    }
    if (counter != m)
    {
        exceptions = 1;
    }
    if (n >= 0 && m >= 0)
    {
        if (n > 2000)
        {
            fprintf(fout, "bad number of vertices");
            FreeAll(fin,fout,colorArray,existOfEdge,0,a);
            return 0;
        }
        if (m < 0 || m > (n * (n - 1)) / 2)
        {
            fprintf(fout, "bad number of edges");
            FreeAll(fin,fout,colorArray,existOfEdge,0,a);
            return 0;
        }
        if (exceptions == 1)
        {
            fprintf(fout, "bad number of lines");
            FreeAll(fin,fout,colorArray,existOfEdge,0,a);
            return 0;
        }
        if (exceptions == 2)
        {
            fprintf(fout, "bad vertex");
            FreeAll(fin,fout,colorArray,existOfEdge,0,a);
            return 0;
        }
    }
    else
    {
        fprintf(fout, "bad number of lines");
        FreeAll(fin,fout,colorArray,existOfEdge,0,a);
        return 0;
    }
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
                existOfEdge[i] = 0;
                whiteTop = i;
                break;
            }
        }
        if (TopologicSort(a, colorArray, finishStack, &finishStackInd, &numberOfBlackTops, whiteTop, n))
        {
            fprintf(fout, "impossible to sort");
            FreeAll(fin,fout,colorArray,existOfEdge,finishStack,a);
            return 0;
        }
        numberOfWhiteTops -= numberOfBlackTops;
    }
    for (int i = n - 1; i > -1; i--)
    {
        fprintf(fout, "%d ", finishStack[i]);
    }
    FreeAll(fin,fout,colorArray,existOfEdge,finishStack,a);
    return 0;
}
