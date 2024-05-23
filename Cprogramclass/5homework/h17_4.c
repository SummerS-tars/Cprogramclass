#include <stdio.h>
#include <string.h>

//please confirm that the size of s1 is enough
void string_cat ( char *s1 , char *s2 )
{
    while( *s1 ) s1 ++ ;
    while( *s2 ) *s1 ++ = *s2 ++ ;
    *s1 = '\0' ;
}

//test entry
int main()
{
    printf("test\n") ;
    char s1[ 100 ] = { '\0' } , s2[ 100 ] = { '\0' } ;
    
    printf("please enter s1 : ") ; fgets( s1 , 100 , stdin ) ; *(s1 + strlen( s1 ) - 1 ) = '\0' ;
    printf("please enter s2 : ") ; fgets( s2 , 100 , stdin ) ; *(s2 + strlen( s2 ) - 1 ) = '\0' ;

    string_cat( s1 , s2 ) ;
    printf("%s" , s1 ) ;

    return 0;
}