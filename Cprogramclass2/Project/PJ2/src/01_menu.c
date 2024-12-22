#include "01_menu.h"
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include "03_mapAndPlayerStatus.h"
#include "02_cursorOperation.h"
#include "04_mapCustom.h"

/* 菜单列表 */
static char menuMainList[3][40] = { // 主菜单列表
    {"开始游戏"},
    {"帮助菜单"},
    {"退出游戏"}};
static char menuGameList[5][40] = { // 游戏菜单列表
    {"第一关"},
    {"第二关"},
    {"第三关"},
    {"自定义关卡"},
    {"返回主菜单"}};
static char menuControlMode[4][40] = { // 控制模式菜单列表
    {"实时模式"},
    {"编程模式"},
    {"帮助菜单"},
    {"返回地图菜单"}};
static char menuCustomMap[4][40] = { // 自定义地图菜单列表
    {"自定义地图一"},
    {"自定义地图二"},
    {"自定义地图三"},
    {"返回地图菜单"}};
static char menuCustomOperation[5][40] = { // 自定义操作菜单列表
    {"开始编辑"},
    {"开始游玩"},
    {"重置地图"},
    {"帮助菜单"},
    {"返回自定义菜单"}};
static char menuProgressList[4][40] = { // 已游玩地图进度选择列表
    {"继续上次游戏"},
    {"开始新游戏"},
    {"清除存档"},
    {"返回主菜单"}};

/* 菜单相关信息列表 */
static char (*menuList[6])[40] = {
    menuMainList,
    menuGameList,
    menuControlMode,
    menuCustomMap,
    menuCustomOperation,
    menuProgressList};
static int menuOption[6] = {3, 5, 4, 4, 5, 4}; // 菜单选项数量
static int mapPlayStatus[6] = {0, 0, 0, 0, 0, 0};   // 地图游玩状态
static int mapEditStatus[3] = {0, 0, 0};            // 地图编辑状态

static void menuCall0(int *Order, int *run);         // 主菜单执行函数
static void menuCall1(int *Order);                   // 游戏菜单执行函数
static int menuCall2(int *Order);                    // 控制模式菜单执行函数
static void menuCall3(int *Order);                   // 自定义地图菜单执行函数
static void menuCall4(int *Order, int customMapNum); // 自定义操作菜单执行函数
static int menuCall5(int mapOrder);                              // 已游玩地图进度选择函数
static void gameStart(int *Order, int num);        // 游戏开始函数

void mapInfoInit()     // 地图游玩（以及自定义地图编辑）状态初始化函数
{
    /* 检测自定义地图编辑状态 */
    for( int i = 1 ; i <= 3 ; i ++ )
    {
        FILE *mapfp = NULL ;
        mapfp = fopen( mapName[ i + 2 ] , "r" ) ;
        char editFlag = 0 ;
        editFlag = fgetc( mapfp ) ;
        if( editFlag == '*' ) mapEditStatus[ i - 1 ] = 0 ; // 未编辑
        else mapEditStatus[ i - 1 ] = 1 ; // 已编辑
        fclose( mapfp ) ;
    }

    /* 检测地图游玩状态 */
    for( int i = 1 ; i <= 6 ; i ++ )
    {
        FILE *mapfp = NULL ;
        mapfp = fopen( mapProgressSave[ i - 1 ] , "r" ) ;
        char playFlag = 0 ;
        playFlag = fgetc( mapfp ) ;
        if( playFlag == '*' ) mapPlayStatus[ i - 1 ] = 0 ; // 未游玩
        else mapPlayStatus[ i - 1 ] = 1 ; // 已游玩
        fclose( mapfp ) ;
    }
}

static void menuPrint(int menuOrder, int listPos) // 菜单打印函数，根据listPos变量控制光标位置
{
    for (int i = 0; i < menuOption[menuOrder]; i++)
    {
        /* 打印基础选项信息 */
        if (i == listPos)
            printf("> ");
        else
            printf("  ");
        printf("%s", menuList[menuOrder] + i);

        /* 自定义地图编辑状态补充 */
        if( menuOrder == 3 && i >= 0 && i <= 2 && !mapEditStatus[ i ] )
            printf("(未编辑)");

        /* 地图游玩状态补充 */
        if( menuOrder == 1 && i >= 0 && i <= 2 && mapPlayStatus[ i ] )
            printf("(上次)");
        else if( menuOrder == 3 && i >= 0 && i <= 2 && mapPlayStatus[ i + 3 ] )
            printf("(上次)");
        
        printf("\n");
    }
    printf("\n输入w上移光标,s下移光标,输入<Enter>选中\n");
    
    /*
    // TODO: test
    printf("\n");
    printf("mapPlayStatus: ") ;
    for( int i = 0 ; i < 6 ; i ++ )
        printf("%d" , mapPlayStatus[i] ) ;
    puts("") ;
    printf("mapEditStatus: ") ;
    for( int i = 0 ; i < 3 ; i ++ )
        printf("%d" , mapEditStatus[i] ) ;
    puts("") ;
    */
}

