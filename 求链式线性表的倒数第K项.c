#include<stdlib.h>
#include<stdio.h>

/* 求链式线性表的倒数第K项
给定一系列正整数，请设计一个尽可能高效的算法，查找倒数第K个位置上的数字。
输入格式:

输入首先给出一个正整数K，随后是若干正整数，最后以一个负整数表示结尾（该负数不算在序列内，不要处理）。
输出格式:

输出倒数第K个位置上的数据。如果这个位置不存在，输出错误信息NULL。
输入样例:

4 1 2 3 4 5 6 7 8 9 0 -1
输出样例:

7*/

  
typedef struct node *ptrNode;  
typedef ptrNode LinkList;  //头结点  
typedef ptrNode Position;//中间节点  
typedef int ElementType;  
struct node{  
    ElementType Element;  
    Position next;  
};  
  
LinkList creatList(void)                
{  
    LinkList head,r,p;  
    int x;  
    head = (struct node*)malloc(sizeof(struct node));    //生成新结点。节点生成很耗时，考虑改掉  
    r = head;  
    scanf("%d",&x);  
  
    while(x >= 0){  
        p = (struct node*)malloc(sizeof(struct node));  
        p->Element = x;  
        r->next = p;  
        r = p;  
        scanf("%d",&x);  
    }  
    r->next = NULL;  
    return head;  
}  
  
void printLastKth(LinkList L, int k)  
{  
    Position ha, hb;  
    int i;  
  
    ha = L;  
    hb = L;  
  
        for(i = 0; i < k; i++){  
            hb = hb->next;  
            if(hb == NULL)  
                break;  
        }  
        if(hb == NULL)  
                printf("NULL");  
        else{  
            while(hb != NULL){  
                hb = hb->next;  
                ha = ha->next;  
            }  
            printf("%d",ha->Element);  
        }  
  
}  
  
void destroyLinkList(LinkList L)  
{  
    LinkList p,q;  
    p = L->next;  
    while(p){  
        q = p->next;  
        free(p);  
        p = q;  
    }  
    L = NULL;  
}  
  
int main(void)  
{  
    LinkList L;  
    int k;  
  
    scanf("%d",&k);  
    L = creatList();  
  
    printLastKth(L, k);  
      
    destroyLinkList(L);  
  
      
    return 0;  
}  