#include "01_menu.h"
#include "02_cursorOperation.h"
#include "03_mapAndPlayerStatus.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>

static const char moveInfo[7][100] = {      // ����������ƶ���Ϣ
    {"ƽƽ������ڿյ��Ͻ������ƶ�..."},
    {"��װ����ǽ�ڣ�����һ�ڣ�"},
    {"��ݺݵ���ԭ����Ϣ��һ�£�ʲôҲû�з���..."},
    {"�㲻С���߽������壬����ס�������ж�..."},
    {"�������ҵ���һ�����أ���ϲ��!"},
    {"�����������еı��أ���ϲ��!"},
    {"��Ĳ�����Ч��ʲôҲû�з���..."}};
char mapName[6][40] = {  // ��ͼ�ļ���
    {"map1.map"}, 
    {"map2.map"}, 
    {"map3.map"}, 
    {"mapCustom1.map"},
    {"mapCustom2.map"}, 
    {"mapCustom3.map"}};
char mapProgressSave[6][40] = { // ��ͼ���ȱ����ļ���
    {"map1.save"}, 
    {"map2.save"}, 
    {"map3.save"}, 
    {"mapCustom1.save"},
    {"mapCustom2.save"}, 
    {"mapCustom3.save"}};

static int infoPrix, infoPriy;  // ���ڴ洢��Ϸ��Ϣ���λ��
static int runGame;         // ��Ϸ����״̬:0��ʾ������1��ʾ����

void mapIni(struct mapInfo *mapInfo) // ��ʼ���Թ�
{
    memset(mapInfo->map, 0, sizeof(mapInfo->map));
    mapInfo->mapRow = 0;
    mapInfo->mapCol = 0;
    mapInfo->treasureNum = 0;
    mapInfo->trapNum = 0;
    return;
}

int mapInput(struct mapInfo *mapInfo, int mapOrder) // �����Թ�
{
    FILE *mapfp = NULL;
    mapfp = fopen(mapName[mapOrder - 1], "r");
    if (mapfp == NULL)
    {
        printf("��ͼ�ļ���ʧ��\n");
        return 0;
    }

    // �ж��Զ����ͼ�Ƿ�༭
    if (mapOrder >= 4)
    {
        char isEdit = 0;
        fscanf(mapfp, "%c", &isEdit);
        if (isEdit == '*')
        {
            ClearPartialScreen(0, 0); // �����Ļ
            printf("��ͼ��δ�༭�����ȱ༭��ͼ֮���ٽ������棡\n");
            system("pause");
            return 0;
        }
        else
            fseek(mapfp, 0, SEEK_SET);
    }

    /* ��ȡ��ͼ������Ϣ */
    fscanf(mapfp, "%d%d", &mapInfo->mapRow, &mapInfo->mapCol);
    fscanf(mapfp, "%d%d", &mapInfo->treasureNum, &mapInfo->trapNum);
    fscanf(mapfp, "%d%d", &mapInfo->pRow, &mapInfo->pCol);
    fgetc(mapfp); // ��ȡ���з�

    /* ��ȡ��ͼ������Ϣ */
    for (int i = 0; i < mapInfo->mapRow; i++)
    {
        for (int j = 0; j < mapInfo->mapCol; j++)
        {
            mapInfo->map[i][j] = fgetc(mapfp);
        }
        fgetc(mapfp); // ��ȡ���з�
    }
    fclose(mapfp);

    return 1;
}

void mapPrint(struct mapInfo *mapInfo) // ��ӡ�Թ�
{
    ClearPartialScreen(0, 0); // �����Ļ
    for (int i = 0; i < mapInfo->mapRow; i++)
    {
        for (int j = 0; j < mapInfo->mapCol; j++)
        {
            printf("%c ", mapInfo->map[i][j]);
        }
        printf("\n");
    }
    puts("");
    printf("��W�����ƶ�����S�����ƶ�����A�����ƶ�����D�����ƶ�����Iԭ�ز�������Z����һ�β�������Y����һ�β�������Q�˳���Ϸ\n");

    GetCursorPosition(&infoPrix, &infoPriy);        // ��ȡ��ǰ���λ��
    MoveCursorTo(2 * mapInfo->pCol, mapInfo->pRow); // �ƶ������λ��
    return;
}

void playerIni(struct playerInfo *player, struct mapInfo *mapInfo) // ��ʼ�������Ϣ
{
    runGame = 1;
    player->px = mapInfo->pRow;
    player->py = mapInfo->pCol;
    player->energyCost = 0;
    player->getTreasure = 0;
    player->isTrapped = 0;
    memset(player->moveMemory, 0, sizeof(player->moveMemory));
    memset(player->moveResult, 0, sizeof(player->moveResult));
    player->tt = 0;

    return;
}

