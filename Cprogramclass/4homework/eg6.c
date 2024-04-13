#include <stdio.h>

int digits ( int n )
{
    int res = 0 ;
    while ( n )
    {
        res ++ ;
        n /= 10 ;
    }

    return res ;
}

int main()
{
    int n ;
    printf("请输入一个数 : n = ") ;
    scanf("%d" , &n ) ;

    printf("它的位数是 : %d\n" , digits( n ) ) ;

    return 0;
}