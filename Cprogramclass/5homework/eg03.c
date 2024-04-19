#include <stdio.h>

int main()
{
    char a[ 10 ] = "C program" , b[ 10 ] , *from , *to ;

    /*
    from = a , to = b ;
    for ( int i = 0 ; from[ i ] <= a[ 9 ] ; i ++ ) to[ i ] = from[ i ] ;
    */
    
    /*
    for ( from = a , to = b ; from < a + 10 ; from ++ , to ++ )
        *to = *from ;
    */

    from = a , to = b ;
    while( *to ++ = *from ++ ) ;

    printf("%s\n" , b ) ;

    return 0;
}