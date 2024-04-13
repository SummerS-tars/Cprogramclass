#include <stdio.h>

//暴力求解法
int main()
{
    for ( int x = 0 ; x * 5 <= 100 ; x ++ )
    {
        for ( int y = 0 ; y * 3 <= 100 ; y ++ )
        {
            for ( int z = 0 ; ; z += 3 )
            {
                int nums = x + y + z ;
                int sum = 5 * x + 3 * y + z / 3 ;
                if ( sum > 100 ) break ;
                else if ( sum == 100 )
                {
                    if ( nums > 100 ) break ;
                    else if ( nums == 100 ) printf("x = %d , y = %d , z = %d\n" , x, y , z ) ;
                }
            }
        }
    }

    return 0 ;
}