#include "03_mapAndPlayerStatus.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include "02_cursorOperation.h"

const char moveInfo[7][100] = {
    {"平平无奇地在空地上进行了移动..."},
    {"你装上了墙壁，两眼一黑！"},
    {"你狠狠地在原地休息了一下，什么也没有发生..."},
    {"你不小心走进了陷阱，被困住了难以行动..."},
    {"你终于找到了一个宝藏，恭喜你!"},
    {"你找齐了所有的宝藏，恭喜你!"},
    {"你的操作无效，什么也没有发生..."}};

int runGame; // 游戏运行状态

static int infoPrix, infoPriy;

void mapIni(struct mapInfo *mapInfo) // 初始化迷宫
{
    memset(mapInfo->map, 0, sizeof(mapInfo->map));
    mapInfo->mapRow = 0;
    mapInfo->mapCol = 0;
    mapInfo->treasureNum = 0;
    mapInfo->trapNum = 0;
    return;
}

int mapInput(struct mapInfo *mapInfo, int mapOrder) // 输入迷宫
{
    FILE *mapfp = NULL;
    switch (mapOrder)
    {
    case 1:
        mapfp = fopen("map1.txt", "r");
        break;
    case 2:
        mapfp = fopen("map2.txt", "r");
        break;
    case 3:
        mapfp = fopen("map3.txt", "r");
        break;
    case 4:
        mapfp = fopen("mapCustom1.txt", "r");
        break;
    case 5:
        mapfp = fopen("mapCustom2.txt", "r");
        break;
    case 6:
        mapfp = fopen("mapCustom3.txt", "r");
        break;
    default:
        break;
    }
    if (mapfp == NULL)
    {
        printf("地图文件打开失败\n");
        return 0;
    }

    // 判断自定义地图是否编辑
    if (mapOrder >= 4)
    {
        char isEdit = 0;
        fscanf(mapfp, "%c", &isEdit);
        if (isEdit == '*')
        {
            ClearPartialScreen(0, 0); // 清空屏幕
            printf("地图还未编辑，请先编辑地图之后再进行游玩！\n");
            system("pause");
            return 0;
        }
        else
            fseek(mapfp, 0, SEEK_SET);
    }

    fscanf(mapfp, "%d%d", &mapInfo->mapRow, &mapInfo->mapCol);
    fscanf(mapfp, "%d%d", &mapInfo->treasureNum, &mapInfo->trapNum);
    fscanf(mapfp, "%d%d", &mapInfo->pRow, &mapInfo->pCol);
    fgetc(mapfp); // 读取换行符

    for (int i = 0; i < mapInfo->mapRow; i++)
    {
        for (int j = 0; j < mapInfo->mapCol; j++)
        {
            mapInfo->map[i][j] = fgetc(mapfp);
        }
        fgetc(mapfp); // 读取换行符
    }
    fclose(mapfp);

    return 1;
}

void mapPrint(struct mapInfo *mapInfo) // 打印迷宫
{
    ClearPartialScreen(0, 0); // 清空屏幕
    for (int i = 0; i < mapInfo->mapRow; i++)
    {
        for (int j = 0; j < mapInfo->mapCol; j++)
        {
            printf("%c ", mapInfo->map[i][j]);
        }
        printf("\n");
    }
    puts("");
    printf("按W向上移动，按S向下移动，按A向左移动，按D向右移动，按I原地不动，按Z撤回一次操作，按Y重做一次操作，按Q退出游戏\n");

    GetCursorPosition(&infoPrix, &infoPriy);        // 获取当前光标位置
    MoveCursorTo(2 * mapInfo->pCol, mapInfo->pRow); // 移动到玩家位置
    return;
}

void playerIni(struct playerInfo *player, struct mapInfo *mapInfo) // 初始化玩家信息
{
    runGame = 1;
    player->px = mapInfo->pRow;
    player->py = mapInfo->pCol;
    player->energyCost = 0;
    player->getTreasure = 0;
    player->isTrapped = 0;
    memset(player->moveMemory, 0, sizeof(player->moveMemory));
    memset(player->moveResult, 0, sizeof(player->moveResult));
    player->tt = 0;

    return;
}

void playerInfoPrint(struct playerInfo *player, int num) // 打印玩家信息
{
    // 打印玩家位置
    MoveCursorTo(2 * player->px, player->py);
    printf("Y");

    // 打印游戏信息
    ClearPartialScreen(infoPrix, infoPriy); // 移动到游戏信息输出位置并清空后续信息
    printf("当前位置：(%d, %d)\n", player->px, player->py);
    printf("已获得宝藏：%d\n", player->getTreasure);
    printf("已消耗能量：%d\n", player->energyCost);
    if (player->isTrapped == 1)
    {
        printf("你被困住了，下一步行动消耗体力增加！\n");
    }
    else
        printf("\n");

    // 打印行动信息
    /*
    特殊调用-1
    正常行动0
    撞墙1
    休息2
    触发陷阱3
    获得宝藏4
    获得所有宝藏5
    无效操作6
    */
    if (num >= 0)
        printf("%s\n", moveInfo[num]);

    return;
}

