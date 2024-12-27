#include "01_menuUpdate.h"
#include "02_cursorOperation.h"
#include "03_mapAndPlayerStatus.h"
#include "04_mapCustomUpdate.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

static void mapInfoSet( struct mapInfo *mapInfo );
static void acceptNumSet( int *pmin , int *pmax , int **info , int order );
static void editInit( struct mapInfo *mapInfo );
static void editPrint( int mapOrder , struct mapInfo *mapInfo , COORD *loc , int Tnum , int Dnum , int playerSetFlag );
static int editMap( struct mapInfo *mapInfo , COORD *loc , int *Tnum , int *Dnum , int *playerSetFlag );
static int editOrderGet() ;
static void editInfoPrintFresh( struct mapInfo *mapInfo , COORD *loc ,int ix , int iy , int Tnum , int Dnum , int playerSetFlag , int Order );
static void editOrderInput( struct mapInfo *mapInfo , COORD loc , int *px , int *py , int *Tnum , int *Dnum , int *playerSetFlag , int Order) ;
static void editMapReplace( struct mapInfo *mapInfo , COORD loc , int ix , int iy , int *Tnum , int *Dnum , int *playerSetFlag , int Order ) ;
static void editMapSave( struct mapInfo *mapInfo , int mapOrder , int Tnum , int Dnum , int playerSetFlag ) ;
static void editProgressLoad( struct mapInfo *mapInfo , int mapOrder , int *Tnum , int *Dnum , int *playerSetFlag ) ;

// 编辑进度读取
static void editProgressLoad( struct mapInfo *mapInfo , int mapOrder , int *Tnum , int *Dnum , int *playerSetFlag )
{
    /* 地图信息读入 */
    int openRight = mapInput( mapInfo , mapOrder ) ;      // TODO:新增地图打开检测
    if( !openRight )
    {
        system("cls") ;
        printf("地图文件打开失败\n") ;
        system("pause") ;
        return ;
    }

    /* 地图进度读入 */
    FILE *mapfp = NULL ;
    mapfp = fopen( mapPath[ mapOrder - 1 ] , "r" ) ;
    if( mapfp == NULL )
    {
        perror("Error opening file");
        return ;
    }
    for( int i = 1 ; ; i ++ )   // 定位到进度信息
    {
        fseek( mapfp , (long)-i , SEEK_END ) ;
        char ch = fgetc( mapfp ) ;
        if( ch == '[' ) break ;
    }
    fscanf( mapfp , "%d %d %d" , Tnum , Dnum , playerSetFlag ) ; // TODO:测试
    fclose(mapfp) ; // TODO:BUG4修复尝试:关闭文件
}

// 编辑地图存储
static void editMapSave( struct mapInfo *mapInfo , int mapOrder , int Tnum , int Dnum , int playerSetFlag )
{
    /* 地图编辑完成度检测 */
    int finishFlag = 0 ;
    if( Tnum == mapInfo->treasureNum && Dnum == mapInfo->trapNum && playerSetFlag ) finishFlag = 1 ;
    else finishFlag = 0 ;

    /* 选择地图文件 */
    FILE *mapfp = NULL ;
    mapfp = fopen( mapPath[ mapOrder - 1 ] , "w" ) ;
    if( mapfp == NULL )
    {
        perror("Error opening file");
        return ;
    }

    /* 写入地图信息 */
    fprintf(mapfp, "%d %d\n", mapInfo->mapRow, mapInfo->mapCol);
    fprintf(mapfp, "%d %d\n", mapInfo->treasureNum, mapInfo->trapNum);
    fprintf(mapfp, "%d %d\n", mapInfo->pRow, mapInfo->pCol );   // TODO:调整记录:根据mapInput函数的地图信息读入顺序调整
    for( int i = 0 ; i < mapInfo->mapRow ; i ++ )
    {
        for( int j = 0 ; j < mapInfo->mapCol ; j ++ )
        {
            fputc(mapInfo->map[i][j], mapfp);
        }
        fputc('\n', mapfp);
    }
    if( !finishFlag ) fprintf(mapfp, "[%d %d %d]" , Tnum , Dnum , playerSetFlag ) ; // 未完成编辑时存储编辑进度和未完成标志
    else fprintf(mapfp, "[%d %d %d*" , Tnum , Dnum , playerSetFlag ) ; // 完成编辑时存储编辑进度和完成标志
    fclose(mapfp);

    system("cls") ;
    printf("已成功编辑并完成保存！\n") ;
    system("pause") ;
    return ;
}

