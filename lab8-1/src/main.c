#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <limits.h>

typedef struct Graph
{
    short int vertices;
    short int edges;
    int *adjacencyList;
} Graph;

typedef struct BitSet
{
    char *bitset;
    int length;
    int width;
    int type; // 0 - symmetrical; 1 - unsymmetrical;
} BitSet;

typedef struct Edges
{
    short int vertice1;
    short int vertice2;
    int length;
} Edges;

Graph *CreateGraph(int n, int m)
{
    Graph *a = (Graph *)malloc(sizeof(Graph));
    a->vertices = n;
    a->edges = m;
    a->adjacencyList = (int *)calloc(((n * n) - (n * (n - 1)) / 2), sizeof(int));
    return a;
}
int Swap(int *a, int *b)
{
    int var;
    var = *a;
    *a = *b;
    *b = var;
}
void WriteLength(Graph *a, int vertice1, int vertice2, int length)
{
    if (vertice1 > vertice2)
    {
        Swap(&vertice1, &vertice2);
    }
    int summ = (vertice1 * (vertice1 + 1)) / 2;
    (a->adjacencyList)[vertice1 * (a->vertices) + vertice2 - summ] = length;
}

int ReadLength(Graph *a, int vertice1, int vertice2)
{
    if (vertice1 > vertice2)
    {
        Swap(&vertice1, &vertice2);
    }
    int summ = (vertice1 * (vertice1 + 1)) / 2;
    return (a->adjacencyList)[vertice1 * (a->vertices) + vertice2 - summ];
}

void FreeGraph(Graph *a)
{
    if (a)
    {
        free(a->adjacencyList);
        free(a);
    }
}

BitSet *CreateBitSet(int length, int width, int type)
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

