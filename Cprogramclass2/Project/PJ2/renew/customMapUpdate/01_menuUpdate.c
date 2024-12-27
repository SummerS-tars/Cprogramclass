#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>
#include "01_menuUpdate.h"
#include "02_cursorOperation.h"
#include "03_mapAndPlayerStatus.h"
#include "04_mapCustomUpdate.h"

/* �˵��б� */
static char mainMenuList[][40] = { // ���˵��б�
    {"��ʼ��Ϸ"},
    {"��ȡ����"},
    {"�˳���Ϸ"}};
static char mapTypeMenuList[][40] = { // ��ͼ���Ͳ˵��б�
    {"Ĭ�ϵ�ͼ�ؿ�"},
    {"�Զ����ͼ�ؿ�"},
    {"�������˵�"}};
static char defaultMapMenuList[][40] = { // Ĭ�ϵ�ͼ�ؿ��˵��б�
    {"��ͼһ"},
    {"��ͼ��"},
    {"��ͼ��"},
    {"���ص�ͼ���Ͳ˵�"}};
static char customMapMenuList[][40] = { // �Զ����ͼ�ؿ��˵��б�
    {"�Զ����ͼһ"},
    {"�Զ����ͼ��"},
    {"�Զ����ͼ��"},
    {"��ȡ����"},
    {"���ص�ͼ���Ͳ˵�"}};
static char customOperationMenuList[][40] = { // �Զ�������˵��б�
    {"��ʼ����"},
    {"��ʼ�༭"},
    {"���õ�ͼ"},
    {"�����Զ���˵�"}};
static char saveLoadMenuList[][40] = { // �浵�˵��б�
    {"�����ϴ���Ϸ"},
    {"��ʼ����Ϸ"},
    {"����浵"},
    {"����"}};
static char controlModeMenuList[][40] = { // ����ģʽ�˵��б�
    {"ʵʱģʽ"},
    {"���ģʽ"},
    {"��ȡ����"},
    {"����"}};
static char editProgressMenuList[][40] = { // �༭���Ȳ˵��б�
    {"�����༭"},
    {"��ʼ�µ�ͼ"},
    {"����"}};
char (*menuList[])[40] = {  // �˵��б�
    mainMenuList,
    mapTypeMenuList,
    defaultMapMenuList,
    customMapMenuList,
    customOperationMenuList,
    saveLoadMenuList,
    controlModeMenuList,
    editProgressMenuList};

static void mainMenu( MENU *pmenu ) ;                // ���˵�����
static void mapTypeMenu( MENU *pmenu ) ;             // ��ͼ����ѡ��˵�����
static void defaultMapMenu( MENU *pmenu ) ;          // Ĭ�ϵ�ͼ�˵�����
static void customMapMenu( MENU *pmenu ) ;           // �Զ����ͼ�˵�����
static void customOperationMenu( int mapOrder ) ;             // �Զ����ͼ�����˵�����
static int saveLoadMenu( int mapOrder ) ;                    // �浵��ȡ�˵�����
static int controlModeMenu() ;                 // ����ģʽ�˵�����
static int editProgressMenu() ;                // �༭���Ȳ˵�����
static int listNumCount( MENU menu ) ;       // ����˵�ѡ������
static void printMenu( MENU menu , int num ) ;                 // ��ӡ�˵�
static int cursorChoose( COORD loc , int num ) ;                  // �˵�����ƶ�����
static void freshCursor( COORD loc , int num , int pos ) ;        // �˵�����ƶ���ʾ�����
static void defaultMapStatus( int mapOrder , int *status ) ;                     // Ĭ�ϵ�ͼ�浵״̬��ʾ
static void customMapStatus( int customMapOrder , int *status ) ;      // �Զ����ͼ�浵״̬��ʾ
static int getMapStatus( int mapOrder ) ;  // ��ȡ�˵���ӡ������Ϣ
static void startGame( int mapOrder ) ;    // ��Ϸ��ʼ����
static void welcome() ;   // ��ӭ����

// TODO:��ӭ�������ݿ��Ը��ḻһ��
static void welcome()
{
    system("cls");
    printf("�Թ���ð�գ�Version:2.1\n\n") ;
    system("pause");
}

