#include "01_menu.h"
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include "03_mapAndPlayerStatus.h"
#include "02_cursorOperation.h"
#include "04_mapCustom.h"

/* �˵��б� */
static char menuMainList[3][40] = { // ���˵��б�
    {"��ʼ��Ϸ"},
    {"�����˵�"},
    {"�˳���Ϸ"}};
static char menuGameList[5][40] = { // ��Ϸ�˵��б�
    {"��һ��"},
    {"�ڶ���"},
    {"������"},
    {"�Զ���ؿ�"},
    {"�������˵�"}};
static char menuControlMode[4][40] = { // ����ģʽ�˵��б�
    {"ʵʱģʽ"},
    {"���ģʽ"},
    {"�����˵�"},
    {"���ص�ͼ�˵�"}};
static char menuCustomMap[4][40] = { // �Զ����ͼ�˵��б�
    {"�Զ����ͼһ"},
    {"�Զ����ͼ��"},
    {"�Զ����ͼ��"},
    {"���ص�ͼ�˵�"}};
static char menuCustomOperation[5][40] = { // �Զ�������˵��б�
    {"��ʼ�༭"},
    {"��ʼ����"},
    {"���õ�ͼ"},
    {"�����˵�"},
    {"�����Զ���˵�"}};
static char menuProgressList[4][40] = { // �������ͼ����ѡ���б�
    {"�����ϴ���Ϸ"},
    {"��ʼ����Ϸ"},
    {"����浵"},
    {"�������˵�"}};

/* �˵������Ϣ�б� */
static char (*menuList[6])[40] = {
    menuMainList,
    menuGameList,
    menuControlMode,
    menuCustomMap,
    menuCustomOperation,
    menuProgressList};
static int menuOption[6] = {3, 5, 4, 4, 5, 4}; // �˵�ѡ������
static int mapPlayStatus[6] = {0, 0, 0, 0, 0, 0};   // ��ͼ����״̬
static int mapEditStatus[3] = {0, 0, 0};            // ��ͼ�༭״̬

static void menuCall0(int *Order, int *run);         // ���˵�ִ�к���
static void menuCall1(int *Order);                   // ��Ϸ�˵�ִ�к���
static int menuCall2(int *Order);                    // ����ģʽ�˵�ִ�к���
static void menuCall3(int *Order);                   // �Զ����ͼ�˵�ִ�к���
static void menuCall4(int *Order, int customMapNum); // �Զ�������˵�ִ�к���
static int menuCall5(int mapOrder);                              // �������ͼ����ѡ����
static void gameStart(int *Order, int num);        // ��Ϸ��ʼ����

void mapInfoInit()     // ��ͼ���棨�Լ��Զ����ͼ�༭��״̬��ʼ������
{
    /* ����Զ����ͼ�༭״̬ */
    for( int i = 1 ; i <= 3 ; i ++ )
    {
        FILE *mapfp = NULL ;
        mapfp = fopen( mapName[ i + 2 ] , "r" ) ;
        char editFlag = 0 ;
        editFlag = fgetc( mapfp ) ;
        if( editFlag == '*' ) mapEditStatus[ i - 1 ] = 0 ; // δ�༭
        else mapEditStatus[ i - 1 ] = 1 ; // �ѱ༭
        fclose( mapfp ) ;
    }

    /* ����ͼ����״̬ */
    for( int i = 1 ; i <= 6 ; i ++ )
    {
        FILE *mapfp = NULL ;
        mapfp = fopen( mapProgressSave[ i - 1 ] , "r" ) ;
        char playFlag = 0 ;
        playFlag = fgetc( mapfp ) ;
        if( playFlag == '*' ) mapPlayStatus[ i - 1 ] = 0 ; // δ����
        else mapPlayStatus[ i - 1 ] = 1 ; // ������
        fclose( mapfp ) ;
    }
}