// 地图信息显示刷新
static void editInfoPrintFresh( struct mapInfo *mapInfo , COORD *loc , int ix , int iy , int Tnum , int Dnum , int playerSetFlag , int Order )
{
    // TODO:BUG修复记录:editInfoPrintFresh中X，Y已经调整对调
    // TODO:BUT修复记录:更改了地图坐标显示可能位数更多导致的括号不对称问题
    enum { MAP_POS = 0 , POS_INFO = 1 , PLAYER_POS = 2 , TREASURE_INFO = 3 , TRAP_INFO = 4 };
    enum { UP = 1 , DOWN , LEFT , RIGHT , WALL , EMPTY , TRAP , TREASURE , PLAYER , SAVE , QUIT } ;

    
    if( Order == UP || Order == DOWN || Order == LEFT || Order == RIGHT )   // 坐标更新，光标移动
    {
        HideConsoleCursor() ;
        MoveCursorTo( loc[POS_INFO].X , loc[POS_INFO].Y ) ;
        printf("( %2d , %2d )\n" , ix , iy ) ;
        MoveCursorTo( loc[MAP_POS].X + 2 * ix , loc[MAP_POS].Y + iy ) ;
        ShowConsoleCursor() ;
    }
    else if( Order == WALL || Order == EMPTY || Order == TRAP || Order == TREASURE || Order == PLAYER ) // 信息显示更新，地块显示更新
    {
        HideConsoleCursor() ;
        if( Order == PLAYER ) putchar('Y') ;        // TODO:BUG11修复记录:修复了玩家位置信息显示错误
        else putchar(mapInfo->map[iy][ix]) ;  // 地块信息更新    // TODO:BUG10修复记录：修复了地块信息刷新错误
        MoveCursorTo( loc[ TREASURE_INFO ].X , loc[ TREASURE_INFO ].Y ) ;
        printf("%3d/%3d" , Tnum , mapInfo->treasureNum ) ;  // 宝藏信息更新
        MoveCursorTo( loc[ TRAP_INFO ].X , loc[ TRAP_INFO ].Y ) ;
        printf("%3d/%3d" , Dnum , mapInfo->trapNum ) ;  // 陷阱信息更新
        MoveCursorTo( loc[ PLAYER_POS ].X , loc[ PLAYER_POS ].Y ) ;
        printf("                    ") ;  // 清空原位置信息
        MoveCursorTo( loc[ PLAYER_POS ].X , loc[ PLAYER_POS ].Y ) ;
        if( playerSetFlag ) printf("( %d , %d )\n" , mapInfo->pCol , mapInfo->pRow ) ;  // TODO:BUG8修复记录:修复了玩家位置信息刷新错误
        else printf("未设置\n") ;  // 玩家位置信息更新

        MoveCursorTo( loc[MAP_POS].X + 2 * ix , loc[MAP_POS].Y + iy ) ; // 光标移动
        ShowConsoleCursor() ;
    }
    else if( Order == SAVE || Order == QUIT ) return ;
    else return ;
}

