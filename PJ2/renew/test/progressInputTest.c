#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *savefp = NULL;
    savefp = fopen("map2.save", "r");
    if( savefp == NULL )
    {
        printf("进度保存文件打开失败！\n") ;
        return 0 ;
    }

    int turn = 0 ;
    scanf("%d" , &turn ) ;

    if( !turn )
    {
        char timeStr1[64] = {0} ;
        char timeStr2[64] = {0} ;
        fscanf( savefp , "%s %s\n" , timeStr1 , timeStr2 ) ;              // 写入保存时间
        int treasureInfoPlayer , treasureInfoMap ;
        fscanf( savefp , "%d %d\n" , &treasureInfoPlayer , &treasureInfoMap ) ; // 读取宝藏信息
        system("cls");
        printf("上次游玩时间：%s %s\n" , timeStr1 , timeStr2 ) ;
        printf("上次游玩宝藏：%d/%d\n\n" , treasureInfoPlayer , treasureInfoMap ) ;
    }
    else if( turn == 1)
    {
        while( fgetc( savefp ) != '*' ) ;   // 跳跃至操作信息
        char saveMovement[1000] = {0} ;
        fscanf( savefp , "%s" , saveMovement ) ; // 读取操作信息
        system("cls");
        printf("Movement Record : %s\n" , saveMovement ) ;
    }
    else if( turn == 2)
    {
        fseek( savefp , -1L , SEEK_END) ;
        char judgeFlag = fgetc( savefp );
        if( judgeFlag == ']' )
            printf("存档已开启\n");
    }
    fclose( savefp ) ;

    return 0;
}