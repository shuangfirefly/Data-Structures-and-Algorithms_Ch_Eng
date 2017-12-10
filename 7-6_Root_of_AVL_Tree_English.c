
///题目网址 ： https://pintia.cn/problem-sets/16/problems/668

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct AVLNode *Position;
typedef Position AVLTree; /* AVL树类型 */
struct AVLNode
{
    ElementType Data; /* 结点数据 */
    AVLTree Left;     /* 指向左子树 */
    AVLTree Right;    /* 指向右子树 */
    int Height;       /* 树高 */
};

int Max ( int a, int b );
AVLTree SingleRightRotation(AVLTree A);
AVLTree SingleLeftRotation ( AVLTree A );
AVLTree DoubleLeftRightRotation ( AVLTree A );
AVLTree DoubleRightLeftRotation(AVLTree A);
AVLTree Insert( AVLTree T, ElementType X );
int GetHeight(AVLTree T);
void FreeNode(AVLTree T, int N);


int main(void)
{
    AVLTree Node = NULL;
    int i=0, N=0, Tmp=0;

    scanf("%d", &N);

    for(i=0; i<N; i++)
    {
        scanf("%d", &Tmp);
        Node = Insert(Node, Tmp);
    }

    printf("%d", Node->Data);
    FreeNode(Node, N);    /// 释放申请的内存。

    return 0;
}

void FreeNode(AVLTree T, int N)    ///此处用到了二维指针, 因为我不想再写一堆遍历二叉树的函数了! 丫那样太麻烦了！！！
{
    AVLTree *NodeQue=NULL;
    int i=0, Cnt=0;

    NodeQue = (AVLTree *) calloc(N, sizeof(struct AVLNode));
    *(NodeQue+(i++)) = T;

    for(i=1, Cnt=0; i<N; )
    {
        if(T->Left)
            *(NodeQue+(i++)) = T->Left;
        if(T->Right)
            *(NodeQue+(i++)) = T->Right;
        T = *(NodeQue+(++Cnt));
    }

    for(i=0; i<N; i++)
        free(*(NodeQue+i));

    free(NodeQue);
}

int Max ( int a, int b )
{
    return a > b ? a : b;
}

AVLTree SingleRightRotation(AVLTree A)
{
    AVLTree B = A->Right;
    A->Right = B->Left;
    B->Left = A;
    A->Height = Max(GetHeight(A->Left), GetHeight(A->Right)) + 1;
    B->Height = Max(GetHeight(B->Right), A->Height) + 1;

    return B;
}

AVLTree SingleLeftRotation ( AVLTree A )
{
    /* 注意：A必须有一个左子结点B */
    /* 将A与B做左单旋，更新A与B的高度，返回新的根结点B */

    AVLTree B = A->Left;
    A->Left = B->Right;
    B->Right = A;
    A->Height = Max( GetHeight(A->Left), GetHeight(A->Right) ) + 1;
    B->Height = Max( GetHeight(B->Left), A->Height ) + 1;

    return B;
}

AVLTree DoubleRightLeftRotation(AVLTree A)
{
    A->Right = SingleLeftRotation(A->Right);

    return SingleRightRotation(A);
}

AVLTree DoubleLeftRightRotation ( AVLTree A )
{
    /* 注意：A必须有一个左子结点B，且B必须有一个右子结点C */
    /* 将A、B与C做两次单旋，返回新的根结点C */

    /* 将B与C做右单旋，C被返回 */
    A->Left = SingleRightRotation(A->Left);
    /* 将A与C做左单旋，C被返回 */
    return SingleLeftRotation(A);
}


AVLTree Insert( AVLTree T, ElementType X )
{
    if(!T)
    {
        T = (AVLTree) malloc(sizeof(struct AVLNode));
        T->Data = X;
        T->Height = 0;
        T->Left = T->Right = NULL;
    }
    else if(X<T->Data)
    {
        T->Left = Insert(T->Left, X);

        if(2 == GetHeight(T->Left)-GetHeight(T->Right))
        {
            if(X<T->Left->Data)
                T = SingleLeftRotation(T);
            else
                T = DoubleLeftRightRotation(T);
        }
    }
    else if(X>T->Data)
    {
        T->Right = Insert(T->Right, X);

        if(-2 == GetHeight(T->Left)-GetHeight(T->Right))
        {
            if(X>T->Right->Data)
                T = SingleRightRotation(T);
            else
                T = DoubleRightLeftRotation(T);
        }
    }

    T->Height = Max(GetHeight(T->Left), GetHeight(T->Right)) + 1;

    return T;
}

int GetHeight(AVLTree T)
{
    if(!T)
        return -1;
    return T->Height;
}
