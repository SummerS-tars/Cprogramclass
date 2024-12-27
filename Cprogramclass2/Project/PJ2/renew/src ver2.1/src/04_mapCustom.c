#include "04_mapCustom.h"
#include "02_cursorOperation.h"
#include "03_mapAndPlayerStatus.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>

void mapCustomIni( int customMapNum , int priInfo )    // ��ʼ������Թ�
{
    FILE *mapfp = NULL ;
    mapfp = fopen( mapName[ customMapNum + 2 ] , "w" ) ;
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
    system("cls") ;
    printf("��ʼ���ɹ���\n");
    system("pause");
    }

    progressSaveInit( customMapNum + 3 ) ; // ͬʱ��ʼ����Ϸ�浵
    return ;
}

void mapCustomEdit( int customMapNum )   // �༭����Թ�
{
    system("cls");
    struct mapInfo mapInfo;
    mapIni( &mapInfo );
    printf("�������Թ���������\n");
    scanf("%d", &mapInfo.mapRow);
    printf("�������Թ���������\n");
    scanf("%d", &mapInfo.mapCol);
    printf("�������Թ��ı���������\n");
    scanf("%d", &mapInfo.treasureNum);
    printf("�������Թ�������������\n");
    scanf("%d", &mapInfo.trapNum);
    system("cls");

    for( int i = 0 ; i < mapInfo.mapRow ; i ++ )    // Ĭ�ϳ�ʼ���Թ�
    {
        for( int j = 0 ; j < mapInfo.mapCol ; j ++ )
        {
            mapInfo.map[i][j] = 'W';
            printf("W ");
        }
        printf("\n");
    }

    int infoPosx = 0 , infoPosy = 0 ;
    GetCursorPosition( &infoPosx , &infoPosy ) ;
    printf("\n\n") ;
    printf("����W���ƹ�꣬S���ƹ�꣬A���ƹ�꣬D���ƹ�꣬Q�������˳��༭��������λ�ý��б���\n");
    printf("����1���ǽ'W'��2��ӿյ�' '��3�������'D'��4��ӱ���'T'��5�����ҳ�ʼλ��'Y'\n");

    int px = 0 , py = 0 ;
    int Tnum = 0 , Dnum = 0 ;
    MoveCursorTo(0, 0);
    int isEdit = 1 ;
    while( isEdit )
    {
        char ch = getch();
        if( ch == 'w' && py > 0 ) py -- ;
        if( ch == 's' && py < mapInfo.mapRow - 1 ) py ++ ;
        if( ch == 'a' && px > 0 ) px -- ;
        if( ch == 'd' && px < mapInfo.mapCol - 1) px ++ ;
        if( ch == '1' )
        {
            if( mapInfo.map[py][px] == 'T' ) Tnum -- ;
            else if( mapInfo.map[py][px] == 'D' ) Dnum -- ;
            mapInfo.map[py][px] = 'W';
            printf("W") ;
        }
        if( ch == '2' )
        {
            if( mapInfo.map[py][px] == 'T' ) Tnum -- ;
            else if( mapInfo.map[py][px] == 'D' ) Dnum -- ;
            mapInfo.map[py][px] = ' ';
            printf(" ");
        }
        if( ch == '3' )
        {
            if( Dnum == mapInfo.trapNum || mapInfo.map[py][px] == 'D' ) continue ;
            else if( mapInfo.map[py][px] == 'T' ) Tnum -- ;
            Dnum ++ ;
            mapInfo.map[py][px] = 'D';
            printf("D");
        }
        if( ch == '4' )
        {
            if( Tnum == mapInfo.treasureNum || mapInfo.map[py][px] == 'T' ) continue ;
            else if( mapInfo.map[py][px] == 'D' ) Dnum -- ;
            Tnum ++ ;
            mapInfo.map[py][px] = 'T';
            printf("T");
        }
        if( ch == '5' )
        {
            mapInfo.map[py][px] = ' ';
            mapInfo.pRow = py;
            mapInfo.pCol = px;
            printf("Y");
            isEdit = 0 ;
        }
        if( ch == 'q' ) return ;

        MoveCursorTo(infoPosx, infoPosy);
        printf("��ǰλ�ã�(%d, %d)  ", px, py);
        printf("����������%d  ", Tnum);
        printf("����������%d  ", Dnum);

        MoveCursorTo(2 * px, py);
    }
  
    // �����ͼ��Ϣ
    FILE *mapfp = NULL ;
    mapfp = fopen( mapName[ customMapNum + 2 ] , "w" ) ;
    if( mapfp == NULL )
    {
        perror("Error opening file");
        return ;
    }

    fprintf(mapfp, "%d %d\n", mapInfo.mapRow, mapInfo.mapCol);
    fprintf(mapfp, "%d %d\n", mapInfo.treasureNum, mapInfo.trapNum);
    fprintf(mapfp, "%d %d\n", mapInfo.pCol, mapInfo.pRow );
    for( int i = 0 ; i < mapInfo.mapRow ; i ++ )
    {
        for( int j = 0 ; j < mapInfo.mapCol ; j ++ )
        {
            fputc(mapInfo.map[i][j], mapfp);
        }
        fputc('\n', mapfp);
    }
    fclose(mapfp);

    ClearPartialScreen(0,0);
    printf("�ѳɹ��༭����ɱ��棡\n") ;
    system("pause") ;
    return ;
}