#include <time.h>
#include <stdio.h>

int main()
{
    time_t t = time(NULL);
    char timeStr[64];
    strftime( timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", localtime(&t) );
    
    FILE *savefp = NULL ;
    savefp = fopen( "outputTest.txt" , "w" ) ;
    if( savefp == NULL )
    {
        printf("进度保存文件打开失败！\n") ;
        return 0 ;
    }
    fprintf( savefp , "%s\n" , timeStr ) ;              // 写入保存时间
    fclose( savefp ) ;
    return 0;
}