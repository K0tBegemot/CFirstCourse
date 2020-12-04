#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int minimizer(int *a, int size)
{
	int counter = 0;
	int s = 0;
	for (int i = size-2; i > 0; i--)
	{
		if (a[i] > a[i-1])
		{
			s = i;
			counter += 1;
			break;
		}
	}
	if (counter == 0)
	{
		return -1;
	}
	int minn = a[s], minn_index = s;
	for (int i = s + 1; i < size - 2; i++)
	{
		if (a[i] < minn && a[i] > a[s-1])
		{
			minn = a[i];
			minn_index = i;
		}
	}
	int u;
	u = a[s-1];
	a[s-1] = minn;
	a[minn_index] = u;
	return s;
}

int main()
{
    char a[100];
	int b[100], cou[10], count;
	FILE* ptrfile = fopen("in.txt", "r");
	if (fgets(a, 100, ptrfile) == 0)
	{
		printf("%s", "bad input");
		fclose(ptrfile);
		return 0;
	}
	if (fscanf(ptrfile, "%d", &count) == 0)
	{
		printf("%s", "bad input");
		fclose(ptrfile);
		return 0;
	}
	int size_a = strlen(a);
	for (int i = 0; i < 10; i++)
	{
		cou[i] = 0;
	}
	for (int i = 0;i < size_a - 1; i++)
	{
		if ((a[i] - '0' >= 0) && (a[i] - '0' <= 9))
		{
			b[i] = a[i]-'0';
			cou[b[i]] += 1;
			if (cou[b[i]] > 1)
			{
				printf("%s", "bad input");
			    return 0;
			}
		}else
		{
			printf("%s", "bad input");
			return 0;
		}
	}
	for (int i = 0; i < count; i++)
	{
		int r = minimizer(b, size_a);
		if(r == -1)
		{
			return 0;
		}
		for(int i = 0; i < size_a - 2 - r; i++)
		{
			for(int ii = r; ii < size_a - 2; ii++)
			{
				if(b[ii] > b[ii+1])
				{
					int c = b[ii];
					b[ii] = b[ii+1];
					b[ii+1] = c;
				}
			}
		}
		for(int ii = 0; ii < size_a-1; ii++)
		{
			printf("%d", b[ii]);
		}
		printf("%c", '\n');
	}
	fclose(ptrfile);
	return 0;
}
