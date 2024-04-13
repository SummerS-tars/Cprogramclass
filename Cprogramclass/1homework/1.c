#include <stdio.h>

int main()
{
    int a[ 8 ] = { 9 , 64 , 85 , -53 , -111 , 2499 , -28654 , 21019 } ;

    puts("********************\n八进制：") ;
    for ( int i = 0 ; i < 8 ; i ++ )
        printf("( %d ) %#-12o ;\n" , i , a[ i ] ) ;
    
    puts("********************\n十六进制：") ;
    for ( int i = 0 ; i < 8 ; i ++ )
        printf("( %d ) %#-12x ;\n" , i , a[ i ] ) ;

    puts("********************") ;
    
    return 0 ;
}