int WriteBit(BitSet *created, int x, int y, int bit)
{
    int returnValue = 1;
    if (created != 0)
    {
        if (x + 1 > created->width || y + 1 > created->length || x < 0 || y < 0)
        {
            //printf("Invalid coordinate fields. Bit not writed");
            return 0;
        }
        int shift;
        int summ;
        switch (created->type)
        {
        case 0:
            shift = (created->length) * (x) + y;
            break;
        case 1:
            summ = ((x + 1) * x) / 2;
            shift = (created->length) * (x) + y - summ;
            break;
        default:
            //printf("Invalid type field. Bad BitSet. Bit not writed");
            return 1;
        }
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
        returnValue = 0;
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
            //printf("Invalid coordinate fields. Bit not readed");
            return 2;
        }
        int shift;
        int summ;
        switch (created->type)
        {
        case 0:
            shift = (created->length) * (x) + y;
            break;
        case 1:
            summ = ((x + 1) * x) / 2;
            shift = (created->length) * (x) + y - summ;
            break;
        default:
            //printf("Invalid type field. Bad BitSet. Bit not readed");
            return 2;
        }
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

void FreeBitSet(BitSet *a)
{
    if (a)
    {
        free(a->bitset);
        free(a);
    }
}

void FreeFILE(FILE *fin, FILE *fout)
{
    if (fin)
    {
        fclose(fin);
    }
    if (fout)
    {
        fclose(fout);
    }
}

void AddEdge(Edges *a, int counter, int vertex1, int vertex2, int length)
{
    (a + counter)->vertice1 = vertex1;
    (a + counter)->vertice2 = vertex2;
    (a + counter)->length = length;
}

int Comparator(const void *edge1, const void *edge2)
{
    return ((((Edges *)edge1)->length) - (((Edges *)edge2)->length));
}

Graph *PrimMinimumSpanningTree(Graph *a)
{
    Graph *b = CreateGraph(a->vertices, a->edges);
    if (a->vertices)
    {
        BitSet *color = CreateBitSet(a->vertices, 1, 0);
        int *distancesToPoints;
        int *parents;
        distancesToPoints = (int *)calloc(a->vertices, sizeof(int));
        parents = (int *)malloc((a->vertices) * sizeof(int));
        for (int i = 0; i < a->vertices; i++)
        {
            if (i == 0)
            {
                parents[0] = 0;
                continue;
            }
            parents[i] = -1;
        }
        int counter = 0;
        WriteBit(color, 0, 0, 1);
        counter += 1;
        int minVertex = 0;
        while (counter < (a->vertices))
        {
            int localCounter = 0;
            for (int i = 0; i < a->vertices; i++)
            {
                if (i != minVertex)
                {
                    int var = ReadLength(a, minVertex, i);
                    if (var != 0)
                    {
                        if ((ReadBit(color, 0, i) == 0) && ((distancesToPoints[i] == 0) ? 1 : (var < distancesToPoints[i])))
                        {
                            distancesToPoints[i] = var;
                            parents[i] = minVertex;
                        }
                        localCounter += 1;
                    }
                }
            }
            if (localCounter == 0)
            {
                FreeGraph(b);
                b = 0;
                break;
            }
            int var = INT_MAX, number = -1;
            for (int i = 0; i < a->vertices; i++)
            {
                if (i != minVertex)
                {
                    if (ReadBit(color, 0, i) == 0)
                    {
                        if ((distancesToPoints[i] == 0) ? 0 : (distancesToPoints[i] <= var))
                        {
                            var = distancesToPoints[i];
                            number = i;
                        }
                    }
                }
            }
            minVertex = number;
            WriteBit(color, 0, minVertex, 1);
            counter += 1;
        }
        if (b)//Output to the graph and to the screen. Lines related to the output to the screen are highlighted: //
        {
            Edges *edge = (Edges *)malloc(sizeof(Edges) * (b->vertices));//
            int localCounter = 0;//
            for (int i = 0; i < b->vertices; i++)
            {
                if (ReadBit(color, 0, i) == 0)
                {
                    FreeGraph(b);
                    b = 0;
                    break;
                }
                else
                {
                    WriteLength(b, parents[i], i, distancesToPoints[i]);
                    AddEdge(edge, localCounter, parents[i], i, distancesToPoints[i]);//
                    localCounter += 1;//
                }
            }
            if (b)//
            {//
                qsort(edge, localCounter, sizeof(Edges), Comparator);//
                for (int i = 0; i < localCounter; i++)//
                {//
                    if (((edge + i)->length) != 0)//
                    {//
                        printf("%d %d\n", ((edge + i)->vertice1) + 1, ((edge + i)->vertice2) + 1);//
                    }//
                }//
            }//
            free(edge);//
        }
        FreeBitSet(color);
        free(distancesToPoints);
        free(parents);
    }
    else
    {
        FreeGraph(b);
        b = 0;
    }
    return b;
}

int main()
{
    int n, m;
    FILE *fin = fopen("in.txt", "r");
    FILE *fout = fopen("out.txt", "w");
    if (fscanf(fin, "%d%d", &n, &m) < 2)
    {
        fprintf(fout, "bad input");
        FreeFILE(fin, fout);
        return 0;
    }
    if (n < 0 || n > 5000)
    {
        fprintf(fout, "bad number of vertices");
        FreeFILE(fin, fout);
        return 0;
    }
    if (m < 0 || m > ((n * (n - 1)) / 2))
    {
        fprintf(fout, "bad number of edges");
        FreeFILE(fin, fout);
        return 0;
    }
    Graph *a = CreateGraph(n, m, 0);
    int ver1, ver2, len;
    for (int i = 0; i < m; i++)
    {
        if (fscanf(fin, "%d%d%d", &ver1, &ver2, &len) < 3)
        {
            fprintf(fout, "bad number of lines");
            FreeGraph(a);
            FreeFILE(fin, fout);
            return 0;
        }
        if (ver1 < 1 || ver1 > n || ver2 < 1 || ver2 > n)
        {
            fprintf(fout, "bad vertex");
            FreeGraph(a);
            FreeFILE(fin, fout);
            return 0;
        }
        if (len < 0 || len > INT_MAX)
        {
            fprintf(fout, "bad length");
            FreeGraph(a);
            FreeFILE(fin, fout);
            return 0;
        }
        WriteLength(a, ver1 - 1, ver2 - 1, len);
    }
    Graph *b = PrimMinimumSpanningTree(a);
    FreeGraph(a);
    if (!b)
    {
        fprintf(fout, "no spanning tree");
    }
    FreeGraph(b);
    FreeFILE(fin, fout);
    return 0;
}