// 地块替换
static void editMapReplace( struct mapInfo *mapInfo , COORD loc , int ix , int iy , int *Tnum , int *Dnum , int *playerSetFlag , int Order )
{
    // TODO:BUG修复记录:editMapReplace中X，Y已对调
    enum { UP = 1 , DOWN , LEFT , RIGHT , WALL , EMPTY , TRAP , TREASURE , PLAYER , SAVE , QUIT } ;
    char newMap = 0 ;

    // 地块赋值以及数量限制
    switch( Order )
    {
        case WALL : 
            newMap = 'W' ;
            break ;
        case EMPTY : 
            newMap = ' ' ;
            break ;
        case TRAP : 
            newMap = 'D' ; 
            if( *Dnum == mapInfo->trapNum ) return ;
            break ;
        case TREASURE : 
            newMap = 'T' ;
            if( *Tnum == mapInfo->treasureNum ) return ;
            break ;
        case PLAYER : 
            newMap = 'Y' ;
            if( *playerSetFlag )  // 若已设置玩家初始位置，则将原位置置为空地
            {
                MoveCursorTo( loc.X + 2 * mapInfo->pCol , loc.Y + mapInfo->pRow ) ;
                putchar(' ') ;
                MoveCursorTo( loc.X + 2 * ix , loc.Y + iy ) ;   // TODO:BUG11修复记录:修复了玩家位置设置时新位置打印错误的问题
            }
            break ;
    }

    // 地块替换以及信息更新
    char *oldMap = &mapInfo->map[iy][ix] ;  // TODO:BUG5修复记录:调整了ix和iy的顺序，尝试修复可能是地图信息读入时坐标错误导致的奇怪现象
    if( *oldMap == newMap ) // 新旧地图地块相等时直接退出，减少计算量
    {
        if( *oldMap == ' ' && ix == mapInfo->pCol && iy == mapInfo->pRow ) ;
        else return ;    // TODO:BUG13修复记录2：补充对于玩家初始位置地块的检测
    }

    switch( *oldMap )   // 旧地图特殊地块处理
    {
        case 'T': 
            (*Tnum) -- ;
            break ;
        case 'D': 
            (*Dnum) -- ;
            break ;
    }
    if( *playerSetFlag && ix == mapInfo->pCol && iy == mapInfo->pRow ) // TODO:BUG13修复记录：修正了对旧地图为玩家初始位置时的检测条件
        *playerSetFlag = 0 , mapInfo->pRow = mapInfo->pCol = -1 ;

    switch( newMap )        // 新地图处理
    {
        case ' ':
            *oldMap = ' ' ;
            break ;
        case 'W':
            *oldMap = 'W' ;
            break ;
        case 'T':
            *oldMap = 'T' ;
            (*Tnum) ++ ;
            break ;
        case 'D':
            *oldMap = 'D' ;
            (*Dnum) ++ ;
            break ;
        case 'Y':
            *oldMap = ' ' ;     // TODO:BUG11修复记录:修复了玩家位置设置时原位置未清空的问题
            *playerSetFlag = 1;
            mapInfo->pRow = iy , mapInfo->pCol = ix ;       // TODO:BUG9修复记录:调整了玩家位置信息存储，将行列位置调换
            break ;
    }
}

// 编辑命令处理
static void editOrderInput( struct mapInfo *mapInfo , COORD loc , int *px , int *py , int *Tnum , int *Dnum , int *playerSetFlag , int Order )
{
    // TODO:BUG修复记录,editOrderInput中X，Y已对调
    enum { UP = 1 , DOWN , LEFT , RIGHT , WALL , EMPTY , TRAP , TREASURE , PLAYER , SAVE , QUIT } ;
    switch( Order )
    {
        case UP:
            if (*py > 0) (*py)--;
            break;
        case DOWN:
            if (*py < mapInfo->mapRow - 1) (*py)++;
            break;
        case LEFT:
            if (*px > 0) (*px)--;
            break;
        case RIGHT:
            if (*px < mapInfo->mapCol - 1) (*px)++;
            break;
        case WALL:
            editMapReplace(mapInfo, loc , *px , *py , Tnum, Dnum, playerSetFlag, WALL);
            break;
        case EMPTY:
            editMapReplace(mapInfo, loc , *px , *py , Tnum, Dnum, playerSetFlag, EMPTY);
            break;
        case TRAP:
            editMapReplace(mapInfo, loc , *px , *py , Tnum, Dnum, playerSetFlag, TRAP);
            break;
        case TREASURE:
            editMapReplace(mapInfo, loc , *px , *py , Tnum, Dnum, playerSetFlag, TREASURE);
            break;
        case PLAYER:
            editMapReplace(mapInfo, loc , *px , *py , Tnum, Dnum, playerSetFlag, PLAYER);
            break;
    }
}

