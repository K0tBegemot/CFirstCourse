#include <stdlib.h>
#include <stdio.h>

typedef struct AVLTree
{
    int value;
    int height;
    struct AVLTree *L;
    struct AVLTree *R;
}AVL;

int GetHeight(AVL *elem)
{
    return (elem) ? elem->height : 0;
}

void RestoreCorrectHeight(AVL *elem)
{
    int RH = GetHeight(elem->R);
    int LH = GetHeight(elem->L);
    elem->height = ((RH > LH ? RH : LH) + 1);
}

int CalculateHeightDifference(AVL *elem)
{
    return (GetHeight(elem->L) - GetHeight(elem->R));
}

AVL *RotateRightSmall(AVL *elem)
{
    AVL *OldTop = elem;
    elem = elem->L;
    OldTop->L = elem->R;
    elem->R = OldTop;
    RestoreCorrectHeight(elem->R);
    RestoreCorrectHeight(elem);
    return elem;
}

AVL *RotateLeftSmall(AVL *elem)
{
    AVL *OldTop = elem;
    elem = elem->R;
    OldTop->R = elem->L;
    elem->L = OldTop;
    RestoreCorrectHeight(elem->L);
    RestoreCorrectHeight(elem);
    return elem;
}

AVL *RotateRightBig(AVL *elem)
{
    AVL *TMP1 = RotateLeftSmall(elem->L);
    elem->L = TMP1;
    AVL *TMP2 = RotateRightSmall(elem);
    RestoreCorrectHeight(TMP2->R);
    RestoreCorrectHeight(TMP2->L);
    RestoreCorrectHeight(TMP2);
    return TMP2;
}

AVL *RotateLeftBig(AVL *elem)
{
    AVL *TMP1 = RotateRightSmall(elem->R);
    elem->R = TMP1;
    AVL *TMP2 = RotateLeftSmall(elem);
    RestoreCorrectHeight(TMP2->R);
    RestoreCorrectHeight(TMP2->L);
    RestoreCorrectHeight(TMP2);
    return TMP2;
}

AVL *Balance(AVL *elem)
{
    int HeightDifference = CalculateHeightDifference(elem);
    if (HeightDifference == 2)
    {
        if (CalculateHeightDifference(elem->L) >= 0)
        {
            return RotateRightSmall(elem);
        }
        else
        {
            return RotateRightBig(elem);
        }
    }
    else
    {
        if (HeightDifference == -2)
        {
            if (CalculateHeightDifference(elem->R) <= 0)
            {
                return RotateLeftSmall(elem);
            }
            else
            {
                return RotateLeftBig(elem);
            }
        }
    }
    return elem;
}

AVL *InsertElement(AVL *tree, int a, AVL *BitArray, int *BitArrayIndex)
{
    if (!tree)
    {
        AVL *NewLeaf;
        NewLeaf = BitArray+(*(BitArrayIndex));
        *(BitArrayIndex)+=1;
        NewLeaf->height = 1;
        NewLeaf->L = 0;
        NewLeaf->R = 0;
        NewLeaf->value = a;
        return NewLeaf;
    }else
    {
    	if (a <= tree->value)
    {
        tree->L = InsertElement(tree->L, a, BitArray, BitArrayIndex);
        RestoreCorrectHeight(tree);
    }
    else
    {
        if (a > tree->value)
        {
            tree->R = InsertElement(tree->R, a, BitArray, BitArrayIndex);
            RestoreCorrectHeight(tree);
        }
    }
	}
    return Balance(tree);
}

int main()
{
    int n;
    if (scanf("%d", &n) == 0)
    {
        printf("%s", "bad input");
    }
    if(n==0)
    {
    	printf("%d",0);
    	return 0;
	}
    AVL *TreeHead=0;
    AVL *BitArray=(AVL* )malloc(sizeof(AVL)*n);
    int BitArrayIndex=0;
    int tmp = 0;
    for (int i = 0; i < n; i++)
    {
        if (scanf("%d", &tmp) == 0)
        {
            printf("%s", "bad input");
        }
        TreeHead = InsertElement(TreeHead, tmp, BitArray, &BitArrayIndex);
    }
    printf("%d", GetHeight(TreeHead));
    free(BitArray);
    return 0;
}
