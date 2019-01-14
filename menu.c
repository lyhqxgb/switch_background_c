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
int free_list_node(node_t *head);//释放某一节点的空间
typedef int (*free_fun_t)(node_t *);//给释放函数起别名
int empty_list(node_t *head, free_fun_t);
int destroy_list(node_t **head);
int del_port(node_t *head);//询问用户要删除的端口，并返回删除结果

//将整形地址转为字符串地址
void trans_int_to_ip(uint32_t num, char *ip)
{
    sprintf(ip, "%u.%u.%u.%u", num >> 24, (num >> 16) & 0xff, (num >> 8) & 0xff, num & 0xff);
}

//将字符串地址转为整形地址
int trans_ip_to_int(char *ip, uint32_t *num)
{
    uint32_t tmp = 0;//用来保存每次读取到的数值
    unsigned long ip_num = 0;//转化后的ip值
    char *last = NULL;//读取整数后，剩余的字符串位置
    int count = 0;//统计一共取了多少次数字
    do{
        ip_num = strtoul(ip, &last, 10);
        //将读取到的数字保存到ip_num中
        tmp = tmp << 8;
        tmp |= ip_num;
        ip = last + 1;//将字符串指针后移一位
    }while(++count < 4);

    *num = tmp;

    return 1;
}

int main(void)
{
    int n;//要操作的菜单项


    while(1){
        SYSTEM_CLS;//进入程序后，清屏
        printf("--------交换机后台-------\n");
        printf("1. 登陆\n");
        printf("2. 注册\n");
        printf("3. 退出\n");

        printf("请输入操作数：");
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
                printf("操作不合法，请重新输入");
                system("pause");
                break;
        }
    }

    return 0;
}

int login(void)
{
    char input_name[32];//用户输入的用户名
    char input_pwd[16];//用户输入的密码
    char name[32];//记录的用户名
    char pwd[16];//记录的密码
    int check = 0;//验证用户名和密码是否一致
    FILE * file;

    SYSTEM_CLS;

    //打开账户文件
    file = fopen("member.txt", "r");
    if(!file){
        printf("文件打开失败\n");
        exit(1);
    }

    printf("请输入用户名：");
    scanf("%s", input_name);
    printf("请输入密码: ");
    scanf("%s", input_pwd);

    //验证用户名和密码
    while(!feof(file)){
        fscanf(file, "%s %s\n", name, pwd);
        if(!strcmp(input_name, name) && !strcmp(input_pwd, pwd)){
            check = 1;
            break;
        }
    }

    if(!check){
        //验证不通过
        printf("用户名或密码错误\n");
        system("pause");//暂停，等待用户后续操作
    }

    fclose(file);

    return check;

}

void registry(void)
{
    char name[32];//要注册的用户名
    char pwd[16];//要注册的密码
    FILE * file;

    file = fopen("member.txt", "a");
    if(!file){
        printf("文件打开失败");
        exit(1);
    }

    printf("请输入要注册的用户名：");
    scanf("%s", name);
    printf("请输入要注册的密码：");
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
    node_t *head = list_init();//端口信息
    static int num = 0;

    while(1){
        SYSTEM_CLS;
        printf("请输入要执行的操作：\n");
        printf("1. 查看端口\n");
        printf("2. 设置端口\n");
        printf("3. 返回\n");

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
            default: show_error("请求的操作不合法");
        }
    }
    
}

void show_ports(node_t *head)
{
    check_head(head);

    SYSTEM_CLS;
    node_t *p = head->next;
    while(p){
        printf("名称：%s\t", p->node->name);
        printf("状态：%s\t", p->node->status ? "激活" : "禁用");
        char ip[16] = {0};
        trans_int_to_ip(p->node->ip, ip);
        printf("IP：%s\t", ip);
        printf("类型：%s\t", p->node->type);
        printf("\n");
        p = p->next;
    }

    system("pause");
}

void set_ports(node_t *head, int *num)
{
    SYSTEM_CLS;
    char tmp;

    printf("请输入要查看的端口:\n");
    for(int i=0; i<*num; i++)
    {
        printf("%d 端口%d\n", i+1, i+1);
    }

    printf("+ 添加端口\n");
    printf("- 删除端口\n");
    printf("q 退出\n");

    fflush(stdin);
    tmp = getc(stdin);

    //退出
    if(tmp == 'q') return ;

    //添加端口
    if(tmp == '+')
    {
        int res;
        res = add_port(head);
        if(res == 1) *num += 1;//添加成功，总端口数+1
        return ;//添加成功或失败，返回上一级目录
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
        //将用户输入的数转为整数
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

    //找到该节点
    node_t *p = head->next;
    int count = 0;
    while(p){
        if(count == place) break;
        p = p->next;
        count++;
    }
    if(count != place){
        printf("找不到可以设置的端口\n");
        exit(1);
    }

    printf("请输入端口名：");
    scanf("%s", p->node->name);

    printf("请输入端口状态：0：禁用，1：启用");
    scanf("%d", &p->node->status);

    char ip[16] = {0};
    printf("请输入ip地址：");
    scanf("%s", ip);
    trans_ip_to_int(ip, &(p->node->ip));

    printf("请输入端口类型（LAN/WAN）：");
    scanf("%s", p->node->type);
}

int add_port(node_t *head)
{
    check_head(head);

    //找到最后一个节点
    node_t *p = head;
    int num = 0;//计算当前节点的位置

    while(p->next){
        p = p->next;
        num++;
    }

    //设置端口
    node_t *insert = (node_t *)malloc(sizeof(node_t));
    insert->node = (elem_t *)malloc(sizeof(elem_t));
    insert->next = NULL;
    p->next = insert;

    //让用户输入端口信息
    set_port(head, num);

    return 1;
}

node_t *list_init(void){
    node_t *head = (node_t *)malloc(sizeof(node_t));
    if(head == NULL){
        printf("链表初始化失败\n");
        return NULL;
    }

    head->next = NULL;

    return head;
}

void check_head(node_t *head)
{
    if(head == NULL)
    {
        printf("传入的头文件为空\n");
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
    printf("请输入要删除的端口号:");
    scanf("%c", &place);

    place -= '0';
    if(place <1 || place > 9){
        printf("请输入1-9的端口\n");
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
        printf("找不到要删除的端口号\n");
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
        printf("传入的节点为NULL\n");
        return 0;
    }

    free(node->node);
    free(node);

    return 1;
}