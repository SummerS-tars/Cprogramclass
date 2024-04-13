#include <stdio.h>
int main()
{
    double a, b ; 
    double min ( double , double ) ;//函数声明
    printf("Input a,b :") ;
    scanf("%lf%lf" , &a , &b ) ;
    printf("MIN(%f,%f) = %f\n" , a , b , min(a, b) ) ;
    return 0 ;
}
double min ( double x ,double y )
{
    return x < y ? x : y ;
}