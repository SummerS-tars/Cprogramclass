#include <stdio.h>

void pop_sort ( int *a[] , int size )
{
    for( int i = 1 ; i <= size ; i ++ )
        for( int j = 0 ; j + i < size ; j ++ )
            if( *a[ j ] > *a[ j + 1 ] )
            {
                int t = *a[ j ] ;
                *a[ j ] = *a[ j + 1 ] , *a[ j + 1 ] = t ;
            }
}

int main()
{
    int a , b , c , d , e , f ;
    printf("please enter 6 numbers : ") ;
    int *ap[] = { &a , &b , &c , &d , &e , &f } ;
    int n = sizeof( ap ) / sizeof( ap[ 0 ]) ;
    
    for( int i = 0 ; i < n ; i ++ )
        scanf("%d" , ap[ i ] ) ;
    
    pop_sort( ap , n ) ;

    for( int i = 0 ; i < n ; i ++ )
        printf("%d " , *ap[ i ] ) ;
    puts("") ;
    
    return 0;
}