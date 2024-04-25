#include <stdio.h>

void string_cat ( char *s1 , char *s2 )
{
    while( *s1 ++ ) ;
    while( *s2 ) *s1 ++ = *s2 ++ ;
    s1 = '\0' ;
}