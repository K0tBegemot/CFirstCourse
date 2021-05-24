#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct Table
{
	int *table;
	int length;
	int height;
	int size;
	int type;
} Table;

typedef struct Vertex
{
	int lengthOfPath;
	int previousVertex;
	int state;
	int visited;
	int numberCongestedPaths;
} Vertex;

Table *CreateTable(int length, int height, int type)
{
	Table *table = (Table *)calloc(1, sizeof(Table));
	int size = length * height;
	if (type == 0)
	{
		table->table = (int *)calloc(size, sizeof(int));
	}
	else
	{
		if (type == 1)
		{
			int summ = ((height - 1) * height) / 2;
			size -= summ;
			table->table = (int *)calloc(size, sizeof(int));
		}
		else
		{
			printf("Bad number of type in function CreateTable\n");
			free(table);
			return 0;
		}
	}
	table->length = length;
	table->height = height;
	table->size = size;
	table->type = type;
	return table;
}

Vertex *CreateArrayOfVertex(int numberOfVertex)
{
	Vertex *array = (Vertex *)calloc(numberOfVertex, sizeof(Vertex));
	for (int i = 0; i < numberOfVertex; i++)
	{
		(array + i)->lengthOfPath = INT_MAX;
		(array + i)->previousVertex = 0;
		(array + i)->state = 1;
		(array + i)->visited = 0;
		(array + i)->numberCongestedPaths = 0;
	}
	return array;
}

void WriteNumberInTable(Table *table, int number, int x, int y)
{
	if (x < table->length && x > -1 && y < table->height && y > -1)
	{
		int linearIndex = 0;
		if (table->type == 0)
		{
			linearIndex = table->length * x + y;
		}
		else
		{
			if (table->type == 1)
			{
				if (x > y)
				{
					int var = x;
					x = y;
					y = var;
				}
				int shift = ((x + 1) * x) / 2;
				linearIndex = table->length * x + y - shift;
			}
		}
		table->table[linearIndex] = number;
	}
	else
	{
		printf("Bad coordinates in function WriteNumberInTable. Bit not writed\n");
	}
}

int ReadNumberInTable(Table *table, int x, int y)
{
	int number;
	if (x < table->length && x > -1 && y < table->height && y > -1)
	{
		int linearIndex = 0;
		if (table->type == 0)
		{
			linearIndex = table->length * x + y;
		}
		else
		{
			if (table->type == 1)
			{
				if (x > y)
				{
					int var = x;
					x = y;
					y = var;
				}
				int shift = ((x + 1) * x) / 2;
				linearIndex = table->length * x + y - shift;
			}
		}
		number = table->table[linearIndex];
	}
	else
	{
		printf("Bad coordinates in function WriteNumberInTable. Bit not readed\n");
		return 2;
	}
	return number;
}

int TakeNextVertex(Vertex *array, int length)
{
	int index = -1;
	int lengthOfPath = INT_MAX;
	int state = 1;
	for (int i = 0; i < length; i++)
	{
		if (!((array + i)->visited))
		{
			//printf("%d ", i);
			if ((array + i)->state != 1)
			{
				if ((array + i)->lengthOfPath <= lengthOfPath)/////////////////////
				{
					if(state == 1)
					{
						lengthOfPath = (array + i)->lengthOfPath;
						index = i;
						state = (array + i)->state;
					}else
					{
						if((array + i)->state < 2 && state == 2)
						{
							lengthOfPath = (array + i)->lengthOfPath;
							index = i;
							state = (array + i)->state;
						}else
						{
							if(state == 0 && state == (array + i)->state)
							{
								lengthOfPath = (array + i)->lengthOfPath;
								index = i;
								state = (array + i)->state;
							}
						}
					}
				}
			}
		}
	}
	//printf("\n");
	return index;
}

