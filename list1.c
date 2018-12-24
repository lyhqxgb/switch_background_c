/**
 * ����Ļ�����������װ����
 * 1 ��ʼ����������ͷ�ڵ�
 * 2 ��β������ڵ�
 * 3 �����ڵ�
 * 4 ɾ��β���ڵ�
 * 5 ɾ���׽ڵ㣬����Ľڵ㲻ɾ��
 * 6 �������ڵ㣬������ͷ�ڵ�
 * 7 ��������
 */

#include <stdio.h>
#include <stdlib.h>
typedef int elem_t;
typedef struct list_node_t
{
    elem_t data;
    struct list_node_t *next;
} node_t;

node_t *init_list(void);//��ʼ����������ͷ�ڵ�
int append_list(node_t *head, elem_t data);//��β������ڵ�
void show_list(node_t *head);//�����ڵ�
int pop_list(node_t *head, elem_t *data);//����β�ڵ�
int shift_list(node_t *head, elem_t *data);//�����׽ڵ�
int empty_list(node_t *head);//�������
int destroy_list(node_t **head);//��������

int main(void)
{
    node_t *head = init_list();

    append_list(head, 1);
    append_list(head, 2);
    append_list(head, 5);
    append_list(head, 2);
    append_list(head, 9);

    //��������
    show_list(head);

    // elem_t data = 0;
    // pop_list(head, &data);
    // printf("%d\n", data);
    // show_list(head);

    // data = 0;
    // shift_list(head, &data);
    // printf("%d\n", data);
    // show_list(head);

    //���ٽڵ�
    destroy_list(&head);

    return 0;
}

node_t *init_list(void)
{
    node_t *p = (node_t *)malloc(sizeof(node_t));
    if(p == NULL)
    {
        printf("�����ʼ��ʧ��");
        return NULL;
    }

    //��ʼ��ʱ��Ҫʼ������nextָ�룬����Ҫ��
    p->next = NULL;

    return p;
}

void show_list(node_t *head)
{
    if(head == NULL)
    {
        printf("����Ϊ��\n");
        return;
    }

    node_t *p = head->next;//�׽ڵ�

    //��ӡ�ڵ�
    while(p != NULL)
    {
        printf("%d ", p->data);
        p = p->next;
    }

    printf("\n");
}

int append_list(node_t *head, elem_t data)
{
    //����Ҫ�����ĩβ�ڵ�
    node_t *insert = (node_t *)malloc(sizeof(node_t));

    if(head == NULL || insert == NULL)
    {
        printf("ͷ�ڵ�Ϊ�ջ�ĩβ�ڵ��ʼ��ʧ�ܣ�����ʧ��");
        return 0;
    }

    insert->data = data;
    insert->next = NULL;

    //�ҵ�ĩβ�ڵ�
    while(head->next != NULL)
    {
        //δ��ĩβ�ڵ㣬ָ������
        head = head->next;
    }

    head->next = insert;

    return 1;
}

int empty_list(node_t *head)
{
    if(head == NULL)
    {
        printf("����ͷΪ��\n");
        return 0;
    }

    node_t *p = head->next;//��ǰ�ڵ�
    while(p)
    {
        head->next = p->next;
        free(p);
        p = head->next;
    }

    return 1;
}

int  destroy_list(node_t **head)
{
    if(*head == NULL)
    {
        //����Ҫ����
        return 1;
    }

    empty_list(*head);

    //ɾ��ͷ�ڵ�
    free(*head);
    *head = NULL;

    return 1;
}

int  pop_list(node_t *head, elem_t *data)
{
    if(head == NULL || head->next == NULL)
    {
        printf("����Ϊ��");
        return 0;
    }

    node_t *pre = head;//��ǰ�ڵ��ǰһ�ڵ�
    node_t *p = head->next;//��ǰ�ڵ����һ�ڵ�

    //�ҵ����һ���ڵ�
    while(p->next != NULL)
    {
        p = p->next;
        pre = pre->next;
    }

    //�������һ���ڵ�
    *data = p->data;
    // pre->next = NULL;
    pre->next = p->next;
    free(p);

    return 1;
}

int shift_list(node_t *head, elem_t *data)
{
    if(head == NULL || head->next == NULL)
    {
        printf("����Ϊ��\n");
        return 0;
    }

    node_t *first = head->next;
    *data = first->data;
    head->next = first->next;
    free(first);

    return 1;
}