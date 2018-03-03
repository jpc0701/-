#include<stdlib.h>
#include<stdio.h>

/* 
堆栈模拟队列
设已知有两个堆栈S1和S2，请用这两个堆栈模拟出一个队列Q。
所谓用堆栈模拟队列，实际上就是通过调用堆栈的下列操作函数:
int IsFull(Stack S)：判断堆栈S是否已满，返回1或0；
int IsEmpty (Stack S )：判断堆栈S是否为空，返回1或0；
void Push(Stack S, ElementType item )：将元素item压入堆栈S；
ElementType Pop(Stack S )：删除并返回S的栈顶元素。
实现队列的操作，即入队void AddQ(ElementType item)和出队ElementType DeleteQ()。
输入格式:

输入首先给出两个正整数N1和N2，表示堆栈S1和S2的最大容量。随后给出一系列的队列操作：A item表示将item入列（这里假设item为整型数字）；D表示出队操作；T表示输入结束。
输出格式:

对输入中的每个D操作，输出相应出队的数字，或者错误信息ERROR:Empty。如果入队操作无法执行，也需要输出ERROR:Full。每个输出占1行。
输入样例:

3 2
A 1 A 2 A 3 A 4 A 5 D A 6 D A 7 D A 8 D D D D T
输出样例:

ERROR:Full
1
ERROR:Full
2
3
4
7
8
ERROR:Empty
*/


#define ERROR 999999
/* 评测结果 时间  结果  得分  题目  编译器     用时（ms）  内存（MB）  用户
2016-09-03 23:44    答案正确    25  5-22    gcc     2   1   569985011
测试点结果 测试点   结果  得分/满分   用时（ms）  内存（MB）
测试点1    答案正确    15/15   2   1
测试点2    答案正确    4/4     1   1
测试点3    答案正确    6/6     2   1
查看代码*/
typedef int ElementType;

typedef struct stack {
    ElementType*S;
    int Left;
    int Right;
    int MaxSize;
}*Stack ;


Stack Creat(int);
int IsFull(Stack S);//：判断堆栈S是否已满，返回1或0；
int IsEmpty (Stack S );//：判断堆栈S是否为空，返回1或0；
void Push(Stack S, ElementType item );//：将元素item压入堆栈S；
ElementType Pop(Stack S );//：删除并返回S的栈顶元素。
void AddQ(ElementType item);//入队
ElementType DeleteQ();//出队

Stack M,N;

int main() {

    int m1,m2;
    scanf("%d%d",&m1,&m2);
    M=Creat(m1>m2?m1:m2);//入列栈
    N=Creat(m1>m2?m2:m1);//出队栈
    int flag=1;
    while(flag) {
        getchar();
        char C;
        scanf("%c",&C);
        ElementType item,temp;
//      printf("{[%c]",C);
        switch(C) {
            case 'A':
                scanf("%d",&item);
                AddQ(item);
                break;
            case 'D':
                temp=DeleteQ();
                if(temp!=ERROR) {
                    printf("%d\n",temp);
                } else printf("ERROR:Empty\n");
                break;
            case 'T':
                flag=0;
                break;
        }
//      printf("}");
    }
    return 0;
}

int IsFull(Stack S) { //：判断堆栈S是否已满，返回1或0；
    if((S->Right+1)%S->MaxSize ==S->Left%S->MaxSize)return 1;
    return 0;
}
int IsEmpty (Stack S ) { //：判断堆栈S是否为空，返回1或0；
    if(S->Right%S->MaxSize==S->Left%S->MaxSize)return 1;
    return 0;
}
void Push(Stack S, ElementType item ) { //：将元素item压入堆栈S；
    S->S[(++S->Right)%S->MaxSize]=item;
}
ElementType Pop(Stack S ) { //：删除并返回S的栈顶元素。
    ElementType temp=S->S[++S->Left%S->MaxSize];
    return temp;
}
void AddQ(ElementType item) { //入队
    if(M->Right-M->Left<N->MaxSize-1) {
        Push(M,item);
        return;
    } else if(IsEmpty(N)) {
        while(!IsEmpty(M))Push(N,Pop(M));
        Push(M,item);
    } else printf("ERROR:Full\n");


}


ElementType DeleteQ() { //出队
    ElementType temp;
    if(IsEmpty(N))while(!IsEmpty(M))Push(N,Pop(M));
    if(IsEmpty(N))return ERROR;
    else {
        temp=Pop(N);
        if(IsEmpty(M))while(!IsEmpty(N))Push(M,Pop(N));
    }
    return temp;
}
Stack Creat(int m) {
    Stack S=(Stack)malloc(sizeof(struct stack));
    S->S=(ElementType*)malloc(sizeof(ElementType)*(m+1));
    S->Left=-1;
    S->Right =-1;
    S->MaxSize =m+1;
    return S;
}