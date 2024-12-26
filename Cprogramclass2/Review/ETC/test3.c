#include<stdio.h>
#include <string.h>
int main(void)
{
    /*********Begin*********/
    char str[ 110 ] = { 0 } ;
    while( 1 )
    {
        if (fgets(str, 110, stdin) == NULL) break;
        int len = strlen(str);
        if (len > 0 && str[len - 1] == '\n') str[len - 1] = 0;    //清理换行符
        if( !strcmp( str , "stop" ) ) break ;

        int i = 0 ;
        int pmax = 0 , max = 0 , cnt_word = 0 , cnt_str = 0 ;
        // pmax 记录最大位置 , max 记录最长长度 , cnt_word 记录当前词长 , cnt_str 记录字符串总有效字符数
        while( str[ i ] )
        {
            if ((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= '0' && str[i] <= '9')) //表明是一个词的一部分
            {
                cnt_word++;
                cnt_str++;
            }
            else if (cnt_word > 0) //表明已经遍历完一个词了
            {
                if (cnt_word > max) max = cnt_word, pmax = i - max;
                cnt_word = 0;      //重置词内计数变量状态
            }
            i++;
        }
        if( cnt_word > max ) max = cnt_word , pmax = i - max ;          //针对整个字符串只有一个词或是最长的词在最后的情况进行比较

        //经过遍历，找到此行输入的最长为词的开头，与其长度
        printf("%d " , cnt_str ) ;
        for( int i = pmax ; i < pmax + max ; i ++ )
            printf("%c" , str[ i ] ) ;
        puts("") ;
    }

    /*********End**********/
    return 0;
}