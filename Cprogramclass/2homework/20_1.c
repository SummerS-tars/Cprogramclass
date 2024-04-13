#include <stdio.h>

int main()
{
    int x; 
    scanf("%d" , &x ) ;

    int b = 1 , a = x ;
    while ( a >= 10 )
    {
        b *= 10 ;
        a /= 10 ;
    }
    a = x ;

    int y = 0 , c = 1;
    while ( b )
    {
        y += a / b * c ;
        c *= 10 ;
        a %= b ;
        b /= 10 ;
    }

    if ( x == y )
        puts("Yes") ;
    else
        puts("No") ;

    return 0 ;
}
//不用数组的解法