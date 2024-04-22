#include <stdio.h>
#define N sizeof a/sizeof a[ 0 ]

double max( double a[] , int n )
{
    int i ; double r ;
    for( r = a[ 0 ] ,i = 1 ; i < n ; i ++ )
        if( r < a[ i ] ) r = a[ i ] ;
    return r ;
}

double min( double a[] , int n )
{
    int i ; double r ;
    for( r = a[ 0] , i = 1 ; i < n ; i ++ )
        if( r > a[ i ] ) r = a[ i ] ;
    return r;
}

double ave( double a[] , int n )
{
    int i ; double r;
    for( r = 0 , i = 0 ; i < n ; i ++ )
        r += a[ i ]; 
    return r / n ;
}

int main()
{
    //生成含10个元素的数组
    double a[ 10 ] = { 1.1 , 2.2 , 3.3 , 4.4 , 5.5 , 6.6 , 7.7 , 8.8 , 9.9 , 10.10 } ;
    double(*fpt[])(double* , int ) = { max , min , ave } ;
    char *title[] = { "最大值" , "最小值" , "平均值" } ;
    char *menuName[] = { "求最大值" , "求最小值" , "求平均值" , "" } ;
    int ans , k ;
    while ( 1 )
    {
        printf("请选择以下菜单命令\n") ;
        for( k = 0 ; menuName[ k ][ 0 ] != '\0' ; k ++ )
            printf("\t%d:%s\n" , k + 1 , menuName[ k ] ) ;
        printf("\t其他选择结束程序运行\n") ;
        scanf("%d" , &ans ) ;
        if( ans < 1 || ans > k ) break ;
        printf("%s = %f\n" , title[ ans - 1 ] , (*fpt[ ans - 1 ])( a , N ) ) ;
    }
    return 0;
}