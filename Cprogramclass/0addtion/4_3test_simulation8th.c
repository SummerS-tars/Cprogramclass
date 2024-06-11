#include <stdio.h>

void RightMove( int *a, int n , int k )
{
    int copy[ n ] ;
    for( int i = 0 ; i < n ; i ++ )
        copy[ (i + k % n) % n ] = a[ i ] ;
    for( int i = 0 ; i < n ; i ++ )
        a[ i ] = copy[ i ] ;

    return ;
}

int main()
{
    int n ;
    printf("please enter the element number of the array : ") ;
    scanf("%d" , &n ) ;
    int a[ n ] ;
    printf("please enter the elements of the array : ") ;
    for( int i = 0 ; i < n ; i ++ )
    {
        printf("%d : " , i ) ;
        scanf("%d" , a + i ) ;
    }

    printf("please enter the number of the right move : ") ;
    for( int i = 0 ; i < n ; i ++ )
        printf("%d " , a[ i ] ) ;
    puts("") ;
}