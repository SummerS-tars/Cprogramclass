/*本程序输出字符文本并计算空格个数*/
/*请在此处添加代码，输出文本并统计空格数*/
#include <stdio.h>
#include <string.h>

#define MAXCHAR 1000
int main(){
    /********** Begin **********/
    char str[ MAXCHAR ] = { 0 } ;
    fgets( str , MAXCHAR , stdin ) ;

    int len = strlen( str ) ;
    int cnt = 0;
    for( int i = 0 ; i < len ; i ++ )
    {
        printf("%c" , str[ i ] ) ;
        if( str[ i ] == ' ' ) cnt ++ ;
    }

    printf("%d" , cnt ) ;
    /********** End **********/
    return 0;
}