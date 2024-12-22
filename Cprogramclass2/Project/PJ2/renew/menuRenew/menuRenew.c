#include "menuRenew.h"
#include "02_cursorOperation.h"
#include "03_mapAndPlayerStatus.h"
#include "04_mapCustom.h"
#include <stdio.h>
#include <conio.h>

// 菜单列表
static char menuMainList[3][40] = { // 主菜单列表
    {"开始游戏"},
    {"获取帮助"},
    {"退出游戏"}};
static char menuGameList[5][40] = { // 游戏菜单列表
    {"第一关"},
    {"第二关"},
    {"第三关"},
    {"自定义关卡"},
    {"返回主菜单"}};
static char menuControlMode[3][40] = { // 控制模式菜单列表
    {"实时模式"},
    {"编程模式"},
    {"返回地图菜单"}};
static char menuCustomMap[4][40] = { // 自定义地图菜单列表
    {"自定义地图一"},
    {"自定义地图二"},
    {"自定义地图三"},
    {"返回地图菜单"}};
static char menuCustomOperation[4][40] = { // 自定义操作菜单列表
    {"开始编辑"},
    {"开始游玩"},
    {"重置地图"},
    {"返回自定义菜单"}};
static char (*menuList[5])[40] = {
    menuMainList,
    menuGameList,
    menuControlMode,
    menuCustomMap,
    menuCustomOperation};
static int menuOption[5] = {3, 5, 3, 4, 4}; // 菜单选项数量

static void menuPrint(int menuOrder, int listPos) // 菜单函数，根据listPos变量控制光标位置
{
    MoveCursorTo(0,0) ;
    for (int i = 0; i < menuOption[menuOrder]; i++)
    {
        if (i == listPos)
            printf("> ");
        else
            printf("  ");
        printf("%s\n", menuList[menuOrder] + i);
    }
    printf("\n输入w上移光标,s下移光标,输入<Enter>选中\n");
}

static void menuCall0(int *Order, int *run);         // 主菜单执行函数
static void menuCall1(int *Order);                   // 游戏菜单执行函数
static int menuCall2(int *Order);                    // 控制模式菜单执行函数
static void menuCall3(int *Order);                   // 自定义地图菜单执行函数
static void menuCall4(int *Order, int customMapNum); // 自定义操作菜单执行函数
static int inputLoop(int Order, int *pos);
static void menuOperation(int *Order, int *run, int pos, int *mode);

static void welcome()
{
    ClearPartialScreen(0, 0);
    printf("欢迎来到小黄的奇妙冒险\n");
    printf("请使用你的智慧来帮助小黄在迷宫中成功的寻宝吧！\n\n");
    printf("<按任意键继续>\n");
    getch();
    return;
}

extern void menuControl()
{
    // 欢迎页面
    welcome();

    int run = 1;        // 运行状态变量
    int menuOrder = 0;  // 菜单级数函数
    int pos = 0;        // 菜单光标位置
    int mode = 0;       // 控制模式
    while (run)
    {                      // 循环逻辑：通过run控制菜单的退出
        pos = inputLoop(menuOrder, &pos);
        menuOperation(&menuOrder, &run, pos, &mode);
    }
}

static int inputLoop(int Order, int *pos)
{
    *pos = 0;
    char ch = '\0';
    while(1)
    {
        MoveCursorTo(0,0);
        ch = getch();
        if( ch == 'w' && pos > 0 )
            pos--;
        if( ch == 's' && pos < menuOption[Order] - 1 )
            pos++;
        if( ch == '\r' )
            break;
    }
    system("cls");
    return pos;
}

static void gameStart(int gameMode, int num)
{
    struct mapInfo map;
    struct playerInfo player;
    mapIni(&map);
    if (!mapInput(&map, num))
        return; // 读取地图失败则直接返回
    playerIni(&player, &map);
    mapPrint(&map);
    HideConsoleCursor();
    if (gameMode == 0)
        playerMove(&player, &map);
    else if (gameMode == 1)
        playerMovePro(&player, &map);
    ShowConsoleCursor();
}

static void menuOperation(int *Order, int *run, int pos, int *mode)
{
    switch(*Order)  // 第一步：选择菜单级数
    {
        case 0:     // 主菜单执行函数
        {
            switch(pos)     
            {
                case 0:
                    *Order = 1;
                    return;
                case 1:
                {
                    printf("Help file...\n");
                    // TODO: 帮助文件
                    printf("<Press any key to return>\n");
                    return;
                }
                case 2:
                    *run = 0;
                    return;
            }
        }
        case 1:     // 游戏菜单执行函数
        {
            switch(pos)
            {
                case 0: // 第一关函数
                {
                    int gameMode = menuCall2(Order);
                    if (gameMode == 2)
                        return;

                    gameStart(gameMode, 1);
                    *Order = 0;
                    welcome();
                    return;
                }
                case 1: // 第二关函数
                {
                    int gameMode = menuCall2(Order);
                    if (gameMode == 2)
                        return;

                    gameStart(gameMode, 2);
                    Order = 0;
                    welcome();
                    return;
                }
                case 2: // 第三关函数
                {
                    int gameMode = menuCall2(Order);
                    if (gameMode == 2)
                        return;

                    gameStart(gameMode, 3);
                    Order = 0;
                    welcome();
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
        case 2:     // 控制模式菜单执行函数
        {
            switch (pos)
            {
            case 0:
                *mode = 0; // 实时模式函数
                return;
            case 1:
                *mode = 1; // 编程模式函数
            case 2:
                *Order = 1;
                return 2;
            }
        }
    }
}

static void menuCall0(int *Order, int *run) // 主菜单执行函数
{
    menuPrint(*Order, 0);
    int pos = inputLoop(*Order);


}

static void menuCall1(int *Order)           // 游戏菜单执行函数
{
    menuPrint(*Order, 0);
    int pos = inputLoop(*Order);

    switch (pos)
    {
        case 0:

}