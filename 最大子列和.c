#include <stdio.h>

/*
求解最大子列和的四种种算法

7-1 最大子列和问题（20 分）
给定K个整数组成的序列{ N1 , N​2 , ..., NK }，“连续子列”被定义为{ Ni , Ni+1 , ..., Nj }，
其中 1≤i≤j≤K。“最大子列和”则被定义为所有连续子列元素的和中最大者。
例如给定序列{ -2, 11, -4, 13, -5, -2 }，其连续子列{ 11, -4, 13 }有最大的和20。现要求你编写程序，计算给定整数序列的最大子列和。
本题旨在测试各种不同的算法在各种数据情况下的表现。各组测试数据特点如下：
数据1：与样例等价，测试基本正确性；
数据2：102个随机整数；
数据3：103个随机整数；
数据4：104个随机整数；
数据5：105个随机整数；
输入格式:

输入第1行给出正整数K (≤100000)；第2行给出K个整数，其间以空格分隔。
输出格式:

在一行中输出最大子列和。如果序列中所有整数皆为负数，则输出0。
输入样例:

6
-2 11 -4 13 -5 -2
输出样例:

20
*/

//第一种算法，复杂度为O(n3)
int MaxSubsequSm1(int A[],int N){
	int ThisSum=0,MaxSum=0;
	for(int i=0;i<N;++i){
		for(int j=i;j<N;++j){
			ThisSum=0;
			for(int k=i;k<=j;++k){
				ThisSum+=A[k];
			}
			if(ThisSum>MaxSum){
				MaxSum=ThisSum;
			}
		}
	}
	return MaxSum;
}

//第二种算法，复杂度为O(n2)
int MaxSubseqSum2(int A[],int N){
	int ThisSum=0,MaxSum=0;
	for(int i=0;i<N;++i){
		ThisSum=0;
		for(int j=i;j<N;++j){
			ThisSum+=A[j];
			if(ThisSum>MaxSum){
				MaxSum=ThisSum;
			}
		}
	}
	return MaxSum;
}

//第三种算法-分而治之，复杂度为nlogn

//比较三个数字的最大值
int Max3(int A,int B,int C){
	return A>B?A>C?A:C:B>C?B:C;
}

//分而治之
int DivideAndConquer(int List[],int left,int right){
    int MaxLeftSum, MaxRightSum, MaxLeftBorderSum=0, MaxRightBorderSum=0, LeftBorderSum=0, RightBorderSum=0, center;
	//递归终止判断
	if(left==right){
		if(List[left]>0)
			return List[left];
		else
			return 0;
	}
	//中间位置
	center=(left+right)/2;
	//左侧最大子列和
	MaxLeftSum=DivideAndConquer(List,left,center);
	//右侧最大子列和
	MaxRightSum=DivideAndConquer(List,center+1,right);
	//扫描左侧跨界最大子列和
	for(int i=center;i>=left;--i){
		LeftBorderSum+=List[i];
		if(LeftBorderSum>MaxLeftBorderSum)
			MaxLeftBorderSum=LeftBorderSum;
	}
	//扫描右侧跨界最大子列和
	for(int i=center+1;i<=right;++i){
		RightBorderSum+=List[i];
		if(RightBorderSum>MaxRightBorderSum)
			MaxRightBorderSum=RightBorderSum;
	}
	//返回最大子列和
	return Max3(MaxLeftSum,MaxRightSum,MaxLeftBorderSum+MaxRightBorderSum);
}

int MaxSubseqSum3(int A[],int N){
	return DivideAndConquer(A,0,N-1);
}

//第四种算法-在线处理，复杂度为O(n)
int MaxSubseqSum4(int A[],int N){
	int ThisSum=0,MaxSum=0;
	for(int i=0;i<N;++i){
		ThisSum+=A[i];
		if(ThisSum>MaxSum){
			MaxSum=ThisSum;
		}else if(ThisSum<0){
			ThisSum=0;
		}
	}
	return MaxSum;
}


int main(){
	int N;
	scanf("%d",&N);
	int A[N];
	for(int i=0;i<N;++i){
		scanf("%d",&A[i]);
	}
	printf("%d",MaxSubseqSum1(A,N));
	printf("%d",MaxSubseqSum2(A,N));
	printf("%d",MaxSubseqSum3(A,N));
	printf("%d",MaxSubseqSum4(A,N));
	return 0;
}




















