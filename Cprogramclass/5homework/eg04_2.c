#include <stdio.h>
#include <string.h>

int main()
{
    char a[ 100 ] = { '\0' } ;
    printf("please enter a string : ") ;
    fgets( a , 100 , stdin ) ;
    
    char c ;
    printf("please enter a character to delete : ") ;
    scanf("%c" , &c ) ;

    char *p , *q ;
    p = a , q = a ;//p用于核对，q用于书写
    while ( *p )
        if ( *p != c ) *q ++ = *p ++ ;
        else p ++ ;
    *q = '\0' ;

    printf("%s" , a ) ;
    return 0;
}