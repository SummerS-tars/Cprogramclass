#include <stdio.h>
#include <conio.h>

struct playerInfo   // 玩家信息
{
    int px , py ;       // 位置信息
    int energyCost ;    // 体力消耗
    int getTreasure ;   // 奖励获取数量
    int isTrapped ;     // 陷阱触发状态
};

struct mapInfo
{
    char map[ 50 ][ 50 ] ;      // 地图信息
    int mapRow ;                // 地图行数
    int mapCol ;                // 地图列数
    int treasureNum ;           // 宝藏数量
    int trapNum ;               // 陷阱数量
};

void menu()         // 菜单栏目
{
    // TODO
}

void iniMap()      // 初始化迷宫
{
    // TODO
}

void prMap()        // 打印迷宫
{
    // TODO
}

void playerMove()   // 玩家移动
{
    // TODO
}

void judgeAction()  // 判断行动结果
{
    // TODO
}

int main()
{
    
}