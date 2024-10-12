#include <stdio.h>
#include <curses.h>

char menuList1[ 10 ][ 100 ] = {
    {"开始游戏"} ,
    {"获取帮助"} ,
    {"退出游戏"} 
} ;
char menuListGame[ 10 ][ 100 ] = {
    {"第一关"} ,
    {"第二关"} ,
    {"第三关"}
} ;

void menu( int listPos )
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

int main()
{
    int pos = 0 ;
    while( 1 )
    {
        menu( pos ) ;

        int menuOption ;
        menuOption = getch() ;
        if( menuOption == 'w' && pos > 0 ) pos -- ;
        else if( menuOption == 's' && pos < 2 ) pos ++ ;
        else if( menuOption == '\n' ) ;
    }
    return 0;
}