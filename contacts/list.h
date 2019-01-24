#include <stddef.h>

typedef struct contact{
    char province[5]; //ʡ
    char postal[6];   //�ʱ�
    char name[10];
    char tel[12];
    char address[50]; //�ֵ�
    char city[50];    //����

} cont_t;

typedef struct contact_list{
    cont_t *data;
    struct contact_list *next;
} cont_list_t;

//�������
int add_list(cont_list_t *head, const cont_t *data);
//ɾ������
int del_list(cont_list_t *head, int place);
//��������
cont_t *search_list(cont_list_t *head, int place);
//��������
int destory_list(cont_list_t **head);
//�������������
int sort_list_as_num(cont_list_t *head);
//��������������
int sort_list_as_name(cont_list_t *head);