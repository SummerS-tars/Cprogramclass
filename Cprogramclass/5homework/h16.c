#include <stdio.h>

int main()
{
    int a , b , c , d , e , f , g ;
    int *ip[] = { &a , &b , &c , &d , &e , &f , &g } ;
    
    void input ( int *ip[] , int n ) ;
    void output ( int *ip[] , int n ) ;
    void sort ( int *ip[] , int n ) ;

    int n ;
    printf("please enter the number of elements(1~7) : ") ;
    scanf("%d" , &n ) ;
    input( ip , n ) ;
    output( ip , n ) ;
    
    sort( ip , n ) ;
    output( ip , n ) ;

    return 0 ;
}

void input ( int *ip[] , int n )
{
    printf("please enter %d element(s) : " , n ) ;
    for( int i = 0 ; i < n ; i ++ )
        scanf("%d" , ip[ i ] ) ;
}

void output ( int *ip[] , int n )
{
    for( int i = 0 ; i < n ; i ++ )
        printf("%d " , *ip[ i ] ) ;
    puts("") ;
}

void sort ( int *ip[] , int n )
{
    for( int i = 1 ; i <= n ; i ++ )
        for( int j = 0 ; j + i < n ; j ++ )
            if( *ip[ j ] > *ip[ j + 1 ] )
            {
                int *temp = ip[ j ] ;
                ip[ j ] = ip[ j + 1 ] ;
                ip[ j + 1 ] = temp ;
            }
    printf("the array is sorted\n") ;
}