#include <stdio.h>

int main()
{
    printf("1000以内的完全数有 : ") ;

    for( int i = 2 ; i <= 1000 ; i ++ )
    {
        int sum = 1 ;

        for ( int j = 2 ; j * j <= i ; j ++ )
            if ( i % j == 0 )//可以整除
                if ( j == i / j )//判断除数和商是否相同
                    sum += j ;
                else sum += j + i / j ;

        if ( i == sum ) printf("%d " , i ) ;     
    }
    puts("") ;

    return 0;
}