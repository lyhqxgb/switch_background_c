/**
 * 1. �ж������Ƿ�Ϊ��
 * 2. ��������ڵ����
 * 3. ɾ��ָ��λ�ýڵ�
 * 4. ��ָ��λ�ò���ڵ�
 */

#include <stdio.h>
#include <stdlib.h>

typedef int elem_t;

typedef struct list_node
{
    elem_t data;
    struct list_node *next;
} node_t;

node_t *init_list(void);//��ʼ������
int count_list(node_t *head);//��������ڵ����
int add_list(node_t *head, int place, elem_t data);//��ָ��λ�ò���ڵ�
int add_list_asc(node_t *head, elem_t data);//�����������
int remove_node(node_t *head, int place, elem_t *data);//ɾ��ָ��λ�ýڵ�
int get_node(node_t *head, int place, elem_t *data);//��ȡ����ָ��λ�õ�����
int list_merge(node_t *head1, node_t *head2);//�ϲ���������
int reverse_list(node_t *head);//ת������
int find_save_node(node_t *head1, node_t *head2, elem_t *data);//�ҳ�����������ͬ����
void show_list(node_t *haed);//��ӡ����
int empty_list(node_t *head);//�������
int destory_list(node_t **head);//��������

int main(void)
{
    node_t *head = init_list();

    add_list(head, 0, 0);
    add_list(head, 1, 1);
    add_list(head, 2, 2);
    add_list(head, 1, 6);

    show_list(head);
    printf("�����ȣ�%d \n", count_list(head));

    /*
    int data = 0;
    get_node(head, 1, &data);
    printf("%d\n", data);
    get_node(head, 4, &data);
    printf("%d\n", data);
    */

    /*
    int remove;
    remove_node(head, 1, &remove);
    printf("remove = %d\n", remove);
    remove_node(head, 7, &remove);
    */

    node_t *head2 = init_list();
    add_list_asc(head2, 3);
    add_list_asc(head2, 1);
    add_list_asc(head2, -1);
    show_list(head2);

    int data = 0;
    find_save_node(head, head2, &data);
    printf("��ͬ�Ľڵ�Ϊ��%d\n", data);

    // list_merge(head, head2);

    show_list(head);

    // reverse_list(head);

    // show_list(head);
    // printf("�����ȣ�%d \n", count_list(head));

    destory_list(&head);
    destory_list(&head2);
    return 0;
}

int count_list(node_t *head)
{
    if(head == NULL)
    {
        printf("����ͷ�ڵ�Ϊ��\n");
        return 0;
    }

    node_t *p = head->next;
    int count = 0;

    while(p)
    {
        count++;
        p = p->next;
    }

    return count;
}

node_t *init_list(void)
{
    node_t *head = (node_t *)malloc(sizeof(node_t));
    if(head == NULL)
    {
        printf("�����ʼ��ʧ��\n");
        return NULL;
    }

    head->next = NULL;

    return head;
}

int add_list(node_t *head, int place, elem_t data)
{
    if(head == NULL)
    {
        printf("ͷ�ڵ�Ϊ��\n");
        return 0;
    }

    node_t *pre = head;//ǰһ���ڵ�
    node_t *p = head->next;//��ǰ�ڵ�
    int num = 0;//��ǰ�ڵ�ı��

    while(p)
    {
        if(num == place) break;
        p = p->next;
        pre = pre->next;
        num++;
    }

    if(num != place)
    {
        printf("����ʧ�ܣ�Ҫ�����λ��%d����������\n", place);
        return 0;
    }

    node_t *insert = (node_t *)malloc(sizeof(node_t));
    insert->data = data;
    insert->next = p;

    pre->next = insert;

    return 1;
}

int add_list_asc(node_t *head, elem_t data)
{
    if(head == NULL)
    {
        printf("��ͷΪ��\n");
        return 0;
    }

    node_t *pre = head;
    node_t *p = head->next;

    while(p)
    {
        if(data < p->data)
        {
            //˵��Ӧ�ò��뵽��ǰ�ڵ�֮ǰ
            break;
        }
        p = p->next;
        pre = pre->next;
    }

    node_t *insert = (node_t *) malloc(sizeof(node_t));
    insert->data = data;

    insert->next = p;
    pre->next = insert;

    return 1;
}

