#include <stdio.h>

int squreByValue ( int n )
{
    return n * n ;
}

void squreByPoint ( int *nPtr )
{
    *nPtr = (*nPtr) * (*nPtr) ;
}

int main()
{
    int m = 5 , *p = &m ;
    printf("1. m = %d\n" , m ) ;
    printf("squreByValue( m ) = %d\n2. m = %d\n" , squreByValue( m ) , m ) ;
    printf("after squreByPoint\n") ;
    squreByPoint( p ) ;//此处直接&m也可以，总之不要写成m
    printf("3. m = %d\n" , m ) ;

    return 0;
}