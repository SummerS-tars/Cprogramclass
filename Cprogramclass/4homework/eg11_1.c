#include <stdio.h>
#include <time.h>

void foo1()
{
    static int a = 10 ;
    printf("a = %d\n", a ) ;

    a -- ;
    return ;
}

int main()
{
    printf("请输入输出次数 : n = ") ;
    int n ;
    scanf("%d" , &n ) ;
    for ( int i = 1 ; i <= n ; i ++ )
        foo1() ;

    return 0;
}