#include <stdio.h>

int poww(int a, int b)
{
    if (b >= 0)
    {
        if (b > 0)
        {
            return a * poww(a, b - 1);
        }
    }
    return 1;
}

int deci(int a, int num)
{
    if (((num - 48) < a) && (num < 58) && (num - 48 > -1))
    {
        return num - 48;
    }
    else
    {
        if ((num - 55 < a) && (num < 71) && (num - 55 > -1))
        {
            return num - 55;
        }
        else
        {
            if ((num - 87 < a) && (num < 103) && (num - 87 > -1))
            {
                return num - 87;
            }
            else
            {
                return -1;
            }
        }
    }
}

int rasdel(int a, int numeral1_size, int numeral2_size, char* numeral1, char* numeral2, int* part1, int* part2)
{
    int n_deci, count = 0, tryy = 0;
    for (int i = 0; i < numeral1_size; i++)
    {
        n_deci = deci(a, numeral1[numeral1_size - i - 1]);
        if (n_deci == -1)
        {
            return -1;
            tryy += 1;
            break;
        }
        else
        {
            count += n_deci * poww(a, i);
        }
    }
    if (tryy == 0)
    {
        *part1 = count;
        count = 0;// now count is counter for fractional numerator
        for (int i = numeral2_size - 1; i > -1; i--)
        {
            n_deci = deci(a, numeral2[numeral2_size - 1 - i]);
            if (n_deci == -1)
            {
                return -1;
                tryy += 1;
                break;
            }
            else
            {
                count += n_deci * poww(a, i);
            }
        }
        *part2 = count;
    }else
    {
        \\costyl№million
    }
    return 0;
}

void perevod(int a, int b, int numeral2_size, int part1, int part2)
{
    int size_part1=0;
    for (int i = 0; i < 1000000; i++)
    {
        if (part1 < poww(b, i))
        {
            size_part1 = i;
            break;
        }
    }
    char mas_part1[size_part1];
    for (int i = size_part1 - 1; i > -1; i--)
    {
        if (part1 % b < 10)
        {
            mas_part1[i] = (char)(part1 % b + 48);
        }
        else
        {
            mas_part1[i] = (char)(part1 % b + 55);
        }
        part1 = (part1 - part1 % b) / b;
    }
    char mas_part2[13];
    for (int i = 0; i < 13; i++)
    {
        mas_part2[i] = 0;
        part2 *= b;
        if (part2 / poww(a, numeral2_size) < 10)
        {
            mas_part2[i] = (char)(part2 / poww(a, numeral2_size) + 48);
        }
        else
        {
            mas_part2[i] = (char)(part2 / poww(a, numeral2_size) + 55);
        }
        part2 = part2 - ((part2 / poww(a, numeral2_size)) * poww(a, numeral2_size));
    }
    for (int i = 0; i < size_part1; i++)
    {
        printf("%c", mas_part1[i]);
    }
    printf("%c", '.');
    int size_part2=0;
    for (int i = 12; i > -1; i--)
    {
        if (mas_part2[i] != '0')
        {
            size_part2 = i + 1;
            break;
        }
    }
    if (size_part2 > 12)
    {
        size_part2 = 12;
    }
    for (int i = 0; i < size_part2; i++)
    {
        printf("%c", mas_part2[i]);
    }
}

int main()
{
    int a, b;
    int u=scanf("%d", &a);
    u+=1;
    int uu=scanf("%d", &b);
    uu+=1;
    char numeral1[12], numeral2[12];
    int numeral1_size = 0, numeral2_size = 0;
    {
        int ii = 0, counter = 0;
        char firststream[14];
        int qwer=scanf("%s", firststream);
        qwer+=1;
        for (int i = 0; i < 13; i++)
        {
            if (firststream[i] == '.')
            {
                numeral1_size = i;
                ii += 1;
                continue;
            }
            else
            {
                if (ii == 00)
                {
                    numeral1[i] = firststream[i];
                }
                else
                {
                    if (firststream[i] == 0)
                    {
                        break;
                    }
                    else
                    {
                        numeral2[i - numeral1_size - 1] = firststream[i];
                        counter = i - numeral1_size - 1;
                    }
                }
            }
        }
        numeral2_size = counter + 1;
    }
    int part1, part2;
    if (a > 1 && a < 17 && b>1 && b < 17)
    {
        int tochka = rasdel(a, numeral1_size, numeral2_size, numeral1, numeral2, &part1, &part2);
        if (tochka == -1)
        {
            printf("%s", "bad input");
        }
        else
        {
            perevod(a, b, numeral2_size, part1, part2);
        }
    }
    else
    {
        printf("%s", "bad input");
    }
    return 0;
}
