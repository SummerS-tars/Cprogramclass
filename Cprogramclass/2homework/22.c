#include <stdio.h>

int main()
{
    int i = 0 ;
    for ( i = 1 ; ; i ++ )
    {
        int a = i ;
        int j = 0 ; 
        while ( a > 0 )
        {
            j ++ ;
            int d = a / 2 + 1 ;
            a -= d ;
        }

        if ( j == 5 && a == 0 )
        {
            printf("all = %d\n" , i ) ;

            for ( int k = 1 ; i ; k ++ )
            {
                int d = i / 2 + 1 ;
                i -= d ;
                printf("day %d = %d\n" , k , d ) ;
            }

            break ;
        }
    }

    return 0 ;
}
//此处一半不太好理解,能不能吃半个?
//因此同意按照计算机的思考方式来写了
/*
all = 31
day 1 = 16
day 2 = 8
day 3 = 4
day 4 = 2
day 5 = 1
*/