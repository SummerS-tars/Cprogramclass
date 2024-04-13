#include <stdio.h>

int main()
{
    double x , y ;
    scanf("%lf%lf" , &x , &y ) ;

    while ( x >= y )
        x -= y ;
    printf("x=%lf\n" , x ) ;

    return 0;
}