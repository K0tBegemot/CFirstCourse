#include <stdlib.h>
#include <stdio.h>

typedef struct AVLTree
{
    int value;
    int height;
    struct AVLTree *LeftKey;
    struct AVLTree *RightKey;
} AVL;

typedef struct TreeHead
{
    struct AVLTree *Top;
} TH;

TH *CreateTree()
{
    TH *Head;
    Head = (TH *)malloc(sizeof(TH));
    Head->Top = 0;
    return Head;
}

int GetHeight(AVL *elem)
{
    return (elem) ? elem->height : 0;
}

void RestorationOfCorrectHeight(AVL *elem)
{
    int RH = GetHeight(elem->RightKey);
    int LH = GetHeight(elem->LeftKey);
    elem->height = ((RH > LH ? RH : LH) + 1);
}

int CalculateHeightDifference(AVL *elem)
{
    return GetHeight(elem->LeftKey) - GetHeight(elem->RightKey);
}

void SmallRightSpin(AVL *elem)
{
    AVL *OldTop = elem;
    elem = elem->LeftKey;
    OldTop->LeftKey = elem->RightKey;
    elem->RightKey = 0;
    RestorationOfCorrectHeight(elem->RightKey);
    RestorationOfCorrectHeight(elem);
}

void SmallLeftSpin(AVL *elem)
{
    AVL *OldTop = elem;
    elem = elem->RightKey;
    OldTop->RightKey = elem->LeftKey;
    elem->LeftKey = 0;
    RestorationOfCorrectHeight(elem->LeftKey);
    RestorationOfCorrectHeight(elem);
}

void BigRightSpin(AVL *elem)
{
    SmallLeftSpin(elem->LeftKey);
    SmallRightSpin(elem);
    RestorationOfCorrectHeight(elem->RightKey);
    RestorationOfCorrectHeight(elem->LeftKey);
    RestorationOfCorrectHeight(elem);
}

void BigLeftSpin(AVL *elem)
{
    SmallRightSpin(elem->RightKey);
    SmallLeftSpin(elem);
    RestorationOfCorrectHeight(elem->RightKey);
    RestorationOfCorrectHeight(elem->LeftKey);
    RestorationOfCorrectHeight(elem);
}

void Balance(AVL *elem)
{
    int HeightDifference = CalculateHeightDifference(elem);
    if (HeightDifference == 2)
    {
        if (CalculateHeightDifference(elem->LeftKey) >= 0)
        {
            SmallRightSpin(elem);
        }
        else
        {
            BigRightSpin(elem);
        }
    }
    else
    {
        if (HeightDifference == -2)
        {
            if (CalculateHeightDifference(elem->RightKey) <= 0)
            {
                SmallLeftSpin(elem);
            }
            else
            {
                BigLeftSpin(elem);
            }
        }
    }
}

AVL *InsertElement(AVL *elem, int a)
{
    if (!elem)
    {
        AVL *NewLeaf;
        NewLeaf = (AVL *)malloc(sizeof(AVL));
        NewLeaf->height = 1;
        NewLeaf->LeftKey = 0;
        NewLeaf->RightKey = 0;
        NewLeaf->value = a;
        return NewLeaf;
    }
    if (a < elem->value)
    {
        elem->LeftKey = InsertElement(elem->LeftKey, a);
        RestorationOfCorrectHeight(elem);
    }
    else
    {
        if (a > elem->value)
        {
            elem->RightKey = InsertElement(elem->RightKey, a);
            RestorationOfCorrectHeight(elem);
        }
    }
    Balance(elem);
    return elem;
}

void clear(AVL *elem)
{
    if ((!(elem->RightKey)) && (!(elem->LeftKey)))
    {
        free(elem);
    }
    else
    {
        if (elem->RightKey)
        {
            clear(elem->RightKey);
        }
        if (elem->LeftKey)
        {
            clear(elem->LeftKey);
        }
    }
}

int main()
{
    int n;
    if(scanf("%d", &n) == 0)
    {
    	printf("%s", "bad input");
	}
    TH *NewTree = CreateTree();
    int tmp=0;
    for (int i = 0; i < n; i++)
    {
        if(scanf("%d", &tmp) == 0)
        {
        	printf("%s", "bad input");
		}
        NewTree->Top=InsertElement(NewTree->Top, tmp);
    }
    printf("%d", GetHeight(NewTree->Top));
    return 0;
}
