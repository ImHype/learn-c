#include <stdio.h>
#include <stdlib.h>

typedef int (*compareFunc)(void *data1);
// getMax 函数参数说明：
// data 待比较数据数组的首地址,uniteSize单元字节个数
// length：数据的长度。{1,3,5,6}：length=4
// 比较data1和data2指向的数据做比较，
// 如果data1>data2，则返回正数
void *getMax(void *data,compareFunc func)
{
    func(data);
    return data;
}

int intDataCompare(void *data1,void *data2)
{
    int *ptr1 = (int*)data1;
    int *ptr2 = (int*)data2;

    int i1=*ptr1;
    int i2=*ptr2;

    return i1-i2;
}

typedef struct _Dog
{
    char *name;
    int age;
} Dog;

int dogDataCompare(void *data1)
{
    Dog *dog1 = (Dog*)data1;
    printf("%s", dog1->name);
    return dog1->age;
}

int main(int argc, char *argv[])
{
    Dog * data = (Dog *) malloc(sizeof(Dog));
    data->name = "shaepi";
    data->age = 3;

    Dog *dog1 = (Dog*) getMax(data, dogDataCompare);
    printf("%s", dog1->name);

    return 0;
}