#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include "01_menuUpdate.h"
#include "02_cursorOperation.h"
#include "03_mapAndPlayerStatus.h"
#include "04_mapCustomUpdate.h"

// 计算菜单选项数量
#define LISTNUMCOUNT(listname) (sizeof(listname)/sizeof(listname[0]))

/* 菜单列表 */
static char mainMenuList[][40] = { // 主菜单列表
    {"开始游戏"},
    {"获取帮助"},
    {"退出游戏"}};
static char mapChooseMenuList[][40] = { // 地图选择菜单
    {"新建地图"},
    {"返回主菜单"}};
static char mapOperationMenuList[][40] = { // 自定义操作菜单列表
    {"开始游玩"},
    {"开始编辑"},
    {"重置地图"},
    {"删除地图"},
    {"重命名地图"},
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
static char boolSelectMenuList[][40] = { // 是否选择菜单列表
    {"确认"},
    {"取消"}};
char (*menuList[])[40] = {  // 菜单列表
    mainMenuList,
    mapChooseMenuList,
    mapOperationMenuList,
    saveLoadMenuList,
    controlModeMenuList,
    editProgressMenuList,
    boolSelectMenuList};
char mapName[10][64] ;  // 地图文件名
char mapPath[10][64] ;  // 地图文件路径
char savePath[10][64] ; // 地图进度文件路径
static int mapNumbers ; // 地图数量

/* 功能类 */
static void welcome() ;   // 欢迎界面
static int getMapStatus( int mapOrder ) ;  // 获取菜单打印补充信息
static void mapNameGet() ; // 获取地图名称并维护mapName数组和mapProgressSave数组和mapNumbers
static void mapNewCreate() ; // 新建地图函数
static void mapNameChange( int mapOrder ) ; // 地图名称更改函数
static void mapRemove( int mapOrder ) ; // 删除地图函数
static void printMenu( MENU menu , int num ) ;                 // 打印菜单
static int cursorChoose( COORD loc , int num ) ;                  // 菜单光标移动控制
static void freshCursor( COORD loc , int num , int pos ) ;        // 菜单光标移动显示与控制
static void freshCursor( COORD loc , int num , int pos ) ;        // 菜单光标移动显示与控制
static void startGame( int mapOrder ) ;    // 游戏开始函数
static void printFile( int num ) ; // 打印文档（只是用来集合比较繁杂的打印操作）

/* 菜单本体 */
static void mainMenu( MENU *pmenu ) ;                // 主菜单函数
static void mapChooseMenu( MENU *pmenu ) ; // 地图选择菜单函数
static void mapOperationMenu( int mapOrder ) ;             // 地图操作菜单函数
static int saveLoadMenu( int mapOrder ) ;                    // 存档读取菜单函数
static int controlModeMenu() ;                 // 控制模式菜单函数
static int editProgressMenu() ;                // 编辑进度菜单函数



// 菜单运行控制主函数
extern void runMenu()
{
    mapNameGet() ; // 获取地图名称
    static void (*treeMenu[])( MENU * ) = { // 主干函数函数指针数组
        mainMenu,
        mapChooseMenu};

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

// 获取地图名称并维护mapName数组和mapProgressSave数组和mapNumbers
static void mapNameGet() 
{
    memset(mapName, 0, sizeof(mapName));
    memset(mapPath, 0, sizeof(mapPath));
    memset(savePath, 0, sizeof(savePath));
    mapNumbers = 0;

    char *mapDirPath = "./map";
    struct dirent *entry;

    DIR *dp = opendir(mapDirPath);
    if (dp == NULL) {
        perror("opendir");
        return;
    }

    int fileCount = 0;
    while ((entry = readdir(dp))) {
        char fullPath[1024];
        snprintf(fullPath, sizeof(fullPath), "%s/%s", mapDirPath , entry->d_name);
        struct stat fileStat;
        if (stat(fullPath, &fileStat) == 0 && S_ISREG(fileStat.st_mode)) {
            char *dot = strrchr(entry->d_name, '.');
            if (dot) {
                *dot = '\0';
            }
            snprintf(mapName[fileCount], sizeof(mapName[fileCount]), "%s", entry->d_name);
            snprintf(mapPath[fileCount], sizeof(mapPath[fileCount]), "./map/%s.map", entry->d_name);
            snprintf(savePath[fileCount], sizeof(savePath[fileCount]), "./save/%s.save", entry->d_name);

            fileCount++;
        }
    }

    closedir(dp);
    mapNumbers = fileCount;
}

// 地图名称更改函数
static void mapNameChange( int mapOrder )
{
    // 初始定义
    mapOrder--; // 地图序号映射为数组下标
    char oldMapPath[64] = {0};
    char oldProgressSavePath[64] = {0};
    char newMapPath[64] = {0};
    char newProgressSavePath[64] = {0};
    snprintf(oldMapPath, sizeof(oldMapPath), "%s", mapPath[mapOrder]);
    snprintf(oldProgressSavePath, sizeof(oldProgressSavePath), "%s", savePath[mapOrder]);

    // 输入新地图名称
    system("cls");
    printf("当前地图名称: %s\n", mapName[mapOrder]);
    char newMapName[40] = {0};
    printf("请输入新的地图名称: ");
    ShowConsoleCursor();
    scanf("%39s", newMapName);
    HideConsoleCursor();
    
    // 检查地图名称是否已存在
    for (int i = 0; i < mapNumbers; i++) {
        if (strcmp( mapName[i], newMapName ) == 0) {
            system("cls");
            printf("地图名称已存在，请输入不同的名称。\n");
            system("pause");
            system("cls");
            return;
        }
    }
    snprintf(newMapPath, sizeof(newMapPath), "./map/%s.map", newMapName);
    snprintf(newProgressSavePath, sizeof(newProgressSavePath), "./save/%s.save", newMapName );

    if (rename(oldMapPath, newMapPath) == 0) {
        system("cls");
        printf("地图名称已更改为: %s\n", newMapName );
        system("pause");
    } else {
        perror("地图名称更改失败");
    }
    if( rename( oldProgressSavePath , newProgressSavePath ))
        perror("存档文件名称更改失败");
}

// 新建地图函数
static void mapNewCreate()
{
    system("cls");
    printf("请输入新地图名称: ");

    // 读取新地图名称
    ShowConsoleCursor();
    char newMapName[40] = {0};
    scanf("%39s", newMapName);
    HideConsoleCursor();
    system("cls") ;

    // 检查地图名称是否已存在
    for (int i = 0; i < mapNumbers; i++) {
        if (strcmp(mapName[i], newMapName) == 0) {
            printf("地图名称已存在，请输入不同的名称。\n");
            system("pause");
            return;
        }
    }

    // 创建地图文件和存档文件
    snprintf(mapName[mapNumbers], sizeof(mapName[mapNumbers]), "%s", newMapName);
    snprintf(mapPath[mapNumbers], sizeof(mapPath[mapNumbers]), "./map/%s.map", newMapName);
    snprintf(savePath[mapNumbers], sizeof(savePath[mapNumbers]), "./save/%s.save", newMapName);
    FILE *mapFile = fopen(mapPath[mapNumbers], "w");
    if (mapFile == NULL) {
        perror("新建地图文件失败");
        return;
    }
    fclose(mapFile);
    FILE *saveFile = fopen(savePath[mapNumbers], "w");
    if (saveFile == NULL) {
        perror("新建存档文件失败");
        return;
    }
    fclose(saveFile);

    // 初始化
    mapNumbers ++ ;
    mapCustomIni( mapNumbers , 0 ); // 初始化地图
    progressSaveInit( mapNumbers ) ;    // 初始化存档
    mapNameGet();   // 更新地图名称
    printf("新地图创建成功: <%s>\n\n", newMapName);

    printf("当前地图列表:\n");
    for(int i = 0 ; i < mapNumbers ; i ++ )
    {
        printf("%d.<%s>\n", i+1 , mapName[i]);
    }
    system("pause");
    system("cls");
}

// 删除地图函数
static void mapRemove( int mapOrder )
{
    mapOrder--; // 地图序号映射为数组下标
    char RemoveMapPath[64] = {0};
    snprintf(RemoveMapPath, sizeof(RemoveMapPath), mapPath[mapOrder]);
    char RemoveSavePath[64] = {0};
    snprintf(RemoveSavePath, sizeof(RemoveSavePath), savePath[mapOrder]);
    system("cls");
    printf("您选择要删除地图是: <%s>\n", mapName[mapOrder]);
    printf("请确认是否删除");
    int boolFlag = boolSelectMenu();

    if (boolFlag) {
        if (remove(RemoveMapPath)== 0) {
            printf("地图文件已删除\n");
        } else {
            perror("地图文件删除失败");
        }
        if (remove(RemoveSavePath) == 0) {
            printf("存档文件已删除\n");
        } else {
            perror("存档文件删除失败");
        }
    } else {
        printf("取消删除\n");
    }
    system("pause");
}

// 欢迎界面
static void welcome()   // TODO:欢迎界面内容可以更丰富一下
{
    system("cls");
    printFile( 1 );
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
    int listNum = LISTNUMCOUNT( mainMenuList ) ;
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
            *pmenu = MAP_CHOOSE_MENU ;
            break;
        case 1:     // 获取帮助
            system("cls");
            printFile( 2 ) ;    // 调用帮助文档1
            break;
        case 2:     // 退出游戏
            *pmenu = -1 ;   
            break;
    }
}

// 地图选择菜单函数
static void mapChooseMenu( MENU *pmenu )
{
    system("cls");
    int listNum = mapNumbers + LISTNUMCOUNT( mapChooseMenuList ) ;
    COORD loc = { 0 , 0 } ;     // 菜单光标位置
    int x = 0 , y = 0 ;

    /* 菜单信息打印与存储 */
    printf("地图选择\n\n") ;
    GetCursorPosition( &x , &y ) , loc.X = x , loc.Y = y ;
    for( int i = 0 ; i < mapNumbers ; i ++ )
    {
        printf("   ") ;
        printf("%d.<%s>\n" , i + 1 , mapName[ i ] ) ;
    }
    printMenu( MAP_CHOOSE_MENU , LISTNUMCOUNT( mapChooseMenuList ) ) ;

    /* 获取菜单选中结果 */
    int op = cursorChoose( loc , listNum ) ;

    /* 菜单选项处理 */
    if( op < mapNumbers ) // 选择地图
    {
        mapOperationMenu( op + 1 ) ;
    }
    else
    {
        switch( op - mapNumbers )
        {
            case 0:     // 新建地图
                mapNewCreate() ;
                break;
            case 1:     // 返回主菜单
                *pmenu = MAIN_MENU ;
                break;
        }
    }
}

// 是否状态获取菜单函数
extern int boolSelectMenu()
{
    int listNum = LISTNUMCOUNT( boolSelectMenuList ) ;
    COORD loc = { 0 , 0 } ;     // 菜单光标位置
    int x = 0 , y = 0 ;

    /* 菜单信息打印与存储 */
    printf("\n\n") ;
    GetCursorPosition( &x , &y ) , loc.X = x , loc.Y = y ;
    printMenu( BOOL_SELECT_MENU , listNum ) ;

    /* 获取菜单选中结果 */
    int op = cursorChoose( loc , listNum ) ;

    /* 菜单选项处理 */
    system("cls");
    if( op == 0 ) return 1 ;
    else return 0 ;
}

// 获取判断打印标志，返回值DEFAULT = 0 , SAVED = 1 , UNEDITED = 2 , EDITED_UNFINISHED = 3
static int getMapStatus( int mapOrder )
{
    enum { EDITED_NOT_SAVED = 0 , EDITED_SAVED = 1 , UNEDITED = 2 , EDITED_UNFINISHED = 3 } STATUS ;

    // 地图状态获取
    FILE *mapfp = NULL ;
    mapfp = fopen( mapPath[ mapOrder - 1 ] , "r" ) ;
    char editFlag = 0 , finishFlag = 0 ;
    editFlag = fgetc( mapfp ) ;
    fseek( mapfp , -1L , SEEK_END ) ;
    finishFlag = fgetc( mapfp ) ;
    fclose( mapfp ) ;
    if( editFlag == '*' )  // 未编辑
    {
        STATUS = UNEDITED ;
    }
    else if( finishFlag == ']' ) // 已编辑但未完成
    {
        STATUS = EDITED_UNFINISHED ;
    }
    else // 已编辑
    {
        mapfp = fopen( savePath[ mapOrder - 1 ] , "r" ) ;
        char playFlag = 0 ;
        playFlag = fgetc( mapfp ) ;
        fclose( mapfp ) ;
        if( playFlag == '*' ) STATUS = EDITED_NOT_SAVED ;// 未游玩
        else STATUS = EDITED_SAVED ; // 已游玩
    }

    return STATUS ;
}

// 地图操作菜单函数
static void mapOperationMenu( int mapOrder )
{
    system("cls");
    int listNum = LISTNUMCOUNT( mapOperationMenuList ) ;
    COORD loc = { 0 , 0 } ;     // 菜单光标位置
    int x = 0 , y = 0 ;

    /* 菜单信息打印与存储 */
    enum { EDITED_NOT_SAVED = 0 , EDITED_SAVED = 1 , UNEDITED = 2 , EDITED_UNFINISHED } STATUS ;
    char addStatus[][20] = { "(已编辑)" , "(已游玩)" , "(未编辑)" , "(编辑未完成)" } ;
    STATUS = getMapStatus( mapOrder ) ;
    
    printf("选中：%s\n状态：%s\n\n" , mapName[ mapOrder - 1 ] , addStatus[ STATUS ] ) ;
    GetCursorPosition( &x , &y ) , loc.X = x , loc.Y = y ;
    int printFlag = STATUS == UNEDITED || STATUS == EDITED_UNFINISHED ; // 为1时不显示开始游玩选项
    for( int i = ( printFlag ? 1 : 0) ; i < listNum ; i ++ ) // 未编辑状态下不显示开始游玩选项   // TODO:BUG12修复，已编辑未完成状态检测补充
    {
        printf("   ") ;
        printf( "%s\n" , menuList[ MAP_OPERATION_MENU ][ i ] ) ;
    }
    if( printFlag ) listNum -- ;
    printf("\n<w>上移光标,<s>下移光标,<Enter>选中\n");

    /* 获取菜单选中结果 */
    int op = cursorChoose( loc , listNum ) ;
    if( printFlag ) op ++ ;

    /* 菜单选项处理 */
    switch( op )
    {
        case 0:     // 开始游玩
            startGame( mapOrder ) ;
            break;
        case 1:     // 开始编辑
            if( STATUS == UNEDITED ) mapCustomEdit( mapOrder , 0 ) ;
            else
            {
                int progressOrder = editProgressMenu() ;
                progressSaveInit( mapOrder ) ; // 重新编辑时初始化存档
                switch( progressOrder )
                {
                    case 0: // 继续编辑
                        mapCustomEdit( mapOrder , 1 ) ;
                        break;
                    case 1: // 开始新地图
                        mapCustomEdit( mapOrder , 0 ) ;
                        break;
                    case 2: // 返回
                        break;
                }
            }
            break;
        case 2:     // 重置地图
            mapCustomIni( mapOrder , 1 ) ;
            break;
        case 3:     // 删除地图
            mapRemove( mapOrder ) ;
            mapNameGet() ; // 更新地图名称
            break;
        case 4:
            mapNameChange( mapOrder ) ;
            mapNameGet() ; // 更新地图名称
            break;
        case 5:     // 返回地图选择菜单
            break;
    }
}

// 编辑进度菜单函数
static int editProgressMenu()
{
    system("cls");
    int listNum = LISTNUMCOUNT( editProgressMenuList ) ;
    COORD loc = { 0 , 0 } ;     // 菜单光标位置
    int x = 0 , y = 0 ;

    /* 菜单信息打印与存储 */
    printf("此地图已经经过编辑过，选择你要进行的操作\n\n") ;
    GetCursorPosition( &x , &y ) , loc.X = x , loc.Y = y ;
    printMenu( EDIT_PROGRESS_MENU , listNum ) ;

    /* 获取菜单选中结果 */
    int op = cursorChoose( loc , listNum ) ;

    /* 菜单选项处理 */
    system("cls");
    return op ;
}

// 存档读取菜单函数
static int saveLoadMenu( int mapOrder )
{
    system("cls");
    int listNum = LISTNUMCOUNT( saveLoadMenuList ) ;
    COORD loc = { 0 , 0 } ;     // 菜单光标位置
    int x = 0 , y = 0 ;

    /* 菜单信息打印与存储 */
    char timeStr1[64] = {0} ;
    char timeStr2[64] = {0} ;
    int treasureInfoPlayer , treasureInfoMap ;
    FILE *mapfp = NULL ;
    mapfp = fopen( savePath[ mapOrder - 1 ] , "r" ) ;
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
    system("cls");
    return op ;
}

// 控制模式菜单函数
static int controlModeMenu()
{
    int op = -1 ;
    do
    {
        system("cls");
        int listNum = LISTNUMCOUNT( controlModeMenuList ) ;
        COORD loc = { 0 , 0 } ;     // 菜单光标位置
        int x = 0 , y = 0 ;

        /* 菜单信息打印与存储 */
        printf("选择你要使用的控制模式\n\n") ;
        GetCursorPosition( &x , &y ) , loc.X = x , loc.Y = y ;
        printMenu( CONTROL_MODE_MENU , listNum ) ;

        /* 获取菜单选中结果 */
        op = cursorChoose( loc , listNum ) ;

        if( op == 2 )
        {
            system("cls");
            printFile( 3 );    // 调用帮助文档2
        }
    } while( op == 2 ) ;

    /* 菜单选项处理 */
    system("cls");
    return op ;
}

// 游戏开始函数
static void startGame( int mapOrder )
{
    enum { EDITED_NOT_SAVED = 0 , EDITED_SAVED = 1 , UNEDITED = 2 , EDITED_UNFINISHED = 3 } mapStatus ;
    mapStatus = getMapStatus( mapOrder ) ;

    /* 是否继续游戏 */
    int keepProgress = 0;
    if( mapStatus == EDITED_SAVED ) // 已编辑且已游玩
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
    gameMode = controlModeMenu() ;
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

// 将程序中需要大段特殊打印的部分集合在一起
static void printFile( int num )
{
    if( num == 1 )  // 欢迎界面
    {
        printf("\033[1;37m**************************************************************\n\
*                                                            *\n\
*                 \033[1m\033[1;32m 欢迎来到迷宫大冒险！！\033[1;37m                    *\n\
*                                                            *\n\
*             \033[34m在这里，你将扮演探险迷宫的勇士！\033[37m               *\n\
*              \033[34m寻找宝藏，躲避陷阱，完成探险！！\033[37m              *\n\
*                \033[5m<触发任意输入准备开始游戏>\033[0m\033[37m                  *\n\
*                                                            *\n\
*                                                            *\n\
*                     \033[31m游玩注意事项：\033[1;37m                         *\n\
*           1. 将窗口调整至全屏以确保程序正常运行            *\n\
*           2. 游玩过程中请勿随意调整窗口大小                *\n\
*                                                            *\n\
*                发布版本 : \033[1;34mVersion:2.3\033[1;37m                      *\n\
*                 制作者  : \033[1;34mTheSumst\033[1;37m                         *\n\
*                                                            *\n\
**************************************************************\n\
\033[0m");
    }
    else if( num == 2 ) // 主菜单帮助
    {
        printf("\033[1;37m**************************************************************\n\
*                                                            *\n\
*                        \033[1m\033[1;32m帮助文档 1\033[0m\033[1;37m                          *\n\
*                                                            *\n\
*             \033[34m这里是帮助文档1的内容。\033[37m                        *\n\
*                                                            *\n\
*             \033[34m1. 游戏目标：\033[37m                                  *\n\
*                \033[34m- 探索迷宫，寻找宝藏。\033[37m                      *\n\
*                \033[34m- 躲避陷阱，完成探险。\033[37m                      *\n\
*                                                            *\n\
*             \033[34m2. 操作指南：\033[37m                                  *\n\
*                \033[34m- 使用'w'上移光标。\033[37m                         *\n\
*                \033[34m- 使用's'下移光标。\033[37m                         *\n\
*                \033[34m- 按'Enter'键选中。\033[37m                         *\n\
*                                                            *\n\
*                \033[5m<触发任意输入返回主菜单>\033[0m\033[1;37m                    *\n\
*                                                            *\n\
**************************************************************\n\
\033[0m");
    }
    else if( num == 3 ) // 控制模式帮助
    {
        printf("\033[1;37m**************************************************************\n\
*                                                            *\n\
*                        \033[1m\033[1;32m帮助文档 2\033[0m\033[1;37m                          *\n\
*                                                            *\n\
*             \033[34m这里是帮助文档2的内容。\033[37m                        *\n\
*                                                            *\n\
*             \033[34m1. 控制模式：\033[37m                                  *\n\
*                \033[34m- 实时模式：实时控制角色移动。\033[37m              *\n\
*                \033[34m- 编程模式：编写程序控制角色移动。\033[37m          *\n\
*                                                            *\n\
*             \033[34m2. 存档与读取：\033[37m                                *\n\
*                \033[34m- 游戏过程中可以随时存档。\033[37m                  *\n\
*                \033[34m- 读取存档继续上次游戏。\033[37m                    *\n\
*                                                            *\n\
*                \033[5m<触发任意输入返回主菜单>\033[0m\033[1;37m                    *\n\
*                                                            *\n\
**************************************************************\n\
\033[0m");
    }
    getch();
}