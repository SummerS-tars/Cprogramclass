#include <stdio.h>

void com_num ( int ) ;

int main()
{
    printf("1000以内的完全数有: \n") ;
    for ( int i = 2 ; i <= 1000 ; i ++ )
        com_num ( i ) ;

    return 0;
}

void com_num ( int n )
{
    int sum = 1 ;
    for ( int i = 2 ; i * i <= n ; i ++ )
        if ( n % i == 0 ) sum += i + n / i ;

    if ( sum == n ) printf("%d\n" , n ) ;
    
    return ;
}