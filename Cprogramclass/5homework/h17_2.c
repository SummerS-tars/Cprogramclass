#include <stdio.h>

//返回所指字符串的不包非空字符的长度
int string_length( char *s )
{
    int num = 0 ;
    while( *s ++ ) num ++ ;
    return num ;
}