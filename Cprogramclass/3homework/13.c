#include <stdio.h>

int a[ 10 ][ 10 ] ;

void rot ( int size )
{
    //注：此处向右位x，向下为y
    int dx[] = { 1 , 0 , -1 , 0 } ;
    int dy[] = { 0 , 1 , 0 , -1 } ;
    for ( int i = 0 ; i < size / 2 ; i ++ )
    {
        //定义初始坐标
        int x1 = i , y1 = i ;
        int x2 = size - 1 - i , y2 = i ;
        int x3 = size - 1 - i , y3 = size - 1 - i ;
        int x4 = i , y4 = size - 1 - i ;

        int times = size - i * 2 - 1 ;
        while ( times -- )
        {
            int t = a[ x1 ][ y1 ] ;
            a[ x1 ][ y1 ] = a[ x2 ][ y2 ] , a[ x2 ][ y2 ] = a[ x3 ][ y3 ] , a[ x3 ][ y3 ] = a[ x4 ][ y4 ] , a[ x4 ][ y4 ] = t ;
            x1 += dx[0] , y2 += dy[1] , x3 += dx[2] , y4 += dy[3] ;
        }
    }
}

int main()
{
    int n ;
    scanf("%d" , &n ) ;
    for ( int i = 0 ; i < n ; i ++ )
        for ( int j = 0 ; j < n ; j ++ )
            scanf("%d" , &a[ i ][ j ]) ;
    
    rot ( n ) ;

    for ( int i = 0 ; i < n ; i ++ )
    {
        for ( int j = 0 ; j < n ; j ++ )
            printf("%3d " , a[ i ][ j ] ) ;
        
        puts("") ;
    }

    return 0;
}
/*
5
1 2 3 4 5
6 7 8 9 10
11 12 13 14 15
16 17 18 19 20 
21 22 23 24 25

5
1 1 1 1 2
4 5 5 6 2
4 8 9 6 2
4 8 7 7 2
4 3 3 3 3
*/