#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Stack
{
    int data;
    struct Stack* next;
} st;

typedef struct Top_of_stack
{
    st* top;
} tos;

int retindex(char symbol)
{
    int k = 0;
    if (symbol == '+')
    {
        k= -1;
    }
    if (symbol == '-')
    {
        k= -2;
    }
    if (symbol == '/')
    {
        k= -3;
    }
    if (symbol == '*')
    {
        k= -4;
    }
    if (symbol == '(')
    {
        k = -5;
    }
    return k;
}

void makenull(tos* a)
{
    st* b;
    while (a->top)
    {
        b = a->top;
        a->top = b->next;
        free(b);
    }
}

void view(tos* a)
{
    st* b = a->top;
    while (b != NULL)
    {
        printf("%d%s", (b->data), " ");
        b = b->next;
    }
}

tos* create()
{
    tos* a = (tos*)malloc(sizeof(tos));
    a->top = NULL;
    return a;
}

int top(tos* a)
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

int pop(tos* a)
{
    st* b = a->top;
    if (b == NULL)
    {
        return -10;
    }
    int c = b->data;
    a->top = b->next;
    //free(b);
    return c;
}

void push(tos* a, int b)
{
    st* c = (st*)malloc(sizeof(st));
    if (c)
    {
        c->data = b;
        c->next = a->top;
        a->top = c;
    }
}

int empty(tos* a)
{
    return (a->top == NULL);
}

int main()
{
    char* a = (char*)malloc(1000);
    FILE* ptrfile;
    fopen_s(&ptrfile,"input.txt", "r");
    if(fgets(a, 1000,ptrfile)==0)
    {
        printf("%s", "syntax error");
        return 0;
    }
    int size_a = strlen(a);
    if (size_a == 1)
    {
        printf("%s", "syntax error");
        return 0;
    }
    //printf("%d%c", size_a, '\n');
    int* b = (int*)malloc(size_a);
    int index_of_b = 0;
    tos* aa = create();
    for (int i = 0; i < size_a; i++)
    {
        //printf("%c%s", a[i], " ");
        if (a[i] == '+' || a[i] == '-' || a[i] == '*' || a[i] == '/')
        {
            if (a[i + 1] == '+' || a[i + 1] == '-' || a[i + 1] == '*' || a[i + 1] == '/')
            {
                printf("%s", "syntax error");
                return 0;
            }
        }
    }
    int wera = 0;
    int i=0;
    while(i<size_a-1)
    {
        //printf("%c%s%d%c", a[i], " ", i, '\n');
        if ((a[i] - '0' >= 0) && (a[i] - '0' <= 9))
        {
            int l = i;
            int r = 1;
            int* vrmass = (int*)malloc(50);
            int vrmass_size = 0;
            while ((a[l] - '0' >= 0) && (a[l] - '0' <= 9))
            {
                //printf("%d%s%d%c", a[l] - '0',"su",l,'\n');
                vrmass[vrmass_size] = (a[l]-'0');
                l += 1;
                vrmass_size += 1;
            }
            b[index_of_b] = 0;
            for (int op = vrmass_size - 1; op > -1; op--)
            {
                b[index_of_b] += vrmass[op] * r;
                r *= 10;
            }
            i = l;
            index_of_b += 1;
            wera = 1;
            free(vrmass);
            continue;
        }
        else
        {
            if (a[i] == ')')
            {
                int opr = pop(aa);
                int cy = 0;
                while (opr != -5 && opr != -10)
                {
                    b[index_of_b] = opr;
                    index_of_b += 1;
                    opr = pop(aa);
                    cy += 1;
                }
                if (opr == -10 || cy == 0)
                {
                    printf("%s", "syntax error");
                    return 0;
                }
                wera = 1;
                i += 1;
                continue;
            }
            else
            {
                if (a[i] == '+')
                {
                    if (empty(aa) == 0 && top(aa)<0&&top(aa)>-5)
                    {
                        b[index_of_b] = pop(aa);
                        index_of_b += 1;
                        push(aa, retindex('+'));
                    }
                    else
                    {
                        push(aa, retindex('+'));
                    }
                    wera = 0;
                    i += 1;
                    continue;
                }
                else
                {
                    if (a[i] == '-')
                    {
                        if (empty(aa) == 0 && top(aa)<0&&top(aa)>-5)
                        {
                            b[index_of_b] = pop(aa);
                            index_of_b += 1;
                            push(aa, retindex('-'));
                        }
                        else
                        {
                            push(aa, retindex('-'));
                        }
                        wera = 0;
                        i += 1;
                        continue;
                    }
                    else
                    {
                        if (a[i] == '/')
                        {
                            if (empty(aa) == 0 && top(aa)<-2&&top(aa)>-5)
                            {
                                b[index_of_b] =pop(aa);
                                index_of_b += 1;
                                push(aa, retindex('/'));
                            }
                            else
                            {
                                push(aa, retindex('/'));
                            }
                            wera = 0;
                            i += 1;
                            continue;
                        }
                        else
                        {
                            if (a[i] == '*')
                            {
                                if (empty(aa) == 0 && top(aa) < -2 && top(aa) > -5)
                                {
                                    b[index_of_b] = pop(aa);
                                    index_of_b += 1;
                                    push(aa, retindex('*'));
                                }
                                else
                                {
                                    push(aa, retindex('*'));
                                }
                                wera = 0;
                                i += 1;
                                continue;
                            }
                            else
                            {
                                if (a[i] == '(')
                                {
                                    push(aa, retindex('('));
                                }
                                else
                                {
                                    printf("%s", "syntax error");
                                    return 0;
                                }
                                wera = 0;
                                i += 1;
                                continue;
                            }
                        }
                    }
                }
            }
        }
    }
    //printf("%s", "dg");
    if (empty(aa) == 0)
    {
        //printf("%s", "carr");
        int q;
        while (empty(aa) == 0)
        {
            q = pop(aa);
            if (wera == 1)
            {
                //printf("%s", "dfsdrg");
                b[index_of_b] = q;
                index_of_b += 1;
            }
            else
            {
                printf("%s", "syntax error");
                return 0;
            }
        }
    }
    //printf("%s", "dg");
    makenull(aa);
    tos* lol = create();
    /*
    for (int i = 0; i < index_of_b; i++)
    {
        printf("%c", b[i]);
    }
    */
    //printf("%s", "dg");
    for (int i = 0; i < index_of_b; i++)
    {
        view(lol);
        printf("%c", '\n');
        if (b[i]>=0)
        {
            push(lol,b[i]);
        }
        else
        {
            int chislo_1 = pop(lol);
            int chislo_2 = pop(lol);
            if (chislo_1 == -10 || chislo_2 == -10)
            {
                printf("%s", "syntax error");
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
    printf("%s", "dg");
    printf("%d", pop(lol));
    makenull(lol);
    return 0;
}