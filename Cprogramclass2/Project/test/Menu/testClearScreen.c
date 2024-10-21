#include <stdio.h>
#include <windows.h>

int main() {
    // 前置输出
    printf("即将于3秒后开始清屏测试\n") ;
    for( int i = 1 ; i <= 3 ; i ++ )
    {
        printf("%d\n" , i ) ;
        Sleep( 1000 ) ;                        // 休眠1秒，Sleep函数在windows.h头文件中
    }

    // 清除控制台屏幕
    printf("\033[H\033[J");
    // printf("\033[2J") ;
    // 上述备注语句，会清屏，但在之后直接输出而不是回到屏幕左上角
    // 使用\033[H\033[J可以清屏并回到屏幕左上角

    // 输出一些文本
    printf("屏幕已清除！\n");

    return 0;
}