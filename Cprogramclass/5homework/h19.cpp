#include <stdio.h>

int main()
{
    char *cp[ 2 ] ;
    char s1[ 100 ] = { '\0' } , s2[ 100 ] = { '\0' } ;

    printf("please enter the first string : " ) ;
    fgets( s1 , 100 , stdin ) ;
    printf("please enter the second string : " ) ;
    fgets( s2 , 100 , stdin ) ;

    cp[ 0 ] = s1 , cp[ 1 ] = s2 ;
    void swap_str ( char *& , char *& ) ;

    swap_str( cp[ 0 ] , cp[ 1 ] ) ;
    
    puts("after swap") ;
    printf("the 1st string : %s\nthe 2nd string : %s\n" , cp[ 0 ] , cp [ 1 ] ) ;
    return 0;
}

void swap_str ( char *& a , char *& b )
{
    char *c = a ;
    a = b , b = c ;
}