// 编辑命令获取
static int editOrderGet()
{
    enum { UP = 1 , DOWN , LEFT , RIGHT , WALL , EMPTY , TRAP , TREASURE , PLAYER , SAVE , QUIT } ;
    char ch = getch();
    switch (ch) 
    {
        case 'w': return UP;
        case 's': return DOWN;
        case 'a': return LEFT;
        case 'd': return RIGHT;
        case '1': return WALL;
        case '2': return EMPTY;
        case '3': return TRAP;
        case '4': return TREASURE;
        case '5': return PLAYER;
        case 'z': return SAVE;
        case 'q': return QUIT;
        default: return 0;  // 无效命令
    }
    return 0 ;  // 无效命令
}

// 编辑地图函数
static int editMap( struct mapInfo *mapInfo , COORD *loc , int *Tnum , int *Dnum , int *playerSetFlag)
{
    enum { MAP_POS = 0 , POS_INFO = 1 , PLAYER_POS = 2 , TREASURE_INFO = 3 , TRAP_INFO = 4 };
    enum { UP = 1 , DOWN , LEFT , RIGHT , WALL , EMPTY , TRAP , TREASURE , PLAYER , SAVE , QUIT } ;
    int px = 0 , py = 0 ;
    MoveCursorTo( loc[MAP_POS].X , loc[MAP_POS].Y ) ; // TODO:BUG修复记录:处理了打印完地图后光标位置不对的问题


    int runFlag = 1 ;
    int saveFlag = 0 ;
    while( runFlag )
    {
        ShowConsoleCursor() ;
        int Order = editOrderGet() ;
        if( !Order ) continue ;
        if( Order == SAVE ) saveFlag = 1 , runFlag = 0 ;
        if( Order == QUIT ) saveFlag = 0 , runFlag = 0 ;
        editOrderInput( mapInfo , loc[ MAP_POS ] , &px , &py , Tnum , Dnum , playerSetFlag , Order ) ;
        editInfoPrintFresh( mapInfo , loc , px , py , *Tnum , *Dnum , *playerSetFlag , Order ) ;
    }
    HideConsoleCursor() ;

    return saveFlag ;
}

