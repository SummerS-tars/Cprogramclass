#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

extern char menuList1[ 10 ][ 20 ] = {
    {"开始游戏"} ,
    {"获取帮助"} ,
    {"退出游戏"} 
} ;
extern char menuListGame[ 10 ][ 20 ] = {
    {"第一关"} ,
    {"第二关"} ,
    {"第三关"}
} ;

extern void menu( int listPos )                                     // 菜单函数，根据listPos变量控制光标位置
{
    printf("欢迎来到小黄的奇妙冒险\n\n") ;

    for( int i = 0 ; i <= 2 ; i ++ )
    {
        if( i == listPos ) printf("> ") ;
        else printf("  ") ;
        printf("%s\n" , menuList1 + i ) ;
    }
    printf("\n输入w上移光标,s下移光标,输入<Enter>选中\n") ;
}

extern void menuControl()
{
    int pos = 0 ;
    while( 1 )                                                      // 菜单循环逻辑：不断根据输入刷新菜单，
    {                                                               // 直至enter选择，通过pos变量控制光标位置并且记录选择状态
        system("cls") ;
        // 如果要求跨平台，可以使用如下代码代替
        // printf("\033[H\033[J");

        menu( pos ) ;

        int menuOption ;
        menuOption = getch() ;
        if( menuOption == 'w' && pos > 0 ) pos -- ;
        else if( menuOption == 's' && pos < 2 ) pos ++ ;
        else if( menuOption == '\r') break ;
    }
}