#include<stdio.h>

typedef int (*Operation)(int a, int b);
typedef struct _str {
    int result ; // to sotre the resut
    int a ; // to sotre the resut
    int b ; // to sotre the resut
    Operation  opt; // funtion pointer 
} STR;

//a和b相加
int Add (int a, int b){
    return a + b ;
}

//a和b相乘
int Multi (int a, int b){
    return a * b ;
}

void DoOperation (STR *str, Operation opt){
    str->opt = *opt;
    str->result = str->opt(str->a, str->b);
}

STR strs[100];

typedef struct LinkedList {
    STR data;
    struct LinkedList *next;
} LinkedList;

int main (int argc , char **argv){
    STR str;

    str.a = 1;
    str.b = 2;

    DoOperation(&str, &Add);
    
    printf("%d", str.result);
    return 0 ;
}