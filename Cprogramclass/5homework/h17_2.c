#include <stdio.h>
#include <string.h>

//返回所指字符串的不包非空字符的长度
int string_length( char *s )
{
    int num = 0 ;
    while( *s ++ ) num ++ ;
    return num ;
}

int main()
{
    printf("test\n") ;
    char str[ 1000 ] = { '\0' } ;
    printf("please input the string : ") ; fgets( str ,1000 , stdin ) ; str[ strlen(str) - 1 ] = '\0' ;

    int num = string_length( str ) ;
    printf("num = %d\n" , num ) ;

    return 0;
}