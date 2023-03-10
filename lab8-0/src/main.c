#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <limits.h>

typedef struct Edges
{
    short vertice1;
    short vertice2;
    int length;
} Edges;

typedef struct ConnectedComponents
{
    int vertices;
    short *color;
    short *rank;
} ConnectedComponents;

typedef struct Graph
{
    short vertices;
    int edges;
    int edgesPointer;
    Edges *edge;
} Graph;

Graph *CreateGraph(int n, int m)
{
    Graph *a = (Graph *)malloc(sizeof(Graph));
    a->vertices = n;
    a->edgesPointer = 0;
    a->edges = m;
    a->edge = (Edges *)malloc(sizeof(Edges) * m);
    return a;
}

void AddEdge(Graph *a, int vertice1, int vertice2, int length)
{
    (a->edge + a->edgesPointer)->vertice1 = vertice1;
    (a->edge + a->edgesPointer)->vertice2 = vertice2;
    (a->edge + a->edgesPointer)->length = length;
    a->edgesPointer += 1;
}

ConnectedComponents *CreateConnectedComponents(int vertices)
{
    ConnectedComponents *c = (ConnectedComponents *)malloc(sizeof(ConnectedComponents));
    c->color = (short *)malloc(sizeof(short) * (vertices));
    for (int i = 0; i < vertices; i++)
    {
        (c->color)[i] = i;
    }
    c->rank = (short *)calloc(vertices, sizeof(short));
    c->vertices = vertices;
    return c;
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
        free(c);
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

int IsOneComponent(ConnectedComponents *c)
{
    int color0 = (c->color)[0];
    for (int i = 0; i < c->vertices; i++)
    {
        if ((c->color[i]) != (color0))
        {
            return 1;
        }
    }
    return 0;
}

Graph *KruskalMinimumSpanningTree(Graph *a)
{
    Edges *sortedEdge = (Edges *)malloc(sizeof(Edges) * (a->edges));
    SortEdge(a, sortedEdge);
    Graph *b = CreateGraph(a->vertices, a->edges);
    ConnectedComponents *c = CreateConnectedComponents(a->vertices);
    if (a->vertices)
    {
        int newNumberOfEdges = 0;
        for (int i = 0; i < b->edges; i++)
        {
            int set1 = FindConnectedComponent(c, (sortedEdge + i)->vertice1);
            int set2 = FindConnectedComponent(c, (sortedEdge + i)->vertice2);
            if (set1 != set2)
            {
                AddEdge(b, (sortedEdge + i)->vertice1, (sortedEdge + i)->vertice2, (sortedEdge + i)->length);
                newNumberOfEdges += 1;
                MergeConnectedComponent(c, set1, set2);
            }
        }
        b->edges = newNumberOfEdges;
        if (IsOneComponent(c))
        {
            FreeGraph(b);
            b = 0;
        }
    }
    else
    {
        FreeGraph(b);
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
    Graph *a = CreateGraph(n, m);
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
        if (len < 0)
        {
            fprintf(fout, "bad length");
            FreeGraph(a);
            FreeFILE(fin, fout);
            return 0;
        }
        AddEdge(a, ver1 - 1, ver2 - 1, len);
    }
    Graph *b = KruskalMinimumSpanningTree(a);
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
    }
    FreeGraph(a);
    FreeGraph(b);
    FreeFILE(fin, fout);
    return 0;
}
