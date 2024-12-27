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

// �༭���ȶ�ȡ
static void editProgressLoad( struct mapInfo *mapInfo , int mapOrder , int *Tnum , int *Dnum , int *playerSetFlag )
{
    /* ��ͼ��Ϣ���� */
    int openRight = mapInput( mapInfo , mapOrder ) ;      // TODO:������ͼ�򿪼��
    if( !openRight )
    {
        system("cls") ;
        printf("��ͼ�ļ���ʧ��\n") ;
        system("pause") ;
        return ;
    }

    /* ��ͼ���ȶ��� */
    FILE *mapfp = NULL ;
    mapfp = fopen( mapPath[ mapOrder - 1 ] , "r" ) ;
    if( mapfp == NULL )
    {
        perror("Error opening file");
        return ;
    }
    for( int i = 1 ; ; i ++ )   // ��λ��������Ϣ
    {
        fseek( mapfp , (long)-i , SEEK_END ) ;
        char ch = fgetc( mapfp ) ;
        if( ch == '[' ) break ;
    }
    fscanf( mapfp , "%d %d %d" , Tnum , Dnum , playerSetFlag ) ; // TODO:����
    fclose(mapfp) ; // TODO:BUG4�޸�����:�ر��ļ�
}

// �༭��ͼ�洢
static void editMapSave( struct mapInfo *mapInfo , int mapOrder , int Tnum , int Dnum , int playerSetFlag )
{
    /* ��ͼ�༭��ɶȼ�� */
    int finishFlag = 0 ;
    if( Tnum == mapInfo->treasureNum && Dnum == mapInfo->trapNum && playerSetFlag ) finishFlag = 1 ;
    else finishFlag = 0 ;

    /* ѡ���ͼ�ļ� */
    FILE *mapfp = NULL ;
    mapfp = fopen( mapPath[ mapOrder - 1 ] , "w" ) ;
    if( mapfp == NULL )
    {
        perror("Error opening file");
        return ;
    }

    /* д���ͼ��Ϣ */
    fprintf(mapfp, "%d %d\n", mapInfo->mapRow, mapInfo->mapCol);
    fprintf(mapfp, "%d %d\n", mapInfo->treasureNum, mapInfo->trapNum);
    fprintf(mapfp, "%d %d\n", mapInfo->pRow, mapInfo->pCol );   // TODO:������¼:����mapInput�����ĵ�ͼ��Ϣ����˳�����
    for( int i = 0 ; i < mapInfo->mapRow ; i ++ )
    {
        for( int j = 0 ; j < mapInfo->mapCol ; j ++ )
        {
            fputc(mapInfo->map[i][j], mapfp);
        }
        fputc('\n', mapfp);
    }
    if( !finishFlag ) fprintf(mapfp, "[%d %d %d]" , Tnum , Dnum , playerSetFlag ) ; // δ��ɱ༭ʱ�洢�༭���Ⱥ�δ��ɱ�־
    else fprintf(mapfp, "[%d %d %d*" , Tnum , Dnum , playerSetFlag ) ; // ��ɱ༭ʱ�洢�༭���Ⱥ���ɱ�־
    fclose(mapfp);

    system("cls") ;
    printf("�ѳɹ��༭����ɱ��棡\n") ;
    system("pause") ;
    return ;
}

