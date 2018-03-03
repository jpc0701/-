#include<stdlib.h>
#include<stdio.h>

/* 
两个有序链表序列的交集
已知两个非降序链表序列S1与S2，设计函数构造出S1与S2的交集新链表S3。
输入格式:

输入分两行，分别在每行给出由若干个正整数构成的非降序序列，用−1表示序列的结尾（−1不属于这个序列）。数字用空格间隔。
输出格式:

在一行中输出两个输入序列的交集序列，数字间用空格分开，结尾不能有多余空格；若新链表为空，输出NULL。
输入样例:

1 2 5 -1
2 4 5 8 10 -1
输出样例:

2 5
*/

typedef struct Node* List;
struct Node{
    int Data;
    struct Node*Next;
};
List Search(List L1,List L2,List L3);
List init();
void Insert(List L,int t);
int main(){
    List L1,L2,L3;
    int t;
    L1=init();
    L2=init();
    L3=init();
    while(1){
        scanf("%d",&t);
        if(t==-1){
            break;
        }
        else{
            Insert(L1,t);
        }
    }
    while(1){
        scanf("%d",&t);
        if(t==-1){
            break;
        }
        else{
            Insert(L2,t);
        }
    }
  //  for(;L1!=NULL;L1=L1->Next){
   //     printf("%d ",L1->Data);
  //  }
    if((!L1)||(!L1->Next)||(!L2)||(!L2->Next)){
        printf("NULL");
        return 0;
    }
    L3=Search(L1,L2,L3);
    if((!L3)||(!L3->Next)){
        printf("NULL");
        return 0;
    }
    for(L3=L3->Next;L3->Next!=NULL;L3=L3->Next){
        printf("%d ",L3->Data);
    }
    printf("%d",L3->Data);
    return 0;
}

List init(){
    List L;
    L=(List)malloc(sizeof(struct Node));
    if(!L)return NULL;
    L->Next=NULL;
    return L;
}
void Insert(List L,int t){
    List p=(List)malloc(sizeof(struct Node));
    if(!p)return ;
    p->Data=t;
    p->Next=L->Next;
    L->Next=p;
    return ;
}
List Search(List L1,List L2,List L3){
    List p,q;
    p=L1->Next;
    q=L2->Next;
    while((p!=NULL)&&(q!=NULL)){
        if(p->Data<q->Data){
            q=q->Next;
        }
        else if(p->Data>q->Data){
            p=p->Next;
        }
        else{
            Insert(L3,p->Data);
            p=p->Next;
            q=q->Next;
        }
    }
    return L3;
}
