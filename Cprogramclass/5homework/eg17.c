#include <stdio.h>

char *find( char *s , char c )
{
    while( *s )
        if ( *s == c ) return s ;
        else s ++ ;
    return NULL ;

    /*另外一种写法：
    while( *s && *s != c) s ++ ;
    return *s ? s : NULL ;
    */
}

int main()
{
    char str[ 100 ] = { '\0' } ;
    printf("please enter a string : ") ;
    fgets( str , 100 , stdin ) ;
    
    char c;
    printf("please enter a character to find : ") ;
    scanf("%c" , &c ) ;

    char *p = find( str , c ) ;

    printf("%s" , p ? p : "not found" ) ;

    return 0;
}