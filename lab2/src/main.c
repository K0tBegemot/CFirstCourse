#include <cstdlib>
#include <cstdio>
#include <string.h>

int main()
{
    char a[1000];
    int count,a_size,numb[10],exiter=0;
    gets_s(a, 999);
    a_size = strlen(a);
    if (scanf_s("%d", &count) == 0)
    {

    }
    for (int i = 0; i < 10; i++)
    {
        numb[i] = 0;
    }
    for (int i = 0; i < a_size; i++)
    {
        if (((a[i] - '0') >= 0) && ((a[i] - '0') <= 9))
        {
            if (numb[(a[i] - '0')] == 0)
            {
                numb[(a[i] - '0')] += 1;
            }
            else
            {
                printf("%s", "bad input");
                exiter += 1;
                break;
            }
        }
        else
        {
            printf("%s", "bad input");
            exiter += 1;
            break;
        }
    }
    char q;
    if (exiter == 0)
    {
        for (int ii = 0; ii < count; ii++)
        {
            for (int i = a_size - 1; i > 0; i--)
            {
                if (a[i] > a[i - 1])
                {
                    char min = 0,indx;
                    for (int u = i; u < a_size; u++)
                    {
                        if ((a[u] > a[i - 1]) && (a[u] <= a[i]))
                        {
                            min = a[u];
                            indx = u;
                        }
                    }
                    a[indx] = a[i - 1];
                    a[i - 1] = min;
                    char e;
                    for (int iii = 0; iii < a_size - i-1; iii++)
                    {
                        for (int iiii = i; iiii < a_size - 1; iiii++)
                        {
                            if (a[iiii] > a[iiii + 1])
                            {
                                e = a[iiii];
                                a[iiii] = a[iiii + 1];
                                a[iiii + 1] = e;
                            }
                        }
                    }
                    printf("%s%c", a, '\n');
                    break;
                }
            }
        }
    }
    return 0;
}

