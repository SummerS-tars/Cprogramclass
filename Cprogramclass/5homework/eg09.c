#include <stdio.h>

void strcpy( char *from , char *to )
{
    while ( *from )
        *to ++ = *from ++ ;
}

int strcmp( char *a , char *b )
{
    while ( *a && *b )
        if ( *a > *b ) return 1 ;//前者大于后者，返回1
        else if ( *a < *b ) return -1 ;//前者小于后者，返回-1
        else a++ , b++ ;
    return 0;//遍历到最后，字典序相等
}

int main()
{
    char a[ 1000 ] = { '\0' } , b[ 1000 ] = { '\0' } ;
    printf("please enter string a : ") ;
    fgets( a , 1000 , stdin ) ;
    printf("please enter string b : ") ;
    fgets( b , 1000 , stdin ) ;

    int res = strcmp( a , b ) ;
    if( res == 1 ) printf("a > b\n") ;
    else if( res == -1 ) printf("a < b\n") ;
    else printf("a = b") ;

    strcpy( a , b ) ;
    printf("a : %sb : %s" , a , b ) ;
    
    return 0;
}