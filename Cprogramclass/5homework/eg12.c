#include <stdio.h>

void pop_sort( int *a[] , int n )
{
    for( int i = 1 ; i <= n ; i ++ )
        for( int j = 0 ; j + i < n ; j ++ )
            if( *a[ j ] > *a[ j + 1 ] )
            {
                int *t = a[ j ] ;
                a[ j ] = a[ j + 1 ] , a[ j + 1 ] = t ;
            }
}

int main()
{
    int a , b , c , d , e , f ;
    int *ap[] = { &a , &b , &c , &d , &e , &f} ;
    printf("please input 6 numbers : ") ;
    for( int i = 0 ; i < 6 ; i ++ )
        scanf("%d" , ap[ i ] ) ;
    
    pop_sort( ap , 6 ) ;

    for( int i = 0 ; i < 6 ; i ++ )
        printf("%d " , *ap[ i ] ) ;
    puts("") ;
    
    return 0;
}