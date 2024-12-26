#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>
#include "02_cursorOperation.h"
#include "menuUpdate.h"

/* �˵��б� */
static char mainMenuList[3][40] = { // ���˵��б�
    {"��ʼ��Ϸ"},
    {"��ȡ����"},
    {"�˳���Ϸ"}};
static char mapTypeMenuList[3][40] = { // ��ͼ���Ͳ˵��б�
    {"Ĭ�ϵ�ͼ�ؿ�"},
    {"�Զ����ͼ�ؿ�"},
    {"�������˵�"}};
static char defaultMapMenuList[4][40] = { // Ĭ�ϵ�ͼ�ؿ��˵��б�
    {"��ͼһ"},
    {"��ͼ��"},
    {"��ͼ��"},
    {"���ص�ͼ���Ͳ˵�"}};
static char customMapMenuList[4][40] = { // �Զ����ͼ�ؿ��˵��б�
    {"�Զ����ͼһ"},
    {"�Զ����ͼ��"},
    {"�Զ����ͼ��"},
    {"���ص�ͼ���Ͳ˵�"}};
static char customOperationMenuList[5][40] = { // �Զ�������˵��б�
    {"��ʼ����"},
    {"��ʼ�༭"},
    {"���õ�ͼ"},
    {"��ȡ����"},
    {"�����Զ���˵�"}};
static char saveLoadMenuList[4][40] = { // �浵�˵��б�
    {"�����ϴ���Ϸ"},
    {"��ʼ����Ϸ"},
    {"����浵"},
    {"����"}};
static char controlModeMenuList[4][40] = { // ����ģʽ�˵��б�
    {"ʵʱģʽ"},
    {"���ģʽ"},
    {"��ȡ����"},
    {"����"}};
char (*menuList[])[40] = {  // �˵��б�
    mainMenuList,
    mapTypeMenuList,
    defaultMapMenuList,
    customMapMenuList,
    customOperationMenuList,
    saveLoadMenuList,
    controlModeMenuList};

static void mainMenu( MENU *pmenu ) ;                // ���˵�����
static void mapTypeMenu( MENU *pmenu ) ;             // ��ͼ����ѡ��˵�����
static void defaultMapMenu( MENU *pmenu ) ;          // Ĭ�ϵ�ͼ�˵�����
static void customMapMenu( MENU *pmenu ) ;           // �Զ����ͼ�˵�����
static void customOperationMenu() ;             // �Զ����ͼ�����˵�����
static void saveLoadMenu() ;                    // �浵��ȡ�˵�����
static void controlModeMenu() ;                 // ����ģʽ�˵�����
static int listNumCount( MENU menu ) ;       // ����˵�ѡ������
static void printMenu( MENU menu , int num ) ;                 // ��ӡ�˵�
static int cursorChoose( COORD loc , int num ) ;                  // �˵�����ƶ�����
static void freshCursor( COORD loc , int num , int pos ) ;        // �˵�����ƶ���ʾ�����

extern void runMenu()
{
    static void (*treeMenu[])( MENU * ) = { // ���ɺ�������ָ������
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
    printf("\nw���ƹ��,s���ƹ��,����<Enter>ѡ��\n");
}

static void freshCursor( COORD loc , int num , int pos )
{
    for( int i = 0 ; i < num ; i ++ )   // ˢ�¹��λ�ã���posλ�ô�ӡ���
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
    while( 1 )      // ����ƶ����ƣ���������ֱ��ѡ�У�����ѡ�й��ѡ������
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
    switch( op )
    {
        case 0:     // ��ͼһ
            system("cls");
            system("pause");    // TODO:����Ϸ����ӿ�ʩ��
            break;
        case 1:     // ��ͼ��
            break;
        case 2:     // ��ͼ��
            break;
        case 3:     // ���ص�ͼ���Ͳ˵�
            *pmenu = MAP_TYPE_MENU ;
            break;
    }
}

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
    switch( op )
    {
        case 0:     // �Զ����ͼһ
            system("cls");
            system("pause");    // TODO:���Զ�����Ϸ����ӿ�ʩ��
            break;
        case 1:     // �Զ����ͼ��
            break;
        case 2:     // �Զ����ͼ��
            break;
        case 3:     // ���ص�ͼ���Ͳ˵�
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
    system("mode con: cols=80 lines=30"); // �����ն˴��ڴ�С
    HideConsoleCursor();
    printf("�Թ���ð�գ�Version:2.1\n\n") ;
    system("pause");
    runMenu() ;
    return 0;
}