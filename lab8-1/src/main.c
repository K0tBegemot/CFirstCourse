#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#define INT_MAX 2147483647

typedef struct Edges
{
    short int vertice1;
    short int vertice2;
    int length;
} Edges;

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

typedef struct Graph
{
    short int vertices;
    short int edges;
    int *adjacencyList;
} Graph;

Graph *CreateGraph(int n, int m, int *adjacencyList)
{
    Graph *a = (Graph *)malloc(sizeof(Graph));
    a->vertices = n;
    a->edges = m;
    if (adjacencyList)
    {
        a->adjacencyList = adjacencyList;
    }
    else
    {
        a->adjacencyList = (int *)calloc(((n * n) - (n * (n - 1)) / 2), sizeof(int));
    }
    return a;
}

void WriteLength(Graph *a, int vertice1, int vertice2, int length)
{
    if (vertice1 > vertice2)
    {
        int var;
        var = vertice1;
        vertice1 = vertice2;
        vertice2 = var;
    }
    int summ = (vertice1 * (vertice1 + 1)) / 2;
    (a->adjacencyList)[vertice1 * (a->vertices) + vertice2 - summ] = length;
}

int ReadLength(Graph *a, int vertice1, int vertice2)
{
    if (vertice1 > vertice2)
    {
        int var;
        var = vertice1;
        vertice1 = vertice2;
        vertice2 = var;
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

void FreeBitSet(BitSet *a)
{
    free(a->bitset);
    free(a);
}

void WriteToEdge(Edges *a, int counter, int vertex1, int vertex2, int length)
{
    (a + counter)->vertice1 = vertex1;
    (a + counter)->vertice2 = vertex2;
    (a + counter)->length = length;
}

Graph *PrimMinimumSpanningTree(Graph *a)
{
    Graph *b = CreateGraph(a->vertices, a->edges, 0);
    if (a->vertices)
    {
        BitSet *color = CreateBitSet(a->vertices, 1, 0);
        Edges *arrOfEdges = (Edges *)malloc(sizeof(Edges) * (a->edges));
        int counter1 = 0, counter2 = 0;
        for (int i = 0; i < (a->vertices); i++)
        {
            int var = ReadLength(a, 0, i);
            if (var)
            {
                WriteToEdge(arrOfEdges, counter1, 0, i, var);
                counter1 += 1;
            }
        }
        WriteBit(color, 0, 0, 1);
        counter2 += 1;
        while (counter2 < (a->vertices))
        {
            int min = INT_MAX;
            int nextVertex = 0, prevVertex = 0, ii = -1; // bit = 0; // counter3=0;
            for (int i = 0; i < counter1; i++)
            {
                if (((arrOfEdges + i)->length) <= (min) && ((arrOfEdges + i)->length > 0) && (ReadBit(color, 0, (arrOfEdges + i)->vertice2) == 0)) //|| ReadBit(color, 0, (arrOfEdges + i)->vertice1) == 0
                {
                    min = ((arrOfEdges + i)->length);
                    prevVertex = ((arrOfEdges + i)->vertice1);
                    nextVertex = ((arrOfEdges + i)->vertice2);
                    ii = i;
                    //bit = ReadBit(color, 0, (arrOfEdges + i)->vertice2);
                }
            }
            if ((ii == -1) && (counter2 < (a->vertices)))
            {
                FreeGraph(b);
                FreeBitSet(color);
                free(arrOfEdges);
                return 0;
            }
            if (ii != -1)
            {
                WriteLength(b, prevVertex, nextVertex, min);
                WriteToEdge(arrOfEdges, ii, 0, 0, 0);
                int rightVertex;
                /*
            if (bit == 0)
            {
            */
                WriteBit(color, 0, nextVertex, 1);
                rightVertex = nextVertex;
                /*
            }
            else
            {

                WriteBit(color, 0, prevVertex, 1);
                rightVertex = prevVertex;
            }
            */
                counter2 += 1;
                for (int i = rightVertex; i < (a->vertices); i++)
                {
                    int var = ReadLength(a, rightVertex, i);
                    if (var && ReadBit(color, 0, i) == 0)
                    {
                        WriteToEdge(arrOfEdges, counter1, rightVertex, i, var);
                        counter1 += 1;
                    }
                }
                for (int i = 0; i < rightVertex + 1; i++)
                {
                    int var = ReadLength(a, i, rightVertex);
                    if (var && ReadBit(color, 0, i) == 0)
                    {
                        WriteToEdge(arrOfEdges, counter1, rightVertex, i, var);
                        counter1 += 1;
                    }
                }
            }
        }
    }
    else
    {
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
    unsigned long long int ver1, ver2, len, counter = 0, error = 0;
    for (unsigned int i = 0; i < m; i++)
    {
        if (fscanf(fin, "%llu%llu%llu", &ver1, &ver2, &len) == EOF)
        {
            break;
        }
        if (ver1 < 1 || ver1 > (unsigned int)n || ver2 < 1 || ver2 > (unsigned int)n)
        {
            error = 1;
            break;
        }
        if ((int)(len) < 0 || len > INT_MAX)
        {
            error = 2;
            break;
        }
        counter += 1;
        /*
        for(int i=0;i<n;i++)
        {
        	for(int ii=i;ii<n;ii++)
        	{
        		printf("%d ", ReadLength(a, i, ii));
			}
			printf("\n");
		}
		*/
        WriteLength(a, (int)(ver1) - 1, (int)(ver2) - 1, (int)(len));
        /*
        for(int i=0;i<n;i++)
        {
        	for(int ii=i;ii<n;ii++)
        	{
        		printf("%d ", ReadLength(a, i, ii));
			}
			printf("\n");
		}
		*/
    }
    if (counter != (unsigned int)m)
    {
        fprintf(fout, "bad number of lines");
        FreeGraph(a);
        FreeFILE(fin, fout);
        return 0;
    }
    if (error == 1)
    {
        fprintf(fout, "bad vertex");
        FreeGraph(a);
        FreeFILE(fin, fout);
        return 0;
    }
    if (error == 2)
    {
        fprintf(fout, "bad length");
        FreeGraph(a);
        FreeFILE(fin, fout);
        return 0;
    }
    Graph *b = PrimMinimumSpanningTree(a);
    if (b)
    {
        for (int i = 0; i < (b->vertices); i++)
        {
            for (int ii = i; ii < (b->vertices); ii++)
            {
                if (ReadLength(b, i, ii))
                {
                    fprintf(fout, "%d %d\n", i + 1, ii + 1);
                }
            }
        }
    }
    else
    {
        fprintf(fout, "no spanning tree");
        FreeGraph(a);
        FreeGraph(b);
        FreeFILE(fin, fout);
        return 0;
    }
    FreeGraph(a);
    FreeGraph(b);
    FreeFILE(fin, fout);
    return 0;
}
