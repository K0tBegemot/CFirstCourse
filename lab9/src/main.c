#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct IncidentEdge
{
    int vertex;
    int weight;
} IncidentEdge;

typedef struct Vertex
{
    IncidentEdge **edges;
    int edges_len;
    int edges_size;
    int dist;
    int prev;
    int visited;
    short badWays;
} Vertex;

typedef struct Graph
{
    Vertex **vertices;
    int vertices_len;
    int vertices_size;
} Graph;

typedef struct BHeap
{
    int *data;
    int *prio;
    int *index;
    int len;
    int size;
} BHeap;

Graph *CreateGraph(int l)
{
    Graph *a = calloc(1, sizeof(Graph));
    a->vertices = calloc(l, sizeof(Vertex *));
    for (int i = 0; i < l; i++)
    {
        a->vertices[i] = calloc(1, sizeof(Vertex));
    }
    a->vertices_size = l;
    a->vertices_len = 0;
    return a;
}

void AddVertex(Graph *g, int i)
{
    if (g->vertices_size < i + 1)
    {
        int size = g->vertices_size * 2 > i ? g->vertices_size * 2 : i + 4;
        g->vertices = realloc(g->vertices, size * sizeof(Vertex *));
        for (int j = g->vertices_size; j < size; j++)
            g->vertices[j] = NULL;
        g->vertices_size = size;
    }
    if (!g->vertices[i])
    {
        g->vertices[i] = calloc(1, sizeof(Vertex));
        g->vertices_len += 1;
    }
}

void AddIncidentEdge(Vertex *v, int b, int w)
{
    if (v->edges_len >= v->edges_size)
    {
        v->edges_size = ((v->edges_size) ? v->edges_size * 2 : 4);
        v->edges = realloc(v->edges, v->edges_size * sizeof(IncidentEdge *));
    }
    IncidentEdge *e = calloc(1, sizeof(IncidentEdge));
    e->vertex = b;
    e->weight = w;
    v->edges[v->edges_len] = e;
    v->edges_len += 1;
}

void AddEdge(Graph *g, int a, int b, int w)
{
    AddVertex(g, a);
    AddVertex(g, b);
    Vertex *v = g->vertices[a];
    AddIncidentEdge(v, b, w);
	Vertex *v2 = g->vertices[b];
	AddIncidentEdge(v2, a, w);
}

BHeap *CreateHeap(int n)
{
    BHeap *h = calloc(1, sizeof(BHeap));
    h->data = calloc(n + 1, sizeof(int));
    h->prio = calloc(n + 1, sizeof(int));
    h->index = calloc(n + 1, sizeof(int));
    h->size = n+1;
    return h;
}

void PushHeap(BHeap *h, int v, int p)
{
    int i = h->index[v] == 0 ? ++h->len : h->index[v];
    int j = i / 2;
    while (i > 1)
    {
        if (h->prio[j] < p)
            break;
        h->data[i] = h->data[j];
        h->prio[i] = h->prio[j];
        h->index[h->data[i]] = i;
        i = j;
        j = j / 2;
    }
    h->data[i] = v;
    h->prio[i] = p;
    h->index[v] = i;
}

int Min(BHeap *h, int i, int j, int k)
{
    int m = i;
    if (j <= h->len && h->prio[j] < h->prio[m])
        m = j;
    if (k <= h->len && h->prio[k] < h->prio[m])
        m = k;
    return m;
}

int PopHeap(BHeap *h)
{
    int v = h->data[1];
    int i = 1;
    while (1)
    {
        int j = Min(h, h->len, 2 * i, 2 * i + 1);
        if (j == h->len)
            break;
        h->data[i] = h->data[j];
        h->prio[i] = h->prio[j];
        h->index[h->data[i]] = i;
        i = j;
    }
    h->data[i] = h->data[h->len];
    h->prio[i] = h->prio[h->len];
    h->index[h->data[i]] = i;
    h->len -= 1;
    return v;
}

void FreeHeap(BHeap *h)
{
	if(h)
	{
	free(h->data);
	free(h->index);
	free(h->prio);
	}
}

void Dijkstra(Graph *g, int a)
{
    int i, j;
    for (i = 0; i < g->vertices_size; i++)
    {
        Vertex *v = g->vertices[i];
        v->dist = INT_MAX;
        v->prev = 0;
        v->visited = 0;
        v->badWays = -1;
    }
    Vertex *v = g->vertices[a];
    v->dist = 0;
    BHeap *h = CreateHeap(g->vertices_len);
    PushHeap(h, a, v->dist);
    while (h->len)
    {
        i = PopHeap(h);
        //printf("%d ", i);
        v = g->vertices[i];
        v->visited = 1;
        /*
        if (i == b)
            break;
            */
        //printf("%d ", v->edges_len);
        for (j = 0; j < v->edges_len; j++)
        {
            IncidentEdge *e = v->edges[j];
            //printf("%d ", e->vertex);
            Vertex *u = g->vertices[e->vertex];
            if ((!(u->visited) && (v->dist + e->weight <= u->dist)) || u->dist < 0)
            {
                if (u->dist > 0)
                {
                    if (u->badWays < 0)
                    {
                        u->dist = v->dist + e->weight;
                        u->badWays = 0;
                        if (v->dist < 0)
                        {
                            u->badWays += 1;
                            u->dist = -1;
                        }
                        else
                        {
                            if (v->dist + e->weight < 0)
                            {
                                u->badWays += 1;
                                u->dist = -1;
                            }
                        }
                    }
                    else
                    {
                        if (v->dist + e->weight > 0)
                        {
                            u->dist = v->dist + e->weight;
                        }
                    }
                }
                else
                {
                    if (v->dist + e->weight > 0)
                    {
                        u->dist = v->dist + e->weight;
                        u->badWays = 0;
                    }
                    else
                    {
                        u->badWays += 1;
                    }
                }
                u->prev = i;
                PushHeap(h, e->vertex, u->dist);
            }
        }
        //printf("\n");
    }
    FreeHeap(h);
}

