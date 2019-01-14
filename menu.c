#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#define SYSTEM_CLS system("cls")

typedef struct port{
    char name[16];
    int status;
    uint32_t ip;
    char type[4];
} elem_t;

typedef struct list_node{
    struct port *node;
    struct list_node *next;
} node_t;

int login(void);
void registry(void);
void show_menu(void);
void show_ports(node_t *head);
void set_ports(node_t *head, int *num);
void set_port(node_t *head, int place);
void show_error(char *msg);
int add_port(node_t *head);
node_t *list_init(void);
void check_head(node_t *head);
int free_list_node(node_t *head);//�ͷ�ĳһ�ڵ�Ŀռ�
typedef int (*free_fun_t)(node_t *);//���ͷź��������
int empty_list(node_t *head, free_fun_t);
int destroy_list(node_t **head);
int del_port(node_t *head);//ѯ���û�Ҫɾ���Ķ˿ڣ�������ɾ�����

//�����ε�ַתΪ�ַ�����ַ
void trans_int_to_ip(uint32_t num, char *ip)
{
    sprintf(ip, "%u.%u.%u.%u", num >> 24, (num >> 16) & 0xff, (num >> 8) & 0xff, num & 0xff);
}

//���ַ�����ַתΪ���ε�ַ
int trans_ip_to_int(char *ip, uint32_t *num)
{
    uint32_t tmp = 0;//��������ÿ�ζ�ȡ������ֵ
    unsigned long ip_num = 0;//ת�����ipֵ
    char *last = NULL;//��ȡ������ʣ����ַ���λ��
    int count = 0;//ͳ��һ��ȡ�˶��ٴ�����
    do{
        ip_num = strtoul(ip, &last, 10);
        //����ȡ�������ֱ��浽ip_num��
        tmp = tmp << 8;
        tmp |= ip_num;
        ip = last + 1;//���ַ���ָ�����һλ
    }while(++count < 4);

    *num = tmp;

    return 1;
}

int main(void)
{
    int n;//Ҫ�����Ĳ˵���


    while(1){
        SYSTEM_CLS;//������������
        printf("--------��������̨-------\n");
        printf("1. ��½\n");
        printf("2. ע��\n");
        printf("3. �˳�\n");

        printf("�������������");
        scanf("%d", &n);

        switch(n)
        {
            case 1:
                if(login()) show_menu();
                break;
            case 2:
                registry();
                break;
            case 3:
                return 0;
            default:
                printf("�������Ϸ�������������");
                system("pause");
                break;
        }
    }

    return 0;
}

int login(void)
{
    char input_name[32];//�û�������û���
    char input_pwd[16];//�û����������
    char name[32];//��¼���û���
    char pwd[16];//��¼������
    int check = 0;//��֤�û����������Ƿ�һ��
    FILE * file;

    SYSTEM_CLS;

    //���˻��ļ�
    file = fopen("member.txt", "r");
    if(!file){
        printf("�ļ���ʧ��\n");
        exit(1);
    }

    printf("�������û�����");
    scanf("%s", input_name);
    printf("����������: ");
    scanf("%s", input_pwd);

    //��֤�û���������
    while(!feof(file)){
        fscanf(file, "%s %s\n", name, pwd);
        if(!strcmp(input_name, name) && !strcmp(input_pwd, pwd)){
            check = 1;
            break;
        }
    }

    if(!check){
        //��֤��ͨ��
        printf("�û������������\n");
        system("pause");//��ͣ���ȴ��û���������
    }

    fclose(file);

    return check;

}

void registry(void)
{
    char name[32];//Ҫע����û���
    char pwd[16];//Ҫע�������
    FILE * file;

    file = fopen("member.txt", "a");
    if(!file){
        printf("�ļ���ʧ��");
        exit(1);
    }

    printf("������Ҫע����û�����");
    scanf("%s", name);
    printf("������Ҫע������룺");
    scanf("%s", pwd);

    fwrite(name, sizeof(char), strlen(name), file);
    fputc('\t', file);
    fwrite(pwd, sizeof(char), strlen(pwd), file);
    fputc('\n', file);

    fclose(file);

    return ;
}

void show_menu(void)
{
    int operate = 0;
    node_t *head = list_init();//�˿���Ϣ
    static int num = 0;

    while(1){
        SYSTEM_CLS;
        printf("������Ҫִ�еĲ�����\n");
        printf("1. �鿴�˿�\n");
        printf("2. ���ö˿�\n");
        printf("3. ����\n");

        fflush(stdin);
        scanf("%d", &operate);

        switch(operate){
            case 1: show_ports(head);
                break;
            case 2: set_ports(head, &num);
                break;
            case 3:
                SYSTEM_CLS;
                destroy_list(&head);
                num = 0;
                return ;
            default: show_error("����Ĳ������Ϸ�");
        }
    }
    
}

