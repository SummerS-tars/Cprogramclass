#include <stdio.h>
#include <stdbool.h>

bool circle ( int n )
{
    char bits[ 12 ] = { '\0' } ;

    int tt = -1 ;
    while ( n )
    {
        bits[ ++ tt ] = n % 10 ;
        n /= 10 ;
    }

    for ( int i = 0 ; i <= tt ; i ++ , tt -- )
        if( bits[ i ] != bits[ tt ] ) return false ;
    
    return true ;
}

int main()
{
    int n ;
    printf("请输入一个数 : n = ") ;
    scanf("%d" , &n ) ;

    if ( circle ( n ) ) printf("%d是一个回文数\n" , n ) ;
    else printf("%d不是一个回文数\n" , n ) ;

    return 0;
}