void FreeGraph(Graph *g)
{
	if(g)
	{
	for(int i=0;i<g->vertices_len;i++)
	{
		Vertex *v = g->vertices[i];
		if(v)
		{
		for(int ii=0;ii<v->edges_len;ii++)
		{
			IncidentEdge *e = v->edges[ii];
			if(e)
			{
			free(e);
			}
		}
		free(v);
		}
	}
	free(g);
	}
}

void FreeFILE(FILE* fin, FILE* fout)
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

void PrintPath(FILE *fin, FILE *fout, Graph *g, int i)
{
    int j;
    Vertex *v, *u;
    v = g->vertices[i];
    /*
    for (n = 1, u = v; u->dist; u = g->vertices[u->prev], n++)
        ;
    char *path = malloc(n);
    path[n - 1] = 'a' + i;
    for (j = 0, u = v; u->dist; u = g->vertices[u->prev], j++)
        printf("%d ", u->dist);
        */
    //printf("%d ", v->badWays);
    for (int i = 0; i < g->vertices_size; i++)
    {
        u = g->vertices[i];
        if (u->dist < 0)
        {
            fprintf(fout, "INT_MAX+ ");
        }
        else
        {
            if (u->visited == 0)
            {
                fprintf(fout, "oo ");
            }
            else
            {
                fprintf(fout, "%d ", u->dist);
            }
        }
    }
    fprintf(fout, "\n");
    if (v->dist == INT_MAX)
    {
        fprintf(fout, "no path");
        FreeGraph(g);
    	FreeFILE(fin,fout);
        return;
    }
    else
    {
        if (v->dist < 0 && (v->badWays > 1))
        {
            fprintf(fout, "overflow");
            FreeGraph(g);
    		FreeFILE(fin,fout);
            return;
        }
    }
    fprintf(fout, "%d ", i + 1);
    for (j = 0, u = v; u->dist; u = g->vertices[u->prev], j++)
        fprintf(fout, "%d ", u->prev + 1);
}

int main()
{
    FILE *fin = fopen("in.txt", "r");
    FILE *fout = fopen("out.txt", "w");
    int n;
    if (fscanf(fin, "%d", &n) < 1)
    {
        fprintf(fout, "bad number of lines");
        FreeFILE(fin, fout);
        return 0;
    }
    if (n < 0 || n > 5000)
    {
        fprintf(fout, "bad number of vertices");
        FreeFILE(fin, fout);
        return 0;
    }
    int s, f;
    if (fscanf(fin, "%d%d", &s, &f) < 2)
    {
        fprintf(fout, "bad number of lines");
        FreeFILE(fin, fout);
        return 0;
    }
    if (s < 1 || s > n || f < 1 || f > n)
    {
        fprintf(fout, "bad vertex");
        FreeFILE(fin, fout);
        return 0;
    }
    int m;
    if (fscanf(fin, "%d", &m) < 1)
    {
        fprintf(fout, "bad number of lines");
        FreeFILE(fin, fout);
        return 0;
    }
    if (m < 0 || m > (n * (n - 1)) / 2)
    {
        fprintf(fout, "bad number of edges");
        FreeFILE(fin, fout);
        return 0;
    }
    int a, b, c;
    Graph *g = CreateGraph(n);
    for (int i = 0; i < m; i++)
    {
        if (fscanf(fin, "%d%d%d", &a, &b, &c) < 3)
        {
            fprintf(fout, "bad number of lines");
            FreeGraph(g);
            FreeFILE(fin, fout);
            return 0;
        }
        if (a < 1 || a > n || b < 1 || b > n)
        {
            fprintf(fout, "bad vertex");
            FreeGraph(g);
            FreeFILE(fin, fout);
            return 0;
        }
        if (c < 0)
        {
            fprintf(fout, "bad length");
            FreeGraph(g);
            FreeFILE(fin, fout);
            return 0;
        }
        AddEdge(g, a - 1, b - 1, c);
    }
    Dijkstra(g, s - 1);
    PrintPath(fin, fout, g, f - 1);
    FreeGraph(g);
    FreeFILE(fin,fout);
    return 0;
}
