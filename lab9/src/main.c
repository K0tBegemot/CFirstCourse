#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct IncidentEdge
{
    short vertex;///
    int weight;
} IncidentEdge;

typedef struct Vertex
{
    IncidentEdge *edges;
    int edges_len;
    int edges_size;
    int dist;
    short prev;///
    short visited;///
    short state;
    short numberCongestedPaths;
} Vertex;

typedef struct Graph
{
    Vertex *vertices;
    int vertices_len;
    int vertices_size;
} Graph;

typedef struct BHeap
{
    short *data;///
    int *prio;
    short *index;///
    int len;
    int size;
} BHeap;

Graph *CreateGraph(int l)
{
    Graph *a = (Graph*)calloc(1, sizeof(Graph));
    a->vertices = (Vertex*)calloc(l, sizeof(Vertex));
    a->vertices_size = l;
    a->vertices_len = 0;
    return a;
}

void AddVertex(Graph *g, short i)///
{
    if (g->vertices_size < i + 1)
    {
        int size = g->vertices_size * 2 > i ? g->vertices_size * 2 : i + 4;
        g->vertices = (Vertex*)realloc(g->vertices, size * sizeof(Vertex));
        for (int j = g->vertices_size; j < size; j++)
        {
        	(g->vertices + j)->dist = 0;
        	(g->vertices + j)->edges = 0;
        	(g->vertices + j)->edges_len = 0;
        	(g->vertices + j)->edges_size = 0;
        	(g->vertices + j)->numberCongestedPaths = 0;
        	(g->vertices + j)->prev = 0;
        	(g->vertices + j)->state = 0;
        	(g->vertices + j)->visited = 0;
		}
        g->vertices_size = size;
    }
    g->vertices_len += 1;
}

void AddIncidentEdge(Vertex *v, short b, int w)
{
    if (v->edges_len >= v->edges_size)
    {
        v->edges_size = ((v->edges_size) ? v->edges_size * 2 : 64);
        v->edges = (IncidentEdge*)realloc(v->edges, v->edges_size * sizeof(IncidentEdge));
    }
    (v->edges + v->edges_len)->vertex = b;
    (v->edges + v->edges_len)->weight = w;
    v->edges_len += 1;
}

void AddEdge(Graph *g, short a, short b, int w)
{
    AddVertex(g, a);
    AddVertex(g, b);
    Vertex *v = g->vertices + a;
    AddIncidentEdge(v, b, w);
	Vertex *v2 = g->vertices + b;
	AddIncidentEdge(v2, a, w);
}

BHeap *CreateHeap(int n)
{
    BHeap *h = (BHeap*)calloc(1, sizeof(BHeap));
    h->data = (short*)calloc(2*n, sizeof(short));
    h->prio = (int*)calloc(2*n, sizeof(int));
    h->index = (short*)calloc(2*n, sizeof(short));
    h->size = 2*n;
    return h;
}

