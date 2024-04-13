#include <stdio.h>

int main()
{
    float x[ 10 ] = { 0 } ;//下标对应指数,对应存储的值为系数

    printf("第一个多项式:\n") ;
    while( 1 )
    {
        float a ;
        int b ;
        printf("请输入多项式的次数b(0<=b<=9,输入负数时结束): b = ") ;
        scanf("%d" , &b ) ;
        if ( b < 0 ) break ;
        if ( b > 9 )
        {
            printf("超出接受按范围,请重新输入\n") ;
            continue;
        }

        printf("请输入次数为%d项的系数a: a = " , b ) ;
        scanf("%f" , &a ) ;
        x[ b ] += a ;
    }

    printf("第二个多项式:\n") ;
    while( 1 )
    {
        float a ;
        int b ;
        printf("请输入多项式的次数b(0<=b<=9,输入负数时结束): b = ") ;
        scanf("%d" , &b ) ;
        if ( b < 0 ) break ;
        if ( b > 9 )
        {
            printf("超出接受按范围,请重新输入\n") ;
            continue;
        }

        printf("请输入次数为%d项的系数a: a = " , b ) ;
        scanf("%f" , &a ) ;
        x[ b ] += a ;
    }

    for ( int i = 9 ; i >= 0 ; i -- )
    {
        if ( i && x[ i ] )
            printf("%.1fx^%d+" , x[ i ] , i ) ;
        if ( ! i )
        {
            if ( x[ i ] ) printf("%.1f" , x[ i ] ) ;
            else
            {
                int j = 9 ;
                while ( j > 0 && ! x[ j ] ) j --;//停留在第一个不是0的位数上
                if ( ! j ) printf("0") ;//全都是0的情况只输出常数0
                else printf("\b ") ;//清除多余的加号
            }
        } 
    }

    return 0;
}