void exitInfoPrint(struct playerInfo *player)
{
    // 打印游戏结束信息
    ClearPartialScreen(infoPrix, infoPriy); // 移动到游戏信息输出位置并清空后续信息
    printf("============================================\n");
    printf("本局结算：\n\n");
    printf("您的行动路径是: %s\n", player->moveMemory);
    printf("你一共消耗了%d点能量！\n", player->energyCost);
    printf("你一共获得了%d个宝藏！\n\n", player->getTreasure);
    printf("感谢你的游玩！\n");
    printf("============================================\n\n");
    system("pause");

    return;
}

int playerMoveJudge(struct playerInfo *player, struct mapInfo *mapInfo, char order)
{
    // 值得注意的是，左右为x，上下为y
    int x = player->px;
    int y = player->py;
    int mapRow = mapInfo->mapRow;
    int mapCol = mapInfo->mapCol;
    int moveFlag = 0; // 0表示位置不变，1表示位置改变

    /**
     * 返回值介绍：
     * -1:无效行动或者直接结束游戏
     * 0:正常行动
     * 1:撞墙
     * 2:休息
     * 3:触发陷阱
     * 4:获得宝藏
     * 5:获得所有宝藏
     */
    

    // 判断玩家行动
    switch (order)
    {
    case 'i': // 原地不动
        return 2;

    case 'q': // 退出游戏
        runGame = 0;
        return -1;

    case 'w':
        player->moveMemory[player->tt] = 'U';
        if (y - 1 >= 0 && mapInfo->map[y - 1][x] == 'W')
        {
            player->moveResult[player->tt++] = 1;
            player->energyCost++;
            return 1;
        }
        else if (y - 1 >= 0)
        {
            moveFlag = 1;
            player->py--;
        }
        break;

    case 's':
        player->moveMemory[player->tt] = 'D';
        if (y + 1 < mapRow && mapInfo->map[y + 1][x] == 'W')
        {
            player->moveResult[player->tt++] = 1;
            player->energyCost++;
            return 1;
        }
        else if (y + 1 < mapRow)
        {
            moveFlag = 1;
            player->py++;
        }
        break;

    case 'a':
        player->moveMemory[player->tt] = 'L';
        if (x - 1 >= 0 && mapInfo->map[y][x - 1] == 'W')
        {
            player->moveResult[player->tt++] = 1;
            player->energyCost++;
            return 1;
        }
        else if (x - 1 >= 0)
        {
            moveFlag = 1;
            player->px--;
        }
        break;

    case 'd':
        player->moveMemory[player->tt] = 'R';
        if (x + 1 < mapCol && mapInfo->map[y][x + 1] == 'W')
        {
            player->moveResult[player->tt++] = 1;
            player->energyCost++;
            return 1;
        }
        else if (x + 1 < mapCol)
        {
            moveFlag = 1;
            player->px++;
        }
        break;
    }

    /**
     * 地图信息说明:
     * 'D'陷阱
     * 'T'宝藏
     * ' '空地
     */

    // 判断玩家位置变化后的状态变化
    if (moveFlag)
    {
        player->energyCost++;
        int TrapFlag = 0;
        if (player->isTrapped == 1)
        {
            TrapFlag = 1;
            player->energyCost++;
            player->isTrapped = 0;
        }

        // 判断玩家位置地块
        if (mapInfo->map[player->py][player->px] == 'D')
        {
            if (TrapFlag == 1)
                player->moveResult[player->tt++] = 6;
            else
                player->moveResult[player->tt++] = 3;
            player->isTrapped = 1;
            return 3;
        }
        else if (mapInfo->map[player->py][player->px] == 'T')
        {
            if (TrapFlag == 1)
                player->moveResult[player->tt++] = 7;
            else
                player->moveResult[player->tt++] = 4;
            mapInfo->map[player->py][player->px] = ' ';
            player->getTreasure++;
            if (player->getTreasure == mapInfo->treasureNum)
            {
                runGame = 0;
                return 5;
            }
            return 4;
        }
        else
        {
            if (TrapFlag == 1)
                player->moveResult[player->tt++] = 5;
            else
                player->moveResult[player->tt++] = 2;
            return 0;
        }
    }
}

void moveBack(struct playerInfo *player, struct mapInfo *mapInfo)
{
    if (player->tt == 0)
    {
        playerInfoPrint(player, -1);
        printf("你还没有移动过，无法撤销！\n");
        return;
    }

    char order = player->moveMemory[player->tt - 1];
    int result = player->moveResult[player->tt - 1];
    player->tt--;

    // 记录恢复前位置
    int tx = 2 * player->px, ty = player->py;

    // 恢复位置与状态
    if (result == 1)
    {
        player->energyCost--;
    }
    else
    {
        // 恢复位置
        switch (order)
        {
        case 'U':
            player->py++;
            break;
        case 'D':
            player->py--;
            break;
        case 'L':
            player->px++;
            break;
        case 'R':
            player->px--;
            break;
        }

        // 恢复体力消耗状态
        if (result >= 5)
        {
            player->energyCost -= 2;
            player->isTrapped = 1;
        }
        else
        {
            player->energyCost--;
            player->isTrapped = 0;
        }

        // 恢复玩家与地图宝藏状态
        if (result == 4 || result == 7)
        {
            player->getTreasure--;
            mapInfo->map[ty][tx / 2] = 'T';
        }
    }

    // 恢复地图状态与显示
    playerInfoPrint(player, -1);
    printf("撤销成功！\n");

    MoveCursorTo(tx, ty);
    switch (result)
    {
    case 2:
        printf(" ");
        break;
    case 3:
        printf("D");
        break;
    case 4:
        printf("T");
        break;
    case 5:
        printf(" ");
        break;
    case 6:
        printf("D");
        break;
    case 7:
        printf("T");
        break;
    }

    return;
}

