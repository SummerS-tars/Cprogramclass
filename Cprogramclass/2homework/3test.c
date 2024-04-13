#include <stdio.h>

int main()
{
    int x = 5 , y = 110 ;
    while ( x <= y ) x *= 2;
    printf("%d %d" , x , y ) ;

    x= 5 ;
    do
    {
        x = y / x ;
        y = y - x ;
    }
    while ( y >=1 ) ;
    printf("\n%d %d" , x, y ) ;
    
    return 0 ;
}