static void welcome()   // 欢迎界面
{
    ClearPartialScreen(0, 0);
    printf("欢迎来到小黄的奇妙冒险\n");
    printf("请使用你的智慧来帮助小黄在迷宫中成功的寻宝吧！\n\n");
    printf("<按任意键继续>\n");
    getch();
    return;
}

static void menuCall0(int *Order, int *run) // 主菜单执行函数
{
    mapInfoInit();
    int pos = 0;
    while (1)
    {
        system("cls");
        // 如果要求跨平台，可以使用如下代码代替
        // printf("\033[H\033[J");

        menuPrint(0, pos);

        char ch = getch();
        if (ch == 'w' && pos > 0)
            pos--;
        if (ch == 's' && pos < menuOption[0] - 1)
            pos++;
        if (ch == '\r')
        {
            switch (pos)
            {
            case 0:
                *Order = 1;
                return;
            case 1:
            {
                system("cls");
                printf("游戏帮助\n\n");
                printf("游戏目标：\n");
                printf("    1. 通过键盘输入指令，帮助小黄在迷宫中找到所有宝藏\n");
                printf("    2. 小黄的默认初始位置为地图左上角，宝藏的位置随机生成\n");
                printf("    3. 实时模式下，小黄的移动指令为：\n");
                printf("        w: 向上移动\n");
                printf("        s: 向下移动\n");
                printf("        a: 向左移动\n");
                printf("        d: 向右移动\n");
                printf("        i: 原地休息\n");
                printf("        q: 退出游戏\n");
                printf("    4. 编程模式下，小黄的移动指令为：\n");
                printf("        U: 向上移动\n");
                printf("        D: 向下移动\n");
                printf("        L: 向左移动\n");
                printf("        R: 向右移动\n");
                printf("        P.S. 编程模式下无效操作或操作错误会直接退出游戏\n");
                printf("    5. 每次移动会消耗一点能量\n");
                printf("    6. 小黄遇到墙壁会停留在原地，遇到陷阱下次行动多消耗一点能量\n");
                printf("    7. 小黄找到所有宝藏后游戏结束\n");
                printf("    8. 祝你好运！\n\n");
                printf("<按任意键返回>\n");
                getch();
                break;
            }
            case 2:
                *run = 0;
                return;
            }
        }
    }
}

static void menuCall1(int *Order) // 游戏菜单执行函数
{
    int pos = 0;
    while (1)
    {
        mapInfoInit();
        system("cls");
        menuPrint(1, pos);

        char ch = getch();
        if (ch == 'w' && pos > 0)
            pos--;
        if (ch == 's' && pos < menuOption[1] - 1)
            pos++;
        if (ch == '\r')
        {
            switch (pos)
            {
            case 0: // 第一关函数
            {
                gameStart(Order , 1);
                return;
            }
            case 1: // 第二关函数
            {
                gameStart(Order , 2);;
                return;
            }
            case 2: // 第三关函数
            {
                gameStart(Order , 3);
                return;
            }
            case 3:
                *Order = 3;
                return;
            case 4:
                *Order = 0;
                return;
            }
        }
    }
}

static int menuCall2(int *Order) // 控制模式菜单执行函数
{
    int pos = 0;
    while (1)
    {
        system("cls");
        menuPrint(2, pos);

        char ch = getch();
        if (ch == 'w' && pos > 0)
            pos--;
        if (ch == 's' && pos < menuOption[2] - 1)
            pos++;
        if (ch == '\r')
        {
            switch (pos)
            {
            case 0:
                return 0; // 实时模式函数
            case 1:
                return 1; // 编程模式函数
            case 2:
            {
                system("cls");
                printf("help file 2 施工中\n") ;
                // TODO: 编写控制模式帮助文档
            }
            case 3:
                return 2;
            }
        }
    }
}

static void menuCall3(int *Order) // 自定义地图地图选择菜单执行函数
{
    int pos = 0;
    while (1)
    {
        mapInfoInit();
        system("cls");
        menuPrint(3, pos);

        char ch = getch();
        if (ch == 'w' && pos > 0)
            pos--;
        if (ch == 's' && pos < menuOption[3] - 1)
            pos++;
        if (ch == '\r')
        {
            switch (pos)
            {
            case 0:
                menuCall4(Order, 1);
                return;
            case 1:
                menuCall4(Order, 2);
                return;
            case 2:
                menuCall4(Order, 3);
                return;
            case 3:
                *Order = 1;
                return;
            }
        }
    }
}

