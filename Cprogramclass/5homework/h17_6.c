#include <stdio.h>

void format_string ( char *s )
{
    char *c1 , *c2 ;//c1 遍历 c2 写入
    c1 = c2 = s ;
    while( *c1 == ' ' ) c1 ++ ;

    for( ; *c1 ; c1 ++ )
    {
        if( *c1 == ' ' )
        {
            *c2 ++ = ' ' ;
            while( *c1 == ' ' ) c1 ++ ;
            c1 -- ;
        }
        else *c2 ++ = *c1 ;
    }
    if( *(c2 - 1) == ' ' ) *(c2 - 1) = '\0' ;
    else *c2 = '\0' ;
}

//test example
int main()
{
    char str[] = "      Whfo1jfafjoj   oseifhoehf  jiesoghoes g  fe f g s ge  !    " ;
    format_string( str ) ;
    printf("%s\n" , str ) ;

    return 0;
}