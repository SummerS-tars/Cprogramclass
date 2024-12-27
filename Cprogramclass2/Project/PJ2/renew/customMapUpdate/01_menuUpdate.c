#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>
#include "01_menuUpdate.h"
#include "02_cursorOperation.h"
#include "03_mapAndPlayerStatus.h"
#include "04_mapCustomUpdate.h"

/* 菜单列表 */
static char mainMenuList[][40] = { // 主菜单列表
    {"开始游戏"},
    {"获取帮助"},
    {"退出游戏"}};
static char mapTypeMenuList[][40] = { // 地图类型菜单列表
    {"默认地图关卡"},
    {"自定义地图关卡"},
    {"返回主菜单"}};
static char defaultMapMenuList[][40] = { // 默认地图关卡菜单列表
    {"地图一"},
    {"地图二"},
    {"地图三"},
    {"返回地图类型菜单"}};
static char customMapMenuList[][40] = { // 自定义地图关卡菜单列表
    {"自定义地图一"},
    {"自定义地图二"},
    {"自定义地图三"},
    {"获取帮助"},
    {"返回地图类型菜单"}};
static char customOperationMenuList[][40] = { // 自定义操作菜单列表
    {"开始游玩"},
    {"开始编辑"},
    {"重置地图"},
    {"返回自定义菜单"}};
static char saveLoadMenuList[][40] = { // 存档菜单列表
    {"继续上次游戏"},
    {"开始新游戏"},
    {"清除存档"},
    {"返回"}};
static char controlModeMenuList[][40] = { // 控制模式菜单列表
    {"实时模式"},
    {"编程模式"},
    {"获取帮助"},
    {"返回"}};
static char editProgressMenuList[][40] = { // 编辑进度菜单列表
    {"继续编辑"},
    {"开始新地图"},
    {"返回"}};
char (*menuList[])[40] = {  // 菜单列表
    mainMenuList,
    mapTypeMenuList,
    defaultMapMenuList,
    customMapMenuList,
    customOperationMenuList,
    saveLoadMenuList,
    controlModeMenuList,
    editProgressMenuList};

static void mainMenu( MENU *pmenu ) ;                // 主菜单函数
static void mapTypeMenu( MENU *pmenu ) ;             // 地图类型选择菜单函数
static void defaultMapMenu( MENU *pmenu ) ;          // 默认地图菜单函数
static void customMapMenu( MENU *pmenu ) ;           // 自定义地图菜单函数
static void customOperationMenu( int mapOrder ) ;             // 自定义地图操作菜单函数
static int saveLoadMenu( int mapOrder ) ;                    // 存档读取菜单函数
static int controlModeMenu() ;                 // 控制模式菜单函数
static int editProgressMenu() ;                // 编辑进度菜单函数
static int listNumCount( MENU menu ) ;       // 计算菜单选项数量
static void printMenu( MENU menu , int num ) ;                 // 打印菜单
static int cursorChoose( COORD loc , int num ) ;                  // 菜单光标移动控制
static void freshCursor( COORD loc , int num , int pos ) ;        // 菜单光标移动显示与控制
static void defaultMapStatus( int mapOrder , int *status ) ;                     // 默认地图存档状态显示
static void customMapStatus( int customMapOrder , int *status ) ;      // 自定义地图存档状态显示
static int getMapStatus( int mapOrder ) ;  // 获取菜单打印补充信息
static void startGame( int mapOrder ) ;    // 游戏开始函数
static void welcome() ;   // 欢迎界面

// TODO:欢迎界面内容可以更丰富一下
static void welcome()
{
    system("cls");
    printf("迷宫大冒险！Version:2.1\n\n") ;
    system("pause");
}

// 菜单运行控制主函数
extern void runMenu()
{
    static void (*treeMenu[])( MENU * ) = { // 主干函数函数指针数组
        mainMenu,
        mapTypeMenu,
        defaultMapMenu,
        customMapMenu};

    system("cls");
    system("mode con: cols=100 lines=50"); // 设置终端窗口大小
    HideConsoleCursor();
    welcome();    
    
    MENU menu = MAIN_MENU;
    int menuRunFlag = 1 ;
    while( menuRunFlag )
    {
        treeMenu[ menu ]( &menu ) ;

        if( menu == -1 ) break ;
    }
    ShowConsoleCursor();
    system("cls");
}

