#include <stdio.h>

int main()
{
    int n ;
    scanf("%d" , &n ) ;
    
    int a[ n ] ;
    for ( int i = 0 ; i < n ; i ++ )
        scanf("%d" , &a[ i ] ) ;

    int len = 1 ;
    for ( int i = 0 ; i < n ; i ++ )
    {
        int j = i , cnt = 1 ; 
        while ( j + 1 < n && a[ j + 1 ] == a[ i ] )
            j ++ , cnt ++ ;
        if ( len < cnt ) len = cnt ;

        i = j ;
    }

    printf("len = %d\n" , len ) ;

    return 0;
}