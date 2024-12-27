#include <stdio.h>
#include "02_cursorOperation.h"
#include <windows.h>

int main()
{
    int px = 0 , py = 0 ;
    COORD loc ;

    printf("测试特殊输入方法中\n\n");
    GetCursorPosition( &px , &py ) , loc.X = px , loc.Y = py ;

    printf("\n\n") ;
    printf("这是最下面的一行");
    MoveCursorTo( loc.X , loc.Y ) ;

    int re = 0 ;
    scanf("%d" , &re) ;

    system("cls") ;
    printf("输入的数字是：%d\n" , re) ;
    return 0; 
}