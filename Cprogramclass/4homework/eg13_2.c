#include <stdio.h>

#define PI 3.141592653
#define AREA(r) (PI*(r)*(r))
#define PERIMETER(r) (2*PI*(r))

int main()
{
    int r ;
    for ( r = 2 ; r <= 10 ; r += 2 )
        printf("r = %d\nAREA = %f\nPERIMETER = %f\n" , r , AREA(r) , PERIMETER(r) ) ;

    return 0 ;
}
/*
r = 2
AREA = 12.566371
PERIMETER = 12.566371
r = 4
AREA = 50.265482
PERIMETER = 25.132741
r = 6
AREA = 113.097336
PERIMETER = 37.699112
r = 8
AREA = 201.061930
PERIMETER = 50.265482
r = 10
AREA = 314.159265
PERIMETER = 62.831853
*/