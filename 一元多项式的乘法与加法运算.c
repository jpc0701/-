#include <stdio.h>
#include <stdlib.h>


/*
一元多项式的乘法与加法运算
设计函数分别求两个一元多项式的乘积与和。
输入格式:

输入分2行，每行分别先给出多项式非零项的个数，再以指数递降方式输入一个多项式非零项系数和指数（绝对值均为不超过1000的整数）。数字间以空格分隔。
输出格式:

输出分2行，分别以指数递降方式输出乘积多项式以及和多项式非零项的系数和指数。数字间以空格分隔，但结尾不能有多余空格。零多项式应输出0 0。
输入样例:

4 3 4 -5 2 6 1 -2 0
3 5 20 -7 4 3 1
输出样例:

15 24 -25 22 30 21 -10 20 -21 8 35 6 -33 5 14 4 -15 3 18 2 -6 1
5 20 -4 4 -5 2 9 1 -2 0
*/

typedef struct PolyNode *Polynomail;
struct PolyNode{
	int coef;
	int expon;
	Polynomail link;
};

int compare(int a, int b);
Polynomail Read();  //用于读取多项式
Polynomail Add(Polynomail P1, Polynomail P2);  //多项式相加
Polynomail Multi(Polynomail P1, Polynomail P2);  //多项式相乘
void Print(Polynomail P);//打印顺序链表

int main(){
	Polynomail P1,P2;
	P1=Read();
	P2=Read();
	Polynomail Sum,Product;
	Sum=Add(P1,P2);
	Product=Multi(P1,P2);
	Print(Product);
	printf("\n");
	Print(Sum);
	return 0;
}

Polynomail Read(){
	int N;  //读取多项式数量
	scanf("%d",&N);
	Polynomail Head,Rear;  //创建头和尾的指针
	Head=(Polynomail)malloc(sizeof(struct PolyNode));  //为头指针分配内存，头指针指向的是一个数据项为空的节点
	Head->link=NULL;
	Rear=Head;  //刚开始头指针和尾指针重合
	for(int i=0;i<N;++i){
		Polynomail temp=(Polynomail)malloc(sizeof(struct PolyNode));  //创建一个节点存储数据
		scanf("%d %d",&(temp->coef),&(temp->expon));
		temp->link=NULL;
		Rear->link=temp;  //之前链表的最后一个节点指向新创建的节点
		Rear=temp;  //新节点作为为节点
	}
	return Head;  //返回头节点
}

int compare(int a, int b)  
{  
    return (a == b) ? 0 : (a > b ? 1: -1);  
} 

Polynomail Add(Polynomail P1, Polynomail P2){
	Polynomail Head,Rear;  //创建头和尾的指针
	Head=(Polynomail)malloc(sizeof(struct PolyNode));  //为头指针分配内存，头指针指向的是一个数据项为空的节点
	Head->link=NULL;
	Rear=Head;  //刚开始头指针和尾指针重合
	P1=P1->link;//因为传进来的是多项式链表的头指针，指向的是第一个节点之前的空节点。多项式链表第一个节点
	P2=P2->link;
	while(P1 || P2){//当P1和P2都是空时，说明多项式已经处理完了，退出循环
		Polynomail temp=(Polynomail)malloc(sizeof(struct PolyNode));  //创建一个节点存储数据
		temp->link=NULL;
		if((P1 && P2) && P1->expon==P2->expon){//两个多项式未处理完，并且当前两个节点的指数相等
			/*系数相加，指数不变，P1和P2各向后移动一个位置*/
			temp->coef=P1->coef+P2->coef;
			temp->expon=P1->expon;
			P1=P1->link;
			P2=P2->link;
		}else if((P1 && !P2) || ((P1 && P2) && P1->expon>P2->expon)){//多项式1未处理完多项式2处理完，或者两个多项式都没处理完并且多项式1当前的节点的指数大于多项式2的
			temp->coef=P1->coef;
			temp->expon=P1->expon;
			P1=P1->link;
		}else if((!P1 && P2) || ((P1 && P2) && P1->expon<P2->expon)){//多项式1处理完了多项式2未处理完，或者两个多项式都没处理完并且多项式1当前节点的指数小于多项式2的
			temp->coef=P2->coef;
			temp->expon=P2->expon;
			P2=P2->link;
		}
		if(temp->coef!=0){
			Rear->link=temp;
			Rear=temp;			
		}else{
			free(temp);
		}
	}
	return Head;
}

//采用逐项插入的方法
Polynomail Multi(Polynomail P1, Polynomail P2){
	Polynomail Head,t1,t2,t3;  //创建头和尾的指针
	Head=(Polynomail)malloc(sizeof(struct PolyNode));  //为头指针分配内存，头指针指向的是一个数据项为空的节点
	Head->link=NULL;
	t1=P1;
	while(t1->link){  //如果下个节点不为空，就打印出下个节点的数据项，P是从空的头节点开始的
		t2=P2;
		while(t2->link){
			Polynomail temp=(Polynomail)malloc(sizeof(struct PolyNode));  //创建一个节点存储数据
			temp->link=NULL;
			temp->coef=t1->link->coef*t2->link->coef;
			temp->expon=t1->link->expon+t2->link->expon;
			//寻找temp的位置
			t3=Head;
			while(1){
				if(t3->link==NULL){
					t3->link=temp;
					break;
				}else if(temp->expon>t3->link->expon){
					temp->link=t3->link;
					t3->link=temp;
					break;
				}else if(temp->expon==t3->link->expon){
					t3->link->coef+=temp->coef;
					if(t3->link->coef==0){
						Polynomail t;
						t=t3->link;
						t3->link=t3->link->link;
						free(t);
					}
					free(temp);
					break;
				}
				t3=t3->link;
			}
			t2=t2->link;
		}
		t1=t1->link;
	}
	return Head;
}

void Print(Polynomail P){
	if(P->link==NULL){
		printf("0 0");
	}else{
		while(P->link){  //如果下个节点不为空，就打印出下个节点的数据项，P是从空的头节点开始的
			if(P->link->link==NULL){
				printf("%d %d",P->link->coef,P->link->expon);
			}else{
				printf("%d %d ",P->link->coef,P->link->expon);
			}
			P=P->link;
		}		
	}
}