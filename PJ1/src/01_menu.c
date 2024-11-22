#include "01_menu.h"
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include "03_mapAndPlayerStatus.h"
#include "02_cursorOperation.h"
#include "04_mapCustom.h"

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

static void welcome()
{
    ClearPartialScreen(0, 0);
    printf("欢迎来到小黄的奇妙冒险\n");
    printf("请使用你的智慧来帮助小黄在迷宫中成功的寻宝吧！\n\n");
    printf("<按任意键继续>\n");
    getch();
    return;
}

void menuControl()
{
    welcome();

    int run = 1;
    int menuOrder = 0;
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

static void menuCall0(int *Order, int *run) // 主菜单执行函数
{
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
                int gameMode = menuCall2(Order);
                if (gameMode == 2)
                    return;

                gameStart(gameMode, 1);
                Order = 0;
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
                *Order = 1;
                return 2;
            }
        }
    }
}

static void menuCall3(int *Order) // 自定义地图菜单执行函数
{
    int pos = 0;
    while (1)
    {
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
                int gameMode = menuCall2(Order);
                if (gameMode == 2)
                    return;

                gameStart(gameMode, customMapNum + 3);
                Order = 0;
                welcome();
                return;
            }
            case 2:
            {
                mapCustomIni(customMapNum, 1);
                break;
            }
            case 3:
                return;
            }
        }
    }
}