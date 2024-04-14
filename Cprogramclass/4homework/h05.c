#include <stdio.h>
#include <time.h>

int time_sec ( int h , int min , int s ) ;

int main()
{
    printf("请输入第一个时间(时 分 秒) : ") ;
    int h1 , min1 , s1 ;
    scanf("%d%d%d" , &h1 , &min1 , &s1 ) ;
    printf("请输入第二个时间(时 分 秒) : ") ;
    int h2 , min2 , s2 ;
    scanf("%d%d%d" , &h2 , &min2 ,&s2  ) ;

    int t1 = time_sec ( h1 , min1 , s1 ) ;
    int t2 = time_sec ( h2 , min2, s2 ) ;
    int t= t1 - t2 ;
    if ( t < 0 ) t = -t ;
    printf("两时间点相差 %d 秒\n" , t ) ;

    return 0;
}

int time_sec ( int h , int min , int s )
{
    return h * 3600 + min * 60 + s ;
}