// ��ͼ��Ϣ��ʾˢ��
static void editInfoPrintFresh( struct mapInfo *mapInfo , COORD *loc , int ix , int iy , int Tnum , int Dnum , int playerSetFlag , int Order )
{
    // TODO:BUG�޸���¼:editInfoPrintFresh��X��Y�Ѿ������Ե�
    // TODO:BUT�޸���¼:�����˵�ͼ������ʾ����λ�����ർ�µ����Ų��Գ�����
    enum { MAP_POS = 0 , POS_INFO = 1 , PLAYER_POS = 2 , TREASURE_INFO = 3 , TRAP_INFO = 4 };
    enum { UP = 1 , DOWN , LEFT , RIGHT , WALL , EMPTY , TRAP , TREASURE , PLAYER , SAVE , QUIT } ;

    
    if( Order == UP || Order == DOWN || Order == LEFT || Order == RIGHT )   // ������£�����ƶ�
    {
        HideConsoleCursor() ;
        MoveCursorTo( loc[POS_INFO].X , loc[POS_INFO].Y ) ;
        printf("( %2d , %2d )\n" , ix , iy ) ;
        MoveCursorTo( loc[MAP_POS].X + 2 * ix , loc[MAP_POS].Y + iy ) ;
        ShowConsoleCursor() ;
    }
    else if( Order == WALL || Order == EMPTY || Order == TRAP || Order == TREASURE || Order == PLAYER ) // ��Ϣ��ʾ���£��ؿ���ʾ����
    {
        HideConsoleCursor() ;
        if( Order == PLAYER ) putchar('Y') ;        // TODO:BUG11�޸���¼:�޸������λ����Ϣ��ʾ����
        else putchar(mapInfo->map[iy][ix]) ;  // �ؿ���Ϣ����    // TODO:BUG10�޸���¼���޸��˵ؿ���Ϣˢ�´���
        MoveCursorTo( loc[ TREASURE_INFO ].X , loc[ TREASURE_INFO ].Y ) ;
        printf("%3d/%3d" , Tnum , mapInfo->treasureNum ) ;  // ������Ϣ����
        MoveCursorTo( loc[ TRAP_INFO ].X , loc[ TRAP_INFO ].Y ) ;
        printf("%3d/%3d" , Dnum , mapInfo->trapNum ) ;  // ������Ϣ����
        MoveCursorTo( loc[ PLAYER_POS ].X , loc[ PLAYER_POS ].Y ) ;
        printf("                    ") ;  // ���ԭλ����Ϣ
        MoveCursorTo( loc[ PLAYER_POS ].X , loc[ PLAYER_POS ].Y ) ;
        if( playerSetFlag ) printf("( %d , %d )\n" , mapInfo->pCol , mapInfo->pRow ) ;  // TODO:BUG8�޸���¼:�޸������λ����Ϣˢ�´���
        else printf("δ����\n") ;  // ���λ����Ϣ����

        MoveCursorTo( loc[MAP_POS].X + 2 * ix , loc[MAP_POS].Y + iy ) ; // ����ƶ�
        ShowConsoleCursor() ;
    }
    else if( Order == SAVE || Order == QUIT ) return ;
    else return ;
}

// �ؿ��滻
static void editMapReplace( struct mapInfo *mapInfo , COORD loc , int ix , int iy , int *Tnum , int *Dnum , int *playerSetFlag , int Order )
{
    // TODO:BUG�޸���¼:editMapReplace��X��Y�ѶԵ�
    enum { UP = 1 , DOWN , LEFT , RIGHT , WALL , EMPTY , TRAP , TREASURE , PLAYER , SAVE , QUIT } ;
    char newMap = 0 ;

    // �ؿ鸳ֵ�Լ���������
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
            if( *playerSetFlag )  // ����������ҳ�ʼλ�ã���ԭλ����Ϊ�յ�
            {
                MoveCursorTo( loc.X + 2 * mapInfo->pCol , loc.Y + mapInfo->pRow ) ;
                putchar(' ') ;
                MoveCursorTo( loc.X + 2 * ix , loc.Y + iy ) ;   // TODO:BUG11�޸���¼:�޸������λ������ʱ��λ�ô�ӡ���������
            }
            break ;
    }

    // �ؿ��滻�Լ���Ϣ����
    char *oldMap = &mapInfo->map[iy][ix] ;  // TODO:BUG5�޸���¼:������ix��iy��˳�򣬳����޸������ǵ�ͼ��Ϣ����ʱ��������µ��������
    if( *oldMap == newMap ) // �¾ɵ�ͼ�ؿ����ʱֱ���˳������ټ�����
    {
        if( *oldMap == ' ' && ix == mapInfo->pCol && iy == mapInfo->pRow ) ;
        else return ;    // TODO:BUG13�޸���¼2�����������ҳ�ʼλ�õؿ�ļ��
    }

    switch( *oldMap )   // �ɵ�ͼ����ؿ鴦��
    {
        case 'T': 
            (*Tnum) -- ;
            break ;
        case 'D': 
            (*Dnum) -- ;
            break ;
    }
    if( *playerSetFlag && ix == mapInfo->pCol && iy == mapInfo->pRow ) // TODO:BUG13�޸���¼�������˶Ծɵ�ͼΪ��ҳ�ʼλ��ʱ�ļ������
        *playerSetFlag = 0 , mapInfo->pRow = mapInfo->pCol = -1 ;

    switch( newMap )        // �µ�ͼ����
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
            *oldMap = ' ' ;     // TODO:BUG11�޸���¼:�޸������λ������ʱԭλ��δ��յ�����
            *playerSetFlag = 1;
            mapInfo->pRow = iy , mapInfo->pCol = ix ;       // TODO:BUG9�޸���¼:���������λ����Ϣ�洢��������λ�õ���
            break ;
    }
}

// �༭�����
static void editOrderInput( struct mapInfo *mapInfo , COORD loc , int *px , int *py , int *Tnum , int *Dnum , int *playerSetFlag , int Order )
{
    // TODO:BUG�޸���¼,editOrderInput��X��Y�ѶԵ�
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

// �༭�����ȡ
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
        default: return 0;  // ��Ч����
    }
    return 0 ;  // ��Ч����
}

