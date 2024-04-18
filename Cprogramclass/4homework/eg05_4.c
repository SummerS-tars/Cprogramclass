#include <stdio.h>

void hanoi ( int , char , char , char ) ;
void move ( int , char , char ) ;

int main()
{
    int n ;
    printf("please enter the number of dishes : n = ") ;
    scanf("%d" , &n ) ;

    hanoi( n , 'A' , 'C' , 'B' ) ;

    return 0;
}

//第一个char为取盘处，第二个char为送盘处，第三个char为中间点
void hanoi ( int n , char A , char C , char B )
{
    if ( n == 1 ) move ( n , A , C ) ;
    else
    {
        hanoi( n - 1 , A , B , C ) ;
        move( n , A , C ) ;
        hanoi( n - 1 , B , C , A ) ;
    }

    return ;
}

void move ( int m , char from , char to )
{
    printf("%d号盘子被从%c针搬向%c针\n" , m , from , to ) ;

    return ;
}