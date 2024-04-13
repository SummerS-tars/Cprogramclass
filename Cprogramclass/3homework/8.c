#include <stdio.h>
#include <stdbool.h>

int main()
{
    int n ;
    scanf("%d" , &n ) ;
    int a[ n ] ;

    int tt = 0 ;
    a[ ++ tt ] = 2; 
    for ( int i = 3 ; tt < n ; i ++ )
    {
        bool is_prime = true ;
        for ( int j = 0 ; j <= tt ; j ++ )
            if ( i % a[ j ] == 0 )
            {
                is_prime = false ;
                break ;
            }
        
        if ( is_prime ) a[ ++ tt ] = i ;
    }

    for ( int i = 1 ; i <= tt ; i ++ )
        printf("%d " , a[ i ] ) ;
    
    return 0 ;
}