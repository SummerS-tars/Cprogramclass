#include <stdio.h>

int main()
{
    int year ;
    printf("please enter the year : ") ;
    scanf("%d" , &year ) ;

    printf("%d年\n" , year ) ;
    int a1[] = { 1 , 3 , 5 , 7 , 8 , 10 , 12 } , a2[] = { 4 , 6 , 9 , 11 } ;
    for ( int i = 1 ; i <= 12 ; i ++ )//月份
    {
        printf("第%d月\n" , i ) ;
        printf("Sun Mon Tus Wen Thu Fri Sat\n") ;

        int days = 30 ;
        for ( int j = 0 ; j < 7 ; j ++ )//判断每月的天数
        {
            if ( i == 2 )
            {
                if ( year % 4 == 0 )
                {
                    if ( year % 100 == 0 )
                    {
                        if ( year % 400 == 0 ) days = 29 ;
                        else days = 28 ;
                    }
                    else days = 29 ;
                }
                break ;
            }
            else if ( i == a1[ j ] )
            {
                days = 31;
                break ;
            }
        }
        
        int f , g ;
        if ( i < 3 ) f = year - 1;
        else f =year ;

        if ( i < 3 ) g = i + 13 ;
        else g = i + 1 ;

        int k = 1 ;       
        int N = 1461 * f / 4 + 153 * g / 5 + k ;
        int d = ( N - 621049 ) % 7 ;
            
        for ( int l = 0 ; l < d ; l ++ )
            printf("    ") ;
    
        for ( int l = 1 ; l <= days ; l ++ )
        {
            printf("%3d " , l ) ;
            d ++ ;
            if ( d == 7 )
            {
                puts("") ;
                d = 0 ;
            }
        }
        puts("") ;
    }

    return 0;
}