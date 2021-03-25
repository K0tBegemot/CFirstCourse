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

typedef struct ConnectedComponents
{
    int vertices;
    short int *color;
    short int *rank;
} ConnectedComponents;

typedef struct Graph
{
    short int vertices;
    int edges;
    Edges *edge;
} Graph;

Graph *CreateGraph(int n, int m, Edges *b)
{
    Graph *a = (Graph *)malloc(sizeof(Graph));
    a->vertices = n;
    a->edges = m;
    if (b)
    {
        a->edge = b;
    }
    else
    {
        a->edge = (Edges *)malloc(sizeof(Edges) * m);
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

ConnectedComponents *CreateConnectedComponents(int vertices)
{
    ConnectedComponents *c = (ConnectedComponents *)malloc(sizeof(ConnectedComponents));
    c->color = (short int *)malloc(sizeof(short int) * (vertices));
    for (int i = 0; i < vertices; i++)
    {
        (c->color)[i] = i;
    }
    c->rank = (short int *)calloc(vertices, sizeof(short int));
    c->vertices = vertices;
}

int FindConnectedComponent(ConnectedComponents *c, int vertice)
{
    if (vertice == (c->color)[vertice])
    {
        return vertice;
    }
    (c->color)[vertice] = FindConnectedComponent(c, (c->color)[vertice]);
    return (c->color)[vertice];
}

void MergeConnectedComponent(ConnectedComponents *c, int set1, int set2)
{
    assert((c->color)[set1] == set1);
    assert((c->color)[set2] == set2);
    if ((c->rank)[set1] > (c->rank)[set2])
    {
        (c->color)[set2] = set1;
        (c->rank)[set1] += (c->rank)[set2];
    }
    else
    {
        (c->color)[set1] = set2;
        (c->rank)[set2] += (c->rank)[set1];
    }
    for (int i = 0; i < c->vertices; i++)
    {
        FindConnectedComponent(c, i);
    }
    if (((c->rank)[set1] == (c->rank)[set2]) && ((c->rank)[set2] == 0))
    {
        (c->rank)[set2] += 1;
    }
}

int Comparator(const void *edge1, const void *edge2)
{
    return ((((Edges *)edge1)->length) - (((Edges *)edge2)->length));
}

void SortEdge(Graph *a, Edges *sortedEdge)
{
    for (int i = 0; i < a->edgesPointer; i++)
    {
        ((sortedEdge + i)->length) = (a->edge + i)->length;
        ((sortedEdge + i)->vertice1) = (a->edge + i)->vertice1;
        ((sortedEdge + i)->vertice2) = (a->edge + i)->vertice2;
    }
    qsort(sortedEdge, a->edgesPointer, sizeof(Edges), Comparator);
}

void FreeGraph(Graph *a)
{
    if (a)
    {
        free(a->edge);
        free(a);
    }
}

void FreeCC(ConnectedComponents *c)
{
    if (c)
    {
        free(c->color);
        free(c->rank);
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

Graph *CrusalMinimumSpanningTree(Graph *a)
{
    Edges *sortedEdge = (Edges *)malloc(sizeof(Edges) * (a->edges));
    SortEdge(a, sortedEdge);
    Graph *b = CreateGraph(a->vertices, a->edges, 0);
    ConnectedComponents *c = CreateConnectedComponents(a->vertices);
    if (a->vertices)
    {
        int counter = 0;
        for (int i = 0; i < a->edges; i++)
        {
            int set1 = FindConnectedComponent(c, (sortedEdge + i)->vertice1);
            int set2 = FindConnectedComponent(c, (sortedEdge + i)->vertice2);
            if (set1 != set2)
            {
                PushToEdges(b, (sortedEdge + i)->vertice1, (sortedEdge + i)->vertice2, (sortedEdge + i)->length);
                counter += 1;
                MergeConnectedComponent(c, set1, set2);
            }
        }
        b->edges = counter;
        int color0 = (c->color)[0];
        for (int i = 0; i < a->vertices; i++)
        {
            if (((c->color)[i]) != (color0))
            {
                free(sortedEdge);
                FreeGraph(b);
                FreeCC(c);
                b = 0;
                break;
            }
        }
    }
    else
    {
        free(sortedEdge);
        FreeGraph(b);
        FreeCC(c);
        b = 0;
    }
    free(sortedEdge);
    FreeCC(c);
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
    if (counter != m)
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
    Graph *b = CrusalMinimumSpanningTree(a);
    if (b)
    {
        for (int i = 0; i < (b->edges); i++)
        {
            int q, w;
            q = ((b->edge + i)->vertice1);
            w = ((b->edge + i)->vertice2);
            if (q < w)
            {
                fprintf(fout, "%d %d\n", q + 1, w + 1);
            }
            else
            {
                fprintf(fout, "%d %d\n", w + 1, q + 1);
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