void progressLoad(struct playerInfo *player, struct mapInfo *mapInfo, int mapOrder) // ���ش浵
{
    FILE *savefp = NULL;
    savefp = fopen(mapProgressSave[mapOrder - 1], "r");
    if( savefp == NULL )
    {
        printf("���ȱ����ļ���ʧ�ܣ�\n") ;
        return ;
    }

    /* ��ȡ�浵��Ϣ */
    char saveMovement[1000] = {0} ;
    while( fgetc( savefp ) != '*' ) ;   // ��Ծ��������Ϣ
    fscanf( savefp , "%s" , saveMovement ) ; // ��ȡ������Ϣ
    fclose( savefp ) ;

    /* ���������Ϣ */
    int len = strlen( saveMovement ) ;
    for( int i = 0 ; i < len ; i ++ )
    {
        char order = saveMovement[i] ;
        switch (order) // ����������ת��Ϊʵ�ʲ���
        {
        case 'U':
            order = 'w';
            break;
        case 'D':
            order = 's';
            break;
        case 'L':
            order = 'a';
            break;
        case 'R':
            order = 'd';
            break;
        }
        playerMoveJudge( player , mapInfo , order ) ;
    }
}

void playerInfoPrint(struct playerInfo *player, int num) // ��ӡ�����Ϣ
{
    // ��ӡ���λ��
    MoveCursorTo(2 * player->px, player->py);
    printf("Y");

    // ��ӡ��Ϸ��Ϣ
    ClearPartialScreen(infoPrix, infoPriy); // �ƶ�����Ϸ��Ϣ���λ�ò���պ�����Ϣ
    printf("��ǰλ�ã�(%d, %d)\n", player->px, player->py);
    printf("�ѻ�ñ��أ�%d\n", player->getTreasure);
    printf("������������%d\n", player->energyCost);
    if (player->isTrapped == 1)
    {
        printf("�㱻��ס�ˣ���һ���ж������������ӣ�\n");
    }
    else
        printf("\n");

    // ��ӡ�ж���Ϣ
    /**
     * �������-1
     * �����ж�0
     * ײǽ1
     * ��Ϣ2
     * ��������3
     * ��ñ���4
     * ������б���5
     * ��Ч����6
     */
    if (num >= 0)
        printf("%s\n", moveInfo[num]);

    return;
}

void exitInfoPrint(struct playerInfo *player)
{
    // ��ӡ��Ϸ������Ϣ
    ClearPartialScreen(infoPrix, infoPriy); // �ƶ�����Ϸ��Ϣ���λ�ò���պ�����Ϣ
    printf("============================================\n");
    printf("���ֽ��㣺\n\n");
    printf("�����ж�·����: %s\n", player->moveMemory);
    printf("��һ��������%d��������\n", player->energyCost);
    printf("��һ�������%d�����أ�\n\n", player->getTreasure);
    printf("��л������棡\n");
    printf("============================================\n\n");
    system("pause");

    return;
}

