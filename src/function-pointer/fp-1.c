#include <stdio.h>
#include <assert.h>
 
typedef int (*FP_CALC)(int,int);//定义一个函数指针类型
 
int add(int a, int b)
{
	return a + b;
}
 
int sub(int a, int b)
{
	return a - b;
}
 
int mul(int a, int b)
{
	return a * b;
}
 
int div(int a, int b)
{
	return b ? a/b : -1;
}
 
//定义一个函数，参数为op，返回一个指针,该指针类型为拥有两个int参数、
//返回类型为int的函数指针。它的作用是根据操作符返回相应函数的地址
FP_CALC calc_func(char op)
{
	switch( op )
	{
	case '+':
		return add;
	case '-':
		return sub;
	case '*':
		return mul;
	case '/':
		return div;
	default:
		return NULL;
	}
	return NULL;
}
 
//s_calc_func为函数，它的参数是 op，   
//返回值为一个拥有两个int参数、返回类型为int的函数指针  
FP_CALC s_calc_func(char op)
{
	return calc_func(op);
}
 
//最终用户直接调用的函数，该函数接收两个int整数，
//和一个算术运算符，返回两数的运算结果
int calc(int a, int b, char op)
{
	FP_CALC fp = calc_func(op);
	FP_CALC s_fp = s_calc_func(op);//用于测试
 
	assert(fp == s_fp);// 可以断言这两个是相等的
 
	if(fp)
		return fp(a,b);
	else
		return -1;
}
 
int main() {
	int a = 100, b = 20;
 
	printf("calc(%d, %d, %c) = %d\n", a, b, '+', calc(a, b, '+'));
	printf("calc(%d, %d, %c) = %d\n", a, b, '-', calc(a, b, '-'));   
    printf("calc(%d, %d, %c) = %d\n", a, b, '*', calc(a, b, '*'));   
    printf("calc(%d, %d, %c) = %d\n", a, b, '/', calc(a, b, '/')); 

    return 0;
}
