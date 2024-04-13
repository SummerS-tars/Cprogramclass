#include <stdio.h>

int main()
{
    int n ;
    printf("请输入你要输入的数的数量n(n>2):") ;
    scanf("%d" , &n ) ;

    int a , b , x ;
    // a存次最大数 , b存最大数

    //处理的思路,对前两次特别处理,可以绕过对 a , b 的不方便的初始化
    int i = 1 ;
    printf("第1个数:") ;
    scanf("%d" , &a ) ;
    i ++ ;
    printf("第2个数:") ;
    scanf("%d" , &b ) ;
    i ++ ;

    if ( a > b )
    {
        int t = b ;
        b = a ;
        a = t ;
    }

    while ( i <= n )
    {
        printf("第%d个数:", i ) ;
        scanf("%d" , &x ) ;
        if ( x > b )
        {
            a = b , b = x ;
        }
        else if ( x > a )
        {
            a = x ;
        }
        i ++ ;
    }

    printf("次最大数:%d" , a ) ;

    return 0;
}