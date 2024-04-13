#include <stdio.h>
#include <stdbool.h>

int main()
{
    int n ;
    scanf("%d" , &n ) ;

    int a = n ;
    printf("%d=" , n ) ;
    for ( int i = 2 ; n > 1 ; i ++ )//注意最后n被分解完之后还剩下1
    {
        bool is_prime = true ;
        for ( int j = 2 ; j * j <= i ; j ++ )//寻找质数
            if ( i % j == 0 ) 
            {
                is_prime = false ;
                break ;
            }
        
        if ( is_prime )
        {
            while ( n % i == 0 )//试除法,并输出质因数直到不再整除
            {
                n /= i ;
                if ( n > 1 )
                    printf("%d*" , i ) ;
                else
                {
                    printf("%d\n" , i ) ;
                    break ;
                }
            }
        }
    }

    return 0 ;
}