// 计算菜单选项数量
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
        case EDIT_PROGRESS_MENU:
            return sizeof( editProgressMenuList ) / sizeof( editProgressMenuList[0] ) ;
    }
    return -1 ;
}

// 菜单打印
static void printMenu( MENU menu , int num )
{
    for( int i = 0 ; i < num ; i ++ )
    {
        printf("   ") ;
        printf( "%s\n" , menuList[ menu ][ i ] ) ;
    }
    printf("\n<w>上移光标,<s>下移光标,<Enter>选中\n");
}

// 菜单光标移动显示与控制
static void freshCursor( COORD loc , int num , int pos )
{
    for( int i = 0 ; i < num ; i ++ )   // 刷新光标位置，在pos位置打印光标
    {
        MoveCursorTo( loc.X , loc.Y + i ) ;
        if( i == pos ) putchar('>') ;
        else putchar(' ') ;
    }
}

// 菜单光标移动控制
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

// 主菜单函数
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

// 地图类型选择菜单函数
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

// 默认地图菜单函数
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
    enum { DefaultMap1 = 1 , DefaultMap2 = 2 , DefaultMap3 = 3 } ;
    switch( op )
    {
        case 0:     // 地图一
            startGame( DefaultMap1 ) ;
            break;
        case 1:     // 地图二
            startGame( DefaultMap2 ) ;
            break;
        case 2:     // 地图三
            startGame( DefaultMap3 ) ;
            break;
        case 3:     // 返回地图类型菜单
            *pmenu = MAP_TYPE_MENU ;
            break;
    }
}

// 自定义地图菜单函数
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
    enum { CustomMap1 = 1 , CustomMap2 = 2 , CustomMap3 = 3 } ;
    switch( op )
    {
        case 0:     // 自定义地图一
            customOperationMenu( CustomMap1 ) ;
            break;
        case 1:     // 自定义地图二
            customOperationMenu( CustomMap2 ) ;
            break;
        case 2:     // 自定义地图三
            customOperationMenu( CustomMap3 ) ;
            break;
        case 3:     // 获取帮助
            system("cls");
            printf("help file 2 施工中\n") ;    // TODO:帮助文档2
            system("pause");
            break;
        case 4:     // 返回地图类型菜单
            *pmenu = MAP_TYPE_MENU ;
            break;
    }
}

// 默认地图状态获取函数
static void defaultMapStatus( int defaultMapOrder , int *status )
{
    enum { NOT_SAVED = 0 , SAVED = 1 } ;
    FILE *mapfp = NULL ;
    mapfp = fopen( mapProgressSave[ defaultMapOrder - 1 ] , "r" ) ;
    char playFlag = 0 ;
    playFlag = fgetc( mapfp ) ;
    fclose( mapfp ) ;
    if( playFlag == '*' ) *status = NOT_SAVED ;// 未游玩
    else *status = SAVED ; // 已游玩
}

// 自定义地图状态获取函数
static void customMapStatus( int customMapOrder , int *status )
{
    enum { EDITED_NOT_SAVED = 0 , EDITED_SAVED = 1 , UNEDITED = 2 , EDITED_UNFINISHED = 3 } ;
    FILE *mapfp = NULL ;
    mapfp = fopen( mapName[ customMapOrder + 2 ] , "r" ) ;
    char editFlag = 0 , finishFlag = 0 ;
    editFlag = fgetc( mapfp ) ;
    fseek( mapfp , -1L , SEEK_END ) ;
    finishFlag = fgetc( mapfp ) ;
    if( editFlag == '*' )  // 未编辑
    {
        *status = UNEDITED ;
    }
    else if( finishFlag == ']' ) // 已编辑但未完成
    {
        *status = EDITED_UNFINISHED ;
    }
    else // 已编辑
    {
        mapfp = fopen( mapProgressSave[ customMapOrder + 2 ] , "r" ) ;
        char playFlag = 0 ;
        playFlag = fgetc( mapfp ) ;
        fclose( mapfp ) ;
        if( playFlag == '*' ) *status = EDITED_NOT_SAVED ;// 未游玩
        else *status = EDITED_SAVED ; // 已游玩
    }
}

