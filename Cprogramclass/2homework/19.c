#include <stdio.h>

int main()
{
    float x ;
    scanf("%f" , &x ) ;

    int n ;
    for ( n = 1 ; n * n <= x ; n ++ ) ;
    n -- ;

    printf("n = %d\n" , n ) ;

    return 0 ;
}