void show_ports(node_t *head)
{
    check_head(head);

    SYSTEM_CLS;
    node_t *p = head->next;
    while(p){
        printf("���ƣ�%s\t", p->node->name);
        printf("״̬��%s\t", p->node->status ? "����" : "����");
        char ip[16] = {0};
        trans_int_to_ip(p->node->ip, ip);
        printf("IP��%s\t", ip);
        printf("���ͣ�%s\t", p->node->type);
        printf("\n");
        p = p->next;
    }

    system("pause");
}

void set_ports(node_t *head, int *num)
{
    SYSTEM_CLS;
    char tmp;

    printf("������Ҫ�鿴�Ķ˿�:\n");
    for(int i=0; i<*num; i++)
    {
        printf("%d �˿�%d\n", i+1, i+1);
    }

    printf("+ ��Ӷ˿�\n");
    printf("- ɾ���˿�\n");
    printf("q �˳�\n");

    fflush(stdin);
    tmp = getc(stdin);

    //�˳�
    if(tmp == 'q') return ;

    //��Ӷ˿�
    if(tmp == '+')
    {
        int res;
        res = add_port(head);
        if(res == 1) *num += 1;//��ӳɹ����ܶ˿���+1
        return ;//��ӳɹ���ʧ�ܣ�������һ��Ŀ¼
    }

    if(tmp == '-')
    {
        int res;
        res = del_port(head);
        if(res == 1) *num -= 1;
        return ;
    }

    int edit_num = 0;
    while(tmp >= '0' && tmp <= '9'){
        //���û��������תΪ����
        tmp -= '0';
        edit_num = edit_num * 10 + tmp;
        tmp = getc(stdin);
    }

    for(int i=0; i<9; i++){
        add_port(head);
    }

    set_port(head, edit_num--);


}

void show_error(char *msg)
{
    printf("%s", msg);
    system("pause");
}

void set_port(node_t *head, int place)
{
    check_head(head);
    SYSTEM_CLS;

    //�ҵ��ýڵ�
    node_t *p = head->next;
    int count = 0;
    while(p){
        if(count == place) break;
        p = p->next;
        count++;
    }
    if(count != place){
        printf("�Ҳ����������õĶ˿�\n");
        exit(1);
    }

    printf("������˿�����");
    scanf("%s", p->node->name);

    printf("������˿�״̬��0�����ã�1������");
    scanf("%d", &p->node->status);

    char ip[16] = {0};
    printf("������ip��ַ��");
    scanf("%s", ip);
    trans_ip_to_int(ip, &(p->node->ip));

    printf("������˿����ͣ�LAN/WAN����");
    scanf("%s", p->node->type);
}

int add_port(node_t *head)
{
    check_head(head);

    //�ҵ����һ���ڵ�
    node_t *p = head;
    int num = 0;//���㵱ǰ�ڵ��λ��

    while(p->next){
        p = p->next;
        num++;
    }

    //���ö˿�
    node_t *insert = (node_t *)malloc(sizeof(node_t));
    insert->node = (elem_t *)malloc(sizeof(elem_t));
    insert->next = NULL;
    p->next = insert;

    //���û�����˿���Ϣ
    set_port(head, num);

    return 1;
}

node_t *list_init(void){
    node_t *head = (node_t *)malloc(sizeof(node_t));
    if(head == NULL){
        printf("�����ʼ��ʧ��\n");
        return NULL;
    }

    head->next = NULL;

    return head;
}

void check_head(node_t *head)
{
    if(head == NULL)
    {
        printf("�����ͷ�ļ�Ϊ��\n");
        exit(1);
    }
}

int empty_list(node_t *head, free_fun_t fun)
{
    check_head(head);

    node_t *p = head->next;
    node_t *first = NULL;
    int count = 0;

    while(p){
        first = p;
        p = p->next;
        fun(p);
        count++;
    }

    return count;
}

int destroy_list(node_t **head)
{
    empty_list(*head, free_list_node);
    free(*head);
    *head = NULL;

    return 1;
}

int del_port(node_t *head)
{
    check_head(head);

    int place = 0;
    fflush(stdin);
    printf("������Ҫɾ���Ķ˿ں�:");
    scanf("%c", &place);

    place -= '0';
    if(place <1 || place > 9){
        printf("������1-9�Ķ˿�\n");
        return 0;
    }

    node_t *pre = head;
    node_t *p = head->next;
    int count = 0;

    while(p){
        count++;
        if(count == place) break;
        p = p->next;
        pre = pre->next;
    }

    if(count != place){
        printf("�Ҳ���Ҫɾ���Ķ˿ں�\n");
        return 0;
    }

    pre->next = p->next;
    free(p->node);
    free(p);

    return 1;
}

int free_list_node(node_t *node)
{
    if(node == NULL)
    {
        printf("����Ľڵ�ΪNULL\n");
        return 0;
    }

    free(node->node);
    free(node);

    return 1;
}