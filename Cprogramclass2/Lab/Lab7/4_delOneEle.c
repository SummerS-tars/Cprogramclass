#include <stdio.h>

int main()
{
    int n , a[ 100 ] ;
    printf("Enter the number of elements: ") ;
    scanf("%d" , &n ) ;
    for( int i = 0 ; i < n ; i ++ )
        scanf("%d" , a + i ) ;
    
    int k ;
    printf("Enter the order of element to be deleted: ") ;
    scanf("%d" , &k ) ;

    for( int i = 0 ; i < n ; i ++ )
    {
        if( i == k  ) continue ;
        printf("%d " , a[ i ] ) ;
    }

    return 0;
}