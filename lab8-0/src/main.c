#include <stdlib.h>
#include <stdio.h>

#define INT_MAX 2147483647

struct edges
{
	int vertex1;
	int vertex2;
	int length;
};


void swap(int **arr, int i, int j, int widthSize)
{
    int a[3];
    for (int o = 0; o < widthSize; o++)
    {
        a[o] = arr[i][o];
    }
    for (int o = 0; o < widthSize; o++)
    {
        arr[i][o] = arr[j][o];
    }
    for (int o = 0; o < widthSize; o++)
    {
        arr[j][o] = a[o];
    }
}

/*this is begin of heapsort's part

void shiftDown(int **arr, int size, int index, int numberOfSortedElement, int widthSize)
{
    int largest = index;
    int l = 2 * index + 1;
    int r = 2 * index + 2;
    if (l < (size) && arr[l][numberOfSortedElement] > arr[largest][numberOfSortedElement])
    {
        largest = l;
    }
    if (r < (size) && arr[r][numberOfSortedElement] > arr[largest][numberOfSortedElement])
    {
        largest = r;
    }
    if (largest != index)
    {
        swap(arr, largest, index, widthSize);
        shiftDown(arr, size, largest, numberOfSortedElement, widthSize);
    }
}

void printArr(int **arr, int size, int widthSize)
{
    for (int i = 0; i < size; i++)
    {
        for (int ii = 0; ii < widthSize; ii++)
        {
            printf("%d ", arr[i][0]);
        }
        printf("\n");
    }
}

void heapSort(int **arr, int size, int numberOfSortedElement, int widthSize)
{
    for (int i = size / 2 - 1; i >= 0; i--)
    {
        shiftDown(arr, size, i, numberOfSortedElement, widthSize);
    }
    for (int i = size - 1; i >= 0; i--)
    {
        swap(arr, 0, i, widthSize);
        shiftDown(arr, i, 0, numberOfSortedElement, widthSize);
    }
}

this is end of heapsort's part*/

int edgesCmp( const void *a, const void *b)
{
	return ( (*(edges*)a).length - (*(edges*)b).length );
}



int findRoot(short int *parents, int vertex)
{
    if (vertex == parents[vertex])
    {
        return vertex;
    }
    return parents[vertex] = findRoot(parents, parents[vertex]);
}

void unionSubTree(short int *parents, short int *color, int vertex1, int vertex2)
{
    vertex1 = parents[vertex1];
    vertex2 = parents[vertex2];
    if (vertex1 != vertex2)
    {
        if (color[vertex1] < color[vertex2])
        {
            int o;
            o = vertex1;
            vertex1 = vertex2;
            vertex2 = o;
        }
        parents[vertex2] = vertex1;
        if (color[vertex1] == color[vertex2])
        {
            color[vertex1] += 1;
        }
    }
}

void freeAll(short int *color, short int *parents, int **edges, int edge)
{
    free(color);
    free(parents);
    free(edges);
}

int main()
{
    FILE *fin = fopen("in.txt", "r");
    FILE *fout = fopen("out.txt", "w");
    int ver, edge;
    if (fscanf(fin, "%d\n%d\n", &ver, &edge) < 2)
    {
    }
    if (ver < 0 || ver > 5000)
    {
        fprintf(fout, "bad number of vertices");
        return 0;
    }
    if ((edge < 0) || (edge > ((ver + 1) * ver) / 2))
    {
        fprintf(fout, "bad number of edges");
        return 0;
    }
    short int *parents = (short int *)malloc(sizeof(short int) * ver);
    short int *color = (short int *)malloc(sizeof(short int) * ver);
    struct edges *tree = (struct edges*)malloc(sizeof(struct edges) * edge);
    if (ver == 0 || (ver > 1 && edge == 0) || (edge < ver - 1))
    {
        fprintf(fout, "no spanning tree");
        freeAll(color, parents, edges, edge);
        return 0;
    }
    for (int i = 0; i < edge; i++)
    {
        if (fscanf(fin, "%d%d%d", &(edges[i].vertex1), &(edges[i].vertex2), &(edges[i].length) == EOF)
        {
            fprintf(fout, "bad number of lines");
            freeAll(color, parents, edges, edge);
            return 0;
        }
        else
        {
            if ((edges[i].vertex1 < 1 || edges[i].vertex1 > ver) || (edges[i].vertex2 < 1 || edges[i].vertex2 > ver))
            {
                fprintf(fout, "bad vertex");
                freeAll(color, parents, edges, edge);
                return 0;
            }
            else
            {
                if (edges[i].length < 0 || edges[i].length > INT_MAX)
                {
                    fprintf(fout, "bad length");
                    freeAll(color, parents, edges, edge);
                    return 0;
                }
            }
        }
        edges[i].vertex1 -= 1;
        edges[i].vertex2 -= 1;
    }
    if (ver == 1)
    {
        freeAll(color, parents, edges, edge);
        return 0;
    }
    qsort(edges, edge, sizeof(edges), edgesCmp);
    //heapSort(edges, edge, 2, 3);
    for (int i = 0; i < ver; i++)
    {
        parents[i] = i;
        color[i] = 0;
    }
    int positionInProcess = 1;
    for (int i = 0; i < edge; i++)
    {
        if (findRoot(parents, edges[i].vertex1) != findRoot(parents, edges[i].vertex2))
        {
            unionSubTree(parents, color, edges[i].vertex1, edges[i].vertex2);
            fprintf(fout, "%d %d\n", edges[i].vertex1 + 1, edges[i].vertex2 + 1);
            positionInProcess += 1;
        }
    }
    if (positionInProcess != ver)
    {
        rewind(fout);
        fprintf(fout, "no spanning tree");
    }
    freeAll(color, parents, edges, edge);
    return 0;
}
