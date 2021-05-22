#include <stdio.h>
#include <stdlib.h>

typedef struct BitSet
{
    char *bitset;
    int length;
    int width;
    int type; // 0 - symmetrical; 1 - unsymmetrical;
} BitSet;

BitSet *CreateBitSet(int length, int width, int type)
{
    if (length == 0 || width == 0)
    {
        //printf("Invalid length or value field. Bitset not created\n");
        return 0;
    }
    BitSet *created = (struct BitSet *)malloc(sizeof(struct BitSet));
    int size = length * width;
    created->bitset = (char *)calloc((size / 8 + ((size % 8) ? 1 : 0)), sizeof(char));
    created->length = length;
    created->width = width;
    created->type = type;
    return created;
}

int WriteBit(BitSet *created, int x, int y, int bit)
{
    int returnValue = 0;
    if (created != 0)
    {
        if (x + 1 > created->width || y + 1 > created->length || x < 0 || y < 0)
        {
            //printf("Invalid coordinate fields. Bit not writed\n");
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
    }
    return returnValue;
}

int ReadBit(BitSet *created, int x, int y)
{
    int returnValue = 2;
    if (created != 0)
    {
        if (x + 1 > created->width || y + 1 > created->length || x < 0 || y < 0)
        {
            //printf("Invalid coordinate fields. Bit not readed\n");
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
    }
    return returnValue;
}

int TopologicSortAuxilary(BitSet *bitSet, int *colorArray, int *finishStack, int *finishStackInd, int *numberOfBlackTops, int whiteTop)
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
    for (int i = bitSet->length - 1; i > -1; i--)
    {
        if (ReadBit(bitSet, whiteTop, i) == 1)
        {
            if (TopologicSortAuxilary(bitSet, colorArray, finishStack, finishStackInd, numberOfBlackTops, i))
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

int TopologicSort(BitSet *bitSet, int *finishStack)
{
    int *colorArray = (int *)calloc(bitSet->length, sizeof(int));
    int numberOfWhiteTops = bitSet->length;
    int finishStackIndex = 0;
    while (numberOfWhiteTops > 0)
    {
        int numberOfBlackTopsLocal = 0, whiteTop = 0;
        for (int i = 0; i < bitSet->length; i++)
        {
            if (colorArray[i] == 0)
            {
                whiteTop = i;
                break;
            }
        }
        if (TopologicSortAuxilary(bitSet, colorArray, finishStack, &finishStackIndex, &numberOfBlackTopsLocal, whiteTop))
        {
            free(colorArray);
            return 0;
        }
        numberOfWhiteTops -= numberOfBlackTopsLocal;
    }
    return bitSet->length;
}

void FreeAll(FILE *fin, FILE *fout, int *finishStack, BitSet *a)
{
    if (fin)
    {
        fclose(fin);
    }
    if (fout)
    {
        fclose(fout);
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
    if (fscanf(fin, "%d%d", &n, &m) < 2)
    {
        fprintf(fout, "bad number of lines");
        FreeAll(fin, fout, 0, 0);
        return 0;
    }
    if ((n < 0) && (m < 0))
    {
        fprintf(fout, "bad number of lines");
        FreeAll(fin, fout, 0, 0);
        return 0;
    }
    if (n < 0 || n > 2000)
    {
        fprintf(fout, "bad number of vertices");
        FreeAll(fin, fout, 0, 0);
        return 0;
    }
    if (m < 0 || m > (n * (n - 1)) / 2)
    {
        fprintf(fout, "bad number of edges");
        FreeAll(fin, fout, 0, 0);
        return 0;
    }
    int f, s;
    BitSet *bitSet = CreateBitSet(n, n, 0);
    for (int i = 0; i < m; i++)
    {
        if (fscanf(fin, "%d%d", &f, &s) < 2)
        {
            fprintf(fout, "bad number of lines");
            FreeAll(fin, fout, 0, bitSet);
            return 0;
        }
        if ((f < 1 || f > n) || (s < 1 || s > n))
        {
            fprintf(fout, "bad vertex");
            FreeAll(fin, fout, 0, bitSet);
            return 0;
        }
        else
        {
            WriteBit(bitSet, f - 1, s - 1, 1);
        }
    }
    int *finishStack = malloc(sizeof(int) * n);
    if (TopologicSort(bitSet, finishStack) == n)
    {
        for (int i = n - 1; i > -1; i--)
        {
            fprintf(fout, "%d ", finishStack[i]);
        }
    }
    else
    {
        fprintf(fout, "impossible to sort");
    }
    FreeAll(fin, fout, finishStack, bitSet);
    return 0;
}
