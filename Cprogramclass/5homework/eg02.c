#include <stdio.h>


int main()
{
    //一些指向数组元素的指针变量的基本操作  
    int a[ 100 ] , b[ 100 ] , *p , *q ;
    for ( p = a ; p < a + 100 ; )    //利用指针遍历接收输入的数组元素  
        scanf("%d" , p ++ ) ;

    for ( p = a ; p <= &a[ 99 ] ; p ++ )    //利用指针遍历输出数组元素
        printf("*p = %d\t" , *p ) ;
    puts("") ;

    for ( p = a , q = b ; p < a + 100 ; )   //利用指针将a数组复制给b数组
        *q ++ = *p ++ ;

    for ( q = b ; q <= &b[ 99 ] ; q ++ )
        printf("*q = %d\t" , *q ) ;
    puts("") ;
    
    return 0;
}