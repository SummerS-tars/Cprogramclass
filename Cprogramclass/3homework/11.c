#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int main()
{
    int rest[ 100 ] = { 0 } ;//存储每一位算术留下的余数
    char str[ 100 ] ;


    for ( int i = 2 ; i <= 50 ; i ++ )
    {
        memset( str , 0 , sizeof( str )) ;
        printf("1/%d=0.", i ) ;
        
        int d = 1 ;

        int tt = -1 ;
        for ( int j = 0 ; j < 100 ; j ++ )//模拟竖式运算,这个很有用！
        {
            d *= 10 ;
            rest[ j ] = d % i ;
            str[ j ] = d / i + '0';

            bool loop = false ;
            for ( int k = 0 ; k < j ; k ++ )
                if ( rest[ j ] == rest[ k ] )
                {
                    loop = true ;
                    tt = j ;
                    break ;
                }
            if ( loop ) break ;
            d %= i ;
        }
        
        if ( tt > 0 & str[ tt ] == str[ tt - 1 ] ) str[ tt ] = '\0' ;
        printf("%s\n" , str) ;
    }

    return 0;
}