#include <stdio.h>

int is_prime ( int ) ;

int main()
{
    int n ;
    printf("请输入一个整数 : ") ;
    scanf("%d" , &n ) ;
    if ( is_prime ( n ) ) printf("%d是质数\n", n ) ;
    else printf("%d不是质数\n" , n ) ;

    printf("1000以内的质数有 : \n" ) ;
    for ( int i = 2 ; i<= 1000 ; i ++ )
        if ( is_prime ( i ) ) printf("%d " , i ) ;

    return 0;
}

int is_prime ( int n )
{
    if ( n == 1 ) return 0 ;
    for ( int i = 2 ; i * i <= n ; i ++ )
        if ( n % i == 0 ) return 0 ;
    return 1 ;
}