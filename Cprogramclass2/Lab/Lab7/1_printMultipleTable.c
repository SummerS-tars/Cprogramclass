#include <stdio.h>

int main()
{
    for( int i = 0 ; i <= 9 ; i ++ )
        if( i ) printf("%d\t" , i ) ;
        else printf("\t" ) ;
    puts("") ;
    
    for( int i = 1 ; i <= 9 ; i ++ )
    {
        printf("%d\t" , i ) ;
        for( int j = 1 ; j <= i ; j ++ )
            printf("%d\t" , i * j ) ;
        puts("") ;
    }
}