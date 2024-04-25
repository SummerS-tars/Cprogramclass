#include <stdio.h>

struct stuScore
{
    char name[ 20 ];
    int chinese ;
    int math ;
};

float chinese_all_eve( struct stuScore* stu , int n )
{
    int sum = 0 ;
    for( int i = 0 ; i < n ; i ++ )
        sum += stu[ i ].chinese ;
    return sum / (float) n ; 
}

float math_all_eve( struct stuScore* stu , int n )
{
    int sum = 0 ;
    for( int i = 0 ; i < n ; i ++ )
        sum += stu[ i ].math ;
    return sum / (float) n ; 
}

int main()
{
    struct stuScore stu[ 3 ] = { { "zhangsan", 90, 80 }, { "lisi", 85, 90 }, { "wangwu", 88, 85 } };
    int i;
    for ( i = 0; i < 3; i++ )
        printf( "name:%s, chinese:%d, math:%d\n", stu[ i ].name, stu[ i ].chinese, stu[ i ].math );
    printf( "chinese average score:%.2f\n", chinese_all_eve( stu, 3 ) );
    printf("math average score:%.2f\n", math_all_eve( stu, 3 ) );
    return 0;
}