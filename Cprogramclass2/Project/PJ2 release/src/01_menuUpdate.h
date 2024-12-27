#ifndef MENU_H
#define MENU_H

typedef enum _MENU{   // 菜单枚举
    MAIN_MENU = 0,
    MAP_CHOOSE_MENU,
    MAP_OPERATION_MENU,
    SAVE_LOAD_MENU,
    CONTROL_MODE_MENU,
    EDIT_PROGRESS_MENU,
    BOOL_SELECT_MENU
} MENU;

extern char mapName[10][64] ; // 地图名称
extern char mapPath[10][64] ;  // 地图文件名
extern char savePath[10][64] ; // 地图进度保存文件名

extern void runMenu() ;    // 菜单运行控制主函数
extern int boolSelectMenu() ; // 是否状态获取菜单函数

#endif // MENU_H