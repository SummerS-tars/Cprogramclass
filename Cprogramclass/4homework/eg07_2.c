#include <stdio.h>
#include <stdbool.h>

bool circle_B ( int n )
{
    char bits[ 33 ] = { '\0' } ;
    
    int tt = -1 ;
    while ( n )
    {
        bits[ ++ tt ] = n % 2 ;
        n /= 2;
    }

    for( int i = 0 ; i <= tt ; i ++ , tt -- )
        if ( bits[ i ] != bits[ tt ]) return false ;
    
    return true ;
}

int main()
{
    int n;
    printf("请输入一个十进制整数 : n = ") ;
    scanf("%d" , &n ) ;

    if ( circle_B ( n ) ) printf("十进制整数%d的二进制是回文数\n", n ) ;
    else printf("十进制整数%d的二进制不是回文数\n", n ) ;

    return 0 ;
}
//以上模版可以直接挪用到八进制或者十六进制或者任意进制