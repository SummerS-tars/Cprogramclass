#include <stdio.h>
#include <string.h>

int main()
{
    char balls[ 1000 ] = { '\0' } ;
    printf("please input the loop of balls:") ;
    fgets( balls , 1000 ,stdin ) ;
    if ( balls[ strlen(balls) - 1 ] == '\n' ) balls[ strlen(balls) - 1 ] = '\0' ;//删掉末尾的换行符

    printf("%s\n" , balls) ;
    int len1 = strlen( balls ) ;
    int maxC = 0 , p = 0 ;
    for ( int i = 0 ; i < len1 ; i ++ )
    {
        int f = 1 ;
        //向右边寻找
        for ( int j = (i + 1) % len1 ; j != i ; j = ( j + 1 ) % len1 )
            if ( balls[ j ] == 'W' || balls[ j ] == balls[ i ] ) 
                f ++ ;
        
        //向左边寻找
        int finish = 0 ;
        int k = (i-1+len1)%len1 ;
        //先排除已经拿取过的情况
        for ( ; balls[ k ] == balls[ i ] || balls[ k ] == 'W' ; k -- )
            if ( k < 0 ) k = len1 - 1 ;
            else if ( k == i )
            {
                finish = 1 ;
                break ;
            }
        //如果finish=0，最后会停在第一个没拿取过的位置

        if ( finish ) continue ;//处理全都取完的情况
        
        for ( int j = (k-1+len1)%len1 ; j != k ; j -- )
        {
            if ( j < 0 ) j = len1 - 1 ;
            if ( balls[ j ] == balls[ j ] == balls[ k ] ) 
                f ++ ;
        }

        //维护最大值
        if ( maxC < f ) maxC = f , p = i ;
    }

    printf("position : %d\nmaxC : %d\n" , p , maxC ) ;

    return 0;
}