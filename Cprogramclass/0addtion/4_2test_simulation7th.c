#include <stdio.h>

int main()
{
    char *st[ 3 ] = {"语文" , "数学" , "英语"} ;
    char fn[ 100 ] = { 0 } ;
    float credit[ 3 ] = { 0 } ;
    int pass_num[ 3 ] = { 0 } ;

    //读取并处理文件名
    scanf("%s" , fn ) ; getchar() ;

    //打开文件
    FILE *fp ;
    if((fp = fopen( fn , "r+" )) == NULL )
    {
        printf("文件打开失败\n") ;
        return 0;
    }

    //从文件读取数据
    for( int i = 0 ; i < 3 ;  i ++ )
    {
        fscanf(fp ,"%*s\n%f\n" , credit + i) ;

        float x[ 6 ] = { 0 } ;
        fread( x , sizeof( float ) , 6 , fp ) ;
        for( int j = 0 ; j < 6 ; j ++ )
            if( *(x + i) >= 60 ) pass_num[ j ] ++ ;
        fgetc( fp ) ;
    }

    //写入文件
    fseek( fp , 0L , SEEK_END ) ;
    fprintf(fp ,"=======统计结果=======\n") ;
    fprintf(fp ,"KCM\t\tKCXF\tJGRS\n") ;
    for( int i = 0 ; i < 3 ; i ++ )
        fprintf(fp , "%s\t\t%.2f\t\t%d\n" , st[ i ] , credit[ i ] , pass_num[ i ] ) ;

    //关闭文件
    fclose( fp ) ;
    return 0;
}