// 获取判断打印标志，返回值DEFAULT = 0 , SAVED = 1 , UNEDITED = 2
// 所有地图，理解时同意按照默认地图1-3，自定义地图1-3的顺序，在参数调用时映射至1-6以符合数组索引
static int getMapStatus( int mapOrder )
{
    int STATUS = 0 ;
    if( mapOrder >= 1 && mapOrder <= 3 ) defaultMapStatus( mapOrder  , &STATUS ) ;
    else customMapStatus( mapOrder - 3 , &STATUS ) ;
    return STATUS ;
}

// 自定义地图操作菜单函数
static void customOperationMenu( int customMapOrder )
{
    system("cls");
    int listNum = listNumCount( CUSTOM_OPERATION_MENU ) ;
    COORD loc = { 0 , 0 } ;     // 菜单光标位置
    int x = 0 , y = 0 ;

    /* 菜单信息打印与存储 */
    enum { EDITED_NOT_SAVED = 0 , EDITED_SAVED = 1 , UNEDITED = 2 , EDITED_NOT_SAVED } STATUS ;
    char mapName[][20] = { "自定义地图一" , "自定义地图二" , "自定义地图三" } ;
    char addStatus[][20] = { "(已编辑)" , "(已游玩)" , "(未编辑)" , "(编辑未完成)" } ;
    STATUS = getMapStatus( customMapOrder + 3 ) ;
    
    printf("选中：%s\n状态：%s\n\n" , mapName[ customMapOrder - 1 ] , addStatus[ STATUS ] ) ;
    GetCursorPosition( &x , &y ) , loc.X = x , loc.Y = y ;
    for( int i = (STATUS == UNEDITED ? 1 : 0) ; i < listNum ; i ++ ) // 未编辑状态下不显示开始游玩选项
    {
        printf("   ") ;
        printf( "%s\n" , menuList[ CUSTOM_OPERATION_MENU ][ i ] ) ;
    }
    if( STATUS == UNEDITED || STATUS == EDITED_NOT_SAVED ) listNum -- ;
    printf("\n<w>上移光标,<s>下移光标,<Enter>选中\n");

    /* 获取菜单选中结果 */
    int op = cursorChoose( loc , listNum ) ;
    if( STATUS == UNEDITED || STATUS == EDITED_NOT_SAVED ) op ++ ;

    /* 菜单选项处理 */
    switch( op )
    {
        case 0:     // 开始游玩
            startGame( customMapOrder + 3 ) ;
            break;
        case 1:     // 开始编辑  // TODO:测试
            if( STATUS == UNEDITED ) mapCustomEdit( customMapOrder , 0 ) ;
            else
            {
                int progressOrder = editProgressMenu() ;
                progressSaveInit( customMapOrder + 2 ) ; // 重新编辑时初始化存档
                switch( progressOrder )
                {
                    case 0: // 继续编辑
                        mapCustomEdit( customMapOrder , 1 ) ;
                        break;
                    case 1: // 开始新地图
                        mapCustomEdit( customMapOrder , 0 ) ;
                        break;
                    case 2: // 返回
                        break;
                }
            }
            break;
        case 2:     // 重置地图
            mapCustomIni( customMapOrder , 1 ) ;
            break;
        case 3:     // 返回自定义菜单
            break;
    }
}

// 编辑进度菜单函数
static int editProgressMenu()
{
    system("cls");
    int listNum = listNumCount( EDIT_PROGRESS_MENU ) ;
    COORD loc = { 0 , 0 } ;     // 菜单光标位置
    int x = 0 , y = 0 ;

    /* 菜单信息打印与存储 */
    printf("此地图已经经过编辑过，选择你要进行的操作\n\n") ;
    GetCursorPosition( &x , &y ) , loc.X = x , loc.Y = y ;
    printMenu( EDIT_PROGRESS_MENU , listNum ) ;

    /* 获取菜单选中结果 */
    int op = cursorChoose( loc , listNum ) ;

    /* 菜单选项处理 */
    return op ;
}

