/**
 * ������ɷ���
 */

#include <stdio.h>
#include <stdlib.h>

/**
 * ��ʮ����תΪ�����ƣ�
 * 1���Ӹ�λ��ʼ����ÿһλ%2���õ��ľ��Ǹ�λ��ֵ
 * 2��ÿ�õ�һλ�󣬽�ʮ������/2������ȡ�����õ��ľ��ǻ�û�������
 * 3���ظ�����1-����2��֪��δ�������Ϊ0
 * example:
 * ʮ���ƣ�5
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
 * ��������תΪʮ���ƣ�
 * �����һλ��ʼ������ֵnum*2^n��nΪ��ǰλ�������һλΪ0�����ε���
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
    // printf("��ʮ����%dתΪ�����ƣ�\n", num);
    // print_10_to_2(num);

    // char num2[] = "1101";
    // printf("��������%s תΪʮ���ƣ�%d\n", num2, trans_2_to_10(num2));

    unsigned int a = 0xc3057ad3;
    unsigned int a_origion = a;
    unsigned int b = 0;

    //1������һ��������a������a��bit3����֤����λ����
    printf("\n");
    a = 0xc3057ad3;
    print_10_to_2(a);
    b = 1 << 3;
    a |= b;
    printf("\n");
    print_10_to_2(a);
    printf("\n");


    //2������һ��������a������a��bit3~bit7����������λ����
    printf("\n");
    a = 0xc3057ad3;
    print_10_to_2(a);
    b = 0x1f << 3; // 11111
    a |= b;
    printf("\n");
    print_10_to_2(a);
    printf("\n");

    //3������һ��������a�����a��bit14����֤����λ���䡣
    printf("\n");
    a = 0xc3057ad3;
    print_10_to_2(a);
    b = ~(1 << 14); // 11111
    a &= b;
    printf("\n");
    print_10_to_2(a);
    printf("\n");

    //4������һ��������a�����a��bit15~bit23����������λ���䡣
    printf("\n");
    a = 0xc3057ad3;
    print_10_to_2(a);
    b = ~(0x1ff << 15); // 1 1111 1111
    a &= b;
    printf("\n");
    print_10_to_2(a);
    printf("\n");

    //5������һ��������a��ȡ��a��bit3~bit8��
    //ע�⣺Ҫȡ�������������Ҫ������λ����&��֮�����ƾͿ��Եó��Ǹ�����
    printf("\n");
    a = 0xc3057ad3;
    print_10_to_2(a);
    b = 0xbf << 3; // 11 1111
    a &= b;
    printf("\n");
    a = a >> 3;
    print_10_to_2(a);
    printf("\n");

    //6����C���Ը�һ���Ĵ�����bit7��bit17��ֵ937������λ����Ӱ�죩��
    //ע�⣺Ҫ��ֵ����Ҫ��Ҫ��ֵ���Ǽ�λ����&��Ȼ�����Ҫ��ֵ�������Ƶ��Ǽ�λ�ϾͿ�����
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

    //7������һ������a, a��bit7��bit17�е�ֵ��17������λ����Ӱ�죩��
    //ע�⣺Ҫ��ֵ����Ҫ���Ǽ�λ������ȡ������Ȼ����Ǽ�λ����&��֮�����ƣ���ӣ����ƣ�����1 |
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


    //8������һ������a, a��bit7��bit17��ֵ937��ͬʱ��bit21��bit25��ֵ17��
    //ע�⣺ͬʱ��ֵ��һ��������ֵ��һ���ģ����Ƕ��˼�������
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

