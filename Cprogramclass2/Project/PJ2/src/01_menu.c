#include "01_menu.h"
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include "03_mapAndPlayerStatus.h"
#include "02_cursorOperation.h"
#include "04_mapCustom.h"

// �˵��б�
static char menuMainList[3][40] = { // ���˵��б�
    {"��ʼ��Ϸ"},
    {"��ȡ����"},
    {"�˳���Ϸ"}};
static char menuGameList[5][40] = { // ��Ϸ�˵��б�
    {"��һ��"},
    {"�ڶ���"},
    {"������"},
    {"�Զ���ؿ�"},
    {"�������˵�"}};
static char menuControlMode[3][40] = { // ����ģʽ�˵��б�
    {"ʵʱģʽ"},
    {"���ģʽ"},
    {"���ص�ͼ�˵�"}};
static char menuCustomMap[4][40] = { // �Զ����ͼ�˵��б�
    {"�Զ����ͼһ"},
    {"�Զ����ͼ��"},
    {"�Զ����ͼ��"},
    {"���ص�ͼ�˵�"}};
static char menuCustomOperation[4][40] = { // �Զ�������˵��б�
    {"��ʼ�༭"},
    {"��ʼ����"},
    {"���õ�ͼ"},
    {"�����Զ���˵�"}};
static char (*menuList[5])[40] = {
    menuMainList,
    menuGameList,
    menuControlMode,
    menuCustomMap,
    menuCustomOperation};
static int menuOption[5] = {3, 5, 3, 4, 4}; // �˵�ѡ������

static void menuPrint(int menuOrder, int listPos) // �˵�����������listPos�������ƹ��λ��
{
    for (int i = 0; i < menuOption[menuOrder]; i++)
    {
        if (i == listPos)
            printf("> ");
        else
            printf("  ");
        printf("%s\n", menuList[menuOrder] + i);
    }
    printf("\n����w���ƹ��,s���ƹ��,����<Enter>ѡ��\n");
}

static void menuCall0(int *Order, int *run);         // ���˵�ִ�к���
static void menuCall1(int *Order);                   // ��Ϸ�˵�ִ�к���
static int menuCall2(int *Order);                    // ����ģʽ�˵�ִ�к���
static void menuCall3(int *Order);                   // �Զ����ͼ�˵�ִ�к���
static void menuCall4(int *Order, int customMapNum); // �Զ�������˵�ִ�к���

static void welcome()
{
    ClearPartialScreen(0, 0);
    printf("��ӭ����С�Ƶ�����ð��\n");
    printf("��ʹ������ǻ�������С�����Թ��гɹ���Ѱ���ɣ�\n\n");
    printf("<�����������>\n");
    getch();
    return;
}

void menuControl()
{
    welcome();

    int run = 1;
    int menuOrder = 0;
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

static void gameStart(int gameMode, int num)
{
    struct mapInfo map;
    struct playerInfo player;
    mapIni(&map);
    if (!mapInput(&map, num))
        return; // ��ȡ��ͼʧ����ֱ�ӷ���
    playerIni(&player, &map);
    mapPrint(&map);
    HideConsoleCursor();
    if (gameMode == 0)
        playerMove(&player, &map);
    else if (gameMode == 1)
        playerMovePro(&player, &map);
    ShowConsoleCursor();
}

static void menuCall0(int *Order, int *run) // ���˵�ִ�к���
{
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
                int gameMode = menuCall2(Order);
                if (gameMode == 2)
                    return;

                gameStart(gameMode, 1);
                Order = 0;
                welcome();
                return;
            }
            case 1: // �ڶ��غ���
            {
                int gameMode = menuCall2(Order);
                if (gameMode == 2)
                    return;

                gameStart(gameMode, 2);
                Order = 0;
                welcome();
                return;
            }
            case 2: // �����غ���
            {
                int gameMode = menuCall2(Order);
                if (gameMode == 2)
                    return;

                gameStart(gameMode, 3);
                Order = 0;
                welcome();
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
                *Order = 1;
                return 2;
            }
        }
    }
}

static void menuCall3(int *Order) // �Զ����ͼ�˵�ִ�к���
{
    int pos = 0;
    while (1)
    {
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
                int gameMode = menuCall2(Order);
                if (gameMode == 2)
                    return;

                gameStart(gameMode, customMapNum + 3);
                Order = 0;
                welcome();
                return;
            }
            case 2:
            {
                mapCustomIni(customMapNum, 1);
                break;
            }
            case 3:
                return;
            }
        }
    }
}