#include <stdio.h>
#include <stdbool.h>

void quick_sort ( int [] , int l , int r ) ;

void swap ( int *x, int *y )
{
    int t = *x ;
    *x = *y , *y = t ;

    return ;
}

int main()
{
    printf("请输入数组的大小: n = ") ;
    int n ;
    scanf("%d" , &n ) ;

    printf("请输入数组元素:") ;
    int a[ n ] ;
    for( int i = 0 ; i < n ; i ++ )
        scanf("%d" , &a[ i ] ) ;
    
    printf("原      数      组  : ") ;
    for ( int i = 0 ; i < n ; i ++ )
        printf("%d " , a[ i ] ) ;
    //思路:
    //要更大中的最小,肯定是从最小位的数开始判断
    //若这个数之后的数都比这个数小,那么对这一位没有办法互换
    //之后找到比这一位大的数中的最小的数,进行互换
    //其余的数从小到大排列即是答案
    bool cpy = false ;
    for ( int i = n - 1 ; i >= 0 ; i -- )
    {
        int j = i ;
        while ( ++ j < n )//寻找有无解
            if ( a[ i ] < a[ j ] )
            {
                cpy = true ;
                break ;
            }
        
        if ( cpy )//此情况有解
        {
            int ans = 10 , p = -1 ;
            int j = i ; 
            while ( ++ j < n ) 
                if ( a[ j ] > a[ i ] && a[ j ] < ans ) ans = a[ j ] , p = j ;
            
            swap ( &a[ i ] , &a[ p ] ) ;
            quick_sort ( a , i + 1 , n - 1 ) ;
            break ;
        }
    }

    printf("\n符合的解(-1表示无解): ") ;
    if ( cpy )
        for ( int i = 0 ; i < n ; i ++ )
            printf("%d " , a[ i ] ) ;    
    else printf("-1\n") ;

    return 0;
}

void quick_sort ( int q[] , int l , int r )
{
    if ( l >= r ) return ;

    int x = q[ l + r >> 1] , i = l - 1 , j = r +  1;
    while ( i < j )
    {
        do i ++ ;while( q[ i] < x ) ;
        do j -- ;while ( q[ j ] > x ) ;
        if ( i < j )
        {
            int t = q[ i ] ; q[ i ] = q[ j ] , q[ j ] = t ;
        }
    }

    quick_sort ( q , l , j ) ;
    quick_sort ( q , j + 1 , r ) ;

    return ;
}