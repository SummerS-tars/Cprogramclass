//递归函数的典例——阶乘
#include <stdio.h>

long fac( int n )
{
    if ( n == 1 ) return 1 ;

    return n * fac( n - 1 ) ;
}

int main()
{
    int n ;
    printf("Enter n :") ;
    scanf("%d" , &n ) ;

    long res = fac( n ) ;
    printf("n! = %ld\n", res ) ;
    return 0 ;
}