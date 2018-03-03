#include<stdlib.h>
#include<stdio.h>

/* 
两个有序链表序列的合并
已知两个非降序链表序列S1与S2，设计函数构造出S1与S2的并集新非降序链表S3。
输入格式:

输入分两行，分别在每行给出由若干个正整数构成的非降序序列，用−1表示序列的结尾（−1不属于这个序列）。数字用空格间隔。
输出格式:

在一行中输出合并后新的非降序链表，数字间用空格分开，结尾不能有多余空格；若新链表为空，输出NULL。
输入样例:

1 3 5 -1
2 4 6 8 10 -1
输出样例:

1 2 3 4 5 6 8 10
*/

typedef struct Node* List;
struct Node{
    int data;
    struct Node *Next;
};
List InitList();
void print(List l);
void read(List l);
void combine(List l1,List l2,List l3);
int main()
{
    List l1,l2,l3;
    l1=InitList();
    l2=InitList();
    l3=InitList();
    read(l1);
    read(l2);
    combine(l1,l2,l3);
    print(l3);
    return 0;
}
List InitList()
{
    List l;
    l=(List)malloc(sizeof(struct Node));
    if(!l) return NULL;
    l->Next=NULL;
    return l;
}
void print(List l)
{
    l=l->Next;
    if(l==NULL)
    {
    	printf("NULL");
    	return;
	}
    while(l)
    {
    	if(l->Next==NULL)
    		printf("%d",l->data);
		else printf("%d ",l->data);
		l=l->Next;
	}
        
}
void read(List l)
{
    List tmp;
    int data;
    scanf("%d",&data);
    while(data>0)
    {
        tmp=(List)malloc(sizeof(struct Node));
        if(!tmp) return;
        tmp->data=data;
        tmp->Next=NULL;
        l->Next=tmp;
        l=tmp;
        scanf("%d",&data);
    }
    return;
}
void combine(List l1,List l2,List l3)
{
    l1=l1->Next;
    l2=l2->Next;
    while(l1!=NULL&&l2!=NULL)
    {
        if(l1->data>l2->data)
        {
            l3->Next=l2;
            l2=l2->Next;
        }
        else
        {
            l3->Next=l1;
            l1=l1->Next;
        }
        l3=l3->Next;
    }
    if(l1==NULL&&l2==NULL) return;
    if(l1!=NULL)
        l3->Next=l1;
    else l3->Next=l2;
    return;
}