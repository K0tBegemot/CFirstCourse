#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Stack
{
    int data;
    struct Stack *next;
} st;

typedef struct TopOfStack
{
    st *top;
} tos;

void errorfunc()
{
    printf("syntax error");
}

int retindex(char symbol)
{
    int k = 0;
    if (symbol == '+')
    {
        k = -1;
    }
    if (symbol == '-')
    {
        k = -2;
    }
    if (symbol == '/')
    {
        k = -3;
    }
    if (symbol == '*')
    {
        k = -4;
    }
    if (symbol == '(')
    {
        k = -5;
    }
    return k;
}

void makenull(tos *a)
{
    st *b;
    while (a->top)
    {
        b = a->top;
        a->top = b->next;
        free(b);
    }
    free(a);
}

int top(tos *a)
{
    if (a->top)
    {
        return (a->top->data);
    }
    else
    {
        return 0;
    }
}

int pop(tos *a)
{
    st *b;
    b = a->top;
    if (b == 0)
    {
        return -10;
    }
    int c = b->data;
    a->top = b->next;
    free(b);
    return c;
}

void push(tos *a, int b)
{
    st *c = (st *)malloc(sizeof(st));
    if (c)
    {
        c->data = b;
        c->next = a->top;
        a->top = c;
    }
}

int empty(tos *a)
{
    return (a->top == 0);
}

void error(char *a, int *b, tos *aa)
{
    free(a);
    free(b);
    makenull(aa);
    errorfunc();
}

int checkForDoubleOperations(int size_a, char *a, int *b, tos *aa)
{
    int counter = 0;
    for (int i = 0; i < size_a; i++)
    {
        if (a[i] == '+' || a[i] == '-' || a[i] == '*' || a[i] == '/' || a[i] == '(')
        {
            if (a[i + 1] == '+' || a[i + 1] == '-' || a[i + 1] == '*' || a[i + 1] == '/' || a[i + 1] == ')')
            {
                error(a, b, aa);
                counter = 1;
                break;
            }
        }
    }
    return counter;
}

int chooseNextActionInExpression(char *a, int *i, int aSize, int *b, int *indexOfB, int *wera, tos *aa)
{
    int counter = 2;
    if (a[*i] == '\n')
    {
        counter = 1;
    }
    else

        if ((a[*i] - '0' >= 0) && (a[*i] - '0' <= 9))
    {
        int l = *i;
        long long int r = 1;
        int *vrmass = (int *)malloc(50 * sizeof(int));
        int vrmassSize = 0;
        while ((a[l] - '0' >= 0) && (a[l] - '0' <= 9) && (l < aSize - 1))
        {
            vrmass[vrmassSize] = (a[l] - '0');
            l += 1;
            vrmassSize += 1;
        }
        b[*indexOfB] = 0;
        for (int op = vrmassSize - 1; op > -1; op--)
        {
            b[*indexOfB] += vrmass[op] * r;
            r *= 10;
        }
        *i = l;
        *indexOfB += 1;
        *wera = 1;
        free(vrmass);
    }
    else

        switch (a[*i])
        {
        case ')':
        {
            int opr = pop(aa);
            while (opr != -5 && opr != -10)
            {
                b[*indexOfB] = opr;
                *indexOfB += 1;
                opr = pop(aa);
            }
            *wera = 1;
            *i += 1;
            if (opr == -10)
            {
                error(a, b, aa);
                counter = 0;
            }
            break;
        }
        case '+':
        {
            if (empty(aa) == 0 && top(aa) < 0 && top(aa) > -5)
            {
                b[*indexOfB] = pop(aa);
                *indexOfB += 1;
                push(aa, retindex('+'));
            }
            else
            {
                push(aa, retindex('+'));
            }
            *wera = 0;
            *i += 1;
            break;
        }
        case '-':
        {
            if (empty(aa) == 0 && top(aa) < 0 && top(aa) > -5)
            {
                b[*indexOfB] = pop(aa);
                *indexOfB += 1;
                push(aa, retindex('-'));
            }
            else
            {
                push(aa, retindex('-'));
            }
            *wera = 0;
            *i += 1;
            break;
        }
        case '/':
        {
            if (empty(aa) == 0 && top(aa) < -2 && top(aa) > -5)
            {
                b[*indexOfB] = pop(aa);
                *indexOfB += 1;
                push(aa, retindex('/'));
            }
            else
            {
                push(aa, retindex('/'));
            }
            *wera = 0;
            *i += 1;
            break;
        }
        case '*':
        {
            if (empty(aa) == 0 && top(aa) < -2 && top(aa) > -5)
            {
                b[*indexOfB] = pop(aa);
                *indexOfB += 1;
                push(aa, retindex('*'));
            }
            else
            {
                push(aa, retindex('*'));
            }
            *wera = 0;
            *i += 1;
            break;
        }
        case '(':
        {
            push(aa, retindex('('));
            *wera = 0;
            *i += 1;
            break;
        }
        default:
        {
            error(a, b, aa);
            counter = 0;
        }
        }

    return counter;
}

