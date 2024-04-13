#include <stdio.h>

//方法二：2n

//将数组指定区间倒序
//区间[ l , r )
void reverse ( int a[] , int l , int r )
{
    r -- ;
    while ( l < r )
    {
        int t = a[ l ] ;
        a[ l ] = a[ r ] , a[ r ] = t ;
        l ++ , r -- ;
    }

    return ;
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

    reverse ( a , 0 , n ) ;
    reverse ( a , 0 , n - m ) ;
    reverse ( a , n - m , n ) ;

    for ( int i = 0 ; i < n ; i ++ )
        printf("%d " , a[ i ] ) ;
    
    return 0;
}