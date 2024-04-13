#include <stdio.h>

void get_4mul ( int* a , int size ) ;
int find_key ( int* a , int size , int key ) ;
void reverse ( int* a , int size ) ;
void init ( int* a , int size ) ;
void print ( int* a , int size ) ;

//此处a为传入的数组头部指针,此处默认数组每个元素都被传入使用
int main()
{
    int n ; 
    printf("请输入数组长度:") ;
    scanf("%d" , &n ) ;
    int a[ n ] ;

    init( a , n ) ;
    while( 1 )
    {
        printf("请输入你的操作: 1.(1) 2.(2) 3.(3) 4.打印 5.结束\n") ;
        int i = 0 ;
        scanf("%d" , &i ) ;
        if ( i == 1 ) get_4mul( a , n ) ;
        else if ( i == 2 )
        {
            printf("请输入key的值:") ;
            int key ;
            scanf("%d" , &key ) ;
            int k = find_key( a , n , key ) ;
            if ( k == -1 ) printf("没有对应的元素\n") ;
            else printf("目标元素的下标是:%d\n" , k ) ;
        }
        else if ( i == 3 ) reverse( a , n ) ;
        else if ( i == 4 ) print( a , n ) ;
        else if ( i == 5 ) break ;
        else printf("不是有效的操作\n") ;
    }

    return 0 ;
}

//数组初始化
//传入( 数组名 , 数组长度 )
void init ( int* a , int size )
{
    for ( int i = 0 ; i < size ; i ++ )
    {
        printf("请输入第%i个元素:" , i + 1 ) ;
        scanf("%d" , a + i ) ;
    }
}

//打印下标为4倍数的元素
//传入( 数组名 , 数组长度 )
void get_4mul ( int* a , int size )
{
    if ( size <= 4 )
        printf("没有符合元素") ;
    else
        for( int i = 0 ; i < size ; i ++ )
            if ( i && !( i % 4 ) ) printf("%d " , *(a + i ) ) ;
    puts("") ;
    return ;
}

//寻找值为key的元素的下标(不成立则返回-1)
//传入( 数组名 , 数组长度 , 目标值 )
int find_key ( int* a , int size , int key )
{
    for( int i = 0 ; i < size ; i ++ )
        if ( *(a + i) == key ) return i ;
    
    return -1 ;
}

//将数组元素反向存储
//传入( 数组名 , 数组长度 )
void reverse ( int* a , int size )
{
    int* b  = a + size - 1 ;
    while ( a < b )
    {
        int t = *a ;
        *a = *b ;
        *b = t ;
        a ++ , b -- ;
    }
    printf("已逆转完毕\n") ;
    return ;
}

//打印数组
//传入( 数组名 , 数组长度 )
void print ( int* a , int size )
{
    for ( int i = 0 ; i < size ; i ++ )
        printf("%d " , *( a +  i ) ) ;
    puts("") ;
    return ;
}