int chooseNextActionInStack(int *b, int *i, tos *lol)
{
    int counter = 0;
    if (b[*i] >= 0)
    {
        push(lol, b[*i]);
    }
    else
    {
        int chislo_1 = pop(lol);
        int chislo_2 = pop(lol);
        if (chislo_1 == -10 || chislo_2 == -10)
        {
            makenull(lol);
            free(b);
            errorfunc();
            counter = 1;
        }
        else
            switch (b[*i])
            {
            case -1:
            {
                push(lol, chislo_2 + chislo_1);
                break;
            }
            case -2:
            {
                push(lol, chislo_2 - chislo_1);
                break;
            }
            case -4:
            {
                push(lol, chislo_2 * chislo_1);
                break;
            }
            case -3:
            {
                if (chislo_1 == 0)
                {
                    free(b);
                    makenull(lol);
                    printf("%s", "division by zero");
                    counter = 1;
                }
                else
                {
                    push(lol, (chislo_2 / chislo_1));
                }
                break;
            }
            }
    }
    return counter;
}

int makeAANotEmpty(char *a, int *b, tos *aa, int *wera, int *indexOfB)
{
    int counter = 0;
    while (empty(aa) == 0)
    {
        int q = pop(aa);
        if (*wera == 1)
        {
            b[*indexOfB] = q;
            *indexOfB += 1;
        }
        else
        {
            error(a, b, aa);
            counter = 1;
            break;
        }
    }
    return counter;
}

int main()
{
    char *a = (char *)malloc(1100 * sizeof(char));
    FILE *ptrfile = fopen("in.txt", "r");
    if (fgets(a, 1100, ptrfile) == 0)
    {
        errorfunc();
        return 0;
    }
    fclose(ptrfile);
    int aSize = strlen(a);
    if (aSize == 1 || aSize == 0)
    {
        free(a);
        errorfunc();
        return 0;
    }
    int *b = (int *)malloc(aSize * sizeof(int));
    int indexOfB = 0;
    tos *aa;
    aa = (tos *)malloc(sizeof(tos));
    aa->top = 0;
    if (checkForDoubleOperations(aSize, a, b, aa))
    {
        return 0;
    }
    int wera = 0;
    int i = 0;
    while (i < aSize)
    {
        switch (chooseNextActionInExpression(a, &i, aSize, b, &indexOfB, &wera, aa))
        {
        case 0:
        {
            return 0;
        }
        case 1:
        {
            i = aSize;
            break;
        }
        }
    }
    if (empty(aa) == 0)
    {
        if (makeAANotEmpty(a, b, aa, &wera, &indexOfB))
        {
            return 0;
        }
    }
    free(a);
    makenull(aa);
    tos *lol;
    lol = (tos *)malloc(sizeof(tos));
    lol->top = 0;
    for (int i = 0; i < indexOfB; ++i)
    {
        if (chooseNextActionInStack(b, &i, lol))
        {
            return 0;
        }
    }
    free(b);
    printf("%d", pop(lol));
    makenull(lol);
    return 0;
}