int playerMoveJudge(struct playerInfo *player, struct mapInfo *mapInfo, char order)
{
    // ֵ��ע����ǣ�����Ϊx������Ϊy
    int x = player->px;
    int y = player->py;
    int mapRow = mapInfo->mapRow;
    int mapCol = mapInfo->mapCol;
    int moveFlag = 0; // 0��ʾλ�ò��䣬1��ʾλ�øı�

    /**
     * ����ֵ���ܣ�
     * -1:��Ч�ж�����ֱ�ӽ�����Ϸ
     * 0:�����ж�
     * 1:ײǽ
     * 2:��Ϣ
     * 3:��������
     * 4:��ñ���
     * 5:������б���
     */
    

    // �ж�����ж�
    switch (order)
    {
    case 'i': // ԭ�ز���
        return 2;

    case 'q': // �˳���Ϸ
        runGame = 0;
        return -1;

    case 'w':
        player->moveMemory[player->tt] = 'U';
        if (y - 1 >= 0 && mapInfo->map[y - 1][x] == 'W')
        {
            player->moveResult[player->tt++] = 1;
            player->energyCost++;
            return 1;
        }
        else if (y - 1 >= 0)
        {
            moveFlag = 1;
            player->py--;
        }
        break;

    case 's':
        player->moveMemory[player->tt] = 'D';
        if (y + 1 < mapRow && mapInfo->map[y + 1][x] == 'W')
        {
            player->moveResult[player->tt++] = 1;
            player->energyCost++;
            return 1;
        }
        else if (y + 1 < mapRow)
        {
            moveFlag = 1;
            player->py++;
        }
        break;

    case 'a':
        player->moveMemory[player->tt] = 'L';
        if (x - 1 >= 0 && mapInfo->map[y][x - 1] == 'W')
        {
            player->moveResult[player->tt++] = 1;
            player->energyCost++;
            return 1;
        }
        else if (x - 1 >= 0)
        {
            moveFlag = 1;
            player->px--;
        }
        break;

    case 'd':
        player->moveMemory[player->tt] = 'R';
        if (x + 1 < mapCol && mapInfo->map[y][x + 1] == 'W')
        {
            player->moveResult[player->tt++] = 1;
            player->energyCost++;
            return 1;
        }
        else if (x + 1 < mapCol)
        {
            moveFlag = 1;
            player->px++;
        }
        break;
    }

    /**
     * ��ͼ��Ϣ˵��:
     * 'D'����
     * 'T'����
     * ' '�յ�
     */

    // �ж�����������λ�ñ仯���״̬�仯
    if (moveFlag)
    {
        player->energyCost++;
        int TrapFlag = 0;
        if (player->isTrapped == 1)
        {
            TrapFlag = 1;
            player->energyCost++;
            player->isTrapped = 0;
        }

        // �ж����λ�õؿ�
        if (mapInfo->map[player->py][player->px] == 'D')
        {
            if (TrapFlag == 1)
                player->moveResult[player->tt++] = 6;
            else
                player->moveResult[player->tt++] = 3;
            player->isTrapped = 1;
            return 3;
        }
        else if (mapInfo->map[player->py][player->px] == 'T')
        {
            if (TrapFlag == 1)
                player->moveResult[player->tt++] = 7;
            else
                player->moveResult[player->tt++] = 4;
            mapInfo->map[player->py][player->px] = ' ';
            player->getTreasure++;
            if (player->getTreasure == mapInfo->treasureNum)
            {
                runGame = 0;
                return 5;
            }
            return 4;
        }
        else
        {
            if (TrapFlag == 1)
                player->moveResult[player->tt++] = 5;
            else
                player->moveResult[player->tt++] = 2;
            return 0;
        }
    }
}

void moveBack(struct playerInfo *player, struct mapInfo *mapInfo)   // ��������
{
    if (player->tt == 0)
    {
        playerInfoPrint(player, -1);
        printf("�㻹û���ƶ������޷�������\n");
        return;
    }

    char order = player->moveMemory[player->tt - 1];
    int result = player->moveResult[player->tt - 1];
    player->tt--;

    // ��¼�ָ�ǰλ��
    int tx = 2 * player->px, ty = player->py;

    // �ָ�λ����״̬
    if (result == 1)
    {
        player->energyCost--;
    }
    else
    {
        // �ָ�λ��
        switch (order)
        {
        case 'U':
            player->py++;
            break;
        case 'D':
            player->py--;
            break;
        case 'L':
            player->px++;
            break;
        case 'R':
            player->px--;
            break;
        }

        // �ָ���������״̬
        if (result >= 5)
        {
            player->energyCost -= 2;
            player->isTrapped = 1;
        }
        else
        {
            player->energyCost--;
            player->isTrapped = 0;
        }

        // �ָ�������ͼ����״̬
        if (result == 4 || result == 7)
        {
            player->getTreasure--;
            mapInfo->map[ty][tx / 2] = 'T';
        }
    }

    // �ָ���ͼ״̬����ʾ
    playerInfoPrint(player, -1);
    printf("�����ɹ���\n");

    MoveCursorTo(tx, ty);
    switch (result)
    {
    case 2:
        printf(" ");
        break;
    case 3:
        printf("D");
        break;
    case 4:
        printf("T");
        break;
    case 5:
        printf(" ");
        break;
    case 6:
        printf("D");
        break;
    case 7:
        printf("T");
        break;
    }

    return;
}

char moveRedo(struct playerInfo *player, struct mapInfo *mapInfo)   // ��������
{
    if (player->moveResult[player->tt] == 0)
    {
        playerInfoPrint(player, -1);
        printf("���Ѿ�������״̬���޷�������\n");
        return 0;
    }

    char order = player->moveMemory[player->tt];
    switch (order)
    {
    case 'U':
        order = 'w';
        break;
    case 'D':
        order = 's';
        break;
    case 'L':
        order = 'a';
        break;
    case 'R':
        order = 'd';
        break;
    }
    return order;
}

