/**
 * 链表的基本参数，封装函数
 * 1 初始化链表，创建头节点
 * 2 在尾部插入节点
 * 3 遍历节点
 * 4 删除尾部节点
 * 5 删除首节点，后面的节点不删除
 * 6 清空链表节点，不包括头节点
 * 7 销毁链表
 */

#include <stdio.h>
#include <stdlib.h>
typedef int elem_t;
typedef struct list_node_t
{
    elem_t data;
    struct list_node_t *next;
} node_t;

node_t *init_list(void);//初始话链表，返回头节点
int append_list(node_t *head, elem_t data);//在尾部插入节点
void show_list(node_t *head);//遍历节点
int destroy_list(node_t **head);

int main(void)
{
    node_t *head = init_list();

    append_list(head, 1);
    append_list(head, 2);
    append_list(head, 5);
    append_list(head, 2);
    append_list(head, 9);

    //遍历链表
    show_list(head);

    //销毁节点
    destroy_list(&head);

    return 0;
}

node_t *init_list(void)
{
    node_t *p = (node_t *)malloc(sizeof(node_t));
    if(p == NULL)
    {
        printf("链表初始化失败");
        return NULL;
    }

    //初始化时，要始终留意next指针，很重要！
    p->next = NULL;

    return p;
}

void show_list(node_t *head)
{
    if(head == NULL || head->next == NULL)
    {
        printf("链表为空\n");
        return;
    }

    node_t *p = head->next;//首节点

    //打印中间节点
    while(p->next)
    {
        printf("%d ", p->data);
        p = p->next;
    }

    //打印末尾节点
    printf("%d\n", p->data);
}

int append_list(node_t *head, elem_t data)
{
    //定义要插入的末尾节点
    node_t *insert = (node_t *)malloc(sizeof(node_t));

    if(head == NULL || insert == NULL)
    {
        printf("头节点为空或末尾节点初始化失败，插入失败");
        return 0;
    }

    insert->data = data;
    insert->next = NULL;

    node_t *p = head;//当前节点

    //找到末尾节点
    while(p->next != NULL)
    {
        //未到末尾节点，指针下移
        p = p->next;
    }

    p->next = insert;
    return 1;
}

int  destroy_list(node_t **head)
{
    if(*head == NULL)
    {
        //不需要销毁
        return 1;
    }

    node_t *p = (*head)->next;//当前节点，初始为首节点
    node_t *next = NULL;//当前节点的下一节点
    while(p)
    {
        next = p->next;
        free(p);
        p = next;
    }

    //删除头节点
    free(*head);
    *head = NULL;

    return 1;
}