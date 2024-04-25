#include <stdio.h>

void string_copy_n ( char *s1 , char *s2 , int n )
{
    for( int i = 0 ; i < n ; i ++ )
    {
        if( *s2 ) *s1 ++ = *s2 ++ ;
        else break ;
    }
    s1 = '\0' ;
}