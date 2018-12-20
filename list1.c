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
int destroy_list(node_t **head);

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
    if(head == NULL || head->next == NULL)
    {
        printf("����Ϊ��\n");
        return;
    }

    node_t *p = head->next;//�׽ڵ�

    //��ӡ�м�ڵ�
    while(p->next)
    {
        printf("%d ", p->data);
        p = p->next;
    }

    //��ӡĩβ�ڵ�
    printf("%d\n", p->data);
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

    node_t *p = head;//��ǰ�ڵ�

    //�ҵ�ĩβ�ڵ�
    while(p->next != NULL)
    {
        //δ��ĩβ�ڵ㣬ָ������
        p = p->next;
    }

    p->next = insert;
    return 1;
}

int  destroy_list(node_t **head)
{
    if(*head == NULL)
    {
        //����Ҫ����
        return 1;
    }

    node_t *p = (*head)->next;//��ǰ�ڵ㣬��ʼΪ�׽ڵ�
    node_t *next = NULL;//��ǰ�ڵ����һ�ڵ�
    while(p)
    {
        next = p->next;
        free(p);
        p = next;
    }

    //ɾ��ͷ�ڵ�
    free(*head);
    *head = NULL;

    return 1;
}