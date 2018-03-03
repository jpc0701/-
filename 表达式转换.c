#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


/*
表达式转换
算术表达式有前缀表示法、中缀表示法和后缀表示法等形式。日常使用的算术表达式是采用中缀表示法，即二元运算符位于两个运算数中间。请设计程序将中缀表达式转换为后缀表达式。
输入格式:

输入在一行中给出不含空格的中缀表达式，可包含+、-、*、\以及左右括号()，表达式不超过20个字符。
输出格式:

在一行中输出转换后的后缀表达式，要求不同对象（运算数、运算符号）之间以空格分隔，但结尾不得有多余空格。
输入样例:

2+3*(7-4)+8/4
输出样例:

2 3 7 4 - * + 8 4 / +
*/

//此题开始有一个测试点未过，因为只考虑了-有两种形式，符号和运算符；对于+，未考虑其为符号
//我想说的是，真是为了出题而出题，虽然代码量没有因此增加，但正数把符号+加上，滑稽......

char stack[30];
int top=-1;
int getnum(char data[],int loc)//返回此运算数的字符形式有几个字符
{
    if((data[loc]=='-'||data[loc]=='+')&&loc-1>=0&&(isdigit(data[loc-1])||data[loc-1]==')'))//+和-的特殊情况，此时为运算符，不是符号
        return 0;
    int count=0;
    if(data[loc]=='-'||data[loc]=='+'){
        count++;
        loc++;
    }
    while(data[loc]&&strchr("+-*/()",data[loc])==NULL){
        count++;
        loc++;
    }
    return count;
}
void deal(char ch)
{
    if(ch=='+'){
        while(top>=0&&stack[top]!='(')
            printf(" %c",stack[top--]);
        stack[++top]='+';
    }
    else if(ch=='-'){
        while(top>=0&&stack[top]!='(')
            printf(" %c",stack[top--]);
        stack[++top]='-';
    }
    else if(ch=='*'){
        while(top>=0&&stack[top]!='('&&stack[top]!='+'&&stack[top]!='-')
            printf(" %c",stack[top--]);
        stack[++top]='*';
    }
    else if(ch=='/'){
        while(top>=0&&stack[top]!='('&&stack[top]!='+'&&stack[top]!='-')
            printf(" %c",stack[top--]);
        stack[++top]='/';

    }
    return;
}
int main()
{
    int i,j;
    int flag=0;//用来判断此字符前输不输出空格
    char data[30];//原始数据
    gets(data);
    for(i=0;data[i];i++){
        int num;
        if((num=getnum(data,i))!=0){//如果为运算数
            char temp[30];//存运算数的字符串形式
            for(j=0;j<num;j++)
                temp[j]=data[i+j];
            temp[j]='\n';
            i=i+num-1;//更新i
            double result=atof(temp);
            if(flag)
              printf(" %g",result);
            else
              printf("%g",result);
            flag=1;
        }
        else if(data[i]=='(')
            stack[++top]='(';//（入栈
        else if(data[i]==')'){//（）内运算符出栈
            while(stack[top]!='('){
                printf(" %c",stack[top--]);
            }
            top--;
        }
        else if(strchr("+-*/",data[i])!=NULL){//为运算符
            deal(data[i]);
        }
    }
    for(int i=top;i>=0;i--)//弹出栈内剩余运算符
        printf(" %c",stack[i]);
    return 0;
}
