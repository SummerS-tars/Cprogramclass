#ifndef MENU_H
#define MENU_H

typedef enum _MENU{   // 菜单枚举
    MAIN_MENU = 0,
    MAP_TYPE_MENU,
    DEFAULT_MAP_MENU,
    CUSTOM_MAP_MENU,
    CUSTOM_OPERATION_MENU,
    SAVE_LOAD_MENU,
    CONTROL_MODE_MENU
} MENU;

extern void runMenu() ;    // 菜单运行控制主函数

#endif // MENU_H