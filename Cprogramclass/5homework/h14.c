#include <stdio.h>

char *strpos( char *s , char *t )
{
    char *j , *k ;
    for( ; *s ; s ++ )
    {
        for( j = s , k = t ; *k && *j == *k ; j ++ , k ++ ) ;
        if( k != t && ! *k ) return s ;
    }
    return NULL ;
}
//此函数用于在字符串s中查找字符串t，如果找到则返回t在s中的位置，否则返回NULL。