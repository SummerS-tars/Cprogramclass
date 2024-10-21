#include <stdio.h>
#include <math.h>

double foo( double x )
{
    return 2 * pow( x , 3 ) - 3 * pow( x , 2 ) + 4 * x - 1 ;
}

double simpson( double a , double b , int n )
{
    double h = ( b - a ) / n ;
    double sum = 0 ;
    for( int i = 0 ; i < n ; i ++ )
    {
        double x0 = a + i * h ;
        double x1 = a + ( i + 1 ) * h ;
        sum += ( foo( x0 ) + 4 * foo( ( x0 + x1 ) / 2 ) + foo( x1 ) ) * h / 6 ;
    }
    return sum ;
}

int main()
{
    double r = simpson( -1 , 10 , 200 ) ;
    printf("%.2lf" , r ) ;
    return 0;
}