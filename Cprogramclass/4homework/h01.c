#include <stdio.h>

int main()
{
    int n ;
    printf("please enter the size :") ;
    scanf("%d" , &n ) ;

    void pri_tri ( int ) ;
    pri_tri( n ) ;

    return 0;
}

void pri_tri ( int n )
{
    for ( int i = 1 ; i <= n ; i ++ )
    {
        for ( int j = 1 ; j <= i ; j ++ )
            if ( i == n ) printf("* ") ;
            else if ( j == 1 ) printf("* ") ;
            else if ( j == i ) printf("* ") ;
            else printf("  ") ;

        puts("") ;
    }
}