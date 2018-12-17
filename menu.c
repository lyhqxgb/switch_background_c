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
    int n;//要操作的菜单项


    while(1){
        system("cls");//进入程序后，清屏
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

    system("cls");

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
    struct port *ports = NULL;//端口信息
    ports = malloc(sizeof(struct port));
    static int num = 0;

    while(1){
        system("cls");
        printf("请输入要执行的操作：\n");
        printf("1. 查看端口\n");
        printf("2. 设置端口\n");
        printf("3. 返回\n");

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
            default: show_error("请求的操作不合法");
        }
    }

    free(ports);
    
}

void show_ports(struct port *p, int num)
{
    system("cls");
    for(int i=0; i<num; i++)
    {
        printf("名称：%s\t", p[i].name);
        printf("状态：%s\t", p[i].status ? "激活" : "禁用");
        printf("IP：%s\t", p[i].ip);
        printf("类型：%s\t", p[i].type);
        printf("\n");
    }
    system("pause");
}

void set_ports(struct port **p, int *num)
{
    system("cls");
    char tmp;

    printf("请输入要查看的端口:\n");
    for(int i=0; i<*num; i++)
    {
        printf("%d 端口%d\n", i+1, i+1);
    }

    printf("+ 添加端口\n");
    printf("q 退出\n");

    fflush(stdin);
    tmp = getc(stdin);

    //退出
    if(tmp == 'q') return ;

    //添加端口
    if(tmp == '+')
    {
        int res;
        res = add_port(*p, num);
        return ;//添加成功或失败，返回上一级目录
    }

    int edit_num = tmp - '1';

    //暂时只允许添加9个端口(0-8)
    if(num >= 0 && edit_num < 9){
        set_port(*p + edit_num);
    }else{
        printf("%d", num);
        show_error("没有这个端口");
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
    printf("请输入端口名：");
    scanf("%s", p->name);

    printf("请输入端口状态：0：禁用，1：启用");
    scanf("%d", &p->status);

    printf("请输入ip地址：");
    scanf("%s", p->ip);

    printf("请输入端口类型（LAN/WAN）：");
    scanf("%s", p->type);
}

int add_port(struct port *p, int *num)
{
    int re_size = (*num + 1) * sizeof(struct port);
    p = (struct port *)realloc(p, re_size);
    if(p == NULL){
        show_error("动态添加内存失败");
    }

    //设置端口
    set_port(p + *num);
    *num += 1;
    return 1;
}