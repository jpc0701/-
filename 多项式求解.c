#include <stdio.h>
#include <time.h>
#include <math.h>

#define MAXN 10
#define MAXK 1e7

/*
多项式的求解
*/

clock_t start,end;
double duration;

double f1(int n,double a[],double x){
	double p=0;
	for(int i=0;i<=n;++i)
		p+=(a[i]*pow(x,i));
	return p;
}

double f2(int n,double a[],double x){
	double p=a[n];
	for(int i=n;i>0;--i)
		p=a[i-1]+x*p;
	return p;
}

int main(){
	double x=1.1,a[MAXN];
	int n=MAXN;
	for(int i=0;i<n;++i)
		a[i]=(double)i;	
	
	start=clock();
	for(int i=0;i<MAXK;++i)
		f1(n-1,a,x);
	end=clock();
	duration=((double)(end-start))/CLK_TCK/MAXK;
	printf("ticks1 = %f\n",(double)(end-start));
	printf("duration1 = %6.2e\n",duration);
	
	start=clock();
	for(int i=0;i<MAXK;++i)
		f2(n-1,a,x);
	end=clock();
	duration=((double)(end-start))/CLK_TCK/MAXK;
	printf("ticks2 = %f\n",(double)(end-start));
	printf("duration2 = %6.2e\n",duration);
	return 0;
}