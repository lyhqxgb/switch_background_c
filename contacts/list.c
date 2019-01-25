/**
 * ������ز���
 */

#include "list.h"

int check_head(cont_list_t *head)
{
	if(head == NULL)
	{
		printf("ͷ�ڵ�Ϊ��\n");
		exit(0);
	}

	return 1;
}

//����һ���ڵ㵽ͷ��
int add_list(cont_list_t *head, const cont_t *data)
{
	check_head(head);

	cont_t *first = head->next;
	head->next = data;

	//�ж��Ƿ����׽ڵ�
	data->next = first ? first : NULL;

    return 0;
}

//ɾ��һ������
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

//��������
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

//��������
int destory_list(cont_list_t **head)
{
	check_head(*head);

	cont_t *p = *head->next;
	if(!p){
		//˵���ǿ�����
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

	//ɾ����ͷ
	free(*head);
	**head = NULL;

    return 0;
}

//�������������
int sort_list_as_num(cont_list_t *head)
{
    return 0;
}

//��������������
int sort_list_as_name(cont_list_t *head)
{
    return 0;
}