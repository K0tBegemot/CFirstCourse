#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef long long int lli;

void choiceOfTheNextAction(char *number, long long int *indx, long long int *tochka, int *numeral)
{
    if (number[*indx] == '.')
    {
        *tochka = 1;
        *numeral = 0;
    }
    else
    {
        if ('0' <= number[*indx] && number[*indx] <= '9')
        {
            *numeral = number[*indx] - '0';
        }
        else
        {
            if (number[*indx] - 'A' >= 0 && number[*indx] - 'F' <= 0)
            {
                *numeral = number[*indx] - 'A' + 10;
            }
            else
            {
                if (number[*indx] - 'a' >= 0 && number[*indx] - 'f' <= 0)
                {
                    *numeral = number[*indx] - 'a' + 10;
                }
                else
                {
                    *numeral = (-1);
                }
            }
        }
    }
}

void error(FILE *ptrfile)
{
    printf("%s", "bad input");
    fclose(ptrfile);
}

int choiceOfTheNextActionFromTochka(char *number, long long int *tochka, long long int *part1, long long int *part2, long long int *treq, long long int *step, int numeral, long long int *p1, long long int *indx, int a, FILE *ptrfile)
{
    int counter = 0;
    if (*tochka == 0)
    {
        *part1 = numeral + (*part1) * a;
    }
    else
    {
        if (*tochka == 1)
        {
            *p1 += 1;
            if (*indx == 0)
            {
                error(ptrfile);
                counter = 1;
            }
            else
            {
                if (number[*indx + 1] == 0)
                {
                    error(ptrfile);
                    counter = 1;
                }
            }
            *tochka = 2;
        }
        else
        {
            if (*tochka == 2)
            {
                *treq += 1;
                *part2 = (*part2) * a + numeral;
                *step *= a;
            }
        }
    }
    return counter;
}

void makeNumber(long long int *part1Size, long long int *symbol, long long int *symb, char *part1End, char *part2End, long long int *part1, long long int *part2, int *b, long long int *step)
{
    for (long long int i = 0; i < *part1Size; (*part1 /= *b), i++)
    {
        *symbol = *part1 % *b;
        if (*symbol <= 9)
        {
            *symb = (char)((int)'0' + (int)(*symbol));
        }
        else
        {
            *symb = (char)((int)'a' + (int)(*symbol) - 10);
        }
        part1End[i] = *symb;
    }
    for (long long int i = 0; i < 15; i++)
    {
        *symbol = ((*part2) * (*b)) / (*step);
        if (*symbol <= 9)
        {
            *symb = (char)((int)'0' + (int)(*symbol));
        }
        else
        {
            *symb = (char)((int)'a' + (int)(*symbol) - 10);
        }
        part2End[i] = *symb;
        *part2 = (*part2) * (*b) - (*symbol) * (*step);
    }
}

void printNumber(long long int *part1Size, char *part1End, char *part2End, long long int *tochka, long long int *copyPart2)
{
    for (long long int i = *part1Size - 1; i > -1; i--)
    {
        printf("%c", part1End[i]);
    }
    if (*tochka == 2 && *copyPart2 != 0)
    {
        printf("%c", '.');
        for (long long int i = 0; i < 12; i++)
        {
            if (part2End[i] != '-')
            {
                printf("%c", part2End[i]);
            }
        }
    }
}

int main()
{
    long long int indx = 0, tochka = 0, treq = 0, part1 = 0, part2 = 0, step = 1, part1Size = 0, p1 = 0;
    int a, b;
    char number[14], j;
    FILE *ptrfile = fopen("in.txt", "r");
    if (fscanf(ptrfile, "%d%d%c", &a, &b, &j) != 3)
    {
        error(ptrfile);
        return 0;
    }
    if (fgets(number, 14, ptrfile) == 0)
    {
        error(ptrfile);
        return 0;
    }
    if (a < 2 || a > 16 || b < 2 || b > 16)
    {
        error(ptrfile);
        return 0;
    }
    int numberSize = strlen(number);
    for (indx = 0; indx < numberSize; indx++)
    {
        if (number[indx] != '\n')
        {
            int numeral = -1;
            choiceOfTheNextAction(number, &indx, &tochka, &numeral);
            if (numeral != -1)
            {
                if (numeral < 0 || numeral > a - 1)
                {
                    error(ptrfile);
                    return 0;
                }
                if (choiceOfTheNextActionFromTochka(number, &tochka, &part1, &part2, &treq, &step, numeral, &p1, &indx, a, ptrfile))
                {
                    return 0;
                }
            }
            else
            {
                error(ptrfile);
                return 0;
            }
        }
    }
    if (p1 > 1)
    {
        error(ptrfile);
        return 0;
    }
    long long int copyPart1 = part1, copyPart2 = part2;
    if (part1 == 0 && part2 == 0 && tochka == 2)
    {
        error(ptrfile);
        return 0;
    }
    while (copyPart1 != 0)
    {
        copyPart1 /= b;
        part1Size += 1;
    }
    if (indx > 0 && part1Size == 0)
    {
        part1Size = 1;
    }
    long long int symbol, symb;
    char part1End[part1Size], part2End[15];
    makeNumber(&part1Size, &symbol, &symb, part1End, part2End, &part1, &part2, &b, &step);
    printNumber(&part1Size, part1End, part2End, &tochka, &copyPart2);
    fclose(ptrfile);
    return 0;
}
