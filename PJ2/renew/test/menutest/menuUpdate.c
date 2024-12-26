#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>
#include "02_cursorOperation.h"
#include "menuUpdate.h"

/* 菜单列表 */
static char mainMenuList[3][40] = { // 主菜单列表
    {"开始游戏"},
    {"获取帮助"},
    {"退出游戏"}};
static char mapTypeMenuList[3][40] = { // 地图类型菜单列表
    {"默认地图关卡"},
    {"自定义地图关卡"},
    {"返回主菜单"}};
static char defaultMapMenuList[4][40] = { // 默认地图关卡菜单列表
    {"地图一"},
    {"地图二"},
    {"地图三"},
    {"返回地图类型菜单"}};
static char customMapMenuList[4][40] = { // 自定义地图关卡菜单列表
    {"自定义地图一"},
    {"自定义地图二"},
    {"自定义地图三"},
    {"返回地图类型菜单"}};
static char customOperationMenuList[5][40] = { // 自定义操作菜单列表
    {"开始游玩"},
    {"开始编辑"},
    {"重置地图"},
    {"获取帮助"},
    {"返回自定义菜单"}};
static char saveLoadMenuList[4][40] = { // 存档菜单列表
    {"继续上次游戏"},
    {"开始新游戏"},
    {"清除存档"},
    {"返回"}};
static char controlModeMenuList[4][40] = { // 控制模式菜单列表
    {"实时模式"},
    {"编程模式"},
    {"获取帮助"},
    {"返回"}};
char (*menuList[])[40] = {  // 菜单列表
    mainMenuList,
    mapTypeMenuList,
    defaultMapMenuList,
    customMapMenuList,
    customOperationMenuList,
    saveLoadMenuList,
    controlModeMenuList};

static void mainMenu( MENU *pmenu ) ;                // 主菜单函数
static void mapTypeMenu( MENU *pmenu ) ;             // 地图类型选择菜单函数
static void defaultMapMenu( MENU *pmenu ) ;          // 默认地图菜单函数
static void customMapMenu( MENU *pmenu ) ;           // 自定义地图菜单函数
static void customOperationMenu() ;             // 自定义地图操作菜单函数
static void saveLoadMenu() ;                    // 存档读取菜单函数
static void controlModeMenu() ;                 // 控制模式菜单函数
static int listNumCount( MENU menu ) ;       // 计算菜单选项数量
static void printMenu( MENU menu , int num ) ;                 // 打印菜单
static int cursorChoose( COORD loc , int num ) ;                  // 菜单光标移动控制
static void freshCursor( COORD loc , int num , int pos ) ;        // 菜单光标移动显示与控制

extern void runMenu()
{
    static void (*treeMenu[])( MENU * ) = { // 主干函数函数指针数组
        mainMenu,
        mapTypeMenu,
        defaultMapMenu,
        customMapMenu};
    
    MENU menu = MAIN_MENU;
    int menuRunFlag = 1 ;
    while( menuRunFlag )
    {
        treeMenu[ menu ]( &menu ) ;

        if( menu == -1 ) break ;
    }
}

static int listNumCount( MENU menu )
{
    switch( menu )
    {
        case MAIN_MENU:
            return sizeof( mainMenuList ) / sizeof( mainMenuList[0] ) ;
        case MAP_TYPE_MENU:
            return sizeof( mapTypeMenuList ) / sizeof( mapTypeMenuList[0] ) ;
        case DEFAULT_MAP_MENU:
            return sizeof( defaultMapMenuList ) / sizeof( defaultMapMenuList[0] ) ;
        case CUSTOM_MAP_MENU:
            return sizeof( customMapMenuList ) / sizeof( customMapMenuList[0] ) ;
        case CUSTOM_OPERATION_MENU:
            return sizeof( customOperationMenuList ) / sizeof( customOperationMenuList[0] ) ;
        case SAVE_LOAD_MENU:
            return sizeof( saveLoadMenuList ) / sizeof( saveLoadMenuList[0] ) ;
        case CONTROL_MODE_MENU:
            return sizeof( controlModeMenuList ) / sizeof( controlModeMenuList[0] ) ;
    }
    return -1 ;
}

static void printMenu( MENU menu , int num )
{
    for( int i = 0 ; i < num ; i ++ )
    {
        printf("   ") ;
        printf( "%s\n" , menuList[ menu ][ i ] ) ;
    }
    printf("\nw上移光标,s下移光标,输入<Enter>选中\n");
}

static void freshCursor( COORD loc , int num , int pos )
{
    for( int i = 0 ; i < num ; i ++ )   // 刷新光标位置，在pos位置打印光标
    {
        MoveCursorTo( loc.X , loc.Y + i ) ;
        if( i == pos ) putchar('>') ;
        else putchar(' ') ;
    }
}

