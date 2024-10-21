#include <stdio.h>
#include <math.h>

double cal_sin( double x ) ;

int main()
{
    double x ;
    scanf("%lf" , &x ) ;
    printf("%.2lf" , cal_sin( x ) ) ;
    return 0;
}

double cal_sin( double x ) 
{
    double sum = 0 ;
    double dy = x ;
    int i = 3 ;
    while( fabs(dy) > 1e-6  )
    {
        sum += dy ;
        dy = - dy * x * x / ( (i - 1) * i ) ;
        i += 2 ;
    }
    return sum ;
}