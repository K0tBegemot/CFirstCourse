#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#define INT_MAX 2147483647
/*
typedef struct BitSet
{
    char *bitset;
    int length;
    int width;
    int type; // 0 - symmetrical; 1 - unsymmetrical;
}BitSet;

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

int ReadBit(BitSet *created, int x, int y)
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

int CheckForFullness(BitSet *a)
{
	int size = (a->length) * (a->width);
	int charSize;
	if(a->type)
	{
		int summ = (((a->width) - 1) * (a->width) / 2);
		charSize = ((size - summ) / 8 + (((size - summ) % 8) ? 1 : 0));
		
	}else
	{
		charSize = (size / 8 + ((size % 8) ? 1 : 0));
	}
	for(int i=0;i<charSize;i++)
	{
		if((a->bitset)[i]!=255)
		{
			return 1;
		}
	}
	return 0;
}
*/

typedef struct Edges
{
    int vertice1;
    int vertice2;
    int length;
} Edges;

typedef struct ConnectedComponents
{
    int *color;
    int *rank;
} ConnectedComponents;

typedef struct Graph
{
    int vertices;
    int edges;
    int edgesPointer;
    Edges *edge;
    ConnectedComponents *cc;
} Graph;

Graph *CreateGraph(int n, int m, Edges *b, ConnectedComponents *c)
{
    Graph *a = (Graph *)malloc(sizeof(Graph));
    a->vertices = n;
    a->edgesPointer = 0;
    a->edges = m;
    if (b)
    {
        a->edge = b;
    }
    else
    {
        a->edge = (Edges *)malloc(sizeof(Edges) * m);
    }
    if (c)
    {
        a->cc = c;
    }
    else
    {
        a->cc = 0;
    }
    return a;
}

void PushToEdges(Graph *a, int vertice1, int vertice2, int length)
{
    (a->edge + a->edgesPointer)->vertice1 = vertice1;
    (a->edge + a->edgesPointer)->vertice2 = vertice2;
    (a->edge + a->edgesPointer)->length = length;
    a->edgesPointer += 1;
}

void CreateConnectedComponents(Graph *a)
{
    a->cc = (ConnectedComponents *)malloc(sizeof(ConnectedComponents));
    a->cc->color = (int *)malloc(sizeof(int) * (a->vertices));
    for (int i = 0; i < a->vertices; i++)
    {
        (a->cc->color)[i] = i;
    }
    a->cc->rank = (int *)calloc(a->vertices, sizeof(int));
}

int FindConnectedComponent(Graph *a, int vertice)
{
    if (vertice == (a->cc->color)[vertice])
    {
        return vertice;
    }
    (a->cc->color)[vertice] = FindConnectedComponent(a, (a->cc->color)[vertice]);
    return (a->cc->color)[vertice];
}

void MergeConnectedComponent(Graph *a, int set1, int set2)
{
    assert((a->cc->color)[set1] == set1);
    assert((a->cc->color)[set2] == set2);
    if ((a->cc->rank)[set1] > (a->cc->rank)[set2])
    {
        (a->cc->color)[set2] = set1;
        (a->cc->rank)[set1] += (a->cc->rank)[set2];
    }
    else
    {
        (a->cc->color)[set1] = set2;
        (a->cc->rank)[set2] += (a->cc->rank)[set1];
    }
    if ((a->cc->rank)[set1] == (a->cc->rank)[set2])
    {
        (a->cc->rank)[set2] += 1;
    }
}

int Comparator(const void *edge1, const void *edge2)
{
	return ((((Edges*)edge1)->length) - (((Edges*)edge2)->length));
}

void SortEdge(Graph *a, Edges *sortedEdge)
{
	for(int i=0;i<a->edgesPointer;i++)
	{
		((sortedEdge+i)->length)=(a->edge + i)->length;
		((sortedEdge+i)->vertice1)=(a->edge + i)->vertice1;
		((sortedEdge+i)->vertice2)=(a->edge + i)->vertice2;
	}
	qsort(sortedEdge, a->edgesPointer, sizeof(Edges), Comparator);
}

