#include <stdio.h>

void quick_sort ( int [] , int , int ) ;

//这个方法的特点是先对a[]排序,这样就可以利用其单调性的特点将时间复杂度化为o(n)
int main()
{
    int n ; 
    scanf("%d" , &n ) ;
    
    int a[ n ] , b[ n ] ;
    for(int i = 0 ; i < n ; i ++ )
        scanf("%d" ,  &a[ i ] ) ;
    
    quick_sort ( a , 0 , n - 1 ) ;

    int tt = -1 ;
    for ( int i = 0 ; i < n ; i ++ )
    {
        b[ ++ tt ] = a[ i ] ;

        int j = i ;
        while ( j + 1 < n && a[ j + 1 ] == a[ i ] ) j ++ ;//停在最后一个和a[ i ] 相同的元素上

        i = j ;
    }

    for ( int i = 0 ; i <= tt ;  i ++ )
        printf("%d " , b[ i ] ) ;
    
    return 0 ;
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