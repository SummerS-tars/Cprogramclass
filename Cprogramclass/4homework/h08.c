#include <stdio.h>

int gcd ( int , int ) ;

int main()
{
    int a , b ;
    printf("请输入两个整数 : ") ;
    scanf("%d%d" , &a , &b ) ;

    printf(" %d 与 %d 的最大公约数是 %d \n" , a , b , gcd ( a , b ) ) ;

    return 0;
}

int gcd ( int a ,int b )
{
    printf(" %d %d \n" , a , b ) ;

    if ( a == b ) return a ;
    if ( a > b ) return gcd ( a - b , b ) ;
    return gcd ( a , b - a ) ;
}