void PushHeap(BHeap *h, short v, int p)
{
    short i = (h->index[v] == 0) ? (++h->len) : (h->index[v]);
    short j = i / 2;
    while (i > 1)
    {
        if (h->prio[j] <= p)//////////////////////////////////////////////////////
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

int Min(BHeap *h, short i, short j, short k)
{
    short m = i;
    if (j <= h->len && h->prio[j] < h->prio[m])
        m = j;
    if (k <= h->len && h->prio[k] < h->prio[m])
        m = k;
    return m;
}

int PopHeap(BHeap *h)
{
    short v = h->data[1];
    short i = 1;
    while (1)
    {
        short j = Min(h, h->len, 2 * i, 2 * i + 1);
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

void Dijkstra(Graph *g, short a)
{
    int j;
    for (int i = 0; i < g->vertices_size; i++)
    {
        Vertex *v = g->vertices + i;
        v->dist = INT_MAX;
        v->prev = 0;
        v->visited = 0;
        v->state = 1;
        v->numberCongestedPaths = 0;
    }
    Vertex *v = g->vertices + a;
    v->dist = 0;
    v->state = 0;
    BHeap *h = CreateHeap(g->vertices_len);
    PushHeap(h, a, v->dist);
    short i = 0;
    while (h->len)
    {
        i = PopHeap(h);
        v = g->vertices + i;
        v->visited = 1;
        for (j = 0; j < v->edges_len; j++)
        {
            IncidentEdge *e = v->edges + j;
            Vertex *u = (g->vertices) + (e->vertex);
            if (!(u->visited))
            {
            	if(u->state == 0)
            	{
            		if(v->state == 0)
            		{
						if((v->dist + e->weight <= u->dist) && (v->dist + e->weight > 0))///
						{
							u->dist = v->dist + e->weight;
							u->prev = i;
                			PushHeap(h, e->vertex, u->dist);
						}
					}
				}else
				{
					if(u->state == 1)
					{
						if(v->state == 0)
						{
							if((v->dist + e->weight <= u->dist) && (v->dist + e->weight > 0))
							{
								u->dist = v->dist + e->weight;
								u->state = 0;
								u->prev = i;
                				PushHeap(h, e->vertex, u->dist);
							}else
							{
								u->dist = INT_MAX;
								u->state = 2;
								u->prev = i;
								u->numberCongestedPaths = 1;
								PushHeap(h, e->vertex, u->dist);
							}
						}else
						{
							u->dist = INT_MAX;
							u->state = v->state + 1;
							u->prev = i;
							u->numberCongestedPaths = 1;
							PushHeap(h, e->vertex, u->dist);
						}
					}else
					{
						if(v->state == 0)
						{
							if((v->dist + e->weight <= u->dist) && (v->dist + e->weight > 0))
							{
								u->dist = v->dist + e->weight;
								u->state = 0;
								u->prev = i;
								u->numberCongestedPaths = 0;
                				PushHeap(h, e->vertex, u->dist);
							}else
							{
								u->state = 2;
								u->prev = i;
								u->numberCongestedPaths += 1;
								PushHeap(h, e->vertex, u->dist);
							}
						}else
						{
							u->state = 2;
							u->prev = i;
							u->numberCongestedPaths += 1;
							PushHeap(h, e->vertex, u->dist);
						}
					}
				}
            }
        }
    }
    FreeHeap(h);
}

/*
void FreeGraph(Graph *g)
{
	if(g)
	{
	for(int i=0;i<g->vertices_size;i++)
	{
		Vertex *v = g->vertices[i];
		if(v)
		{
		for(int ii=0;ii<v->edges_size;ii++)
		{
			IncidentEdge *e = v->edges[ii];
			if(e)
			{
				free(e);
			}
		}
		if(v->edges)
		{
			free(v->edges);
		}
		free(v);
		}
	}
	if(g->vertices)
	{
		free(g->vertices);
	}
	free(g);
	}
}
*/

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

void PrintPath(FILE *fout, Graph *g, short ir)
{
    short j;
    Vertex *v, *u;
    v = g->vertices + ir;
    for (int i = 0; i < g->vertices_size; i++)
    {
        u = g->vertices + i;
        if (u->dist < INT_MAX)
        {
            fprintf(fout, "%d ", u->dist);
        }
        else
        {
            if (u->state == 0)
            {
                fprintf(fout, "%d ", u->dist);
            }
            else
            {
            	if(u->state == 1)
            	{
            		fprintf(fout, "oo ");
				}else
				{
					fprintf(fout, "INT_MAX+ ");
				}
            }
        }
    }
    fprintf(fout, "\n");
    if (v->state == 1)
    {
        fprintf(fout, "no path");
        return;
    }
    else
    {
        if (v->state == 2 && v->numberCongestedPaths >=2)
        {
            fprintf(fout, "overflow");
            return;
        }
    }
    fprintf(fout, "%d ", ir + 1);
    for (j = 0, u = v; u->dist; u = (g->vertices) + (u->prev), j++)
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
    short s, f;
    if (fscanf(fin, "%hd%hd", &s, &f) < 2)
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
    short a, b;
    int c;
    Graph *g = CreateGraph(n);
    for (int i = 0; i < m; i++)
    {
        if (fscanf(fin, "%hd%hd%d", &a, &b, &c) < 3)
        {
            fprintf(fout, "bad number of lines");
            //FreeGraph(g);
            FreeFILE(fin, fout);
            return 0;
        }
        if (a < 1 || a > n || b < 1 || b > n)
        {
            fprintf(fout, "bad vertex");
            //FreeGraph(g);
            FreeFILE(fin, fout);
            return 0;
        }
        if (c < 0)
        {
            fprintf(fout, "bad length");
            //FreeGraph(g);
            FreeFILE(fin, fout);
            return 0;
        }
        AddEdge(g, a - 1, b - 1, c);
    }
    Dijkstra(g, s - 1);
    PrintPath(fout, g, f - 1);
    //FreeGraph(g);
    FreeFILE(fin,fout);
    return 0;
}
