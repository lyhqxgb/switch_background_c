#include <stdio.h>

int main(void)
{
    //第一种指针常量，指针可以多次改变指向的地址，但不能改变指向的值
    const int *p_int1;
    //int const *p_int1; //这样写效果一样
    int int1 = 10;
    p_int1 = &int1;
    printf("*p_int1 = %d\n", *p_int1);

    //*p_int1 = 20; //这样是错误的，不能改变指向的值
    int1 = 20; //改变原来变量的值不受影响，p_int1也可以取到改变后的值
    printf("*p_int1 = %d\n", *p_int1);


    //第二种指针常量，指针不能改变指向的地址，但可以改变指向的值
    int int2 = 10;
    int * const p_int2 = &int2;
    printf("*p_int2 = %d\n", *p_int2);

    //p_int2 = NULL; //编译错误，p_int2的值不能再改变了

    *p_int2 = 20; //但是p_int2可以改变指向的值
    printf("*p_int2 = %d\n", *p_int2);

    //第三种指针常量，指针不能改变指向的地址，也不能改变指向的值
    const int * const p_int3 = &int2;
    printf("*p_int3 = %d\n", *p_int3);
    //其它变量改变指向的值，指针的值也会改变
    int2 = 30;
    printf("*p_int3 = %d\n", *p_int3);

    return 0;
}