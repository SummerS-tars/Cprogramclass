#include <stdio.h>
#include <time.h>

void guess_number ()
{
    printf("有一个数字(范围1-1000)，你猜猜是多少 : ") ;
    srand( time ( NULL ) ) ;
    int number = 1 + rand() % 1000 ;
    int guess = 0 ;
    
    while ( 1 )
    {
        scanf("%d" , &guess ) ;
        if ( guess != number )
        {
            if ( guess > number ) printf("猜大了，再猜一次 : ") ;
            else printf("猜小了，再猜一次 : ") ;
            continue ;
        }
        else
        {
            printf("恭喜你猜对了，这个数字是 %d\n" , number ) ;
            break ;
        }
    }

    return ;
}

int main()
{
    guess_number() ;
    return 0 ;
}