#include <stdio.h>

int main(void)
{
    //��һ��ָ�볣����ָ����Զ�θı�ָ��ĵ�ַ�������ܸı�ָ���ֵ
    const int *p_int1;
    //int const *p_int1; //����дЧ��һ��
    int int1 = 10;
    p_int1 = &int1;
    printf("*p_int1 = %d\n", *p_int1);

    //*p_int1 = 20; //�����Ǵ���ģ����ܸı�ָ���ֵ
    int1 = 20; //�ı�ԭ��������ֵ����Ӱ�죬p_int1Ҳ����ȡ���ı���ֵ
    printf("*p_int1 = %d\n", *p_int1);


    //�ڶ���ָ�볣����ָ�벻�ܸı�ָ��ĵ�ַ�������Ըı�ָ���ֵ
    int int2 = 10;
    int * const p_int2 = &int2;
    printf("*p_int2 = %d\n", *p_int2);

    //p_int2 = NULL; //�������p_int2��ֵ�����ٸı���

    *p_int2 = 20; //����p_int2���Ըı�ָ���ֵ
    printf("*p_int2 = %d\n", *p_int2);

    //������ָ�볣����ָ�벻�ܸı�ָ��ĵ�ַ��Ҳ���ܸı�ָ���ֵ
    const int * const p_int3 = &int2;
    printf("*p_int3 = %d\n", *p_int3);
    //���������ı�ָ���ֵ��ָ���ֵҲ��ı�
    int2 = 30;
    printf("*p_int3 = %d\n", *p_int3);

    return 0;
}