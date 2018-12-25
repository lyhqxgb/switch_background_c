/**
 * 1. 判断链表是否为空
 * 2. 计算链表节点个数
 * 3. 删除指定位置节点
 * 4. 在指定位置插入节点
 */

#include <stdio.h>
#include <stdlib.h>

typedef int elem_t;

typedef struct list_node
{
    elem_t data;
    struct list_node *next;
} node_t;

node_t *init_list(void);//初始化链表
int count_list(node_t *head);//计算链表节点个数
int add_list(node_t *head, int place, elem_t data);//在指定位置插入节点
int add_list_asc(node_t *head, elem_t data);//升序插入链表
int remove_node(node_t *head, int place, elem_t *data);//删除指定位置节点
int reverse_list(node_t *head);//转置链表
void show_list(node_t *haed);//打印链表
int empty_list(node_t *head);//清空链表
int destory_list(node_t **head);//销毁链表

int main(void)
{
    node_t *head = init_list();

    add_list(head, 0, 0);
    add_list(head, 1, 1);
    add_list(head, 2, 2);
    // add_list(head, 1, 6);

    show_list(head);
    printf("链表长度：%d \n", count_list(head));

    /*
    int remove;
    remove_node(head, 1, &remove);
    printf("remove = %d\n", remove);
    remove_node(head, 7, &remove);
    */

    add_list_asc(head, 3);
    add_list_asc(head, 1);
    add_list_asc(head, -1);

    show_list(head);

    reverse_list(head);

    show_list(head);
    printf("链表长度：%d \n", count_list(head));

    destory_list(&head);
    return 0;
}

int count_list(node_t *head)
{
    if(head == NULL)
    {
        printf("链表头节点为空\n");
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
        printf("链表初始化失败\n");
        return NULL;
    }

    head->next = NULL;

    return head;
}

int add_list(node_t *head, int place, elem_t data)
{
    if(head == NULL)
    {
        printf("头节点为空\n");
        return 0;
    }

    node_t *pre = head;//前一个节点
    node_t *p = head->next;//当前节点
    int num = 0;//当前节点的编号

    while(p)
    {
        if(num == place) break;
        p = p->next;
        pre = pre->next;
        num++;
    }

    if(num != place)
    {
        printf("插入失败，要插入的位置%d不在链表中\n", place);
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
        printf("表头为空\n");
        return 0;
    }

    node_t *pre = head;
    node_t *p = head->next;

    while(p)
    {
        if(data < p->data)
        {
            //说明应该插入到当前节点之前
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
        printf("头节点为空\n");
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

    if(count != place)
    {
        printf("要删除的位置%d不在链表中\n", place);
        return 0;
    }

    pre->next = p->next;
    *data = p->data;
    free(p);

    return 1;
}

int reverse_list(node_t *head)
{
    if(head == NULL)
    {
        printf("头节点为空\n");
        return 0;
    }

    if(head->next == NULL)
    {
        printf("链表为空\n");
        return 0;
    }

    /**方法1
    node_t *p = head->next;//首节点
    node_t *p_next = p->next;//第二个节点
    node_t *p_third = p_next->next;
    p->next = NULL;//首节点变成末尾节点

    while(p_third){
        //第二个节点指向首节点
        p_next->next = p;
        //首节点变成第二个节点
        p = p_next;
        //原第二个节点变成第三个节点
        p_next = p_third;
        //第三个节点指向下一个节点
        p_third = p_third->next;
    }

    //p_third为空，说明p_next已经是最后一个节点
    p_next->next = p;
    head->next = p_next;
    */

    node_t *p_first = NULL;//要插入作为首节点的元素
    node_t *p = head->next;//用来遍历链表的指针，从首节点开始遍历

    head->next = NULL;//初始时，头节点后面接空节点
    while(p)
    {
        p_first = p;
        p = p->next;
        p_first->next = head->next;
        head->next = p_first;
    }

    return 1;
}

void show_list(node_t *head)
{
    if(head == NULL)
    {
        printf("头节点为空\n");
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

    node_t *p = head->next;//当前节点
    int count = 0;//统计已清空的节点个数

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
        printf("链表头节点为空\n");
        return 0;
    }

    empty_list(*head);

    //清除头节点
    free(*head);
    *head = NULL;

    return 1;
}