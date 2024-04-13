#include <stdio.h>

int main()
{
    double x ;
    scanf("%lf" , &x ) ;
    double ex = 1 ;
    double d = 1 ;
    int i = 1 ;
    double y = x ;
    while ( y / d >= 1e-6 )
    {
        ex += y / d ;
        d *= ++ i ;
        y *= x ;
    }

    printf("%lf" , ex ) ;
}