void saveOperation( struct playerInfo *player , struct mapInfo *mapInfo , int mapOrder )    // ������Ϸ����
{
    /* �򿪴浵�ļ�д�� */
    FILE *savefp = NULL ;
    savefp = fopen( mapProgressSave[ mapOrder - 1 ] , "w" ) ;
    if( savefp == NULL )
    {
        printf("���ȱ����ļ���ʧ�ܣ�\n") ;
        return ;
    }

    /* д��浵��Ϣ */
    time_t t = time(NULL);
    char timeStr[64];
    strftime( timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", localtime(&t) );
    fprintf( savefp , "%s\n" , timeStr ) ;              // д�뱣��ʱ��
    fprintf( savefp , "%d %d\n" , player->getTreasure , mapInfo->treasureNum ) ; // д�뱦����Ϣ
    fprintf( savefp , "*%s\n" , player->moveMemory ) ;// д���ƶ�·��
    fprintf( savefp , "]") ; // д�������־

    // ע�⣺���û�ر��ļ����ļ�ֻ���ڳ����˳�ʱ�Żᱻ����
    fclose( savefp ) ;
}

void progressAutoSave( struct playerInfo *player , struct mapInfo *mapInfo , int steps , int mode , int mapOrder )      // �Զ�������Ϸ����
{
    /* �ж��Ƿ�����Զ����� */
    int saveFlag = 0;   // �����־
    if( mode ) saveFlag = 1 ;   // ���ģʽĬ�ϱ���
    else if( steps && steps % 10 == 0 ) saveFlag = 1 ;   // ʵʱģʽÿ10������һ��

    if( !saveFlag ) return ;
    saveOperation( player , mapInfo , mapOrder ) ;
}

void progressExitSave( struct playerInfo *player , struct mapInfo *mapInfo , int mapOrder)     // �˳�������Ϸ����
{
    /* �ж��Ƿ���б������ */
    ClearPartialScreen(0, 0); // �����Ļ
    printf("�Ƿ񱣴浱ǰ��Ϸ���ȣ�(y/n)\n");
    char order = '\0';
    while( order != 'y' && order != 'n' )
        order = getch();

    if( order == 'y' )
    {
        saveOperation( player , mapInfo , mapOrder ) ;
        ClearPartialScreen(0, 0); // �����Ļ
        printf("��Ϸ���ȱ���ɹ�\n");
        system("pause");
    }
    else
    {
        progressSaveInit( mapOrder ) ;
        ClearPartialScreen(0, 0); // �����Ļ
        printf("�ѷ���������Ϸ����\n");
        system("pause");
    }
}

void progressSaveInit( int mapOrder )    // ��ʼ���浵��Ϣ
{
    FILE *savefp = NULL ;
    savefp = fopen( mapProgressSave[ mapOrder - 1 ] , "w" ) ;
    if( savefp == NULL )
    {
        printf("���ȱ����ļ���ʧ�ܣ�\n") ;
        return ;
    }
    fprintf( savefp , "*") ; // д��δ�༭��־
    fclose( savefp ) ;
}

void playerMove(struct playerInfo *player, struct mapInfo *mapInfo, int mapOrder ) // ����ƶ�ʵʱģʽ
{
    playerInfoPrint(player, -1);

    /* ��Ϸ�������� */
    while (runGame)
    {
        char order = '\0';
        order = getch();

        /* �������� */
        // ��Ч�������������������ң���Ϣ���˳�
        if (order == 'y' || order == 'w' || order == 's' || order == 'a' || order == 'd' || order == 'i' || order == 'q')
        {
            int coverFlag = 0;  // �����ж��Ƿ񸲸���һ�β�������ֹ�²������쳣������
            if( order == 'w' || order == 's' || order == 'a' || order == 'd' )
                coverFlag = 1 ;

            if (order == 'y') // ����������order���д���
                order = moveRedo(player, mapInfo);
            if (order == 0) // �Ѿ�������״̬��ֱ�ӽ�����һ������
                continue;

            int tx = 2 * player->px, ty = player->py;
            int printFlag = playerMoveJudge(player, mapInfo, order);
            if( coverFlag ) player->moveMemory[player->tt] = 0; // ������һ�β���
            if (printFlag == -1 ) // ǿ���˳���Ϸ
            {
                // �����Ϣ
                ClearPartialScreen(0, 0); // �����Ļ
                printf("ǿ���˳�����Ϸ������\n\n");
                infoPrix = 0, infoPriy = 2;
                exitInfoPrint(player);

                // ȷ���Ƿ񱣴���Ϸ����
                progressExitSave( player , mapInfo , mapOrder ) ;
                return;
            }

            // ɾ�����ߴ�ӡ��һ��λ��
            if (player->tt > 0 && player->moveResult[player->tt - 1] >= 5)
            {
                MoveCursorTo(tx, ty);
                printf("D"); // ���岻����
            }
            else
            {
                MoveCursorTo(tx, ty);
                printf(" ");
            }

            // ��ӡ�µ������Ϣ
            playerInfoPrint(player, printFlag);
        }
        // ��Ч����������
        else if (order == 'z')
        {
            moveBack(player, mapInfo);
        }
        // ��Ч����
        else
        {
            playerInfoPrint(player, 6);
        }

        // �Զ�������Ϸ����
        progressAutoSave(player, mapInfo, player->tt - 1, 0 , mapOrder ) ;
    }

    /* ���������Ϸ���� */
    progressSaveInit( mapOrder ) ;
    ClearPartialScreen(0, 0); // �����Ļ
    printf("���ɹ��ҵ����б��أ���Ϸ������\n\n");
    infoPrix = 0, infoPriy = 2;
    exitInfoPrint(player);
    return;
}

void playerMovePro(struct playerInfo *player, struct mapInfo *mapInfo, int mapOrder) // ����ƶ����ģʽ
{
    playerInfoPrint(player, -1);

    /* ��Ϸ�������� */
    while (runGame)
    {
        char orderList[250] = {0}; // ���ڴ洢���ÿ�εĲ�������
        /**
         * �������н���:
         * U����
         * D����
         * L����
         * R����
         * ��������ֱ���˳�
         */

        // �����������
        printf("��������Ĳ������У�\n");
        scanf("%s", orderList);
        getchar(); // ��ȡ�س�

        int tp = player->tt, tx = 2 * player->px, ty = player->py;
        /**
         * tp: ���ڼ�¼�������п�ʼǰ�Ĳ������г���
         * tx, ty: ���ڼ�¼�������п�ʼǰ�����λ��
         */
        int len = strlen(orderList);
        for (int i = 0; i < len; i++)   // �����������
        {
            char order = 0;
            switch (orderList[i])   // ����������ת��Ϊʵ�ʲ���
            {
            case 'U':
                order = 'w';
                break;
            case 'D':
                order = 's';
                break;
            case 'L':
                order = 'a';
                break;
            case 'R':
                order = 'd';
                break;
            case 'Q':
            {
                // �����Ϣ
                ClearPartialScreen(0, 0); // �����Ļ
                printf("ǿ���˳�����Ϸ������\n\n");
                infoPrix = 0, infoPriy = 2;
                exitInfoPrint(player);

                // ȷ���Ƿ񱣴���Ϸ����
                progressExitSave( player , mapInfo , mapOrder ) ;
                return;
            }
            default:
            {
                progressSaveInit( mapOrder ) ;
                ClearPartialScreen(0, 0); // �����Ļ
                printf("���ģʽ�²���������Ϸ������\n\n");
                infoPrix = 0, infoPriy = 2;
                exitInfoPrint(player);
                return;
            }
            }

            // ת����ɣ���ʼ�ж���Ҳ���
            int printFlag = playerMoveJudge(player, mapInfo, order);
            if (printFlag == 1) // ���������˳�
            {
                runGame = 0;

                progressSaveInit( mapOrder ) ;
                ClearPartialScreen(0, 0); // �����Ļ
                printf("���ģʽ�²���������Ϸ������\n\n");
                infoPrix = 0, infoPriy = 2;
                exitInfoPrint(player);
                return;
            }
            if (printFlag == 5) // �����Ϸ�˳�
            {
                progressSaveInit( mapOrder ) ;
                ClearPartialScreen(0, 0); // �����Ļ
                printf("���ɹ��ҵ����б��أ���Ϸ������\n\n");
                infoPrix = 0, infoPriy = 2;
                exitInfoPrint(player);
                return;
            }
        }

        // ɾ�����ߴ�ӡ��һ��λ��
        if (tp > 0 && player->moveResult[tp] >= 5)
        {
            MoveCursorTo(tx, ty);
            printf("D"); // ���岻����
        }
        else
        {
            MoveCursorTo(tx, ty);
            printf(" ");
        }

        // ��ӡ�µ������Ϣ
        playerInfoPrint(player, -1);

        // �Զ�������Ϸ����
        progressAutoSave(player, mapInfo, player->tt - 1, 1 , mapOrder ) ;
    }
}