// 编辑界面打印以及信息存储
static void editPrint( int mapOrder , struct mapInfo *mapInfo , COORD *loc , int Tnum , int Dnum , int playerSetFlag )
{
    // TODO:BUG修复记录:处理了地图坐标打印时可能出现的位数错位导致的括号输出异常问题
    enum { MAP_POS = 0 , POS_INFO = 1 , PLAYER_POS = 2 , TREASURE_INFO = 3 , TRAP_INFO = 4 };
    int tpx = 0 , tpy = 0;

    /* 打印初始信息界面并存储信息输出位置 */
    system("cls") ;
    printf("正在编辑：<%s>\n" , mapName[ mapOrder - 1 ] ) ;
    printf("当前位置: ") ;
    GetCursorPosition( &tpx , &tpy ) ;
    loc[ POS_INFO ].X = tpx , loc[ POS_INFO ].Y = tpy ; // 信息打印位置1
    printf("( %2d , %2d )\n" , 0 , 0 ) ;
    printf("玩家初始位置：") ;
    GetCursorPosition( &tpx , &tpy ) ;
    loc[ PLAYER_POS ].X = tpx , loc[ PLAYER_POS ].Y = tpy ; // 信息打印位置2
    if( playerSetFlag ) printf("( %d , %d )\n" , mapInfo->pCol , mapInfo->pRow ) ;      // TODO:BUG9修复记录:跟随玩家位置初始化调整而调整
    else printf("未设置\n") ;
    printf("宝藏数量：") ;
    GetCursorPosition( &tpx , &tpy ) ;
    loc[ TREASURE_INFO ].X = tpx , loc[ TREASURE_INFO ].Y = tpy ; // 信息打印位置3
    printf("%3d/%3d   " , Tnum , mapInfo->treasureNum ) ;
    printf("陷阱数量：") ;
    GetCursorPosition( &tpx , &tpy ) ;
    loc[ TRAP_INFO ].X = tpx , loc[ TRAP_INFO ].Y = tpy ; // 信息打印位置4
    printf("%3d/%3d\n\n" , Dnum , mapInfo->trapNum ) ;
    GetCursorPosition( &tpx , &tpy ) ;
    loc[ MAP_POS ].X = tpx , loc[ MAP_POS ].Y = tpy ; // 当前光标位置

    /* 打印地图界面 */
    for( int i = 0 ; i < mapInfo->mapRow ; i ++ )
    {
        for( int j = 0 ; j < mapInfo->mapCol ; j ++ )
        {
            printf("%c " , mapInfo->map[i][j]) ;
        }
        printf("\n");
    }

    /* 打印操作信息 */
    puts("") ;
    printf("<w>上移光标，<s>下移光标，<a>左移光标，<d>右移光标\n") ;
    printf("<1>添加墙'W'，<2>添加空地' '，<3>添加陷阱'D'，<4>添加宝藏'T'，<5>添加玩家初始位置'Y'\n") ;
    printf("<q>不保存退出编辑，<z>保存退出编辑") ;

    /* 补充输出 */
    if( playerSetFlag ) // TODO:BUG修复记录:处理了第一次打印地图可能出现的玩家未打印的问题
    {
        MoveCursorTo( loc[ MAP_POS ].X + 2 * mapInfo->pCol , loc[ MAP_POS ].Y + mapInfo->pRow ) ;   // TODO:BUG9修复记录:跟随玩家位置初始化调整而调整
        putchar('Y') ;
    }
    // TODO:要更改保存，先行后列，X应该存列，Y存行
}

// 编辑地图时初始化地图信息
static void editInit( struct mapInfo *mapInfo )
{
    for( int i = 0 ; i < mapInfo->mapRow ; i ++ )
    {
        for( int j = 0 ; j < mapInfo->mapCol ; j ++ )
        {
            mapInfo->map[i][j] = 'W';
        }
        printf("\n");
    }
    mapInfo->pRow = mapInfo->pCol = -1 ;
}

// 可接受数值范围设置
static void acceptNumSet( int *pmin , int *pmax , int **info , int order )
{
    enum { ROW = 0, COL, TREASURE, TRAP };
    switch( order )
    {
        case ROW :
            *pmin = 4 ;
            *pmax = 30 ;
            break ;
        case COL :
            *pmin = 4 ;
            *pmax = 49 ;
            break ;
        case TREASURE :
            *pmin = 1 ;
            *pmax = 100 > *info[ROW] * *info[COL] ? *info[ROW] * *info[COL] : 100 ;
            break ;
        case TRAP :
            *pmin = 0 ;
            *pmax = 200 >  *info[ROW] * *info[COL] - *info[TREASURE] ?  *info[ROW] * *info[COL] - *info[TREASURE] : 200 ;
            break ;
    }
}

