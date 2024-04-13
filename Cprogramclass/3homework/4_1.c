#include <stdio.h>
#include <stdbool.h>

//简单的对比方法,这个方法的特点是保序
int main()
{
    printf("请输入a数组的长度:") ;
    int n ;
    scanf("%d" , &n ) ;

    int a[ n ] , b[ n ] ;
    printf("请输入a数组的n个元素:") ;
    for ( int i = 0 ; i < n ; i ++ )
        scanf("%d", &a[ i ] ) ;

    //cpy操作
    int tt = -1 ;
    for ( int i = 0 ; i < n ; i ++ )
    {
        bool unq = true ;
        for ( int j = 0 ; j < i ; j ++ )
            if ( a[ i ] == a[ j ] )
            {
                unq = false ;
                break ;
            }

        if ( unq ) b[ ++ tt ] = a[ i ] ;
    }

    //输出检验
    printf("b数组的元素:") ;
    for ( int i = 0 ; i <= tt ; i ++ )
        printf("%d " , b[ i ] ) ;
    
    return 0;
}