#include <stdio.h>

int reverse ( int ) ;

int main()
{
    int n ;
    printf("请输入一个整数 : " ) ;
    scanf("%d" , &n ) ;
    printf("逆序后的整数是 : %d\n" , reverse ( n ) ) ;

    return 0 ;
}

int reverse ( int n )
{
    // 递归实现

    if ( n < 10 ) return n ;

    int div = 1 ;
    while ( n / div >= 10 ) div *= 10 ;
    return n / div + 10 * reverse ( n % div ) ;
}