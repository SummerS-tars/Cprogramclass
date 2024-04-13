#include <stdio.h>

void swap ( int *x, int *y )
{
    int t = *x ;
    *x = *y , *y = t ;

    return ;
}

int main()
{
    int n ;
    scanf("%d" , &n ) ;
    int a[ n ] ;
    for ( int i = 0 ; i < n ; i ++ )
        scanf("%d" , &a[ i ] ) ;
    
    int i , j , k ;
    i = j = 0 , k = n - 1 ;
    while ( j <= k )
    {
        if ( a[ j ] < 0 )
        {
            swap ( &a[ i ] , &a[ j ] ) ;
            i ++ , j ++ ;
        }
        else if ( a[ j ] == 0 ) j ++ ;
        else
        {
            swap ( &a[ j ] , &a[ k ] ) ;
            k -- ;//此处不能j++,因为换过之后a[ k ]是未知的
        }
    }

    for ( int i = 0 ; i < n ; i ++ )
        printf("%d " , a[ i ] ) ;
    
    return 0;
}