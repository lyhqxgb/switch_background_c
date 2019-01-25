/**
 * 链表相关操作
 */

#include "list.h"

int check_head(cont_list_t *head)
{
	if(head == NULL)
	{
		printf("头节点为空\n");
		exit(0);
	}

	return 1;
}

//增加一个节点到头部
int add_list(cont_list_t *head, const cont_t *data)
{
	check_head(head);

	cont_t *first = head->next;
	head->next = data;

	//判断是否有首节点
	data->next = first ? first : NULL;

    return 0;
}

//删除一个链表
int del_list(cont_list_t *head, int place)
{
	check_head(head);

	cont_t *p = head->next;
	cont_t *pre_p = head;
	int count = 1;

	while(p){
		if(count == place) break;
		p = p->next;
		pre_p = pre_p->next;
	}

	if(count != place){
		return 0;
	}

	pre_p->next = p->next;
	free(p);

    return 1;
}

//查找链表
cont_t *search_list(cont_list_t *head, int place)
{
    check_head(head);

	cont_t *p = head->next;
	int count = 1;

	while(p){
		if(count == place) break;
		p = p->next;
	}

	if(count != place){
		return NULL;
	}

    return p;
}

//销毁链表
int destory_list(cont_list_t **head)
{
	check_head(*head);

	cont_t *p = *head->next;
	if(!p){
		//说明是空链表
		free(*head);
		**head = NULL;
		return 0;
	}

	cont_t *next_p = NULL;
	while(p){
		next_p = p->next;
		free(p);
		p = next_p;
	}

	//删除表头
	free(*head);
	**head = NULL;

    return 0;
}

//按编号排序链表
int sort_list_as_num(cont_list_t *head)
{
    return 0;
}

//按姓名排序链表
int sort_list_as_name(cont_list_t *head)
{
    return 0;
}