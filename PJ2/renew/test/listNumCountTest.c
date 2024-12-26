#include <stdio.h>

static char controlModeMenuList[4][40] = { // 控制模式菜单列表
    {"实时模式"},
    {"编程模式"},
    {"获取帮助"},
    {"返回"}};

int main()
{
    int num = sizeof(controlModeMenuList)/sizeof(*controlModeMenuList);
    printf("%d" , num ) ;
    return 0;
}