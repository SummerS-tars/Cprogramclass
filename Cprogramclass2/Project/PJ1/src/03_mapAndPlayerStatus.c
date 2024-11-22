#include "03_mapAndPlayerStatus.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include "02_cursorOperation.h"

const char moveInfo[7][100] = {
    {"ƽƽ������ڿյ��Ͻ������ƶ�..."},
    {"��װ����ǽ�ڣ�����һ�ڣ�"},
    {"��ݺݵ���ԭ����Ϣ��һ�£�ʲôҲû�з���..."},
    {"�㲻С���߽������壬����ס�������ж�..."},
    {"�������ҵ���һ�����أ���ϲ��!"},
    {"�����������еı��أ���ϲ��!"},
    {"��Ĳ�����Ч��ʲôҲû�з���..."}};

int runGame; // ��Ϸ����״̬

static int infoPrix, infoPriy;

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
    switch (mapOrder)
    {
    case 1:
        mapfp = fopen("map1.txt", "r");
        break;
    case 2:
        mapfp = fopen("map2.txt", "r");
        break;
    case 3:
        mapfp = fopen("map3.txt", "r");
        break;
    case 4:
        mapfp = fopen("mapCustom1.txt", "r");
        break;
    case 5:
        mapfp = fopen("mapCustom2.txt", "r");
        break;
    case 6:
        mapfp = fopen("mapCustom3.txt", "r");
        break;
    default:
        break;
    }
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

    fscanf(mapfp, "%d%d", &mapInfo->mapRow, &mapInfo->mapCol);
    fscanf(mapfp, "%d%d", &mapInfo->treasureNum, &mapInfo->trapNum);
    fscanf(mapfp, "%d%d", &mapInfo->pRow, &mapInfo->pCol);
    fgetc(mapfp); // ��ȡ���з�

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
    /*
    �������-1
    �����ж�0
    ײǽ1
    ��Ϣ2
    ��������3
    ��ñ���4
    ������б���5
    ��Ч����6
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

    /*
    ����ֵ���ܣ�
    -1:��Ч�ж�����ֱ�ӽ�����Ϸ
    0:�����ж�
    1:ײǽ
    2:��Ϣ
    3:��������
    4:��ñ���
    5:������б���
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

    /* ��ͼ��Ϣ˵��:
     * 'D'����
     * 'T'����
     * ' '�յ�
     */

    // �ж����λ�ñ仯���״̬�仯
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

void moveBack(struct playerInfo *player, struct mapInfo *mapInfo)
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

char moveRedo(struct playerInfo *player, struct mapInfo *mapInfo)
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

void playerMove(struct playerInfo *player, struct mapInfo *mapInfo) // ����ƶ�ʵʱģʽ
{
    playerInfoPrint(player, -1);

    while (runGame)
    {
        char order = '\0';
        order = getch();

        // ������Ч����
        if (order == 'y' || order == 'w' || order == 's' || order == 'a' || order == 'd' || order == 'i' || order == 'q')
        {
            if (order == 'y')
                order = moveRedo(player, mapInfo);
            if (order == 0)
                continue;

            int tx = 2 * player->px, ty = player->py;
            int printFlag = playerMoveJudge(player, mapInfo, order);
            if (printFlag == -1)
            {
                ClearPartialScreen(0, 0); // �����Ļ
                printf("ǿ���˳�����Ϸ������\n\n");
                infoPrix = 0, infoPriy = 2;
                exitInfoPrint(player);
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
        else if (order == 'z')
        {
            moveBack(player, mapInfo);
        }
        else
        {
            playerInfoPrint(player, 6);
        }
    }

    ClearPartialScreen(0, 0); // �����Ļ
    printf("���ɹ��ҵ����б��أ���Ϸ������\n\n");
    infoPrix = 0, infoPriy = 2;
    exitInfoPrint(player);
    return;
}

void playerMovePro(struct playerInfo *player, struct mapInfo *mapInfo) // ����ƶ����ģʽ
{
    playerInfoPrint(player, -1);

    while (runGame)
    {
        char orderList[250] = {0}; // ���ڴ洢��Ҳ�������
        /* �������н���:
         * U����
         * D����
         * L����
         * R����
         * ��������ֱ���˳�
         */

        printf("��������Ĳ������У�\n");
        scanf("%s", orderList);
        getchar(); // ��ȡ�س�

        int tp = player->tt, tx = 2 * player->px, ty = player->py;
        int len = strlen(orderList);
        for (int i = 0; i < len; i++)
        {
            char order = 0;
            switch (orderList[i])
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
            default:
            {
                ClearPartialScreen(0, 0); // �����Ļ
                printf("���ģʽ�²���������Ϸ������\n\n");
                infoPrix = 0, infoPriy = 2;
                exitInfoPrint(player);
                return;
            }
            }
            int printFlag = playerMoveJudge(player, mapInfo, order);

            if (printFlag == 1)
            {
                runGame = 0;

                ClearPartialScreen(0, 0); // �����Ļ
                printf("���ģʽ�²���������Ϸ������\n\n");
                infoPrix = 0, infoPriy = 2;
                exitInfoPrint(player);
                return;
            }

            if (printFlag == 5)
            {
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
    }
}