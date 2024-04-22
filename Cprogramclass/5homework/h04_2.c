#include <stdio.h>

int main()
{
    char str[ 10 ] = "C program" ;
    char *cp = "Hello World" ;

    printf("%s\n" , str ) ;
    printf("%s\n" , cp ) ;

    for( int i = 0 ; i < 10 ; i ++ )
        printf("%c " , str[ i ]) ;
    puts("") ;

    for( int i = 0 ; i < 12 ; i ++ )
        printf("%c " , cp[ i ] ) ;
    puts("") ;

    for( int i = 0 ; i < 10 && str[ i ] ; i ++ )
        str[ i ] = '!' ;
    printf("%s\n" , str ) ;

    /*
    for( int i = 0 ; i < 11 && *cp ; i ++ )
        cp[ i ] = '!' ;
    printf("%s\n" , cp ) ;
    */

    return 0;
}