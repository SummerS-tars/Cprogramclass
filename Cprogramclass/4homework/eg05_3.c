#include <stdio.h>

int main()
{
    int n ;
    printf("please enter n : ") ;
    scanf("%d" , &n ) ;

    int fib ( int n ) ;
    int res ;
    res = fib ( n ) ;
    printf("the n of fib : %d\n" , res ) ;

    return 0;
}

int fib ( int n )
{
    if ( n == 1 ) return 1 ;
    if ( n == 2 ) return 1 ;

    return fib ( n - 1 ) + fib( n - 2 ) ;
}