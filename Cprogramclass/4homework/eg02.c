#include <stdio.h>

int gcd ( int a , int b )
{
    if( a < b )
    {
        int t = a ;
        a = b , b =t ;
    }

    int r ;
    while ( r = a % b )
        a = b , b = r ;

    return b ;
}

int main()
{
    printf("intput two numbers:") ;
    int a , b ;
    scanf("%d%d" , &a , &b ) ;

    int res = gcd( a , b ) ;
    printf("the gcd of the two: %d\n" , res ) ;

    return 0;
}