#ifndef MAPSTATUS_H
#define MAPSTATUS_H

struct mapInfo
{
    char map[50][50];      // 地图信息
    int mapRow;            // 地图行数
    int mapCol;            // 地图列数
    int treasureNum;       // 宝藏数量
    int trapNum;           // 陷阱数量
    int pRow, pCol;        // 玩家位置
    /*
    需要注意Row左右计算，Col上下计算 
    地图文档中数据对应的是map数组中的位置 
    map数组中[Col][Row]
    */
};

struct playerInfo
{
    int px , py ;               // 位置信息
    int energyCost ;            // 体力消耗
    int getTreasure ;           // 获得宝物数量
    int isTrapped ;             // 是否触发陷阱
    
    char moveMemory[ 1000 ] ;   // 移动路径
    /* 用于存储玩家的操作记录
     * U:上
     * D:下
     * L:左
     * R:右
     */
    int moveResult[ 1000 ] ;   // 移动结果（回退时使用）
    /* 用于同步记录玩家的操作结果
     * 1表示撞墙
     * 2表示空地行走
     * 3表示正常触发陷阱
     * 4表示正常获得宝藏
     * 5表示陷阱触发后走到空地
     * 6表示陷阱触发后触发陷阱
     * 7表示陷阱触发后获得宝藏
     */
    int tt ;                    // moveMemory与moveResult的长度
};

extern int runGame;         // 游戏运行状态:0表示结束，1表示运行

void mapIni(struct mapInfo *mapInfo);                                                       // 初始化迷宫
int mapInput(struct mapInfo *mapInfo, int mapOrder);                                       // 输入迷宫
void mapPrint(struct mapInfo *mapInfo);                                                     // 打印迷宫
void playerIni( struct playerInfo *player , struct mapInfo *mapInfo );                      // 初始化玩家信息
void playerInfoPrint( struct playerInfo *player , int num );                                // 打印玩家信息
void exitInfoPrint( struct playerInfo *player );                                            // 打印退出信息
int playerMoveJudge( struct playerInfo *player , struct mapInfo *mapInfo , char order );    // 玩家移动判断
void moveBack( struct playerInfo *player , struct mapInfo *mapInfo );
char moveRedo( struct playerInfo *player , struct mapInfo *mapInfo );
void playerMove( struct playerInfo *player , struct mapInfo *mapInfo );                     // 玩家移动实时模式
void playerMovePro( struct playerInfo *player , struct mapInfo *mapInfo );                  // 玩家移动编程模式

#endif // MAPSTATUS_H