/* 题目网址： https://pintia.cn/problem-sets/16/problems/670 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSIZE 1e4+1

int Find(int *Sum, int X);

int main(void)
{
    int i=0, N=0, CompA=0, CompB=0, *Sum=NULL;
    char Tmp='\0';

    scanf("%d", &N);

    Sum = calloc(N+1, sizeof(int));
    memset(Sum, -1, sizeof(int)*(N+1));
    *(Sum+0) = 0;
    for(; 'S'!=Tmp; )
    {
        getchar();
        Tmp = getchar();
        if('S'!=Tmp)
        {
            scanf(" %d %d", &CompA, &CompB);
            if('I'==Tmp)
            {
                if(Find(Sum, CompA)!=Find(Sum, CompB))
                {
                    CompA = Find(Sum, CompA), CompB = Find(Sum, CompB);
                    if(*(Sum+CompA)<*(Sum+CompB))
                    {
                        *(Sum+CompA) += *(Sum+CompB); 
                        ///此方法是记录包括根节点的家族人数，如果记录“树高”，我现在某些时候很难更改根节点的树高。
                        ///记录“树高”时，可用这组数据引发异常：5\n I 1 2\n I 3 4\n I 1 3(此时根节点树高更新为-3)\n I 1 5(此时根节点应该更新树高为-2，但实际仍未-3)
                        ///我可能还是没学明白并集查找。。。。。。
                        *(Sum+CompB) = CompA;
                    }

                    else
                    {
                        *(Sum+CompB) += *(Sum+CompA);
                        *(Sum+CompA) = CompB;
                    }
                }
            }
            else
            {
                if(Find(Sum, CompA)==Find(Sum, CompB))
                        printf("yes\n");
                else
                    printf("no\n");
            }
        }
    }

    for(i=1; i<=N; i++)
    {
            if(*(Sum+i)<0)
                *(Sum+0) += 1;
    }
    if(*(Sum+0)>1)
        printf("There are %d components.", *(Sum+0));
    else
        printf("The network is connected.");

    free(Sum);

    return 0;
}

int Find(int *Sum, int X)
{
    if(*(Sum+X)<0)
        return X;
    else
        return *(Sum+X) = Find(Sum, *(Sum+X));  ///通过尾递归, 在查找父节点的同时进行路径压缩.
}
