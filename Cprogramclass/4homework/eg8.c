#include <stdio.h>
#include <stdbool.h>

int main()
{
    int n ;
    printf("请输入一个偶数 : n = ") ;
    scanf("%d" , &n ) ;

    //思路一，先将偶数分解为两数之和，再判断此两个数是否为质数
    bool is_Prime( int ) ;
    for( int i = 4 ; i <= n ; i += 2 )
        for ( int j = 2 ; j + j <= i ; j ++ )
            if ( is_Prime( j ) && is_Prime( i - j ) ) 
            {
                printf("%d = %d + %d \n" , i , j , i - j ) ;
                break ;
            }
}

bool is_Prime( int n )
{
    if ( n == 1 ) return false ;
    for ( int i = 2 ; i * i <= n ; i ++ )
        if ( n % i == 0 ) return false ;

    return true ;
}