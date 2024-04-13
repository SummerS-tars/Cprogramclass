#include <stdio.h>

int main()
{
    float x = 23.1234 , y ;
    y = (int)( x*1e3 + 0.5 ) ;
    y /= 1e3 ;
    printf("%f" , y ) ;

    return 0;
}