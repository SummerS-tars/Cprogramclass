#ifndef MENU_H
#define MENU_H

typedef enum _MENU{   // �˵�ö��
    MAIN_MENU = 0,
    MAP_TYPE_MENU,
    DEFAULT_MAP_MENU,
    CUSTOM_MAP_MENU,
    CUSTOM_OPERATION_MENU,
    SAVE_LOAD_MENU,
    CONTROL_MODE_MENU
} MENU;

extern void runMenu() ;    // �˵����п���������

#endif // MENU_H