#include <stdio.h>

int main()
{
    int num ;
    do
    {
        printf("enter 0/other to clear the screen or print it out : ") ;
        scanf("%d"  , &num ) ;
        if( num ) printf("You choose to print : %d\n"  , num ) ;
        else system("clear") ;
    } while( num ) ;

    return 0;
}