Vertex *Dijkstra(Table *table, short a)
{
	Vertex *array = CreateArrayOfVertex(table->length);
	Vertex *startVertex = array + a;
	startVertex->lengthOfPath = 0;
	startVertex->state = 0;
	Vertex *vertex = 0;
	int numberOfNextVertex = 0;
	while (numberOfNextVertex != -1)
	{
		numberOfNextVertex = TakeNextVertex(array, table->length);
		//printf("%d\n", numberOfNextVertex);
		if(numberOfNextVertex != -1)
		{
			vertex = array + numberOfNextVertex;
		}else
		{
			break;
		}
		vertex->visited = 1;
		for (int i = 0; i < table->length; i++)
		{
			int lengthOfPath = ReadNumberInTable(table, numberOfNextVertex, i);
			if (lengthOfPath > 0)
			{
				Vertex *neighbour = array + i;
				if (!(neighbour->visited))
				{
					//printf("%d ", i);
					if (neighbour->state == 0)
					{
						if (vertex->state == 0)
						{
							if ((vertex->lengthOfPath +  lengthOfPath <= neighbour->lengthOfPath) && (vertex->lengthOfPath + lengthOfPath > 0)) ///
							{
								neighbour->lengthOfPath = vertex->lengthOfPath + lengthOfPath;
								neighbour->previousVertex = numberOfNextVertex;
							}
						}
					}
					else
					{
						if (neighbour->state == 1)
						{
							if (vertex->state == 0)
							{
								if ((vertex->lengthOfPath + lengthOfPath <= neighbour->lengthOfPath) && (vertex->lengthOfPath + lengthOfPath > 0))
								{
									neighbour->lengthOfPath = vertex->lengthOfPath + lengthOfPath;
									neighbour->state = 0;
									neighbour->previousVertex = numberOfNextVertex;
								}
								else
								{
									neighbour->lengthOfPath = INT_MAX;
									neighbour->state = 2;
									neighbour->previousVertex = numberOfNextVertex;
									neighbour->numberCongestedPaths = 1;
								}
							}
							else
							{
								neighbour->lengthOfPath = INT_MAX;
								neighbour->state = 2;///
								neighbour->previousVertex = numberOfNextVertex;
								neighbour->numberCongestedPaths = 1;
							}
						}
						else
						{
							if (vertex->state == 0)
							{
								if ((vertex->lengthOfPath + lengthOfPath <= neighbour->lengthOfPath) && (vertex->lengthOfPath + lengthOfPath > 0))
								{
									neighbour->lengthOfPath = vertex->lengthOfPath + lengthOfPath;
									neighbour->state = 0;
									neighbour->previousVertex = numberOfNextVertex;
									neighbour->numberCongestedPaths = 0;
								}
								else
								{
									neighbour->state = 2;
									neighbour->previousVertex = numberOfNextVertex;
									neighbour->numberCongestedPaths += 1;
								}
							}
							else
							{
								neighbour->state = 2;
								neighbour->previousVertex = numberOfNextVertex;
								neighbour->numberCongestedPaths += 1;
							}
						}
					}
				}
			}
		}
	}
	return array;
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

void PrintPath(FILE *fout, Vertex *array, int lastVertexIndex, int length)
{
	for (int i = 0; i < length; i++)
	{
		Vertex *vertex = array + i;
		if (vertex->lengthOfPath < INT_MAX)
		{
			fprintf(fout, "%d ", vertex->lengthOfPath);
		}
		else
		{
			if (vertex->state == 0)
			{
				fprintf(fout, "%d ", vertex->lengthOfPath);
			}
			else
			{
				if (vertex->state == 1)
				{
					fprintf(fout, "oo ");
				}
				else
				{
					fprintf(fout, "INT_MAX+ ");
				}
			}
		}
	}
	fprintf(fout, "\n");
	Vertex *lastVertex = array + lastVertexIndex;
	//printf("%d ", lastVertex->numberCongestedPaths);
	if (lastVertex->state == 1)
	{
		fprintf(fout, "no path");
		return;
	}
	else
	{
		if (lastVertex->state == 2 && lastVertex->numberCongestedPaths >= 2)
		{
			fprintf(fout, "overflow");
			return;
		}
	}
	fprintf(fout, "%d ", lastVertexIndex + 1);
	for (int j = 0; lastVertex->lengthOfPath; lastVertex = array + (lastVertex->previousVertex), j++)
	{
		fprintf(fout, "%d ", lastVertex->previousVertex + 1);
	}
}

void FreeTable(Table *table)
{
	if(table)
	{
		if(table->size)
		{
			free(table->table);
		}
		free(table);
	}
}

void FreeArrayOfVertex(Vertex *array)
{
	if(array)
	{
		free(array);
	}
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
	int a, b;
	int c;
	Table *table = CreateTable(n, n, 1);
	for (int i = 0; i < m; i++)
	{
		if (fscanf(fin, "%d%d%d", &a, &b, &c) < 3)
		{
			fprintf(fout, "bad number of lines");
			FreeTable(table);
			FreeFILE(fin, fout);
			return 0;
		}
		if (a < 1 || a > n || b < 1 || b > n)
		{
			fprintf(fout, "bad vertex");
			FreeTable(table);
			FreeFILE(fin, fout);
			return 0;
		}
		if (c < 0)
		{
			fprintf(fout, "bad length");
			FreeTable(table);
			FreeFILE(fin, fout);
			return 0;
		}
		WriteNumberInTable(table, c, a - 1, b - 1);
	}
	/*
	for(int i=0;i< n;i++)
	{
		for(int ii=0;ii< n;ii++)
		{
			printf("%d ", ReadNumberInTable(table, i, ii));
		}
		printf("\n");
	}
	*/
	Vertex *array = Dijkstra(table, s - 1);
	PrintPath(fout, array, f - 1, n);
	FreeFILE(fin, fout);
	FreeTable(table);
	FreeArrayOfVertex(array);
	return 0;
}
