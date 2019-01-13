/**
 * 进制相干方法
 */

#include <stdio.h>
#include <stdlib.h>

/**
 * 将十进制转为二进制：
 * 1、从各位开始，对每一位%2，得到的就是该位的值
 * 2、每得到一位后，将十进制数/2，向下取整，得到的就是还没处理的数
 * 3、重复步骤1-步骤2，知道未处理的数为0
 * example:
 * 十进制：5
 * first: 5 % 2 = 1
 *        (int)5 / 2 = 2
 * second: 2 % 2 = 0
 *        (int)2 / 2 = 1
 * third: 1 % 2 = 1
 *        (int)1 / 2 = 0
 * result: 1111011
 */
void print_10_to_2(unsigned int num){
    if((num / 2) != 0){
        print_10_to_2(num / 2);
    }
   
    printf("%d", num % 2);
}

/**
 * 将二进制转为十进制：
 * 从最后一位开始，将数值num*2^n，n为当前位数，最后一位为0，依次递增
 * example:
 * 101: 1*2^2 + 0*2^1 + 1*2^0 = 5
 */
int trans_2_to_10(char *str){
    int res = 0;
    int num = 0;
    while(*str != '\0'){
        num = *str - '0';
        if(num >=0 && num <2){
            res = res*2 + num;
        }

        str++;
    }

    return res;
}

int main(void)
{
    // int num = 123;
    // printf("将十进制%d转为二进制：\n", num);
    // print_10_to_2(num);

    // char num2[] = "1101";
    // printf("将二进制%s 转为十进制：%d\n", num2, trans_2_to_10(num2));

    unsigned int a = 0xc3057ad3;
    unsigned int a_origion = a;
    unsigned int b = 0;

    //1、给定一个整型数a，设置a的bit3，保证其他位不变
    printf("\n");
    a = 0xc3057ad3;
    print_10_to_2(a);
    b = 1 << 3;
    a |= b;
    printf("\n");
    print_10_to_2(a);
    printf("\n");


    //2、给定一个整形数a，设置a的bit3~bit7，保持其他位不变
    printf("\n");
    a = 0xc3057ad3;
    print_10_to_2(a);
    b = 0x1f << 3; // 11111
    a |= b;
    printf("\n");
    print_10_to_2(a);
    printf("\n");

    //3、给定一个整型数a，清除a的bit14，保证其他位不变。
    printf("\n");
    a = 0xc3057ad3;
    print_10_to_2(a);
    b = ~(1 << 14); // 11111
    a &= b;
    printf("\n");
    print_10_to_2(a);
    printf("\n");

    //4、给定一个整形数a，清除a的bit15~bit23，保持其他位不变。
    printf("\n");
    a = 0xc3057ad3;
    print_10_to_2(a);
    b = ~(0x1ff << 15); // 1 1111 1111
    a &= b;
    printf("\n");
    print_10_to_2(a);
    printf("\n");

    //5、给定一个整形数a，取出a的bit3~bit8。
    //注意：要取出这个数，首先要把其他位清零&，之后右移就可以得出那个数了
    printf("\n");
    a = 0xc3057ad3;
    print_10_to_2(a);
    b = 0xbf << 3; // 11 1111
    a &= b;
    printf("\n");
    a = a >> 3;
    print_10_to_2(a);
    printf("\n");

    //6、用C语言给一个寄存器的bit7～bit17赋值937（其余位不受影响）。
    //注意：要赋值就需要把要赋值的那几位清零&，然后把需要赋值的数左移到那几位上就可以了
    printf("\n");
    a = 0xc3057ad3;
    print_10_to_2(a);
    b = ~(0x7ff << 7); // 111 1111 1111
    a &= b;
    printf("\n");
    print_10_to_2(a);
    printf("\n");
    b = 937 << 7;
    a |= b;
    print_10_to_2(a);
    printf("\n");

    //7、给定一个整数a, a的bit7～bit17中的值加17（其余位不受影响）。
    //注意：要加值，就要把那几位的数字取出来，然后把那几位清零&，之后右移，相加，左移，再置1 |
    printf("\n");
    a = 0xc3057ad3;
    unsigned int old = 0;
    unsigned int new = 0;
    b = 0x7ff << 7; //111 1111 1111
    print_10_to_2(a);
    printf("\n");
    old = a & b;
    old = old >> 7;
    new = old + 17;
    print_10_to_2(new);
    printf("\n");
    new = new << 7;
    a &= ~b;
    a |= new;
    print_10_to_2(a);
    printf("\n");


    //8、给定一个整数a, a的bit7～bit17赋值937，同时给bit21～bit25赋值17。
    //注意：同时赋值和一个个来赋值是一样的，就是多了几步而已
    printf("\n");
    a = 0xc3057ad3;
    print_10_to_2(a);
    printf("\n");
    unsigned int change = 0;
    b = 0x7ff << 7; //111 1111 1111
    a &= ~b;
    a |= 937 << 7;
    print_10_to_2(a);
    printf("\n");

    b = 0x1f << 21; // 1 1111
    a &= ~b;
    a |= 17 << 21;
    print_10_to_2(17);
    printf("\n");
    print_10_to_2(a);

    return 0;
}

