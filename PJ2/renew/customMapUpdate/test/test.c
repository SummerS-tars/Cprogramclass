#include <stdio.h>
#include "02_cursorOperation.h"
#include <windows.h>

int main()
{
    int px = 0 , py = 0 ;
    COORD loc ;

    printf("�����������뷽����\n\n");
    GetCursorPosition( &px , &py ) , loc.X = px , loc.Y = py ;

    printf("\n\n") ;
    printf("�����������һ��");
    MoveCursorTo( loc.X , loc.Y ) ;

    int re = 0 ;
    scanf("%d" , &re) ;

    system("cls") ;
    printf("����������ǣ�%d\n" , re) ;
    return 0; 
}