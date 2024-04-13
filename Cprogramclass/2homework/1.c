#include <stdio.h>

int main()
{
    long long n ;
    scanf("%ld" , &n ) ;
    int nums[ 10 ] = { 0 } ;
    for ( long long i = n ; i ; i /= 10 )
    {
        int res = i % 10 ;
        nums[ res ] ++ ;
    }

    for ( int i = 0 ; i < 10 ; i ++ )
        printf("the times of %d : %d\n" , i , nums[ i ] ) ;
    
    return 0 ;
}