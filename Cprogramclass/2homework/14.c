#include <stdio.h>

int main()
{
    float e = 1 ;
    float d = 1 ;
    int i = 1 ;
    while ( 1 / d >= 1e-6 )
    {
        e += 1 / d ;
        d *= ++ i ;
    }

    printf("%f" , e ) ;

    return 0 ;
}
//若要更精确的话,可以使用double或者long double