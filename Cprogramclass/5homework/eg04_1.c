#include <stdio.h>

int main()
{
    char a[] = "C language is a good language!" ;
    char *p , *q ;
    char c = ' ' ;//以c为空格为例
    printf("%s\n" , a ) ;

    p = a , q = a ;//p用于核对，q用于书写
    while ( *p )
        if ( *p != ' ' ) *q ++ = *p ++ ;
        else p ++ ;
    *q = '\0' ;

    printf("%s\n" , a ) ;
    return 0;
}