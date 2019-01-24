#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "list.h"

#define CONT_FILE "contacts.txt" //通讯录保存文件

// void new_record(void);
// void search_menu(void);
// void delete_menu(void);
// void sort_menu(void);
// void write_to_file(void);

cont_list_t *init_main(void); //初始化main函数

int main(void)
{
    //初始化
    cont_list_t *head = NULL;
    head = init_main();

    while(1)
    {
        int operate = 0;

        printf("1. 添加联系人\n");
        printf("2. 查询联系人\n");
        printf("3. 删除联系人\n");
        printf("4. 对联系人排序\n");
        printf("5. 保存并退出\n");
        printf("6. 退出\n");

        scanf("%d", &operate);
        switch(operate)
        {
            case 1:
                // new_record();
                break;
            case 2:
                // search_menu();
                break;
            case 3:
                // delete_menu();
                break;
            case 4:
                // sort_menu();
                break;
            case 5:
                // write_to_file();
                break;
            case 6:
                exit(0);
        }
    }

    return 0;
}

cont_list_t *init_main(void)
{
    cont_list_t *head = (cont_list_t *)malloc(sizeof(cont_list_t));
    if(head == NULL){
        printf("初始化联系人失败\n");
        exit(1);
    }

    head->data = NULL;
    head->next = NULL;
    return head;
}