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

typedef struct Edge
{
    short int vertice1;
    short int vertice2;
    int length;
} Edge;

typedef struct Edges
{
    int numberOfEdges;
    Edge *edges;
} Edges;

Edges *CreateEdges(int numberOfEdges)
{
    Edges *edges = (Edges *)malloc(sizeof(Edges));
    edges->edges = (Edge *)calloc(numberOfEdges, sizeof(Edge));
    edges->numberOfEdges = numberOfEdges;
    return edges;
}

Graph *CreateGraph(int n, int m)
{
    Graph *a = (Graph *)malloc(sizeof(Graph));
    a->vertices = n;
    a->edges = m;
    a->adjacencyList = (int *)calloc(((n * n) - (n * (n - 1)) / 2), sizeof(int));
    return a;
}
void Swap(int *a, int *b)
{
    int var;
    var = *a;
    *a = *b;
    *b = var;
}
void ChangeDistanceBetweenVertices(Graph *graph, int vertice1, int vertice2, int length)
{
    if (vertice1 > vertice2)
    {
        Swap(&vertice1, &vertice2);
    }
    int summ = (vertice1 * (vertice1 + 1)) / 2;
    (graph->adjacencyList)[vertice1 * (graph->vertices) + vertice2 - summ] = length;
}

int FindOutDistanceBetweenVertices(Graph *graph, int vertice1, int vertice2)
{
    if (vertice1 > vertice2)
    {
        Swap(&vertice1, &vertice2);
    }
    int summ = (vertice1 * (vertice1 + 1)) / 2;
    return (graph->adjacencyList)[vertice1 * (graph->vertices) + vertice2 - summ];
}

void FreeEdges(Edges *edges)
{
    if (edges)
    {
        if (edges->edges)
        {
            free(edges->edges);
        }
        free(edges);
    }
}

void FreeGraph(Graph *graph)
{
    if (graph)
    {
        free(graph->adjacencyList);
        free(graph);
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

void FreeBitSet(BitSet *bitSet)
{
    if (bitSet)
    {
        if (bitSet->bitset)
        {
            free(bitSet->bitset);
        }
        free(bitSet);
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

void AddEdge(Edges *edges, int counter, int vertex1, int vertex2, int length)
{
    if (counter < edges->numberOfEdges)
    {
        (edges->edges + counter)->vertice1 = vertex1;
        (edges->edges + counter)->vertice2 = vertex2;
        (edges->edges + counter)->length = length;
    }
}

int Comparator(const void *edge1, const void *edge2)
{
    return ((((Edge *)edge1)->length) - (((Edge *)edge2)->length));
}

Edges *PrimMinimumSpanningTree(Graph *graph)
{
    //printf("%d ", graph->vertices);
    Edges *edges = CreateEdges(graph->vertices);
    if (graph->vertices)
    {
        BitSet *color = CreateBitSet(graph->vertices, 1, 0);
        int *distancesToPoints, *parents;
        distancesToPoints = (int *)calloc(graph->vertices, sizeof(int));
        parents = (int *)malloc((graph->vertices) * sizeof(int));
        for (int i = 0; i < graph->vertices; i++)
        {
            parents[i] = -1;
        }
        parents[0] = 0;
        int counter = 0;
        WriteBit(color, 0, 0, 1);
        counter += 1;
        int minVertex = 0;
        while (counter < (graph->vertices))
        {
            int localCounter = 0;
            for (int i = 0; i < graph->vertices; i++)
            {
                if (i != minVertex)
                {
                    int distanceBetweenVertices = FindOutDistanceBetweenVertices(graph, minVertex, i);
                    if (distanceBetweenVertices != 0)
                    {
                        if ((ReadBit(color, 0, i) == 0) && ((distancesToPoints[i] == 0) ? 1 : (distanceBetweenVertices < distancesToPoints[i])))
                        {
                            distancesToPoints[i] = distanceBetweenVertices;
                            parents[i] = minVertex;
                        }
                        localCounter += 1;
                    }
                }
            }
            if (localCounter == 0)
            {
                FreeEdges(edges);
                edges = 0;
                break;
            }
            int minimalDistanceToVertex = INT_MAX, number = -1;
            for (int i = 0; i < graph->vertices; i++)
            {
                if (i != minVertex)
                {
                    if (ReadBit(color, 0, i) == 0)
                    {
                        if ((distancesToPoints[i] == 0) ? 0 : (distancesToPoints[i] <= minimalDistanceToVertex))
                        {
                            minimalDistanceToVertex = distancesToPoints[i];
                            number = i;
                        }
                    }
                }
            }
            minVertex = number;
            WriteBit(color, 0, minVertex, 1);
            counter += 1;
        }
        if (edges)
        {
            int localCounter = 0;
            for (int i = 0; i < graph->vertices; i++)
            {
                if (ReadBit(color, 0, i) == 0)
                {
                    free(edges);
                    edges = 0;
                    break;
                }
                else
                {
                    AddEdge(edges, localCounter, parents[i], i, distancesToPoints[i]);
                    localCounter += 1;
                }
            }
            if (edges)
            {
                qsort(edges->edges, localCounter, sizeof(Edge), Comparator);
            }
        }
        FreeBitSet(color);
        free(distancesToPoints);
        free(parents);
    }
    else
    {
        FreeEdges(edges);
        edges = 0;
    }
    return edges;
}

void PrintMinimalSpanningTree(Edges *edges)
{
    for (int i = 0; i < edges->numberOfEdges; i++)
    {
        if (((edges->edges + i)->length) != 0)
        {
            printf("%d %d\n", ((edges->edges + i)->vertice1) + 1, ((edges->edges + i)->vertice2) + 1);
        }
    }
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
    Graph *graph = CreateGraph(n, m);
    int ver1, ver2, len;
    for (int i = 0; i < m; i++)
    {
        if (fscanf(fin, "%d%d%d", &ver1, &ver2, &len) < 3)
        {
            fprintf(fout, "bad number of lines");
            FreeGraph(graph);
            FreeFILE(fin, fout);
            return 0;
        }
        if (ver1 < 1 || ver1 > n || ver2 < 1 || ver2 > n)
        {
            fprintf(fout, "bad vertex");
            FreeGraph(graph);
            FreeFILE(fin, fout);
            return 0;
        }
        if (len < 0)
        {
            fprintf(fout, "bad length");
            FreeGraph(graph);
            FreeFILE(fin, fout);
            return 0;
        }
        ChangeDistanceBetweenVertices(graph, ver1 - 1, ver2 - 1, len);
    }
    Edges *edges = PrimMinimumSpanningTree(graph);
    FreeGraph(graph);
    if (edges)
    {
        PrintMinimalSpanningTree(edges);
    }
    else
    {
        fprintf(fout, "no spanning tree");
    }
    FreeEdges(edges);
    FreeFILE(fin, fout);
    return 0;
}
