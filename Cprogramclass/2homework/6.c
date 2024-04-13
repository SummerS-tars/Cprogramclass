#include <stdio.h>

int main()
{
    int n ;
    scanf("%d" , &n ) ;

    int mul = 1 ;
    int k = n ;
    while ( k )
    {
        k /= 10 ;
        mul *= 10 ;
    }

    while ( mul > 1 )
    {
        mul /= 10 ;
        printf("%d " , n / mul ) ;
        n %= mul ;
    }

    return 0 ;
}