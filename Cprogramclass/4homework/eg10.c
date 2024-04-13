#include <stdio.h>

int main()
{
    int n ;
    printf("请输入一个整数 : n = ") ;
    scanf("%d" , &n ) ;

    void pri_rev ( int ) ;

    printf("反向输出n : ") ;
    pri_rev ( n ) ;
    puts("") ;

    return 0 ;
}

void pri_rev ( int n )
{
    if ( n == 0 ) return ;

    printf("%d" , n % 10 ) ;
    
    pri_rev( n / 10 ) ;

    return ;
}