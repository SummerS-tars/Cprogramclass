#include <stdio.h>

int main()
{
    float (*fp)( float , float ) ;
    float average( float , float ) ;
    fp = average ;

    float a , b ;
    printf("please input two numbers : " ) ;
    scanf("%f%f" , &a , &b ) ;
    printf("average = %f\n" , (*fp)( a , b ) ) ;

    return 0;
}

float average ( float a , float b )
{
    return ( a + b ) / 2 ;
}