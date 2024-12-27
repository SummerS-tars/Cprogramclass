#ifndef MENU_H
#define MENU_H

typedef enum _MENU{   // �˵�ö��
    MAIN_MENU = 0,
    MAP_CHOOSE_MENU,
    MAP_OPERATION_MENU,
    SAVE_LOAD_MENU,
    CONTROL_MODE_MENU,
    EDIT_PROGRESS_MENU,
    BOOL_SELECT_MENU
} MENU;

extern char mapName[10][64] ; // ��ͼ����
extern char mapPath[10][64] ;  // ��ͼ�ļ���
extern char savePath[10][64] ; // ��ͼ���ȱ����ļ���

extern void runMenu() ;    // �˵����п���������
extern int boolSelectMenu() ; // �Ƿ�״̬��ȡ�˵�����

#endif // MENU_H