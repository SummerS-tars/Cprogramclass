#include <stdio.h>

//方法一：m*n

//实现将最前面的数转移至最后，后面的数向前移动
void be_last ( int a[] , int size )
{
    int t = a[ 0 ] ;
    for ( int i = 0 ; i < size - 1 ; i ++ )
        a[ i ] = a[ i + 1 ] ;
    a[ size - 1 ] = t ;
}

int main()
{
    int n ;
    scanf("%d" , &n ) ;
    int a[ n ] ;
    for ( int i = 0; i < n ; i ++ )
        scanf("%d" , &a[ i ] ) ;

    int m ;
    scanf("%d" , &m ) ;
    while ( m -- ) be_last( a , n ) ;

    for ( int i = 0 ; i < n ; i ++ )
        printf("%d " , a[ i ] ) ;
    
    return 0;
}