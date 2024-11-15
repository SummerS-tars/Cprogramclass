#include <stdio.h>
#include <string.h>
#include <stdlib.h>

extern struct mapInfo
{
    char map[ 50 ][ 50 ] ;      // 地图信息
    int mapRow ;                // 地图行数
    int mapCol ;                // 地图列数
    int treasureNum ;           // 宝藏数量
    int trapNum ;               // 陷阱数量
};

extern void mapIni( struct mapInfo *mapInfo )      // 初始化迷宫
{
    memset( mapInfo->map , 0 , sizeof( mapInfo->map ) ) ;
    mapInfo->mapRow = 0 ;
    mapInfo->mapCol = 0 ;
    mapInfo->treasureNum = 0 ;
    mapInfo->trapNum = 0 ;
    return ;
}

extern void mapInput( struct mapInfo *mapInfo , int mapOrder )    // 输入迷宫
{
    // TODO
}

extern void mapPrint( struct mapInfo *mapInfo )    // 打印迷宫
{
    // TODO
}

extern void mapStatus( struct mapInfo *mapInfo )   // 打印地图状态
{
    // TODO
}

