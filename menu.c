#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct port{
    char name[16];
    int status;
    char ip[16];
    char type[4];
};

int login(void);
void registry(void);
void show_menu(void);
void show_ports(struct port *p, int num);
void set_ports(struct port **p, int *num);
void set_port(struct port *p);
void show_error(char *msg);
int add_port(struct port *p, int *num);

int main(void)
{
    int n;//Ҫ�����Ĳ˵���


    while(1){
        system("cls");//������������
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

    system("cls");

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
    struct port *ports = NULL;//�˿���Ϣ
    ports = malloc(sizeof(struct port));
    static int num = 0;

    while(1){
        system("cls");
        printf("������Ҫִ�еĲ�����\n");
        printf("1. �鿴�˿�\n");
        printf("2. ���ö˿�\n");
        printf("3. ����\n");

        fflush(stdin);
        scanf("%d", &operate);

        switch(operate){
            case 1: show_ports(ports, num);
                break;
            case 2: set_ports(&ports, &num);
                break;
            case 3:
                system("cls");
                return ;
            default: show_error("����Ĳ������Ϸ�");
        }
    }

    free(ports);
    
}

void show_ports(struct port *p, int num)
{
    system("cls");
    for(int i=0; i<num; i++)
    {
        printf("���ƣ�%s\t", p[i].name);
        printf("״̬��%s\t", p[i].status ? "����" : "����");
        printf("IP��%s\t", p[i].ip);
        printf("���ͣ�%s\t", p[i].type);
        printf("\n");
    }
    system("pause");
}

void set_ports(struct port **p, int *num)
{
    system("cls");
    char tmp;

    printf("������Ҫ�鿴�Ķ˿�:\n");
    for(int i=0; i<*num; i++)
    {
        printf("%d �˿�%d\n", i+1, i+1);
    }

    printf("+ ��Ӷ˿�\n");
    printf("q �˳�\n");

    fflush(stdin);
    tmp = getc(stdin);

    //�˳�
    if(tmp == 'q') return ;

    //��Ӷ˿�
    if(tmp == '+')
    {
        int res;
        res = add_port(*p, num);
        return ;//��ӳɹ���ʧ�ܣ�������һ��Ŀ¼
    }

    int edit_num = tmp - '1';

    //��ʱֻ�������9���˿�(0-8)
    if(num >= 0 && edit_num < 9){
        set_port(*p + edit_num);
    }else{
        printf("%d", num);
        show_error("û������˿�");
        return ;
    }

}

void show_error(char *msg)
{
    printf("%s", msg);
    system("pause");
}

void set_port(struct port *p)
{
    system("cls");
    printf("������˿�����");
    scanf("%s", p->name);

    printf("������˿�״̬��0�����ã�1������");
    scanf("%d", &p->status);

    printf("������ip��ַ��");
    scanf("%s", p->ip);

    printf("������˿����ͣ�LAN/WAN����");
    scanf("%s", p->type);
}

int add_port(struct port *p, int *num)
{
    int re_size = (*num + 1) * sizeof(struct port);
    p = (struct port *)realloc(p, re_size);
    if(p == NULL){
        show_error("��̬����ڴ�ʧ��");
    }

    //���ö˿�
    set_port(p + *num);
    *num += 1;
    return 1;
}