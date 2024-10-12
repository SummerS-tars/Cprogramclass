#include <stdio.h>
#include <math.h>

int main()
{
    double x;
    double result = 0;
    printf("Please enter a number:");
    scanf("%lf", &x);

    // TODO 使用库函数实现Sigmoid函数的计算 
    result = 1.0 / ( 1.0 + exp( -x )) ;

    printf("sigmoid(%lf) = %lf\n", x, result);
    return 0;
}