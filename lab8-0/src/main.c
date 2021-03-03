#include <stdlib.h>
#include <stdio.h>

#define INT_MAX 2147483647

//this is begin of heapsort's part
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

//this is end of heapsort's part

int findRoot(int *parents, int vertex)
{
    if (vertex == parents[vertex])
    {
        return vertex;
    }
    return parents[vertex] = findRoot(parents, parents[vertex]);
}

void unionSubTree(int *parents, int *color, int vertex1, int vertex2)
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

int main()
{
    FILE *fin = fopen("in.txt", "r");
    FILE *fout = fopen("out.txt", "w");
    int ver, edge;
    if(fscanf(fin, "%d\n%d\n", &ver, &edge)<2)
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
    int *parents = (int *)malloc(sizeof(int) * ver);
    int *color = (int *)malloc(sizeof(int) * ver);
    int *framesOfProcess = (int *)malloc(sizeof(int) * edge);
    int **edges = (int **)malloc(sizeof(int *) * edge);
    for (int i = 0; i < edge; i++)
    {
        edges[i] = (int *)malloc(sizeof(int) * 3);
    }
    if (ver == 0 || (ver > 1 && edge == 0) || (edge < ver - 1))
    {
        fprintf(fout, "no spanning tree");
        return 0;
    }
    for (int i = 0; i < edge; i++)
    {
        if (fscanf(fin, "%d%d%d", (edges[i] + 0), (edges[i] + 1), (edges[i] + 2)) == EOF)
        {
            fprintf(fout, "bad number of lines");
            return 0;
        }
        else
        {
            if ((edges[i][0] < 1 || edges[i][0] > ver) || (edges[i][1] < 1 || edges[i][1] > ver))
            {
                fprintf(fout, "bad vertex");
                return 0;
            }
            else
            {
                if (edges[i][2] < 0 || edges[i][2] > INT_MAX)
                {
                    fprintf(fout, "bad length");
                    return 0;
                }
            }
        }
        edges[i][0] -= 1;
        edges[i][1] -= 1;
    }
    if (ver == 1)
    {
        return 0;
    }
    heapSort(edges, edge, 2, 3);
    for(int i=0;i<ver;i++)
    {
        parents[i] = i;
        color[i] = 0;
    }
    int positionInProcess=0;
    for(int i=0;i<edge;i++)
    {
        if (findRoot(parents, edges[i][0]) != findRoot(parents, edges[i][1]))
        {
            unionSubTree(parents, color, edges[i][0], edges[i][1]);
            framesOfProcess[positionInProcess] = i;
            positionInProcess += 1;
        }
    }
    int root = parents[0];
    for(int i=0;i<ver;i++)
    {
        if(root!=findRoot(parents, i))
        {
            fprintf(fout, "no spanning tree");
            return 0;
        }
    }
    for(int i=0;i<positionInProcess;i++)
    {
        fprintf(fout, "%d %d\n", edges[framesOfProcess[i]][0]+1, edges[framesOfProcess[i]][1]+1);
    }
    return 0;
}