void FreeGraph(Graph *a)
{
	if(a)
	{
		free(a->cc->color);
	free(a->cc->rank);
	free(a->edge);
	free(a);
	}
}

void FreeFILE(FILE *fin, FILE *fout)
{
	if(fin)
	{
		fclose(fin);
	}
	if(fout)
	{
		fclose(fout);
	}
}

Graph *CrusalMinimumSpanningTree(Graph *a)
{
    Edges *sortedEdge = (Edges *)malloc(sizeof(Edges) * (a->edges));
    SortEdge(a, sortedEdge);
    Graph *b = CreateGraph(a->vertices, a->edges, 0, 0);
    CreateConnectedComponents(b);
    int counter = 0;
    for (int i = 0; i < a->edges; i++)
    {
        int set1 = FindConnectedComponent(b, (sortedEdge + i)->vertice1);
        int set2 = FindConnectedComponent(b, (sortedEdge + i)->vertice2);
        if (set1 != set2)
        {
            PushToEdges(b, (sortedEdge + i)->vertice1, (sortedEdge + i)->vertice2, (sortedEdge + i)->length);
            counter += 1;
            MergeConnectedComponent(b, set1, set2);
        }
    }
    b->edges = counter;
    int color0=(b->cc->color)[0];
    //printf("%d ", b->vertices);
    for(int i=0;i<b->vertices;i++)
    {
    	//printf("bad");
    	//printf("%d ", (b->cc->color)[i]);
    	if(((b->cc->color)[i])!=(color0))
    	{
    		free(sortedEdge);
    		FreeGraph(b);
    		b=0;
    		break;
		}
	}
    return b;
}

int main()
{
    int n, m;
    FILE *fin = fopen("in.txt", "r");
    FILE *fout = fopen("out.txt", "w");
    if(fscanf(fin, "%d%d", &n, &m)<2)
    {
    	fprintf(fout, "bad input");
    	FreeFILE(fin,fout);
    	return 0;
	}
    Graph *a = CreateGraph(n, m, 0, 0);
    CreateConnectedComponents(a);
    int ver1, ver2, len, counter = 0, error = 0;
    for (int i = 0; i < m; i++)
    {
        if (fscanf(fin, "%d%d%d", &ver1, &ver2, &len) == EOF)
        {
            break;
        }
        if (ver1 < 1 || ver1 > n || ver2 < 1 || ver2 > n)
        {
            error = 1;
        }
        if (len < 0 || len > INT_MAX)
        {
            error = 2;
        }
        counter += 1;
        PushToEdges(a, ver1 - 1, ver2 - 1, len);
    }
    if (n < 0 || n > 5000)
    {
        fprintf(fout, "bad number of vertices");
        FreeGraph(a);
        FreeFILE(fin,fout);
        return 0;
    }
    if (m < 0 || m > ((n * (n - 1)) / 2))
    {
        fprintf(fout, "bad number of edges");
        FreeGraph(a);
        FreeFILE(fin,fout);
        return 0;
    }
    if (counter != m)
    {
        fprintf(fout, "bad number of lines");
        FreeGraph(a);
        FreeFILE(fin,fout);
        return 0;
    }
    if (error == 1)
    {
        fprintf(fout, "bad vertex");
        FreeGraph(a);
        FreeFILE(fin,fout);
        return 0;
    }
    if (error == 2)
    {
        fprintf(fout, "bad length");
        FreeGraph(a);
        FreeFILE(fin,fout);
        return 0;
    }
    Graph *b = CrusalMinimumSpanningTree(a);
    if (b)
    {
        int q, w;
        for (int i = 0; i < (b->edges); i++)
        {
            q = ((b->edge + i)->vertice1);
            w = ((b->edge + i)->vertice2);
            if (q < w)
            {
                fprintf(fout, "%d %d\n", q+1, w+1);
            }
            else
            {
                fprintf(fout, "%d %d\n", w+1, q+1);
            }
        }
    }
    else
    {
        fprintf(fout, "no spanning tree");
        FreeGraph(a);
        FreeGraph(b);
        FreeFILE(fin,fout);
        return 0;
    }
    return 0;
}