// �༭��ͼ����
static int editMap( struct mapInfo *mapInfo , COORD *loc , int *Tnum , int *Dnum , int *playerSetFlag)
{
    enum { MAP_POS = 0 , POS_INFO = 1 , PLAYER_POS = 2 , TREASURE_INFO = 3 , TRAP_INFO = 4 };
    enum { UP = 1 , DOWN , LEFT , RIGHT , WALL , EMPTY , TRAP , TREASURE , PLAYER , SAVE , QUIT } ;
    int px = 0 , py = 0 ;
    MoveCursorTo( loc[MAP_POS].X , loc[MAP_POS].Y ) ; // TODO:BUG�޸���¼:�����˴�ӡ���ͼ����λ�ò��Ե�����


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

// �༭�����ӡ�Լ���Ϣ�洢
static void editPrint( int mapOrder , struct mapInfo *mapInfo , COORD *loc , int Tnum , int Dnum , int playerSetFlag )
{
    // TODO:BUG�޸���¼:�����˵�ͼ�����ӡʱ���ܳ��ֵ�λ����λ���µ���������쳣����
    enum { MAP_POS = 0 , POS_INFO = 1 , PLAYER_POS = 2 , TREASURE_INFO = 3 , TRAP_INFO = 4 };
    int tpx = 0 , tpy = 0;

    /* ��ӡ��ʼ��Ϣ���沢�洢��Ϣ���λ�� */
    system("cls") ;
    printf("���ڱ༭��<%s>\n" , mapName[ mapOrder - 1 ] ) ;
    printf("��ǰλ��: ") ;
    GetCursorPosition( &tpx , &tpy ) ;
    loc[ POS_INFO ].X = tpx , loc[ POS_INFO ].Y = tpy ; // ��Ϣ��ӡλ��1
    printf("( %2d , %2d )\n" , 0 , 0 ) ;
    printf("��ҳ�ʼλ�ã�") ;
    GetCursorPosition( &tpx , &tpy ) ;
    loc[ PLAYER_POS ].X = tpx , loc[ PLAYER_POS ].Y = tpy ; // ��Ϣ��ӡλ��2
    if( playerSetFlag ) printf("( %d , %d )\n" , mapInfo->pCol , mapInfo->pRow ) ;      // TODO:BUG9�޸���¼:�������λ�ó�ʼ������������
    else printf("δ����\n") ;
    printf("����������") ;
    GetCursorPosition( &tpx , &tpy ) ;
    loc[ TREASURE_INFO ].X = tpx , loc[ TREASURE_INFO ].Y = tpy ; // ��Ϣ��ӡλ��3
    printf("%3d/%3d   " , Tnum , mapInfo->treasureNum ) ;
    printf("����������") ;
    GetCursorPosition( &tpx , &tpy ) ;
    loc[ TRAP_INFO ].X = tpx , loc[ TRAP_INFO ].Y = tpy ; // ��Ϣ��ӡλ��4
    printf("%3d/%3d\n\n" , Dnum , mapInfo->trapNum ) ;
    GetCursorPosition( &tpx , &tpy ) ;
    loc[ MAP_POS ].X = tpx , loc[ MAP_POS ].Y = tpy ; // ��ǰ���λ��

    /* ��ӡ��ͼ���� */
    for( int i = 0 ; i < mapInfo->mapRow ; i ++ )
    {
        for( int j = 0 ; j < mapInfo->mapCol ; j ++ )
        {
            printf("%c " , mapInfo->map[i][j]) ;
        }
        printf("\n");
    }

    /* ��ӡ������Ϣ */
    puts("") ;
    printf("<w>���ƹ�꣬<s>���ƹ�꣬<a>���ƹ�꣬<d>���ƹ��\n") ;
    printf("<1>���ǽ'W'��<2>��ӿյ�' '��<3>�������'D'��<4>��ӱ���'T'��<5>�����ҳ�ʼλ��'Y'\n") ;
    printf("<q>�������˳��༭��<z>�����˳��༭") ;

    /* ������� */
    if( playerSetFlag ) // TODO:BUG�޸���¼:�����˵�һ�δ�ӡ��ͼ���ܳ��ֵ����δ��ӡ������
    {
        MoveCursorTo( loc[ MAP_POS ].X + 2 * mapInfo->pCol , loc[ MAP_POS ].Y + mapInfo->pRow ) ;   // TODO:BUG9�޸���¼:�������λ�ó�ʼ������������
        putchar('Y') ;
    }
    // TODO:Ҫ���ı��棬���к��У�XӦ�ô��У�Y����
}

// �༭��ͼʱ��ʼ����ͼ��Ϣ
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

// �ɽ�����ֵ��Χ����
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

// ���õ�ͼ����
// ���ƣ�
// 1. ��ͼ�в�����30���в�����49
// 2. ��������������100�����ڵ�ͼ��С
// 3. ��������������200���뱦������֮�����ڵ�ͼ��С
static void mapInfoSet( struct mapInfo *mapInfo )
{
    enum { ROW = 0, COL, TREASURE, TRAP };
    int *pSet[] = { &mapInfo->mapRow, &mapInfo->mapCol, &mapInfo->treasureNum, &mapInfo->trapNum };
    char *info[] = { "����", "����", "��������", "��������" };

    int px = 0 , py = 0 ;
    for( int i = 0 ; i < 4 ; )
    {
        HideConsoleCursor() ;
        system("cls") ;
        printf("�������õ�ͼ����-->%s\n\n", info[i]);
        printf("������һ������ֵ��");
        GetCursorPosition( &px , &py ) ;
        printf("\n\n") ;    // TODO:BUG�޸���¼:���������õ�ͼ����ʱ���λ�ò��Ե�����

        int min = 0 , max = 0 ;
        acceptNumSet( &min , &max , pSet , i ) ;
        printf("����ֵ��Χ��[ %d - %d ]", min , max ) ;
        MoveCursorTo( px , py ) ;
        ShowConsoleCursor() ;

        int num = 0 ;
        scanf("%d" , &num) ;
        if( num >= min && num <= max )
        {
            *pSet[i] = num ;
            i ++ ;
        }
        else    // TODO:������
        {
            system("cls") ;
            printf("����ֵ���ڿ��з�Χ�ڣ����������룡\n") ;
            system("pause") ;
        }
    }
    system("cls") ;
}

// ��ʼ������Թ�
// printInfo: 1-��ӡ��ʼ���ɹ���Ϣ��0-����ӡ
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
    printf("��ʼ���ɹ���\n");
    system("pause");
    }

    progressSaveInit( mapOrder ) ; // ͬʱ��ʼ����Ϸ�浵  // TODO:BUG7�޸���¼:�����˵��ò���������浵��ʼ��ʧЧ������
    system("cls");
    return ;
}

