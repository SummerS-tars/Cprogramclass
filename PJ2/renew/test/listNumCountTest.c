#include <stdio.h>

static char controlModeMenuList[4][40] = { // ����ģʽ�˵��б�
    {"ʵʱģʽ"},
    {"���ģʽ"},
    {"��ȡ����"},
    {"����"}};

int main()
{
    int num = sizeof(controlModeMenuList)/sizeof(*controlModeMenuList);
    printf("%d" , num ) ;
    return 0;
}