#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>

/*
线性表-顺序结构
*/

//定义队列容量
#define MAXSIZE 10
//定义队列的数据类型
typedef int ElementType;
//定义位置
typedef int Position;
//节点结构体
struct LNode{
	//存放数据的数组
	ElementType Data[MAXSIZE];
	//最后一个元素的位置
	Position Last;
};
//节点指针
typedef struct LNode *List;

//初始化
List MakeEmpty(){
	List L;
	//分配内存
	L=(List)malloc(sizeof(struct LNode));
	//目前没有元素
	L->Last=-1;
	return L;
}

//查找
Position Find(List L,ElementType X){
	Position i;
	//循环查找，当超出范围或者遇到要查找的值就退出
	for(i=0;i<=L->Last && L->Data[i]!=X;++i){}
	//判断是超出范围还是遇到要查找的值
	if(i>L->Last) return -1;
	else return i;
}

//插入
bool Insert(List L,ElementType X,Position P){
	//判断线性表是否已满
	if(L->Last+1==MAXSIZE){
		printf("线性表已满！");
		return false;
	}
	//判断插入位置是否合法
	if(X<0 || X>L->Last+1){
		printf("插入位置不合法！");
		return false;
	}
	//将插入位置之后的元素都向后挪以为
	for(Position i=L->Last;i>=P;--i)
		L->Data[i+1]=L->Data[i];
	//插入元素
	L->Data[P]=X;
	//最后一个元素位置增加1
	++L->Last;
	return true;
}

int main(){
	
	return 0;
}