int remove_node(node_t *head, int place, elem_t *data)
{
    if(head == NULL)
    {
        printf("ͷ�ڵ�Ϊ��\n");
        return 0;
    }

    node_t *pre = head;
    node_t *p = head->next;
    int count = 0;

    while(p)
    {
        if(count == place) break;
        p = p->next;
        pre = pre->next;
        count++;
    }

    if(p == NULL)
    {
        printf("Ҫɾ����λ��%d����������\n", place);
        return 0;
    }

    pre->next = p->next;
    *data = p->data;
    free(p);

    return 1;
}

int get_node(node_t *head, int place, elem_t *data)
{
    if(head == NULL)
    {
        printf("ͷ�ڵ�Ϊ��\n");
        return 0;
    }

    node_t *p = head->next;
    int count = 0;

    while(p)
    {
        if(count == place)
        {
            break;
        }
        count++;
        p = p->next;
    }

    if(p == NULL)
    {
        printf("�Ҳ���ָ��λ�õĽڵ�\n");
        return 0;
    }

    *data = p->data;

    return 1;
}

int find_save_node(node_t *head1, node_t *head2, int *data)
{
    if(head1 == NULL || head2 == NULL)
    {
        printf("����ı�ͷΪ��\n");
        return 0;
    }
    
    node_t *p1 = head1->next;
    node_t *p2 = head2->next;

    while(p1)
    {
        while(p2)
        {
            if(p1->data == p2->data)
            {
                *data = p1->data;
                return 1;
            }
            p2 = p2->next;
        }

        p1 = p1->next;
        p2 = head2->next;//whileѭ���У�p2�Ѿ���NULL������Ҫ��ԭΪ�׽ڵ�
    }

    printf("�Ҳ�����ͬ�Ľڵ�\n");

    return 0;
}

int reverse_list(node_t *head)
{
    if(head == NULL)
    {
        printf("ͷ�ڵ�Ϊ��\n");
        return 0;
    }

    if(head->next == NULL)
    {
        printf("����Ϊ��\n");
        return 0;
    }

    /**����1
    node_t *p = head->next;//�׽ڵ�
    node_t *p_next = p->next;//�ڶ����ڵ�
    node_t *p_third = p_next->next;
    p->next = NULL;//�׽ڵ���ĩβ�ڵ�

    while(p_third){
        //�ڶ����ڵ�ָ���׽ڵ�
        p_next->next = p;
        //�׽ڵ��ɵڶ����ڵ�
        p = p_next;
        //ԭ�ڶ����ڵ��ɵ������ڵ�
        p_next = p_third;
        //�������ڵ�ָ����һ���ڵ�
        p_third = p_third->next;
    }

    //p_thirdΪ�գ�˵��p_next�Ѿ������һ���ڵ�
    p_next->next = p;
    head->next = p_next;
    */

    node_t *p_first = NULL;//Ҫ������Ϊ�׽ڵ��Ԫ��
    node_t *p = head->next;//�������������ָ�룬���׽ڵ㿪ʼ����

    head->next = NULL;//��ʼʱ��ͷ�ڵ����ӿսڵ�
    while(p)
    {
        p_first = p;
        p = p->next;
        p_first->next = head->next;
        head->next = p_first;
    }

    return 1;
}

int list_merge(node_t *head1, node_t *head2)
{
    if(head1 == NULL || head2 == NULL)
    {
        printf("����ı�ͷΪ��\n");
        return 0;
    }

    node_t *p = head1;

    //�ҳ�head1�����һ���ڵ�
    while(p->next)
    {
        p = p->next;
    }

    p->next = head2->next;
    head2->next = NULL;

    return 1;
}

void show_list(node_t *head)
{
    if(head == NULL)
    {
        printf("ͷ�ڵ�Ϊ��\n");
    }

    node_t *first = head->next;
    while(first)
    {
        printf("%d ", first->data);
        first = first->next;
    }

    printf("\n");
}

int empty_list(node_t *head)
{
    if(head == NULL)
    {
        return 0;
    }

    node_t *p = head->next;//��ǰ�ڵ�
    int count = 0;//ͳ������յĽڵ����

    while(p)
    {
        head->next = p->next;
        free(p);
        count++;
        p = head->next;
    }

    return count;
}

int destory_list(node_t **head)
{
    if(head == NULL)
    {
        printf("����ͷ�ڵ�Ϊ��\n");
        return 0;
    }

    empty_list(*head);

    //���ͷ�ڵ�
    free(*head);
    *head = NULL;

    return 1;
}