// 设置地图参数
// 限制：
// 1. 地图行不超过30，列不超过49
// 2. 宝藏数量不超过100且少于地图大小
// 3. 陷阱数量不超过200且与宝藏数量之和少于地图大小
static void mapInfoSet( struct mapInfo *mapInfo )
{
    enum { ROW = 0, COL, TREASURE, TRAP };
    int *pSet[] = { &mapInfo->mapRow, &mapInfo->mapCol, &mapInfo->treasureNum, &mapInfo->trapNum };
    char *info[] = { "行数", "列数", "宝藏数量", "陷阱数量" };

    int px = 0 , py = 0 ;
    for( int i = 0 ; i < 4 ; )
    {
        HideConsoleCursor() ;
        system("cls") ;
        printf("正在设置地图参数-->%s\n\n", info[i]);
        printf("请输入一个整数值：");
        GetCursorPosition( &px , &py ) ;
        printf("\n\n") ;    // TODO:BUG修复记录:处理了设置地图参数时光标位置不对的问题

        int min = 0 , max = 0 ;
        acceptNumSet( &min , &max , pSet , i ) ;
        printf("可行值范围：[ %d - %d ]", min , max ) ;
        MoveCursorTo( px , py ) ;
        ShowConsoleCursor() ;

        int num = 0 ;
        scanf("%d" , &num) ;
        if( num >= min && num <= max )
        {
            *pSet[i] = num ;
            i ++ ;
        }
        else    // TODO:待测试
        {
            system("cls") ;
            printf("输入值不在可行范围内，请重新输入！\n") ;
            system("pause") ;
        }
    }
    system("cls") ;
}

// 初始化随机迷宫
// printInfo: 1-打印初始化成功信息，0-不打印
extern void mapCustomIni( int mapOrder , int priInfo )    
{
    FILE *mapfp = NULL ;
    mapfp = fopen( mapPath[ mapOrder - 1 ] , "w" ) ;
    if( mapfp != NULL )
    {
        fputc('*', mapfp);
        fclose(mapfp);
    }
    else
    {
        perror("Error opening file");
        system("pause");
        return ;
    }

    if( priInfo )
    {
    system("cls");
    printf("初始化成功！\n");
    system("pause");
    }

    progressSaveInit( mapOrder ) ; // 同时初始化游戏存档  // TODO:BUG7修复记录:调整了调用参数，解决存档初始化失效的问题
    system("cls");
    return ;
}

// 编辑随机迷宫
// loadFlag: 0-新建地图，1-继续编辑地图
extern void mapCustomEdit( int mapOrder , int loadFlag )   
{
    /* 初始化 */
    int Tnum = 0 , Dnum = 0 ;
    int playerSetFlag = 0 ;
    struct mapInfo mapInfo;
    mapIni( &mapInfo );

    /* 检测地图是否编辑状态，选择是否继续编辑 */
    if( loadFlag )
    {
        progressSaveInit( mapOrder ) ; // 初始化游戏存档  // TODO:BUG7修复记录:增加存档初始化，解决编辑已游玩地图时存档初始化问题
        editProgressLoad( &mapInfo , mapOrder , &Tnum , &Dnum , &playerSetFlag ) ;
    }
    else
    {   // 初始化
        mapCustomIni( mapOrder , 0 ) ;

        // 设置地图信息
        mapInfoSet( &mapInfo );

        // 初始化临时编辑地图
        editInit( &mapInfo );
    }

    // 编辑界面打印与信息存储
    /**
     * 0 当前光标位置：在地图上的位置
     * 1 信息打印位置1：位置信息
     * 2 信息打印位置2：玩家初始位置信息，即：是否已设置，若已设置则打印玩家初始位置
     * 3 信息打印位置3：宝藏设置数量
     * 4 信息打印位置4：陷阱设置数量
     */
    COORD loc[5] = { {0, 0}, {0, 0} , {0, 0}, {0, 0}, {0, 0} };
    enum { MAP_POS = 0 , POS_INFO = 1 , PLAYER_POS = 2 , TREASURE_INFO = 3 , TRAP_INFO = 4 };
    editPrint( mapOrder , &mapInfo , loc , Tnum , Dnum , playerSetFlag ) ;

    /* 编辑地图 */
    int saveFlag = 0 ;
    saveFlag = editMap( &mapInfo , loc , &Tnum , &Dnum , &playerSetFlag ) ;

    /* 存储地图 */
    if( saveFlag ) editMapSave( &mapInfo , mapOrder , Tnum , Dnum , playerSetFlag ) ;

    // TODO:测试通过
}