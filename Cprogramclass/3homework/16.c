#include <stdio.h>
#include <string.h>

int main()
{
    char str[ 1000 ] = { '\0' } ;
    char res[ 1000 ] = { '\0' } ;
    int tt = -1 , hh = -1 ;

    printf("请输入字符串(以换行符结束输入):\n") ;
    fgets( str ,1000 , stdin ) ;
    int len = strlen( str ) ;

    //跳过前导空格,停在第一个非空白字符上
    while( ++ tt < len && str[ tt ] == ' ' ) ; 

    //分单词读入
    for ( ; tt < len ; tt ++ )
    {
        if ( str[ tt ] != ' ' ) res[ ++ hh ] = str[ tt ] ;
        else
        {
            res[ ++ hh ] = ' ' ;
            while ( ++ tt < len && str[ tt ] == ' ' ) ;
            tt -- ;//抵消for循环体内加的部分
        }
    }

    //处理最后的换行符以及可能会多出的空格
    while ( res[ hh ] == ' ' || res[ hh ] == '\n' )
        res[ hh -- ] = '\0' ;

    printf("%s\n" , res ) ;

    return 0;
}