// 存档读取菜单函数
static int saveLoadMenu( int mapOrder )
{
    system("cls");
    int listNum = listNumCount( SAVE_LOAD_MENU ) ;
    COORD loc = { 0 , 0 } ;     // 菜单光标位置
    int x = 0 , y = 0 ;

    /* 菜单信息打印与存储 */
    char timeStr1[64] = {0} ;
    char timeStr2[64] = {0} ;
    int treasureInfoPlayer , treasureInfoMap ;
    FILE *mapfp = NULL ;
    mapfp = fopen( mapProgressSave[ mapOrder - 1 ] , "r" ) ;
    fscanf( mapfp , "%s %s\n" , timeStr1 , timeStr2 ) ;              // 写入保存时间
    fscanf( mapfp , "%d %d\n" , &treasureInfoPlayer , &treasureInfoMap ) ; // 读取宝藏信息
    fclose( mapfp ) ;

    printf("上次游玩时间：%s %s\n" , timeStr1 , timeStr2 ) ;
    printf("上次游玩宝藏：%d/%d\n\n" , treasureInfoPlayer , treasureInfoMap ) ;
    GetCursorPosition( &x , &y ) , loc.X = x , loc.Y = y ;
    printMenu( SAVE_LOAD_MENU , listNum ) ;

    /* 获取菜单选中结果 */
    int op = cursorChoose( loc , listNum ) ;

    /* 菜单选项处理 */
    return op ;
}

// 控制模式菜单函数
static int controlModeMenu()
{
    system("cls");
    int listNum = listNumCount( CONTROL_MODE_MENU ) ;
    COORD loc = { 0 , 0 } ;     // 菜单光标位置
    int x = 0 , y = 0 ;

    /* 菜单信息打印与存储 */
    printf("选择你要使用的控制模式\n\n") ;
    GetCursorPosition( &x , &y ) , loc.X = x , loc.Y = y ;
    printMenu( CONTROL_MODE_MENU , listNum ) ;

    /* 获取菜单选中结果 */
    int op = cursorChoose( loc , listNum ) ;

    /* 菜单选项处理 */
    return op ;
}

// 游戏开始函数
static void startGame( int mapOrder )
{
    enum { UNSAVED = 0 , SAVED = 1 } mapStatus ;
    mapStatus = getMapStatus( mapOrder ) ;

    /* 是否继续游戏 */
    int keepProgress = 0;
    if( mapStatus == SAVED )
    {
        int progressOrder = saveLoadMenu(mapOrder);
        switch (progressOrder) 
        {
            case 0: // 继续上次游戏
                keepProgress = 1;
                break;
            case 1: // 开始新游戏
                keepProgress = 0;
                break;
            case 2: // 清除存档
                progressSaveInit(mapOrder);
                return;
            case 3: // 返回
                return;
        }
    }

    /* 选择控制模式 */
    int gameMode = 0 ;
    while( (gameMode = controlModeMenu()) == 2 )
    {
        system("cls");
        printf("help file 3 施工中\n") ;    // TODO:帮助文档3
        system("pause");
        return;
    }
    if (gameMode == 3)
        return;

    /* 初始化 */
    struct mapInfo map;
    struct playerInfo player;
    mapIni(&map);
    if (!mapInput(&map, mapOrder))
        return; // 读取地图失败则直接返回
    playerIni(&player, &map);
    if( keepProgress )
        progressLoad( &player , &map , mapOrder ) ;
    mapPrint(&map);

    /* 按控制模式进入游戏主体 */
    if (gameMode == 0)
        playerMove(&player, &map, mapOrder);
    else if (gameMode == 1)
        playerMovePro(&player, &map, mapOrder);

    /* 完成游戏，返回菜单 */
    welcome();
}