// �˵����п���������
extern void runMenu()
{
    static void (*treeMenu[])( MENU * ) = { // ���ɺ�������ָ������
        mainMenu,
        mapTypeMenu,
        defaultMapMenu,
        customMapMenu};

    system("cls");
    system("mode con: cols=100 lines=50"); // �����ն˴��ڴ�С
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

// ����˵�ѡ������
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

// �˵���ӡ
static void printMenu( MENU menu , int num )
{
    for( int i = 0 ; i < num ; i ++ )
    {
        printf("   ") ;
        printf( "%s\n" , menuList[ menu ][ i ] ) ;
    }
    printf("\n<w>���ƹ��,<s>���ƹ��,<Enter>ѡ��\n");
}

// �˵�����ƶ���ʾ�����
static void freshCursor( COORD loc , int num , int pos )
{
    for( int i = 0 ; i < num ; i ++ )   // ˢ�¹��λ�ã���posλ�ô�ӡ���
    {
        MoveCursorTo( loc.X , loc.Y + i ) ;
        if( i == pos ) putchar('>') ;
        else putchar(' ') ;
    }
}

// �˵�����ƶ�����
static int cursorChoose( COORD loc , int num )
{
    int pos = 0 ;
    freshCursor( loc , num , pos ) ;
    while( 1 )      // ����ƶ����ƣ���������ֱ��ѡ�У�����ѡ�й��ѡ������
    {
        char ch = getch() ;
        if( ch == 'w' && pos > 0 ) pos -- ;
        else if( ch == 's' && pos < num - 1 ) pos ++ ;
        else if( ch == '\r' ) return pos ;
        freshCursor( loc , num , pos ) ;
    }
}

// ���˵�����
static void mainMenu( MENU *pmenu )
{
    system("cls");
    int listNum = listNumCount( MAIN_MENU ) ;
    COORD loc = { 0 , 0 } ;     // �˵����λ��
    int x = 0 , y = 0 ;

    /* �˵���Ϣ��ӡ��洢 */
    printf("�Թ���ð�գ�Version:2.1\n\n") ;
    GetCursorPosition( &x , &y ) , loc.X = x , loc.Y = y ;
    printMenu( MAIN_MENU , listNum ) ;

    /* ��ȡ�˵�ѡ�н�� */
    int op = cursorChoose( loc , listNum ) ;

    /* �˵�ѡ��� */
    switch( op )
    {
        case 0:     // ��ʼ��Ϸ
            *pmenu = MAP_TYPE_MENU ;
            break;
        case 1:     // ��ȡ����
            system("cls");
            printf("help file 1 ʩ����\n") ;    // TODO:�����ĵ�1
            system("pause");
            break;
        case 2:     // �˳���Ϸ
            *pmenu = -1 ;   
            break;
    }
}

// ��ͼ����ѡ��˵�����
static void mapTypeMenu( MENU *pmenu )
{
    system("cls");
    int listNum = listNumCount( MAP_TYPE_MENU ) ;
    COORD loc = { 0 , 0 } ;     // �˵����λ��
    int x = 0 , y = 0 ;

    /* �˵���Ϣ��ӡ��洢 */
    printf("ѡ����Ҫ����ĵ�ͼ����\n\n") ;
    GetCursorPosition( &x , &y ) , loc.X = x , loc.Y = y ;
    printMenu( MAP_TYPE_MENU , listNum ) ;

    /* ��ȡ�˵�ѡ�н�� */
    int op = cursorChoose( loc , listNum ) ;

    /* �˵�ѡ��� */
    switch( op )
    {
        case 0:     // Ĭ�ϵ�ͼ�ؿ�
            *pmenu = DEFAULT_MAP_MENU ;
            break;
        case 1:     // �Զ����ͼ�ؿ�
            *pmenu = CUSTOM_MAP_MENU ;
            break;
        case 2:     // �������˵�
            *pmenu = MAIN_MENU ;
            break;
    }
}

// Ĭ�ϵ�ͼ�˵�����
static void defaultMapMenu( MENU *pmenu )
{
    system("cls");
    int listNum = listNumCount( DEFAULT_MAP_MENU ) ;
    COORD loc = { 0 , 0 } ;     // �˵����λ��
    int x = 0 , y = 0 ;

    /* �˵���Ϣ��ӡ��洢 */
    printf("ѡ����Ҫ�����Ĭ�ϵ�ͼ\n\n") ;
    GetCursorPosition( &x , &y ) , loc.X = x , loc.Y = y ;
    printMenu( DEFAULT_MAP_MENU , listNum ) ;

    /* ��ȡ�˵�ѡ�н�� */
    int op = cursorChoose( loc , listNum ) ;

    /* �˵�ѡ��� */
    enum { DefaultMap1 = 1 , DefaultMap2 = 2 , DefaultMap3 = 3 } ;
    switch( op )
    {
        case 0:     // ��ͼһ
            startGame( DefaultMap1 ) ;
            break;
        case 1:     // ��ͼ��
            startGame( DefaultMap2 ) ;
            break;
        case 2:     // ��ͼ��
            startGame( DefaultMap3 ) ;
            break;
        case 3:     // ���ص�ͼ���Ͳ˵�
            *pmenu = MAP_TYPE_MENU ;
            break;
    }
}

// �Զ����ͼ�˵�����
static void customMapMenu( MENU *pmenu )
{
    system("cls");
    int listNum = listNumCount( CUSTOM_MAP_MENU ) ;
    COORD loc = { 0 , 0 } ;     // �˵����λ��
    int x = 0 , y = 0 ;

    /* �˵���Ϣ��ӡ��洢 */
    printf("ѡ����Ҫ������Զ����ͼ\n\n") ;
    GetCursorPosition( &x , &y ) , loc.X = x , loc.Y = y ;
    printMenu( CUSTOM_MAP_MENU , listNum ) ;

    /* ��ȡ�˵�ѡ�н�� */
    int op = cursorChoose( loc , listNum ) ;

    /* �˵�ѡ��� */
    enum { CustomMap1 = 1 , CustomMap2 = 2 , CustomMap3 = 3 } ;
    switch( op )
    {
        case 0:     // �Զ����ͼһ
            customOperationMenu( CustomMap1 ) ;
            break;
        case 1:     // �Զ����ͼ��
            customOperationMenu( CustomMap2 ) ;
            break;
        case 2:     // �Զ����ͼ��
            customOperationMenu( CustomMap3 ) ;
            break;
        case 3:     // ��ȡ����
            system("cls");
            printf("help file 2 ʩ����\n") ;    // TODO:�����ĵ�2
            system("pause");
            break;
        case 4:     // ���ص�ͼ���Ͳ˵�
            *pmenu = MAP_TYPE_MENU ;
            break;
    }
}

// Ĭ�ϵ�ͼ״̬��ȡ����
static void defaultMapStatus( int defaultMapOrder , int *status )
{
    enum { NOT_SAVED = 0 , SAVED = 1 } ;
    FILE *mapfp = NULL ;
    mapfp = fopen( mapProgressSave[ defaultMapOrder - 1 ] , "r" ) ;
    char playFlag = 0 ;
    playFlag = fgetc( mapfp ) ;
    fclose( mapfp ) ;
    if( playFlag == '*' ) *status = NOT_SAVED ;// δ����
    else *status = SAVED ; // ������
}

// �Զ����ͼ״̬��ȡ����
static void customMapStatus( int customMapOrder , int *status )
{
    enum { EDITED_NOT_SAVED = 0 , EDITED_SAVED = 1 , UNEDITED = 2 , EDITED_UNFINISHED = 3 } ;
    FILE *mapfp = NULL ;
    mapfp = fopen( mapName[ customMapOrder + 2 ] , "r" ) ;
    char editFlag = 0 , finishFlag = 0 ;
    editFlag = fgetc( mapfp ) ;
    fseek( mapfp , -1L , SEEK_END ) ;
    finishFlag = fgetc( mapfp ) ;
    if( editFlag == '*' )  // δ�༭
    {
        *status = UNEDITED ;
    }
    else if( finishFlag == ']' ) // �ѱ༭��δ���
    {
        *status = EDITED_UNFINISHED ;
    }
    else // �ѱ༭
    {
        mapfp = fopen( mapProgressSave[ customMapOrder + 2 ] , "r" ) ;
        char playFlag = 0 ;
        playFlag = fgetc( mapfp ) ;
        fclose( mapfp ) ;
        if( playFlag == '*' ) *status = EDITED_NOT_SAVED ;// δ����
        else *status = EDITED_SAVED ; // ������
    }
}

// ��ȡ�жϴ�ӡ��־������ֵDEFAULT = 0 , SAVED = 1 , UNEDITED = 2
// ���е�ͼ�����ʱͬ�ⰴ��Ĭ�ϵ�ͼ1-3���Զ����ͼ1-3��˳���ڲ�������ʱӳ����1-6�Է�����������
static int getMapStatus( int mapOrder )
{
    int STATUS = 0 ;
    if( mapOrder >= 1 && mapOrder <= 3 ) defaultMapStatus( mapOrder  , &STATUS ) ;
    else customMapStatus( mapOrder - 3 , &STATUS ) ;
    return STATUS ;
}

// �Զ����ͼ�����˵�����
static void customOperationMenu( int customMapOrder )
{
    system("cls");
    int listNum = listNumCount( CUSTOM_OPERATION_MENU ) ;
    COORD loc = { 0 , 0 } ;     // �˵����λ��
    int x = 0 , y = 0 ;

    /* �˵���Ϣ��ӡ��洢 */
    enum { EDITED_NOT_SAVED = 0 , EDITED_SAVED = 1 , UNEDITED = 2 , EDITED_NOT_SAVED } STATUS ;
    char mapName[][20] = { "�Զ����ͼһ" , "�Զ����ͼ��" , "�Զ����ͼ��" } ;
    char addStatus[][20] = { "(�ѱ༭)" , "(������)" , "(δ�༭)" , "(�༭δ���)" } ;
    STATUS = getMapStatus( customMapOrder + 3 ) ;
    
    printf("ѡ�У�%s\n״̬��%s\n\n" , mapName[ customMapOrder - 1 ] , addStatus[ STATUS ] ) ;
    GetCursorPosition( &x , &y ) , loc.X = x , loc.Y = y ;
    for( int i = (STATUS == UNEDITED ? 1 : 0) ; i < listNum ; i ++ ) // δ�༭״̬�²���ʾ��ʼ����ѡ��
    {
        printf("   ") ;
        printf( "%s\n" , menuList[ CUSTOM_OPERATION_MENU ][ i ] ) ;
    }
    if( STATUS == UNEDITED || STATUS == EDITED_NOT_SAVED ) listNum -- ;
    printf("\n<w>���ƹ��,<s>���ƹ��,<Enter>ѡ��\n");

    /* ��ȡ�˵�ѡ�н�� */
    int op = cursorChoose( loc , listNum ) ;
    if( STATUS == UNEDITED || STATUS == EDITED_NOT_SAVED ) op ++ ;

    /* �˵�ѡ��� */
    switch( op )
    {
        case 0:     // ��ʼ����
            startGame( customMapOrder + 3 ) ;
            break;
        case 1:     // ��ʼ�༭  // TODO:����
            if( STATUS == UNEDITED ) mapCustomEdit( customMapOrder , 0 ) ;
            else
            {
                int progressOrder = editProgressMenu() ;
                progressSaveInit( customMapOrder + 2 ) ; // ���±༭ʱ��ʼ���浵
                switch( progressOrder )
                {
                    case 0: // �����༭
                        mapCustomEdit( customMapOrder , 1 ) ;
                        break;
                    case 1: // ��ʼ�µ�ͼ
                        mapCustomEdit( customMapOrder , 0 ) ;
                        break;
                    case 2: // ����
                        break;
                }
            }
            break;
        case 2:     // ���õ�ͼ
            mapCustomIni( customMapOrder , 1 ) ;
            break;
        case 3:     // �����Զ���˵�
            break;
    }
}

// �༭���Ȳ˵�����
static int editProgressMenu()
{
    system("cls");
    int listNum = listNumCount( EDIT_PROGRESS_MENU ) ;
    COORD loc = { 0 , 0 } ;     // �˵����λ��
    int x = 0 , y = 0 ;

    /* �˵���Ϣ��ӡ��洢 */
    printf("�˵�ͼ�Ѿ������༭����ѡ����Ҫ���еĲ���\n\n") ;
    GetCursorPosition( &x , &y ) , loc.X = x , loc.Y = y ;
    printMenu( EDIT_PROGRESS_MENU , listNum ) ;

    /* ��ȡ�˵�ѡ�н�� */
    int op = cursorChoose( loc , listNum ) ;

    /* �˵�ѡ��� */
    return op ;
}

// �浵��ȡ�˵�����
static int saveLoadMenu( int mapOrder )
{
    system("cls");
    int listNum = listNumCount( SAVE_LOAD_MENU ) ;
    COORD loc = { 0 , 0 } ;     // �˵����λ��
    int x = 0 , y = 0 ;

    /* �˵���Ϣ��ӡ��洢 */
    char timeStr1[64] = {0} ;
    char timeStr2[64] = {0} ;
    int treasureInfoPlayer , treasureInfoMap ;
    FILE *mapfp = NULL ;
    mapfp = fopen( mapProgressSave[ mapOrder - 1 ] , "r" ) ;
    fscanf( mapfp , "%s %s\n" , timeStr1 , timeStr2 ) ;              // д�뱣��ʱ��
    fscanf( mapfp , "%d %d\n" , &treasureInfoPlayer , &treasureInfoMap ) ; // ��ȡ������Ϣ
    fclose( mapfp ) ;

    printf("�ϴ�����ʱ�䣺%s %s\n" , timeStr1 , timeStr2 ) ;
    printf("�ϴ����汦�أ�%d/%d\n\n" , treasureInfoPlayer , treasureInfoMap ) ;
    GetCursorPosition( &x , &y ) , loc.X = x , loc.Y = y ;
    printMenu( SAVE_LOAD_MENU , listNum ) ;

    /* ��ȡ�˵�ѡ�н�� */
    int op = cursorChoose( loc , listNum ) ;

    /* �˵�ѡ��� */
    return op ;
}

// ����ģʽ�˵�����
static int controlModeMenu()
{
    system("cls");
    int listNum = listNumCount( CONTROL_MODE_MENU ) ;
    COORD loc = { 0 , 0 } ;     // �˵����λ��
    int x = 0 , y = 0 ;

    /* �˵���Ϣ��ӡ��洢 */
    printf("ѡ����Ҫʹ�õĿ���ģʽ\n\n") ;
    GetCursorPosition( &x , &y ) , loc.X = x , loc.Y = y ;
    printMenu( CONTROL_MODE_MENU , listNum ) ;

    /* ��ȡ�˵�ѡ�н�� */
    int op = cursorChoose( loc , listNum ) ;

    /* �˵�ѡ��� */
    return op ;
}

// ��Ϸ��ʼ����
static void startGame( int mapOrder )
{
    enum { UNSAVED = 0 , SAVED = 1 } mapStatus ;
    mapStatus = getMapStatus( mapOrder ) ;

    /* �Ƿ������Ϸ */
    int keepProgress = 0;
    if( mapStatus == SAVED )
    {
        int progressOrder = saveLoadMenu(mapOrder);
        switch (progressOrder) 
        {
            case 0: // �����ϴ���Ϸ
                keepProgress = 1;
                break;
            case 1: // ��ʼ����Ϸ
                keepProgress = 0;
                break;
            case 2: // ����浵
                progressSaveInit(mapOrder);
                return;
            case 3: // ����
                return;
        }
    }

    /* ѡ�����ģʽ */
    int gameMode = 0 ;
    while( (gameMode = controlModeMenu()) == 2 )
    {
        system("cls");
        printf("help file 3 ʩ����\n") ;    // TODO:�����ĵ�3
        system("pause");
        return;
    }
    if (gameMode == 3)
        return;

    /* ��ʼ�� */
    struct mapInfo map;
    struct playerInfo player;
    mapIni(&map);
    if (!mapInput(&map, mapOrder))
        return; // ��ȡ��ͼʧ����ֱ�ӷ���
    playerIni(&player, &map);
    if( keepProgress )
        progressLoad( &player , &map , mapOrder ) ;
    mapPrint(&map);

    /* ������ģʽ������Ϸ���� */
    if (gameMode == 0)
        playerMove(&player, &map, mapOrder);
    else if (gameMode == 1)
        playerMovePro(&player, &map, mapOrder);

    /* �����Ϸ�����ز˵� */
    welcome();
}
