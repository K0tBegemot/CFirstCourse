#include <stdlib.h>
#include <stdio.h>

typedef struct AVLTree
{
    int value;
    int height;
    struct AVLTree *L;
    struct AVLTree *R;
} AVL;

typedef struct AVLHead
{
    AVL *head;
    AVL *nodesArr;
    int nodesArrIndex;
}AVLHead;

AVLHead* CreateAVLTree(int n)
{
    AVLHead *a = (AVLHead*)malloc(sizeof(AVLHead));
    a->head = 0;
    a->nodesArr = (AVL *)malloc(sizeof(AVL) * n);
    a->nodesArrIndex = 0;
}

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
    AVL *oldTop = elem;
    elem = elem->L;
    oldTop->L = elem->R;
    elem->R = oldTop;
    RestoreCorrectHeight(elem->R);
    RestoreCorrectHeight(elem);
    return elem;
}

AVL *RotateLeftSmall(AVL *elem)
{
    AVL *oldTop = elem;
    elem = elem->R;
    oldTop->R = elem->L;
    elem->L = oldTop;
    RestoreCorrectHeight(elem->L);
    RestoreCorrectHeight(elem);
    return elem;
}

AVL *RotateRightBig(AVL *elem)
{
    AVL *tmp1 = RotateLeftSmall(elem->L);
    elem->L = tmp1;
    AVL *tmp2 = RotateRightSmall(elem);
    RestoreCorrectHeight(tmp2->R);
    RestoreCorrectHeight(tmp2->L);
    RestoreCorrectHeight(tmp2);
    return tmp2;
}

AVL *RotateLeftBig(AVL *elem)
{
    AVL *tmp1 = RotateRightSmall(elem->R);
    elem->R = tmp1;
    AVL *tmp2 = RotateLeftSmall(elem);
    RestoreCorrectHeight(tmp2->R);
    RestoreCorrectHeight(tmp2->L);
    RestoreCorrectHeight(tmp2);
    return tmp2;
}

AVL *Balance(AVL *elem)
{
    int heightDifference = CalculateHeightDifference(elem);
    if (heightDifference == 2)
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
        if (heightDifference == -2)
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

AVL *InsertElement(AVLHead *head, AVL *tree, int a)
{
    if (!tree)
    {
        AVL *newLeaf;
        newLeaf = (head->nodesArr) + (head->nodesArrIndex);
        head->nodesArrIndex += 1;
        newLeaf->height = 1;
        newLeaf->L = 0;
        newLeaf->R = 0;
        newLeaf->value = a;
        return newLeaf;
    }
    else
    {
        if (a <= tree->value)
        {
            tree->L = InsertElement(head, tree->L, a);
            RestoreCorrectHeight(tree);
        }
        else
        {
            tree->R = InsertElement(head, tree->R, a);
            RestoreCorrectHeight(tree);
        }
    }
    return Balance(tree);
}

FreeAVL(AVLHead *a)
{
    if(a)
    {
        if(a->nodesArr)
        {
            free(a->nodesArr);
        }
        free(a);
    }
}

int main()
{
    int n;
    if (scanf("%d", &n) == 0)
    {
        printf("bad input");
    }
    if (n == 0)
    {
        printf("%d", 0);
        return 0;
    }
    AVLHead *a = CreateAVLTree(n);
    int tmp = 0;
    for (int i = 0; i < n; i++)
    {
        if (scanf("%d", &tmp) == 0)
        {
            printf("bad input");
        }
        a->head = InsertElement(a, a->head, tmp);
    }
    printf("%d", GetHeight(a->head));
    FreeAVL(a);
    return 0;
}