static void menuPrint(int menuOrder, int listPos) // �˵���ӡ����������listPos�������ƹ��λ��
{
    for (int i = 0; i < menuOption[menuOrder]; i++)
    {
        /* ��ӡ����ѡ����Ϣ */
        if (i == listPos)
            printf("> ");
        else
            printf("  ");
        printf("%s", menuList[menuOrder] + i);

        /* �Զ����ͼ�༭״̬���� */
        if( menuOrder == 3 && i >= 0 && i <= 2 && !mapEditStatus[ i ] )
            printf("(δ�༭)");

        /* ��ͼ����״̬���� */
        if( menuOrder == 1 && i >= 0 && i <= 2 && mapPlayStatus[ i ] )
            printf("(�ϴ�)");
        else if( menuOrder == 3 && i >= 0 && i <= 2 && mapPlayStatus[ i + 3 ] )
            printf("(�ϴ�)");
        
        printf("\n");
    }
    printf("\n����w���ƹ��,s���ƹ��,����<Enter>ѡ��\n");
    
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

static void welcome()   // ��ӭ����
{
    ClearPartialScreen(0, 0);
    printf("��ӭ����С�Ƶ�����ð��\n");
    printf("��ʹ������ǻ�������С�����Թ��гɹ���Ѱ���ɣ�\n\n");
    printf("<�����������>\n");
    getch();
    return;
}

static void menuCall0(int *Order, int *run) // ���˵�ִ�к���
{
    mapInfoInit();
    int pos = 0;
    while (1)
    {
        system("cls");
        // ���Ҫ���ƽ̨������ʹ�����´������
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
                printf("��Ϸ����\n\n");
                printf("��ϷĿ�꣺\n");
                printf("    1. ͨ����������ָ�����С�����Թ����ҵ����б���\n");
                printf("    2. С�Ƶ�Ĭ�ϳ�ʼλ��Ϊ��ͼ���Ͻǣ����ص�λ���������\n");
                printf("    3. ʵʱģʽ�£�С�Ƶ��ƶ�ָ��Ϊ��\n");
                printf("        w: �����ƶ�\n");
                printf("        s: �����ƶ�\n");
                printf("        a: �����ƶ�\n");
                printf("        d: �����ƶ�\n");
                printf("        i: ԭ����Ϣ\n");
                printf("        q: �˳���Ϸ\n");
                printf("    4. ���ģʽ�£�С�Ƶ��ƶ�ָ��Ϊ��\n");
                printf("        U: �����ƶ�\n");
                printf("        D: �����ƶ�\n");
                printf("        L: �����ƶ�\n");
                printf("        R: �����ƶ�\n");
                printf("        P.S. ���ģʽ����Ч��������������ֱ���˳���Ϸ\n");
                printf("    5. ÿ���ƶ�������һ������\n");
                printf("    6. С������ǽ�ڻ�ͣ����ԭ�أ����������´��ж�������һ������\n");
                printf("    7. С���ҵ����б��غ���Ϸ����\n");
                printf("    8. ף����ˣ�\n\n");
                printf("<�����������>\n");
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

static void menuCall1(int *Order) // ��Ϸ�˵�ִ�к���
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
            case 0: // ��һ�غ���
            {
                gameStart(Order , 1);
                return;
            }
            case 1: // �ڶ��غ���
            {
                gameStart(Order , 2);;
                return;
            }
            case 2: // �����غ���
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

static int menuCall2(int *Order) // ����ģʽ�˵�ִ�к���
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
                return 0; // ʵʱģʽ����
            case 1:
                return 1; // ���ģʽ����
            case 2:
            {
                system("cls");
                printf("help file 2 ʩ����\n") ;
                // TODO: ��д����ģʽ�����ĵ�
            }
            case 3:
                return 2;
            }
        }
    }
}

static void menuCall3(int *Order) // �Զ����ͼ��ͼѡ��˵�ִ�к���
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

static void menuCall4(int *Order, int customMapNum) // �Զ�������˵�ִ�к���
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
                printf("help file 3 ʩ����\n") ;
                // TODO: ��д�Զ����ͼ�����ĵ�
            }
            case 4:
                *Order = 3;
                return;
            }
        }
    }
}

static int menuCall5(int mapOrder)      // �������ͼ����ѡ����
{
    int pos = 0 ;
    FILE *mapfp = NULL ;
    mapfp = fopen( mapProgressSave[ mapOrder - 1 ] , "r" ) ;
    char timeStr1[64] = {0} ;
    char timeStr2[64] = {0} ;
    int treasureInfoPlayer , treasureInfoMap ;
    fscanf( mapfp , "%s %s\n" , timeStr1 , timeStr2 ) ;              // д�뱣��ʱ��
    fscanf( mapfp , "%d %d\n" , &treasureInfoPlayer , &treasureInfoMap ) ; // ��ȡ������Ϣ
    fclose( mapfp ) ;
    
    while( 1 )
    {
        system("cls");
        printf("�ϴ�����ʱ�䣺%s %s\n" , timeStr1 , timeStr2 ) ;
        printf("�ϴ����汦�أ�%d/%d\n\n" , treasureInfoPlayer , treasureInfoMap ) ;
        
        menuPrint(5, pos);

        char ch = getch();
        if( ch == 'w' && pos > 0 )
            pos -- ;
        if( ch == 's' && pos < menuOption[5] - 1 )
            pos ++ ;
        if( ch == '\r' )
            return pos + 1;
            /**
             * ����ֵ���ܣ�
             * 1�������ϴ���Ϸ
             * 2����ʼ����Ϸ
             * 3: ����浵
             * 4���������˵�
             */
    }
}

static void gameStart( int *Order , int num ) // ��Ϸ��ʼ����
{
    mapInfoInit();
    /* �Ƿ������Ϸ */
    int keepProgress = 0;
    if( mapPlayStatus[ num - 1 ] )
    {
        int progressOrder = menuCall5( num ) ;
        if( progressOrder == 1 ) // �����ϴ���Ϸ
            keepProgress = 1;
        else if( progressOrder == 2 ) // ��ʼ����Ϸ
            keepProgress = 0;
        else if( progressOrder == 3 ) // ����浵
        {
            progressSaveInit( num ) ;
            mapInfoInit() ;
            return ;
        }
        else if( progressOrder == 4 ) // �������˵�
            return;
    }

    /* ѡ�����ģʽ */
    int gameMode = menuCall2(Order);
    if (gameMode == 2)
        return;

    /* ��ʼ�� */
    struct mapInfo map;
    struct playerInfo player;
    mapIni(&map);
    if (!mapInput(&map, num))
        return; // ��ȡ��ͼʧ����ֱ�ӷ���
    playerIni(&player, &map);
    if( keepProgress )
        progressLoad( &player , &map , num ) ;
    mapPrint(&map);
    HideConsoleCursor();

    /* ������ģʽ������Ϸ���� */
    if (gameMode == 0)
        playerMove(&player, &map, num);
    else if (gameMode == 1)
        playerMovePro(&player, &map, num);
    ShowConsoleCursor();

    /* �����Ϸ���������˵� */
    Order = 0;
    mapInfoInit();
    welcome();
}

void menuControl()      // �˵����п���������
{
    welcome();

    int run = 1;
    int menuOrder = 0;
    mapInfoInit();
    while (run)
    {                      // ѭ���߼���ͨ��run���Ʋ˵����˳�
        switch (menuOrder) // �˵�ѡȡ�߼���ͨ��menuOrder�������Ʋ˵���ѡ��
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
