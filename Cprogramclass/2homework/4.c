#include <stdio.h>

int main()
{
    for ( int i = 100 ; i <= 999 ; i ++ )
    {
        int sum = 0 ;
        int nums = i ;
        while ( nums )
        {
            int num = nums % 10 ;
            sum += num * num * num ;
            nums /= 10 ; 
        }

        if ( sum == i ) printf("%d\n" , i ) ;
    }

    return 0 ;
}
/*answer:
 153
 370
 371
 407*/