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

// ����˵�ѡ������
#define LISTNUMCOUNT(listname) (sizeof(listname)/sizeof(listname[0]))

/* �˵��б� */
static char mainMenuList[][40] = { // ���˵��б�
    {"��ʼ��Ϸ"},
    {"��ȡ����"},
    {"�˳���Ϸ"}};
static char mapChooseMenuList[][40] = { // ��ͼѡ��˵�
    {"�½���ͼ"},
    {"�������˵�"}};
static char mapOperationMenuList[][40] = { // �Զ�������˵��б�
    {"��ʼ����"},
    {"��ʼ�༭"},
    {"���õ�ͼ"},
    {"ɾ����ͼ"},
    {"��������ͼ"},
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
static char boolSelectMenuList[][40] = { // �Ƿ�ѡ��˵��б�
    {"ȷ��"},
    {"ȡ��"}};
char (*menuList[])[40] = {  // �˵��б�
    mainMenuList,
    mapChooseMenuList,
    mapOperationMenuList,
    saveLoadMenuList,
    controlModeMenuList,
    editProgressMenuList,
    boolSelectMenuList};
char mapName[10][64] ;  // ��ͼ�ļ���
char mapPath[10][64] ;  // ��ͼ�ļ�·��
char savePath[10][64] ; // ��ͼ�����ļ�·��
static int mapNumbers ; // ��ͼ����

/* ������ */
static void welcome() ;   // ��ӭ����
static int getMapStatus( int mapOrder ) ;  // ��ȡ�˵���ӡ������Ϣ
static void mapNameGet() ; // ��ȡ��ͼ���Ʋ�ά��mapName�����mapProgressSave�����mapNumbers
static void mapNewCreate() ; // �½���ͼ����
static void mapNameChange( int mapOrder ) ; // ��ͼ���Ƹ��ĺ���
static void mapRemove( int mapOrder ) ; // ɾ����ͼ����
static void printMenu( MENU menu , int num ) ;                 // ��ӡ�˵�
static int cursorChoose( COORD loc , int num ) ;                  // �˵�����ƶ�����
static void freshCursor( COORD loc , int num , int pos ) ;        // �˵�����ƶ���ʾ�����
static void freshCursor( COORD loc , int num , int pos ) ;        // �˵�����ƶ���ʾ�����
static void startGame( int mapOrder ) ;    // ��Ϸ��ʼ����
static void printFile( int num ) ; // ��ӡ�ĵ���ֻ���������ϱȽϷ��ӵĴ�ӡ������

/* �˵����� */
static void mainMenu( MENU *pmenu ) ;                // ���˵�����
static void mapChooseMenu( MENU *pmenu ) ; // ��ͼѡ��˵�����
static void mapOperationMenu( int mapOrder ) ;             // ��ͼ�����˵�����
static int saveLoadMenu( int mapOrder ) ;                    // �浵��ȡ�˵�����
static int controlModeMenu() ;                 // ����ģʽ�˵�����
static int editProgressMenu() ;                // �༭���Ȳ˵�����



// �˵����п���������
extern void runMenu()
{
    mapNameGet() ; // ��ȡ��ͼ����
    static void (*treeMenu[])( MENU * ) = { // ���ɺ�������ָ������
        mainMenu,
        mapChooseMenu};

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

// ��ȡ��ͼ���Ʋ�ά��mapName�����mapProgressSave�����mapNumbers
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

// ��ͼ���Ƹ��ĺ���
static void mapNameChange( int mapOrder )
{
    // ��ʼ����
    mapOrder--; // ��ͼ���ӳ��Ϊ�����±�
    char oldMapPath[64] = {0};
    char oldProgressSavePath[64] = {0};
    char newMapPath[64] = {0};
    char newProgressSavePath[64] = {0};
    snprintf(oldMapPath, sizeof(oldMapPath), "%s", mapPath[mapOrder]);
    snprintf(oldProgressSavePath, sizeof(oldProgressSavePath), "%s", savePath[mapOrder]);

    // �����µ�ͼ����
    system("cls");
    printf("��ǰ��ͼ����: %s\n", mapName[mapOrder]);
    char newMapName[40] = {0};
    printf("�������µĵ�ͼ����: ");
    ShowConsoleCursor();
    scanf("%39s", newMapName);
    HideConsoleCursor();
    
    // ����ͼ�����Ƿ��Ѵ���
    for (int i = 0; i < mapNumbers; i++) {
        if (strcmp( mapName[i], newMapName ) == 0) {
            system("cls");
            printf("��ͼ�����Ѵ��ڣ������벻ͬ�����ơ�\n");
            system("pause");
            system("cls");
            return;
        }
    }
    snprintf(newMapPath, sizeof(newMapPath), "./map/%s.map", newMapName);
    snprintf(newProgressSavePath, sizeof(newProgressSavePath), "./save/%s.save", newMapName );

    if (rename(oldMapPath, newMapPath) == 0) {
        system("cls");
        printf("��ͼ�����Ѹ���Ϊ: %s\n", newMapName );
        system("pause");
    } else {
        perror("��ͼ���Ƹ���ʧ��");
    }
    if( rename( oldProgressSavePath , newProgressSavePath ))
        perror("�浵�ļ����Ƹ���ʧ��");
}

// �½���ͼ����
static void mapNewCreate()
{
    system("cls");
    printf("�������µ�ͼ����: ");

    // ��ȡ�µ�ͼ����
    ShowConsoleCursor();
    char newMapName[40] = {0};
    scanf("%39s", newMapName);
    HideConsoleCursor();
    system("cls") ;

    // ����ͼ�����Ƿ��Ѵ���
    for (int i = 0; i < mapNumbers; i++) {
        if (strcmp(mapName[i], newMapName) == 0) {
            printf("��ͼ�����Ѵ��ڣ������벻ͬ�����ơ�\n");
            system("pause");
            return;
        }
    }

    // ������ͼ�ļ��ʹ浵�ļ�
    snprintf(mapName[mapNumbers], sizeof(mapName[mapNumbers]), "%s", newMapName);
    snprintf(mapPath[mapNumbers], sizeof(mapPath[mapNumbers]), "./map/%s.map", newMapName);
    snprintf(savePath[mapNumbers], sizeof(savePath[mapNumbers]), "./save/%s.save", newMapName);
    FILE *mapFile = fopen(mapPath[mapNumbers], "w");
    if (mapFile == NULL) {
        perror("�½���ͼ�ļ�ʧ��");
        return;
    }
    fclose(mapFile);
    FILE *saveFile = fopen(savePath[mapNumbers], "w");
    if (saveFile == NULL) {
        perror("�½��浵�ļ�ʧ��");
        return;
    }
    fclose(saveFile);

    // ��ʼ��
    mapNumbers ++ ;
    mapCustomIni( mapNumbers , 0 ); // ��ʼ����ͼ
    progressSaveInit( mapNumbers ) ;    // ��ʼ���浵
    mapNameGet();   // ���µ�ͼ����
    printf("�µ�ͼ�����ɹ�: <%s>\n\n", newMapName);

    printf("��ǰ��ͼ�б�:\n");
    for(int i = 0 ; i < mapNumbers ; i ++ )
    {
        printf("%d.<%s>\n", i+1 , mapName[i]);
    }
    system("pause");
    system("cls");
}

// ɾ����ͼ����
static void mapRemove( int mapOrder )
{
    mapOrder--; // ��ͼ���ӳ��Ϊ�����±�
    char RemoveMapPath[64] = {0};
    snprintf(RemoveMapPath, sizeof(RemoveMapPath), mapPath[mapOrder]);
    char RemoveSavePath[64] = {0};
    snprintf(RemoveSavePath, sizeof(RemoveSavePath), savePath[mapOrder]);
    system("cls");
    printf("��ѡ��Ҫɾ����ͼ��: <%s>\n", mapName[mapOrder]);
    printf("��ȷ���Ƿ�ɾ��");
    int boolFlag = boolSelectMenu();

    if (boolFlag) {
        if (remove(RemoveMapPath)== 0) {
            printf("��ͼ�ļ���ɾ��\n");
        } else {
            perror("��ͼ�ļ�ɾ��ʧ��");
        }
        if (remove(RemoveSavePath) == 0) {
            printf("�浵�ļ���ɾ��\n");
        } else {
            perror("�浵�ļ�ɾ��ʧ��");
        }
    } else {
        printf("ȡ��ɾ��\n");
    }
    system("pause");
}

// ��ӭ����
static void welcome()   // TODO:��ӭ�������ݿ��Ը��ḻһ��
{
    system("cls");
    printFile( 1 );
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
    int listNum = LISTNUMCOUNT( mainMenuList ) ;
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
            *pmenu = MAP_CHOOSE_MENU ;
            break;
        case 1:     // ��ȡ����
            system("cls");
            printFile( 2 ) ;    // ���ð����ĵ�1
            break;
        case 2:     // �˳���Ϸ
            *pmenu = -1 ;   
            break;
    }
}

// ��ͼѡ��˵�����
static void mapChooseMenu( MENU *pmenu )
{
    system("cls");
    int listNum = mapNumbers + LISTNUMCOUNT( mapChooseMenuList ) ;
    COORD loc = { 0 , 0 } ;     // �˵����λ��
    int x = 0 , y = 0 ;

    /* �˵���Ϣ��ӡ��洢 */
    printf("��ͼѡ��\n\n") ;
    GetCursorPosition( &x , &y ) , loc.X = x , loc.Y = y ;
    for( int i = 0 ; i < mapNumbers ; i ++ )
    {
        printf("   ") ;
        printf("%d.<%s>\n" , i + 1 , mapName[ i ] ) ;
    }
    printMenu( MAP_CHOOSE_MENU , LISTNUMCOUNT( mapChooseMenuList ) ) ;

    /* ��ȡ�˵�ѡ�н�� */
    int op = cursorChoose( loc , listNum ) ;

    /* �˵�ѡ��� */
    if( op < mapNumbers ) // ѡ���ͼ
    {
        mapOperationMenu( op + 1 ) ;
    }
    else
    {
        switch( op - mapNumbers )
        {
            case 0:     // �½���ͼ
                mapNewCreate() ;
                break;
            case 1:     // �������˵�
                *pmenu = MAIN_MENU ;
                break;
        }
    }
}

// �Ƿ�״̬��ȡ�˵�����
extern int boolSelectMenu()
{
    int listNum = LISTNUMCOUNT( boolSelectMenuList ) ;
    COORD loc = { 0 , 0 } ;     // �˵����λ��
    int x = 0 , y = 0 ;

    /* �˵���Ϣ��ӡ��洢 */
    printf("\n\n") ;
    GetCursorPosition( &x , &y ) , loc.X = x , loc.Y = y ;
    printMenu( BOOL_SELECT_MENU , listNum ) ;

    /* ��ȡ�˵�ѡ�н�� */
    int op = cursorChoose( loc , listNum ) ;

    /* �˵�ѡ��� */
    system("cls");
    if( op == 0 ) return 1 ;
    else return 0 ;
}

// ��ȡ�жϴ�ӡ��־������ֵDEFAULT = 0 , SAVED = 1 , UNEDITED = 2 , EDITED_UNFINISHED = 3
static int getMapStatus( int mapOrder )
{
    enum { EDITED_NOT_SAVED = 0 , EDITED_SAVED = 1 , UNEDITED = 2 , EDITED_UNFINISHED = 3 } STATUS ;

    // ��ͼ״̬��ȡ
    FILE *mapfp = NULL ;
    mapfp = fopen( mapPath[ mapOrder - 1 ] , "r" ) ;
    char editFlag = 0 , finishFlag = 0 ;
    editFlag = fgetc( mapfp ) ;
    fseek( mapfp , -1L , SEEK_END ) ;
    finishFlag = fgetc( mapfp ) ;
    fclose( mapfp ) ;
    if( editFlag == '*' )  // δ�༭
    {
        STATUS = UNEDITED ;
    }
    else if( finishFlag == ']' ) // �ѱ༭��δ���
    {
        STATUS = EDITED_UNFINISHED ;
    }
    else // �ѱ༭
    {
        mapfp = fopen( savePath[ mapOrder - 1 ] , "r" ) ;
        char playFlag = 0 ;
        playFlag = fgetc( mapfp ) ;
        fclose( mapfp ) ;
        if( playFlag == '*' ) STATUS = EDITED_NOT_SAVED ;// δ����
        else STATUS = EDITED_SAVED ; // ������
    }

    return STATUS ;
}

// ��ͼ�����˵�����
static void mapOperationMenu( int mapOrder )
{
    system("cls");
    int listNum = LISTNUMCOUNT( mapOperationMenuList ) ;
    COORD loc = { 0 , 0 } ;     // �˵����λ��
    int x = 0 , y = 0 ;

    /* �˵���Ϣ��ӡ��洢 */
    enum { EDITED_NOT_SAVED = 0 , EDITED_SAVED = 1 , UNEDITED = 2 , EDITED_UNFINISHED } STATUS ;
    char addStatus[][20] = { "(�ѱ༭)" , "(������)" , "(δ�༭)" , "(�༭δ���)" } ;
    STATUS = getMapStatus( mapOrder ) ;
    
    printf("ѡ�У�%s\n״̬��%s\n\n" , mapName[ mapOrder - 1 ] , addStatus[ STATUS ] ) ;
    GetCursorPosition( &x , &y ) , loc.X = x , loc.Y = y ;
    int printFlag = STATUS == UNEDITED || STATUS == EDITED_UNFINISHED ; // Ϊ1ʱ����ʾ��ʼ����ѡ��
    for( int i = ( printFlag ? 1 : 0) ; i < listNum ; i ++ ) // δ�༭״̬�²���ʾ��ʼ����ѡ��   // TODO:BUG12�޸����ѱ༭δ���״̬��ⲹ��
    {
        printf("   ") ;
        printf( "%s\n" , menuList[ MAP_OPERATION_MENU ][ i ] ) ;
    }
    if( printFlag ) listNum -- ;
    printf("\n<w>���ƹ��,<s>���ƹ��,<Enter>ѡ��\n");

    /* ��ȡ�˵�ѡ�н�� */
    int op = cursorChoose( loc , listNum ) ;
    if( printFlag ) op ++ ;

    /* �˵�ѡ��� */
    switch( op )
    {
        case 0:     // ��ʼ����
            startGame( mapOrder ) ;
            break;
        case 1:     // ��ʼ�༭
            if( STATUS == UNEDITED ) mapCustomEdit( mapOrder , 0 ) ;
            else
            {
                int progressOrder = editProgressMenu() ;
                progressSaveInit( mapOrder ) ; // ���±༭ʱ��ʼ���浵
                switch( progressOrder )
                {
                    case 0: // �����༭
                        mapCustomEdit( mapOrder , 1 ) ;
                        break;
                    case 1: // ��ʼ�µ�ͼ
                        mapCustomEdit( mapOrder , 0 ) ;
                        break;
                    case 2: // ����
                        break;
                }
            }
            break;
        case 2:     // ���õ�ͼ
            mapCustomIni( mapOrder , 1 ) ;
            break;
        case 3:     // ɾ����ͼ
            mapRemove( mapOrder ) ;
            mapNameGet() ; // ���µ�ͼ����
            break;
        case 4:
            mapNameChange( mapOrder ) ;
            mapNameGet() ; // ���µ�ͼ����
            break;
        case 5:     // ���ص�ͼѡ��˵�
            break;
    }
}

// �༭���Ȳ˵�����
static int editProgressMenu()
{
    system("cls");
    int listNum = LISTNUMCOUNT( editProgressMenuList ) ;
    COORD loc = { 0 , 0 } ;     // �˵����λ��
    int x = 0 , y = 0 ;

    /* �˵���Ϣ��ӡ��洢 */
    printf("�˵�ͼ�Ѿ������༭����ѡ����Ҫ���еĲ���\n\n") ;
    GetCursorPosition( &x , &y ) , loc.X = x , loc.Y = y ;
    printMenu( EDIT_PROGRESS_MENU , listNum ) ;

    /* ��ȡ�˵�ѡ�н�� */
    int op = cursorChoose( loc , listNum ) ;

    /* �˵�ѡ��� */
    system("cls");
    return op ;
}

// �浵��ȡ�˵�����
static int saveLoadMenu( int mapOrder )
{
    system("cls");
    int listNum = LISTNUMCOUNT( saveLoadMenuList ) ;
    COORD loc = { 0 , 0 } ;     // �˵����λ��
    int x = 0 , y = 0 ;

    /* �˵���Ϣ��ӡ��洢 */
    char timeStr1[64] = {0} ;
    char timeStr2[64] = {0} ;
    int treasureInfoPlayer , treasureInfoMap ;
    FILE *mapfp = NULL ;
    mapfp = fopen( savePath[ mapOrder - 1 ] , "r" ) ;
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
    system("cls");
    return op ;
}

// ����ģʽ�˵�����
static int controlModeMenu()
{
    int op = -1 ;
    do
    {
        system("cls");
        int listNum = LISTNUMCOUNT( controlModeMenuList ) ;
        COORD loc = { 0 , 0 } ;     // �˵����λ��
        int x = 0 , y = 0 ;

        /* �˵���Ϣ��ӡ��洢 */
        printf("ѡ����Ҫʹ�õĿ���ģʽ\n\n") ;
        GetCursorPosition( &x , &y ) , loc.X = x , loc.Y = y ;
        printMenu( CONTROL_MODE_MENU , listNum ) ;

        /* ��ȡ�˵�ѡ�н�� */
        op = cursorChoose( loc , listNum ) ;

        if( op == 2 )
        {
            system("cls");
            printFile( 3 );    // ���ð����ĵ�2
        }
    } while( op == 2 ) ;

    /* �˵�ѡ��� */
    system("cls");
    return op ;
}

// ��Ϸ��ʼ����
static void startGame( int mapOrder )
{
    enum { EDITED_NOT_SAVED = 0 , EDITED_SAVED = 1 , UNEDITED = 2 , EDITED_UNFINISHED = 3 } mapStatus ;
    mapStatus = getMapStatus( mapOrder ) ;

    /* �Ƿ������Ϸ */
    int keepProgress = 0;
    if( mapStatus == EDITED_SAVED ) // �ѱ༭��������
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
    gameMode = controlModeMenu() ;
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

// ����������Ҫ��������ӡ�Ĳ��ּ�����һ��
static void printFile( int num )
{
    if( num == 1 )  // ��ӭ����
    {
        printf("\033[1;37m**************************************************************\n\
*                                                            *\n\
*                 \033[1m\033[1;32m ��ӭ�����Թ���ð�գ���\033[1;37m                    *\n\
*                                                            *\n\
*             \033[34m������㽫����̽���Թ�����ʿ��\033[37m               *\n\
*              \033[34mѰ�ұ��أ�������壬���̽�գ���\033[37m              *\n\
*                \033[5m<������������׼����ʼ��Ϸ>\033[0m\033[37m                  *\n\
*                                                            *\n\
*                                                            *\n\
*                     \033[31m����ע�����\033[1;37m                         *\n\
*           1. �����ڵ�����ȫ����ȷ��������������            *\n\
*           2. �����������������������ڴ�С                *\n\
*                                                            *\n\
*                �����汾 : \033[1;34mVersion:2.3\033[1;37m                      *\n\
*                 ������  : \033[1;34mTheSumst\033[1;37m                         *\n\
*                                                            *\n\
**************************************************************\n\
\033[0m");
    }
    else if( num == 2 ) // ���˵�����
    {
        printf("\033[1;37m**************************************************************\n\
*                                                            *\n\
*                        \033[1m\033[1;32m�����ĵ� 1\033[0m\033[1;37m                          *\n\
*                                                            *\n\
*             \033[34m�����ǰ����ĵ�1�����ݡ�\033[37m                        *\n\
*                                                            *\n\
*             \033[34m1. ��ϷĿ�꣺\033[37m                                  *\n\
*                \033[34m- ̽���Թ���Ѱ�ұ��ء�\033[37m                      *\n\
*                \033[34m- ������壬���̽�ա�\033[37m                      *\n\
*                                                            *\n\
*             \033[34m2. ����ָ�ϣ�\033[37m                                  *\n\
*                \033[34m- ʹ��'w'���ƹ�ꡣ\033[37m                         *\n\
*                \033[34m- ʹ��'s'���ƹ�ꡣ\033[37m                         *\n\
*                \033[34m- ��'Enter'��ѡ�С�\033[37m                         *\n\
*                                                            *\n\
*                \033[5m<�����������뷵�����˵�>\033[0m\033[1;37m                    *\n\
*                                                            *\n\
**************************************************************\n\
\033[0m");
    }
    else if( num == 3 ) // ����ģʽ����
    {
        printf("\033[1;37m**************************************************************\n\
*                                                            *\n\
*                        \033[1m\033[1;32m�����ĵ� 2\033[0m\033[1;37m                          *\n\
*                                                            *\n\
*             \033[34m�����ǰ����ĵ�2�����ݡ�\033[37m                        *\n\
*                                                            *\n\
*             \033[34m1. ����ģʽ��\033[37m                                  *\n\
*                \033[34m- ʵʱģʽ��ʵʱ���ƽ�ɫ�ƶ���\033[37m              *\n\
*                \033[34m- ���ģʽ����д������ƽ�ɫ�ƶ���\033[37m          *\n\
*                                                            *\n\
*             \033[34m2. �浵���ȡ��\033[37m                                *\n\
*                \033[34m- ��Ϸ�����п�����ʱ�浵��\033[37m                  *\n\
*                \033[34m- ��ȡ�浵�����ϴ���Ϸ��\033[37m                    *\n\
*                                                            *\n\
*                \033[5m<�����������뷵�����˵�>\033[0m\033[1;37m                    *\n\
*                                                            *\n\
**************************************************************\n\
\033[0m");
    }
    getch();
}