#include <cstdio>
#include "ClientOP.h"
void showmenu();
int main()
{
    int select = 0;
    while (1) {
        showmenu();
        printf("请输入您的选择：");
        scanf("%d", &select);
        ClientOP op("config.json");
        switch (select)
        {
        case 1: //密钥协商
            op.keyAgreement();
            break;
        case 2: //密钥校验
            break;
        case 3: //密钥注销
            break;
        case 4: //退出系统
        {
            printf("谢谢使用！");
            return 0;
        }
        default:
            break;
        }
    }
    return 0;
}
void showmenu() 
{
    printf("****************************\n");
    printf("********1、密钥协商*********\n");
    printf("********2、密钥校验*********\n");
    printf("********3、密钥注销*********\n");
    printf("********4、退出系统*********\n");
    printf("****************************\n");
}