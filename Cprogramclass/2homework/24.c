#include <stdio.h>
#include <math.h>
#include <stdbool.h>

double function ( double x )
{
    return x * x * x - x * x - 1 ;
}

int main()
{
    double l = 0 , r = 3 ;
    while ( fabs( l - r ) > 1e-6 )//注意此处已经指明了解的唯一性
    {
        double mid = ( l + r ) / 2 ;
        //判断正负性,注意此处针对题目忽略了function()刚好等于零的情况,不太可能刚好出现零,实际上也可加一句讨论一下
        if ( function( mid ) > 0 == function( l ) > 0 )//判断与区间左边界的正负性的符号的一致性
            l = mid ;
        else
            r = mid ;
    }

    printf("x = %.6lf\n" , l ) ;

    return 0 ;
}