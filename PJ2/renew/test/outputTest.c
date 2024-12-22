#include <stdio.h>

int main()
{
    FILE *savefp = NULL ;
    savefp = fopen( "outputTest.txt" , "r" ) ;
    if( savefp == NULL )
    {
        printf("进度保存文件打开失败！\n") ;
        return 0 ;
    }

    // 不管以哪个为基准，正数向后偏移，负数向前偏移，别弄错了
    fseek( savefp , -1L , SEEK_END );
    char judgeFlag = fgetc( savefp );
    printf("judgeFlag = %d\n" , judgeFlag ) ;
    if ( judgeFlag == ']' )
        printf("存档已开启\n");

    return 0;
}