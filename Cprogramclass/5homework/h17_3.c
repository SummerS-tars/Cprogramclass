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

//test entry
int main()
{
    char s1[ 100 ] = { '\0' } , s2[ 100 ] = { '\0' } ;
    int n ;
    printf("test\nplease enter the s2 : ") ; fgets( s2 , 100 , stdin ) ;
    
    printf("please enter how many chars you want to copy to s1 : n = ") ;
    scanf("%d" , &n) ;

    string_copy_n( s1 , s2 , n ) ;
    printf("%s\n" , s1 ) ;

    return 0;
}