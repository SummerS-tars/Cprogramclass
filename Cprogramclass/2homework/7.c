#include <stdio.h>

int main()
{
    for ( int i = 1 ; i <= 10 ; i ++ )
    {
        printf("squire of %2d : %4d\n" , i , i * i ) ;
        printf("cubic  of %2d : %4d\n" , i , i * i * i ) ;
        puts("") ;
    }

    return 0 ;
}