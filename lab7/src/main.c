#include <stdio.h>
#include <stdlib.h>

typedef struct Stack
{
	int TreeNode;
	struct Stack *Next;
} st;

typedef struct TopOfStack
{
	int length;
	st *Top;
} tost;

tost *CreateStack(int X)
{
	tost *Array = (tost *)malloc(sizeof(tost) * X);
	for (int i = 0; i < X; i++)
	{
		(Array + i)->length = 0;
		(Array + i)->Top = 0;
	}
	return Array;
}

int Empty(tost *Head)
{
	if (Head->Top)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

int PopFromStack(tost *Head)
{
	if (Empty(Head))
	{
		return -1;
	}
	else
	{
		int a = Head->Top->TreeNode;
		st *OldTop = Head->Top;
		Head->Top = Head->Top->Next;
		free(OldTop);
		Head->length -= 1;
		return a;
	}
}

void DeleteStack(st* Top)
{
	if(Top)
	{
		if(Top->Next)
	    {
	    	DeleteStack(Top->Next);
    	}
		free(Top);
	}
}

void DeleteStacks(tost *Head, int X)
{
	for(int i=0;i<X;i++)
	{
		DeleteStack((Head+i)->Top);
	}
	free(Head);
}

void PushToStack(tost *Head, int element)
{
	st *NewElement = (st *)malloc(sizeof(st));
	NewElement->TreeNode = element;
	NewElement->Next = Head->Top;
	Head->Top = NewElement;
	Head->length += 1;
}

int TopologicSort(int *ColorArray, tost *Array, int *NumberOfBlackTops, int WhiteTop, tost *FinishStack)
{
	if (ColorArray[WhiteTop] == 0)
	{
		ColorArray[WhiteTop] = 1;
	}
	else
	{
		if (ColorArray[WhiteTop] == 1)
		{
			return 1;
		}
		else
		{
			if (ColorArray[WhiteTop] == 2)
			{
				return 0;
			}
		}
	}
	st *Element = (Array + WhiteTop)->Top;
	for (int i = 0; i < (Array + WhiteTop)->length; i++)
	{
		if (Element == 0)
		{
			break;
		}
		if (TopologicSort(ColorArray, Array, NumberOfBlackTops, (Element->TreeNode) - 1, FinishStack))
		{
			return 1;
		}
		Element = Element->Next;
	}
	ColorArray[WhiteTop] = 2;
	*NumberOfBlackTops += 1;
	PushToStack(FinishStack, WhiteTop + 1);
	return 0;
}

int main()
{
	int n, m;
	if(scanf("%d", &n)==0)
	{
		printf("bad number of vertices");
		return 0;
	}
	if(scanf("%d", &m)==0)
	{
		printf("bad number of lines");
		return 0;
	}
	tost *Array = CreateStack(n);
	int *ColorArray = (int *)malloc(sizeof(int) * n);
	for (int i = 0; i < n; i++)
	{
		ColorArray[i] = 0;
	}
	int f, s;
	int exceptions = 0, counter=0;
	for (int i = 0; i < m; i++)
	{
		if(scanf("%d%d", &f, &s)<2)
		{
			break;
		}
		if (f == s)
		{
			exceptions = 1;
			break;
		}
		else
		{
			if ((f < 1 || f > n) || (s < 1 || s > n))
			{
				exceptions = 2;
			}
		}
		PushToStack(&Array[f - 1], s);
	}
	if(counter<m)
	{
		exceptions = 1;
	}
	if (n < 0 || n > 2000)
	{
		printf("bad number of vertices");
		return 0;
	}
	else
	{
		if (m < 0 || m > (n * (n - 1)) / 2)
		{
			printf("bad number of edges");
			return 0;
		}
		else
		{
			if (exceptions == 1)
			{
				printf("bad number of lines");
				return 0;
			}
			else
			{
				if (exceptions == 2)
				{
					printf("bad vertex");
					return 0;
				}
			}
		}
	}
	int NumberOfWhiteTops = n;
	tost *FinishStack = CreateStack(1);
	while (NumberOfWhiteTops > 0)
	{
		int NumberOfBlackTops = 0, WhiteTop=0;
		for (int i = 0; i < n; i++)
		{
			if (ColorArray[i] == 0)
			{
				WhiteTop = i;
				break;
			}
		}
		if (TopologicSort(ColorArray, Array, &NumberOfBlackTops, WhiteTop, FinishStack))
		{
			printf("impossible to sort");
			return 0;
		}
		NumberOfWhiteTops -= NumberOfBlackTops;
	}
	while (!Empty(FinishStack))
	{
		printf("%d ", PopFromStack(FinishStack));
	}
	DeleteStacks(FinishStack,1);
	DeleteStacks(Array,n);
	free(ColorArray);
}