static int cursorChoose( COORD loc , int num )
{
    int pos = 0 ;
    freshCursor( loc , num , pos ) ;
    while( 1 )      // 光标移动控制，反复读入直到选中，返回选中光标选项的序号
    {
        char ch = getch() ;
        if( ch == 'w' && pos > 0 ) pos -- ;
        else if( ch == 's' && pos < num - 1 ) pos ++ ;
        else if( ch == '\r' ) return pos ;
        freshCursor( loc , num , pos ) ;
    }
}

static void mainMenu( MENU *pmenu )
{
    system("cls");
    int listNum = listNumCount( MAIN_MENU ) ;
    COORD loc = { 0 , 0 } ;     // 菜单光标位置
    int x = 0 , y = 0 ;

    /* 菜单信息打印与存储 */
    printf("迷宫大冒险！Version:2.1\n\n") ;
    GetCursorPosition( &x , &y ) , loc.X = x , loc.Y = y ;
    printMenu( MAIN_MENU , listNum ) ;

    /* 获取菜单选中结果 */
    int op = cursorChoose( loc , listNum ) ;

    /* 菜单选项处理 */
    switch( op )
    {
        case 0:     // 开始游戏
            *pmenu = MAP_TYPE_MENU ;
            break;
        case 1:     // 获取帮助
            system("cls");
            printf("help file 1 施工中\n") ;    // TODO:帮助文档1
            system("pause");
            break;
        case 2:     // 退出游戏
            *pmenu = -1 ;   
            break;
    }
}

static void mapTypeMenu( MENU *pmenu )
{
    system("cls");
    int listNum = listNumCount( MAP_TYPE_MENU ) ;
    COORD loc = { 0 , 0 } ;     // 菜单光标位置
    int x = 0 , y = 0 ;

    /* 菜单信息打印与存储 */
    printf("选择你要游玩的地图类型\n\n") ;
    GetCursorPosition( &x , &y ) , loc.X = x , loc.Y = y ;
    printMenu( MAP_TYPE_MENU , listNum ) ;

    /* 获取菜单选中结果 */
    int op = cursorChoose( loc , listNum ) ;

    /* 菜单选项处理 */
    switch( op )
    {
        case 0:     // 默认地图关卡
            *pmenu = DEFAULT_MAP_MENU ;
            break;
        case 1:     // 自定义地图关卡
            *pmenu = CUSTOM_MAP_MENU ;
            break;
        case 2:     // 返回主菜单
            *pmenu = MAIN_MENU ;
            break;
    }
}

static void defaultMapMenu( MENU *pmenu )
{
    system("cls");
    int listNum = listNumCount( DEFAULT_MAP_MENU ) ;
    COORD loc = { 0 , 0 } ;     // 菜单光标位置
    int x = 0 , y = 0 ;

    /* 菜单信息打印与存储 */
    printf("选择你要游玩的默认地图\n\n") ;
    GetCursorPosition( &x , &y ) , loc.X = x , loc.Y = y ;
    printMenu( DEFAULT_MAP_MENU , listNum ) ;

    /* 获取菜单选中结果 */
    int op = cursorChoose( loc , listNum ) ;

    /* 菜单选项处理 */
    switch( op )
    {
        case 0:     // 地图一
            system("cls");
            system("pause");    // TODO:新游戏进入接口施工
            break;
        case 1:     // 地图二
            break;
        case 2:     // 地图三
            break;
        case 3:     // 返回地图类型菜单
            *pmenu = MAP_TYPE_MENU ;
            break;
    }
}

static void customMapMenu( MENU *pmenu )
{
    system("cls");
    int listNum = listNumCount( CUSTOM_MAP_MENU ) ;
    COORD loc = { 0 , 0 } ;     // 菜单光标位置
    int x = 0 , y = 0 ;

    /* 菜单信息打印与存储 */
    printf("选择你要游玩的自定义地图\n\n") ;
    GetCursorPosition( &x , &y ) , loc.X = x , loc.Y = y ;
    printMenu( CUSTOM_MAP_MENU , listNum ) ;

    /* 获取菜单选中结果 */
    int op = cursorChoose( loc , listNum ) ;

    /* 菜单选项处理 */
    switch( op )
    {
        case 0:     // 自定义地图一
            system("cls");
            system("pause");    // TODO:新自定义游戏进入接口施工
            break;
        case 1:     // 自定义地图二
            break;
        case 2:     // 自定义地图三
            break;
        case 3:     // 返回地图类型菜单
            *pmenu = MAP_TYPE_MENU ;
            break;
    }
}

static void customOperationMenu()
{

}

static void saveLoadMenu()
{

}

static void controlModeMenu()
{

}

int main()
{
    system("cls");
    system("mode con: cols=80 lines=30"); // 设置终端窗口大小
    HideConsoleCursor();
    printf("迷宫大冒险！Version:2.1\n\n") ;
    system("pause");
    runMenu() ;
    return 0;
}