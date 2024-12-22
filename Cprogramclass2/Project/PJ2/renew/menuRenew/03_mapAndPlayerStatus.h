#ifndef MAPSTATUS_H
#define MAPSTATUS_H

struct mapInfo
{
    char map[50][50];      // ��ͼ��Ϣ
    int mapRow;            // ��ͼ����
    int mapCol;            // ��ͼ����
    int treasureNum;       // ��������
    int trapNum;           // ��������
    int pRow, pCol;        // ���λ��
    /*
    ��Ҫע��Row���Ҽ��㣬Col���¼��� 
    ��ͼ�ĵ������ݶ�Ӧ����map�����е�λ�� 
    map������[Col][Row]
    */
};

struct playerInfo
{
    int px , py ;               // λ����Ϣ
    int energyCost ;            // ��������
    int getTreasure ;           // ��ñ�������
    int isTrapped ;             // �Ƿ񴥷�����
    
    char moveMemory[ 1000 ] ;   // �ƶ�·��
    /* ���ڴ洢��ҵĲ�����¼
     * U:��
     * D:��
     * L:��
     * R:��
     */
    int moveResult[ 1000 ] ;   // �ƶ����������ʱʹ�ã�
    /* ����ͬ����¼��ҵĲ������
     * 1��ʾײǽ
     * 2��ʾ�յ�����
     * 3��ʾ������������
     * 4��ʾ������ñ���
     * 5��ʾ���崥�����ߵ��յ�
     * 6��ʾ���崥���󴥷�����
     * 7��ʾ���崥�����ñ���
     */
    int tt ;                    // moveMemory��moveResult�ĳ���
};

extern int runGame;         // ��Ϸ����״̬:0��ʾ������1��ʾ����

void mapIni(struct mapInfo *mapInfo);                                                       // ��ʼ���Թ�
int mapInput(struct mapInfo *mapInfo, int mapOrder);                                       // �����Թ�
void mapPrint(struct mapInfo *mapInfo);                                                     // ��ӡ�Թ�
void playerIni( struct playerInfo *player , struct mapInfo *mapInfo );                      // ��ʼ�������Ϣ
void playerInfoPrint( struct playerInfo *player , int num );                                // ��ӡ�����Ϣ
void exitInfoPrint( struct playerInfo *player );                                            // ��ӡ�˳���Ϣ
int playerMoveJudge( struct playerInfo *player , struct mapInfo *mapInfo , char order );    // ����ƶ��ж�
void moveBack( struct playerInfo *player , struct mapInfo *mapInfo );
char moveRedo( struct playerInfo *player , struct mapInfo *mapInfo );
void playerMove( struct playerInfo *player , struct mapInfo *mapInfo );                     // ����ƶ�ʵʱģʽ
void playerMovePro( struct playerInfo *player , struct mapInfo *mapInfo );                  // ����ƶ����ģʽ

#endif // MAPSTATUS_H