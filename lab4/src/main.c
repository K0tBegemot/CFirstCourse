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

void errorfunc()
{
    printf("syntax error");
}

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
    st* b; 
	b=a->top;
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
    st* b;
	b=a->top;
    if (b == NULL)
    {
        return -10;
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
    char* a = (char*)malloc(1000*sizeof(char));
    FILE* ptrfile=fopen("in.txt", "r");
    if(fgets(a, 1000,ptrfile)==0)
    {
    	/*
    	printf("%s","sgs");
        errorfunc();
        return 0;
        */
    }
    fclose(ptrfile);
    int size_a = strlen(a);
    if (size_a == 1)
    {
        errorfunc();
        return 0;
    }
    int* b = (int*)malloc(size_a*sizeof(int));
    int index_of_b = 0;
    tos* aa = create();
    for (int i = 0; i < size_a; i++)
    {
        //printf("%c%s", a[i], " ");
        if (a[i] == '+' || a[i] == '-' || a[i] == '*' || a[i] == '/')
        {
            if (a[i + 1] == '+' || a[i + 1] == '-' || a[i + 1] == '*' || a[i + 1] == '/'||a[i+1]==')')
            {
            	//printf("%s","sgs");
                errorfunc();
                return 0;
            }
        }
        if(a[i]=='(')
        {
            if (a[i + 1] == '+' || a[i + 1] == '-' || a[i + 1] == '*' || a[i + 1] == '/'||a[i+1]==')')
            {
            	//printf("%s","sgs");
                errorfunc();
                return 0;
            }
        }
    }
    int wera = 0;
    int i=0;
    while(i<size_a)
    {
        if(a[i]=='\n')
        {
            break;
        }
    	//printf("%c",'\n');
    	//printf("%d%s%c%s",i," ",a[i]," ");
        //printf("%c%s%d%c", a[i], " ", i, '\n');
        if ((a[i] - '0' >= 0) && (a[i] - '0' <= 9))
        {
            int l = i;
            int r = 1;
            int* vrmass = (int*)malloc(50*sizeof(int));
            int vrmass_size = 0;
            while ((a[l] - '0' >= 0) && (a[l] - '0' <= 9)&&(l<size_a-1))
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
            //view(aa);
            continue;
        }
        else
        {
            if (a[i] == ')')
            {
                int opr = pop(aa);
                while (opr != -5 && opr != -10)
                {
                    b[index_of_b] = opr;
                    index_of_b += 1;
                    opr = pop(aa);
                }
                if (opr == -10 )
                {
                    errorfunc();
                    //printf("%s","sgs");
                    return 0;
                }
                wera = 1;
                i += 1;
                //view(aa);
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
                    //view(aa);
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
                        //view(aa);
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
                            //view(aa);
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
                                //view(aa);
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
                                    errorfunc();
                                    return 0;
                                }
                                wera = 0;
                                i += 1;
                                //view(aa);
                                continue;
                            }
                        }
                    }
                }
            }
        }
    }
    if (empty(aa) == 0)
    {
        //printf("%s", "carr");
        int q;
        while (empty(aa) == 0)
        {
        	//view(aa);
            //printf("%c", '\n');
            //printf("%s","dvor");
            q = pop(aa);
            //printf("%d",empty(aa));
            if (wera == 1)
            {
                //printf("%s", "dfsdrg");
                b[index_of_b] = q;
                index_of_b += 1;
            }
            else
            {
                errorfunc();
                return 0;
            }
        }
    }
    makenull(aa);
    tos* lol = create();
    /*
    for (int i = 0; i < index_of_b; i++)
    {
        printf("%d", b[i]);
    }
    */
    for (int i = 0; i < index_of_b; i++)
    {
        //printf("%c", '\n');
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
                                    printf("%s","division by zero");
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
    printf("%d",pop(lol));
    return 0;
}