char moveRedo(struct playerInfo *player, struct mapInfo *mapInfo)
{
    if (player->moveResult[player->tt] == 0)
    {
        playerInfoPrint(player, -1);
        printf("你已经是最新状态，无法重做！\n");
        return 0;
    }

    char order = player->moveMemory[player->tt];
    switch (order)
    {
    case 'U':
        order = 'w';
        break;
    case 'D':
        order = 's';
        break;
    case 'L':
        order = 'a';
        break;
    case 'R':
        order = 'd';
        break;
    }
    return order;
}

void playerMove(struct playerInfo *player, struct mapInfo *mapInfo) // 玩家移动实时模式
{
    playerInfoPrint(player, -1);

    while (runGame)
    {
        char order = '\0';
        order = getch();

        // 过滤无效输入
        if (order == 'y' || order == 'w' || order == 's' || order == 'a' || order == 'd' || order == 'i' || order == 'q')
        {
            if (order == 'y')
                order = moveRedo(player, mapInfo);
            if (order == 0)
                continue;

            int tx = 2 * player->px, ty = player->py;
            int printFlag = playerMoveJudge(player, mapInfo, order);
            if (printFlag == -1)
            {
                ClearPartialScreen(0, 0); // 清空屏幕
                printf("强制退出，游戏结束！\n\n");
                infoPrix = 0, infoPriy = 2;
                exitInfoPrint(player);
                return;
            }

            // 删除或者打印上一次位置
            if (player->tt > 0 && player->moveResult[player->tt - 1] >= 5)
            {
                MoveCursorTo(tx, ty);
                printf("D"); // 陷阱不消耗
            }
            else
            {
                MoveCursorTo(tx, ty);
                printf(" ");
            }

            // 打印新的玩家信息
            playerInfoPrint(player, printFlag);
        }
        else if (order == 'z')
        {
            moveBack(player, mapInfo);
        }
        else
        {
            playerInfoPrint(player, 6);
        }
    }

    ClearPartialScreen(0, 0); // 清空屏幕
    printf("您成功找到所有宝藏，游戏结束！\n\n");
    infoPrix = 0, infoPriy = 2;
    exitInfoPrint(player);
    return;
}

void playerMovePro(struct playerInfo *player, struct mapInfo *mapInfo) // 玩家移动编程模式
{
    playerInfoPrint(player, -1);

    while (runGame)
    {
        char orderList[250] = {0}; // 用于存储玩家操作序列
        /* 操作序列解释:
         * U向上
         * D向下
         * L向左
         * R向右
         * 其他操作直接退出
         */

        printf("请输入你的操作序列：\n");
        scanf("%s", orderList);
        getchar(); // 读取回车

        int tp = player->tt, tx = 2 * player->px, ty = player->py;
        int len = strlen(orderList);
        for (int i = 0; i < len; i++)
        {
            char order = 0;
            switch (orderList[i])
            {
            case 'U':
                order = 'w';
                break;
            case 'D':
                order = 's';
                break;
            case 'L':
                order = 'a';
                break;
            case 'R':
                order = 'd';
                break;
            default:
            {
                ClearPartialScreen(0, 0); // 清空屏幕
                printf("编程模式下操作错误，游戏结束！\n\n");
                infoPrix = 0, infoPriy = 2;
                exitInfoPrint(player);
                return;
            }
            }
            int printFlag = playerMoveJudge(player, mapInfo, order);

            if (printFlag == 1)
            {
                runGame = 0;

                ClearPartialScreen(0, 0); // 清空屏幕
                printf("编程模式下操作错误，游戏结束！\n\n");
                infoPrix = 0, infoPriy = 2;
                exitInfoPrint(player);
                return;
            }

            if (printFlag == 5)
            {
                ClearPartialScreen(0, 0); // 清空屏幕
                printf("您成功找到所有宝藏，游戏结束！\n\n");
                infoPrix = 0, infoPriy = 2;
                exitInfoPrint(player);
                return;
            }
        }

        // 删除或者打印上一次位置
        if (tp > 0 && player->moveResult[tp] >= 5)
        {
            MoveCursorTo(tx, ty);
            printf("D"); // 陷阱不消耗
        }
        else
        {
            MoveCursorTo(tx, ty);
            printf(" ");
        }

        // 打印新的玩家信息
        playerInfoPrint(player, -1);
    }
}