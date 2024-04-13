#include <stdio.h>
#include <math.h>

int main()
{
    double a , b , c ;
    scanf("%lf%lf%lf" , &a , &b , &c ) ;

    if ( a + b <= c || a + c <= b || b + c <= a )
        printf("-1\n") ;
    else
    {
        double p = ( a + b + c ) / 2 ;
        double s = sqrt( p * (p - a) * (p - b) * (p - c) ) ;
        printf("S = %.2lf\n" , s ) ;
    }

    return 0 ;
}