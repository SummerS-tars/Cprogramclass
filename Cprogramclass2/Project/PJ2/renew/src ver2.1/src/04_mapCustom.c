#include "04_mapCustom.h"
#include "02_cursorOperation.h"
#include "03_mapAndPlayerStatus.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>

void mapCustomIni( int customMapNum , int priInfo )    // 初始化随机迷宫
{
    FILE *mapfp = NULL ;
    mapfp = fopen( mapName[ customMapNum + 2 ] , "w" ) ;
    if( mapfp != NULL )
    {
        fputc('*', mapfp);
        fclose(mapfp);
    }
    else
    {
        perror("Error opening file");
        system("pause");
        return ;
    }

    if( priInfo )
    {
    system("cls") ;
    printf("初始化成功！\n");
    system("pause");
    }

    progressSaveInit( customMapNum + 3 ) ; // 同时初始化游戏存档
    return ;
}

void mapCustomEdit( int customMapNum )   // 编辑随机迷宫
{
    system("cls");
    struct mapInfo mapInfo;
    mapIni( &mapInfo );
    printf("请输入迷宫的行数：\n");
    scanf("%d", &mapInfo.mapRow);
    printf("请输入迷宫的列数：\n");
    scanf("%d", &mapInfo.mapCol);
    printf("请输入迷宫的宝藏数量：\n");
    scanf("%d", &mapInfo.treasureNum);
    printf("请输入迷宫的陷阱数量：\n");
    scanf("%d", &mapInfo.trapNum);
    system("cls");

    for( int i = 0 ; i < mapInfo.mapRow ; i ++ )    // 默认初始化迷宫
    {
        for( int j = 0 ; j < mapInfo.mapCol ; j ++ )
        {
            mapInfo.map[i][j] = 'W';
            printf("W ");
        }
        printf("\n");
    }

    int infoPosx = 0 , infoPosy = 0 ;
    GetCursorPosition( &infoPosx , &infoPosy ) ;
    printf("\n\n") ;
    printf("输入W上移光标，S下移光标，A左移光标，D右移光标，Q不保存退出编辑，添加玩家位置进行保存\n");
    printf("输入1添加墙'W'，2添加空地' '，3添加陷阱'D'，4添加宝藏'T'，5添加玩家初始位置'Y'\n");

    int px = 0 , py = 0 ;
    int Tnum = 0 , Dnum = 0 ;
    MoveCursorTo(0, 0);
    int isEdit = 1 ;
    while( isEdit )
    {
        char ch = getch();
        if( ch == 'w' && py > 0 ) py -- ;
        if( ch == 's' && py < mapInfo.mapRow - 1 ) py ++ ;
        if( ch == 'a' && px > 0 ) px -- ;
        if( ch == 'd' && px < mapInfo.mapCol - 1) px ++ ;
        if( ch == '1' )
        {
            if( mapInfo.map[py][px] == 'T' ) Tnum -- ;
            else if( mapInfo.map[py][px] == 'D' ) Dnum -- ;
            mapInfo.map[py][px] = 'W';
            printf("W") ;
        }
        if( ch == '2' )
        {
            if( mapInfo.map[py][px] == 'T' ) Tnum -- ;
            else if( mapInfo.map[py][px] == 'D' ) Dnum -- ;
            mapInfo.map[py][px] = ' ';
            printf(" ");
        }
        if( ch == '3' )
        {
            if( Dnum == mapInfo.trapNum || mapInfo.map[py][px] == 'D' ) continue ;
            else if( mapInfo.map[py][px] == 'T' ) Tnum -- ;
            Dnum ++ ;
            mapInfo.map[py][px] = 'D';
            printf("D");
        }
        if( ch == '4' )
        {
            if( Tnum == mapInfo.treasureNum || mapInfo.map[py][px] == 'T' ) continue ;
            else if( mapInfo.map[py][px] == 'D' ) Dnum -- ;
            Tnum ++ ;
            mapInfo.map[py][px] = 'T';
            printf("T");
        }
        if( ch == '5' )
        {
            mapInfo.map[py][px] = ' ';
            mapInfo.pRow = py;
            mapInfo.pCol = px;
            printf("Y");
            isEdit = 0 ;
        }
        if( ch == 'q' ) return ;

        MoveCursorTo(infoPosx, infoPosy);
        printf("当前位置：(%d, %d)  ", px, py);
        printf("宝藏数量：%d  ", Tnum);
        printf("陷阱数量：%d  ", Dnum);

        MoveCursorTo(2 * px, py);
    }
  
    // 保存地图信息
    FILE *mapfp = NULL ;
    mapfp = fopen( mapName[ customMapNum + 2 ] , "w" ) ;
    if( mapfp == NULL )
    {
        perror("Error opening file");
        return ;
    }

    fprintf(mapfp, "%d %d\n", mapInfo.mapRow, mapInfo.mapCol);
    fprintf(mapfp, "%d %d\n", mapInfo.treasureNum, mapInfo.trapNum);
    fprintf(mapfp, "%d %d\n", mapInfo.pCol, mapInfo.pRow );
    for( int i = 0 ; i < mapInfo.mapRow ; i ++ )
    {
        for( int j = 0 ; j < mapInfo.mapCol ; j ++ )
        {
            fputc(mapInfo.map[i][j], mapfp);
        }
        fputc('\n', mapfp);
    }
    fclose(mapfp);

    ClearPartialScreen(0,0);
    printf("已成功编辑并完成保存！\n") ;
    system("pause") ;
    return ;
}