// �༭����Թ�
// loadFlag: 0-�½���ͼ��1-�����༭��ͼ
extern void mapCustomEdit( int mapOrder , int loadFlag )   
{
    /* ��ʼ�� */
    int Tnum = 0 , Dnum = 0 ;
    int playerSetFlag = 0 ;
    struct mapInfo mapInfo;
    mapIni( &mapInfo );

    /* ����ͼ�Ƿ�༭״̬��ѡ���Ƿ�����༭ */
    if( loadFlag )
    {
        progressSaveInit( mapOrder ) ; // ��ʼ����Ϸ�浵  // TODO:BUG7�޸���¼:���Ӵ浵��ʼ��������༭�������ͼʱ�浵��ʼ������
        editProgressLoad( &mapInfo , mapOrder , &Tnum , &Dnum , &playerSetFlag ) ;
    }
    else
    {   // ��ʼ��
        mapCustomIni( mapOrder , 0 ) ;

        // ���õ�ͼ��Ϣ
        mapInfoSet( &mapInfo );

        // ��ʼ����ʱ�༭��ͼ
        editInit( &mapInfo );
    }

    // �༭�����ӡ����Ϣ�洢
    /**
     * 0 ��ǰ���λ�ã��ڵ�ͼ�ϵ�λ��
     * 1 ��Ϣ��ӡλ��1��λ����Ϣ
     * 2 ��Ϣ��ӡλ��2����ҳ�ʼλ����Ϣ�������Ƿ������ã������������ӡ��ҳ�ʼλ��
     * 3 ��Ϣ��ӡλ��3��������������
     * 4 ��Ϣ��ӡλ��4��������������
     */
    COORD loc[5] = { {0, 0}, {0, 0} , {0, 0}, {0, 0}, {0, 0} };
    enum { MAP_POS = 0 , POS_INFO = 1 , PLAYER_POS = 2 , TREASURE_INFO = 3 , TRAP_INFO = 4 };
    editPrint( mapOrder , &mapInfo , loc , Tnum , Dnum , playerSetFlag ) ;

    /* �༭��ͼ */
    int saveFlag = 0 ;
    saveFlag = editMap( &mapInfo , loc , &Tnum , &Dnum , &playerSetFlag ) ;

    /* �洢��ͼ */
    if( saveFlag ) editMapSave( &mapInfo , mapOrder , Tnum , Dnum , playerSetFlag ) ;

    // TODO:����ͨ��
}