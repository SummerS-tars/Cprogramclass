#include <stdio.h>

int main()
{
    int k = 3 ;
    int triangle1 , triangle2 ;
    triangle1 = k * k ++ / 2 ;

    int m = 3 ;
    triangle2 = m * (m ++) / 2 ;

    return 0;
}