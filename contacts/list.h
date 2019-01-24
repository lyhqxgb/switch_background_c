#include <stddef.h>

typedef struct contact{
    char province[5]; //省
    char postal[6];   //邮编
    char name[10];
    char tel[12];
    char address[50]; //街道
    char city[50];    //城市

} cont_t;

typedef struct contact_list{
    cont_t *data;
    struct contact_list *next;
} cont_list_t;

//添加链表
int add_list(cont_list_t *head, const cont_t *data);
//删除链表
int del_list(cont_list_t *head, int place);
//查找链表
cont_t *search_list(cont_list_t *head, int place);
//销毁链表
int destory_list(cont_list_t **head);
//按编号排序链表
int sort_list_as_num(cont_list_t *head);
//按姓名排序链表
int sort_list_as_name(cont_list_t *head);