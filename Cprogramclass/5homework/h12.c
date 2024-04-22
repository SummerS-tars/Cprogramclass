#include <stdio.h>
#include <string.h>

int main()
{
    char str[ 1000 ] = { '\0' } ;
    printf("Enter a string : ") ;
    fgets( str , 1000 , stdin ) ;
    str[ strlen( str ) - 1 ] = '\0' ;

    void del_rep( char *str ) ;

    del_rep( str ) ;
    printf("string after delete : %s\n" , str ) ;

    return 0;
}

void del_rep( char *str )
{
    int c[ 256 ] = { 0 } ;

    char *cp1 , *cp2 ;//cp1 用于覆写，cp2 用于遍历
    for( cp1 = cp2 = str ; *cp2 ; cp2 ++ )
        if( c[ *cp2 ] == 0 )
        {
            c[ *cp2 ] ++ ;
            *cp1 ++ = *cp2 ;
        }
    *cp1 = '\0' ;
}