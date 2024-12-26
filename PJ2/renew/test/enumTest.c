#include <stdio.h>
#include <stdlib.h>

typedef enum MENU{   // ≤Àµ•¿‡–Õ
    MAIN_MENU = 0,
    MAP_TYPE_MENU,
    DEFAULT_MAP_MENU,
    CUSTOM_MAP_MENU,
    CUSTOM_OPERATION_MENU,
    SAVE_LOAD_MENU,
    CONTROL_MODE_MENU
} MENU;

int main()
{
    MENU menu = -1;
    printf("%d" , menu ) ;
    return 0;
}