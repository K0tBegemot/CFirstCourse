#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Stack
{
    int data;
    struct Stack *next;
} st;

typedef struct Top_of_stack
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

int globalError = 0;

void choiceOfNextAction(char *a, int size_a, int *i, int *b, int *index_of_b, int *wera, tos *aa)
{
    if (a[*i] == '\n')
    {
        *i = size_a;
    }
    if ((a[*i] - '0' >= 0) && (a[*i] - '0' <= 9))
    {
        int l = *i;
        long long int r = 1;
        int *vrmass = (int *)malloc(50 * sizeof(int));
        int vrmass_size = 0;
        while ((a[l] - '0' >= 0) && (a[l] - '0' <= 9) && (l < size_a - 1))
        {
            vrmass[vrmass_size] = (a[l] - '0');
            l += 1;
            vrmass_size += 1;
        }
        b[*index_of_b] = 0;
        for (int op = vrmass_size - 1; op > -1; op--)
        {
            b[*index_of_b] += vrmass[op] * r;
            r *= 10;
        }
        *i = l;
        *index_of_b += 1;
        *wera = 1;
        free(vrmass);
    }
    else
    {
        if (a[*i] == ')')
        {
            int opr = pop(aa);
            while (opr != -5 && opr != -10)
            {
                b[*index_of_b] = opr;
                *index_of_b += 1;
                opr = pop(aa);
            }
            if (opr == -10)
            {
                error(a, b, aa);
                *i = size_a;
                globalError = 1;
            }
            *wera = 1;
            *i += 1;
        }
        else
        {
            if (a[*i] == '+')
            {
                if (empty(aa) == 0 && top(aa) < 0 && top(aa) > -5)
                {
                    b[*index_of_b] = pop(aa);
                    *index_of_b += 1;
                    push(aa, retindex('+'));
                }
                else
                {
                    push(aa, retindex('+'));
                }
                *wera = 0;
                *i += 1;
            }
            else
            {
                if (a[*i] == '-')
                {
                    if (empty(aa) == 0 && top(aa) < 0 && top(aa) > -5)
                    {
                        b[*index_of_b] = pop(aa);
                        *index_of_b += 1;
                        push(aa, retindex('-'));
                    }
                    else
                    {
                        push(aa, retindex('-'));
                    }
                    *wera = 0;
                    *i += 1;
                }
                else
                {
                    if (a[*i] == '/')
                    {
                        if (empty(aa) == 0 && top(aa) < -2 && top(aa) > -5)
                        {
                            b[*index_of_b] = pop(aa);
                            *index_of_b += 1;
                            push(aa, retindex('/'));
                        }
                        else
                        {
                            push(aa, retindex('/'));
                        }
                        *wera = 0;
                        *i += 1;
                    }
                    else
                    {
                        if (a[*i] == '*')
                        {
                            if (empty(aa) == 0 && top(aa) < -2 && top(aa) > -5)
                            {
                                b[*index_of_b] = pop(aa);
                                *index_of_b += 1;
                                push(aa, retindex('*'));
                            }
                            else
                            {
                                push(aa, retindex('*'));
                            }
                            *wera = 0;
                            *i += 1;
                        }
                        else
                        {
                            if (a[*i] == '(')
                            {
                                push(aa, retindex('('));
                            }
                            else
                            {
                                error(a, b, aa);
                                *i = size_a;
                                globalError = 1;
                            }
                            *wera = 0;
                            *i += 1;
                        }
                    }
                }
            }
        }
    }
}

int main()
{
    char *a = (char *)malloc(1100 * sizeof(char));
    FILE *ptrfile = fopen("in.txt", "r");
    if (fgets(a, 1100, ptrfile) == 0)
    {
    }
    fclose(ptrfile);
    int size_a = strlen(a);
    if (size_a == 1 || size_a == 0)
    {
        free(a);
        errorfunc();
        return 0;
    }
    int *b = (int *)malloc(size_a * sizeof(int));
    int index_of_b = 0;
    tos *aa;
    aa = (tos *)malloc(sizeof(tos));
    aa->top = 0;
    for (int i = 0; i < size_a; i++)
    {
        if (a[i] == '+' || a[i] == '-' || a[i] == '*' || a[i] == '/' || a[i] == '(')
        {
            if (a[i + 1] == '+' || a[i + 1] == '-' || a[i + 1] == '*' || a[i + 1] == '/' || a[i + 1] == ')')
            {
                error(a, b, aa);
                return 0;
            }
        }
    }
    int wera = 0;
    int i = 0;
    while (i < size_a)
    {
        choiceOfNextAction(a, size_a, &i, b, &index_of_b, &wera, aa);
    }
    if (globalError == 1)
    {
        return 0;
    }
    if (empty(aa) == 0)
    {
        while (empty(aa) == 0)
        {
            int q = pop(aa);
            if (wera == 1)
            {
                b[index_of_b] = q;
                index_of_b += 1;
            }
            else
            {
                free(a);
                free(b);
                makenull(aa);
                errorfunc();
                return 0;
            }
        }
    }
    free(a);
    makenull(aa);
    tos *lol;
    lol = (tos *)malloc(sizeof(tos));
    lol->top = 0;
    for (int i = 0; i < index_of_b; i++)
    {
        if (b[i] >= 0)
        {
            push(lol, b[i]);
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
                return 0;
            }
            else
            {
                if (b[i] == -1)
                {
                    push(lol, chislo_2 + chislo_1);
                }
                else
                {
                    if (b[i] == -2)
                    {
                        push(lol, chislo_2 - chislo_1);
                    }
                    else
                    {
                        if (b[i] == -4)
                        {
                            push(lol, chislo_2 * chislo_1);
                        }
                        else
                        {
                            if (b[i] == -3)
                            {
                                if (chislo_1 == 0)
                                {
                                    free(b);
                                    makenull(lol);
                                    printf("%s", "division by zero");
                                    return 0;
                                }
                                else
                                {
                                    push(lol, (chislo_2 / chislo_1));
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    free(b);
    printf("%d", pop(lol));
    makenull(lol);
    return 0;
}
