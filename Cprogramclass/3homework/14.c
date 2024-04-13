#include <stdio.h>



//生成样例1
void foo1 ( int size ) ;

//生成样例2
void foo2 ( int size ) ;

int main()
{
    printf("请输入想要得到的矩阵(1/2):") ;
    int op ;
    scanf("%d" , &op ) ;

    printf("请输入矩阵的大小(不大于9):") ;
    int n ;
    scanf("%d" , &n ) ;

    if ( op == 1 ) foo1( n ) ;
    else if ( op == 2 ) foo2( n ) ;
    else printf("操作有误！\n") ;
}

void foo1 ( int size )
{
    int a[ 10 ][ 10 ] = { 0 } ;
    
    //注:向下为x,向右为y
    int dx[] = { 1 , -1 } ;
    int dy[] = { -1 , 1 } ;
    int x = 0 , y = 0 , idx = 1 ;
    for ( int i = 0 ; ; i = (i + 1) % 2 )//i表示操作序号,0为向左下,1为向右上
    {
        if ( x == size -1 && y == size - 1 )
        {
            a[ x ][ y ] = idx ;
            break ;
        }

        while( x >= 0 && y >= 0 && x < size && y < size )
        {
            a[ x ][ y ] = idx ++ ;
            x += dx[ i ] , y += dy[ i ] ;
        }

        if ( i == 0 )
        {
            if ( y < 0 && x < size ) y = 0 ;
            else if ( x >= size ) x += dx[ 1] , y += dy[ 1 ] , y ++ ;
        }
        else
        {
            if ( x < 0 && y < size ) x = 0;
            else if ( y >= size ) x += dx[ 0 ] , y += dy[ 0 ] , x ++ ;
        }
    }

    for ( int i = 0 ; i < size ; i ++ )
    {
        for ( int j = 0 ; j < size ; j ++ )
            printf("%3d " , a[ i ][ j ] ) ;
        puts("") ;
    }

    return ;
}

void foo2 ( int size )
{
    int a[ 10 ][ 10 ] = { 0 } ;

    //四种操作,0向右,1向下,2向左,3向上
    int dx[] = {0 ,1 ,0 ,-1 } ;
    int dy[] = {1 ,0 ,-1 ,0 } ;

    int x = 0 , y = 0 , idx = 1 ;
    int i = 0 ;
    while ( idx <= size*size)
    {
        a[ x ][ y ] = idx ++ ;
        if ( x + dx[ i ] >= 0 && x + dx[ i ] < size && y + dy[ i ] >= 0 && y + dy[ i ] < size && ! a[ x + dx[ i ] ][ y + dy[ i ] ] ) ;
        else i = ( i + 1 ) % 4 ;

        x += dx[ i ] , y += dy[ i ] ;
    }

    for ( int i = 0 ; i < size ; i ++ )
    {
        for ( int j = 0 ; j < size ; j ++ )
            printf("%3d " , a[ i ][ j ] ) ;
        puts("") ;
    }

    return ;
}