static void menuCall4(int *Order, int customMapNum) // 自定义操作菜单执行函数
{
    int pos = 0;
    while (1)
    {
        system("cls");
        menuPrint(4, pos);

        char ch = getch();
        if (ch == 'w' && pos > 0)
            pos--;
        if (ch == 's' && pos < menuOption[4] - 1)
            pos++;
        if (ch == '\r')
        {
            switch (pos)
            {
            case 0:
            {
                mapCustomEdit(customMapNum);
                return;
            }
            case 1:
            {
                gameStart(Order , customMapNum + 3);
                return;
            }
            case 2:
            {
                mapCustomIni(customMapNum, 1);
                mapInfoInit();
                break;
            }
            case 3:
            {
                system("cls");
                printf("help file 3 施工中\n") ;
                // TODO: 编写自定义地图帮助文档
            }
            case 4:
                *Order = 3;
                return;
            }
        }
    }
}

static int menuCall5(int mapOrder)      // 已游玩地图进度选择函数
{
    int pos = 0 ;
    FILE *mapfp = NULL ;
    mapfp = fopen( mapProgressSave[ mapOrder - 1 ] , "r" ) ;
    char timeStr1[64] = {0} ;
    char timeStr2[64] = {0} ;
    int treasureInfoPlayer , treasureInfoMap ;
    fscanf( mapfp , "%s %s\n" , timeStr1 , timeStr2 ) ;              // 写入保存时间
    fscanf( mapfp , "%d %d\n" , &treasureInfoPlayer , &treasureInfoMap ) ; // 读取宝藏信息
    fclose( mapfp ) ;
    
    while( 1 )
    {
        system("cls");
        printf("上次游玩时间：%s %s\n" , timeStr1 , timeStr2 ) ;
        printf("上次游玩宝藏：%d/%d\n\n" , treasureInfoPlayer , treasureInfoMap ) ;
        
        menuPrint(5, pos);

        char ch = getch();
        if( ch == 'w' && pos > 0 )
            pos -- ;
        if( ch == 's' && pos < menuOption[5] - 1 )
            pos ++ ;
        if( ch == '\r' )
            return pos + 1;
            /**
             * 返回值介绍：
             * 1：继续上次游戏
             * 2：开始新游戏
             * 3: 清除存档
             * 4：返回主菜单
             */
    }
}

static void gameStart( int *Order , int num ) // 游戏开始函数
{
    mapInfoInit();
    /* 是否继续游戏 */
    int keepProgress = 0;
    if( mapPlayStatus[ num - 1 ] )
    {
        int progressOrder = menuCall5( num ) ;
        if( progressOrder == 1 ) // 继续上次游戏
            keepProgress = 1;
        else if( progressOrder == 2 ) // 开始新游戏
            keepProgress = 0;
        else if( progressOrder == 3 ) // 清除存档
        {
            progressSaveInit( num ) ;
            mapInfoInit() ;
            return ;
        }
        else if( progressOrder == 4 ) // 返回主菜单
            return;
    }

    /* 选择控制模式 */
    int gameMode = menuCall2(Order);
    if (gameMode == 2)
        return;

    /* 初始化 */
    struct mapInfo map;
    struct playerInfo player;
    mapIni(&map);
    if (!mapInput(&map, num))
        return; // 读取地图失败则直接返回
    playerIni(&player, &map);
    if( keepProgress )
        progressLoad( &player , &map , num ) ;
    mapPrint(&map);
    HideConsoleCursor();

    /* 按控制模式进入游戏主体 */
    if (gameMode == 0)
        playerMove(&player, &map, num);
    else if (gameMode == 1)
        playerMovePro(&player, &map, num);
    ShowConsoleCursor();

    /* 完成游戏，返回主菜单 */
    Order = 0;
    mapInfoInit();
    welcome();
}

void menuControl()      // 菜单运行控制主函数
{
    welcome();

    int run = 1;
    int menuOrder = 0;
    mapInfoInit();
    while (run)
    {                      // 循环逻辑：通过run控制菜单的退出
        switch (menuOrder) // 菜单选取逻辑：通过menuOrder变量控制菜单的选择
        {
        case 0:
            menuCall0(&menuOrder, &run);
            break;
        case 1:
            menuCall1(&menuOrder);
            break;
        case 2:
            menuCall2(&menuOrder);
            break;
        case 3:
            menuCall3(&menuOrder);
            break;
        }
    }
}
