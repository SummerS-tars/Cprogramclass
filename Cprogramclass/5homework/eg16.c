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

double afun( double a[] , int n , double(*fpt)(double * , int ))
{
    return (*fpt)( a , n ) ;
}

int main()
{
    //生成含10个元素的数组
    double a[ 10 ] = { 1.1 , 2.2 , 3.3 , 4.4 , 5.5 , 6.6 , 7.7 , 8.8 , 9.9 , 10.10 } ;
    printf( "the results are : \n" ) ;
    printf("max = %f\n" , afun( a, N , max ) ) ;
    printf("min = %f\n" , afun( a, N , min ) ) ;
    printf("ave = %f\n" , afun( a, N , ave ) ) ;
    return 0;
}