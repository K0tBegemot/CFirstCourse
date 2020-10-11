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
        while (b!=NULL)
        {
            printf("%d%s",(b->data)," ");
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
        return -1;
    }
    int c = b->data;
    a->top = b->next;
    free(b);
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
    char* a =(char*)malloc(1000);
    int scan=scanf("%s",a);
    if(scan)
    {
        
    }
    int size_a = strlen(a);
    char* b = (char*)malloc(size_a);
    int index_of_b = 0;
    tos* aa = create();
    for (int i = 0; i < size_a; i++)
    {
        if ((((int)a[i]) - '0')>= 0 && (((int)a[i]) - '0') <= 9)
        {
            b[index_of_b] =a[i];
            index_of_b += 1;
        }
        else
        {
                if (a[i] == ')')
                {
                    int opr=pop(aa);
                    while (opr != ((int)('('))&&(opr!=-1))
                    {
                        b[index_of_b] = ((char)opr);
                        index_of_b += 1;
                        opr = pop(aa);
                    }
                    if (opr == -1)
                    {
                        printf("%s", "syntax error");
                        return 0;
                    }
                }
                else
                {
                    if (a[i] == '+' )
                    {
                        if (empty(aa) == 0 && ((char)top(aa) == '+' || (char)top(aa) == '*' || (char)top(aa) == '/'))
                        {
                            b[index_of_b] = (char)pop(aa);
                            index_of_b += 1;
                            push(aa, (int)a[i]);
                        }
                        else
                        {
                            push(aa, (int)a[i]);
                        }
                    }
                    else
                    {
                        if (a[i] == '-' )
                        {
                            if (empty(aa) == 0 && ((char)top(aa) == '+' || (char)top(aa) == '*' || (char)top(aa) == '/'))
                            {
                                b[index_of_b] = (char)pop(aa);
                                index_of_b += 1;
                                push(aa, (int)a[i]);
                            }
                            else
                            {
                                push(aa, (int)a[i]);
                            }
                        }
                        else
                        {
                            if (a[i] == '/')
                            {
                                if (empty(aa) == 0 && ((char)top(aa) == '*' || (char)top(aa) == '/'))
                                {
                                    b[index_of_b] = (char)pop(aa);
                                    index_of_b += 1;
                                    push(aa, (int)a[i]);
                                }
                                else
                                {
                                    push(aa, (int)a[i]);
                                }
                            }
                            else
                            {
                                if (a[i] == '*' )
                                {
                                    if (empty(aa) == 0 && ((char)top(aa) == '*' || (char)top(aa) == '/'))
                                    {
                                        b[index_of_b] = (char)pop(aa);
                                        index_of_b += 1;
                                        push(aa, (int)a[i]);
                                    }
                                    else
                                    {
                                        push(aa, (int)a[i]);
                                    }
                                }
                                else
                                {
                                    if (a[i] == '(')
                                    {
                                        push(aa, (int)a[i]);
                                    }
                                    else
                                    {
                                        printf("%s", "syntax error");
                                    }
                                }
                            }
                        }
                    }
                }
        }
    }
    if (empty(aa) == 0)
    {
        int q;
        while (empty(aa) == 0)
        {
            q = pop(aa);
            if (((char)q) == '+')
            {
                b[index_of_b] = '+';
                index_of_b += 1;
            }
            else
            {
                if (((char)q) == '-')
                {
                    b[index_of_b] = '-';
                    index_of_b += 1;
                }
                else
                {
                    if (((char)q) == '/')
                    {
                        b[index_of_b] = '/';
                        index_of_b += 1;
                    }
                    else
                    {
                        if (((char)q) == '*')
                        {
                            b[index_of_b] = '*';
                            index_of_b += 1;
                        }
                        else
                        {
                            printf("%s", "syntax error");
                            return 0;
                        }
                    }
                }
            }
        }
    }
    tos *lol = create();
    /*
    for (int i = 0; i < index_of_b; i++)
    {
        printf("%c", b[i]);
    }
    */
    for (int i = 0; i < index_of_b; i++)
    {
        if (((b[i] - '0') >= 0) && ((b[i] - '0') <= 9))
        {
            push(lol, (int)(b[i] - '0'));
        }
        else
        {
            int chislo_1 = pop(lol);
            int chislo_2 = pop(lol);
            if (b[i] == '+')
            {
                push(lol, chislo_2 + chislo_1);
            }
            else
            {
                if (b[i] == '-')
                {
                    push(lol, chislo_2 - chislo_1);
                }
                else
                {
                    if (b[i] == '*')
                    {
                        push(lol, chislo_2 * chislo_1);
                    }
                    else
                    {
                        if (b[i] == '/')
                        {
                            if (chislo_1 == 0)
                            {
                                printf("%s", "division by zero");
                                return 0;
                            }
                            else
                            {
                                push(lol, chislo_2 / chislo_1);
                            }
                        }
                    }
                }
            }
        }
    }
    printf("%d", pop(lol));
    return 0;
}

