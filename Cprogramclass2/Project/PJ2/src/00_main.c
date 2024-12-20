#include <stdio.h>
#include "01_menu.h"
#include "02_cursorOperation.h"
#include "03_mapAndPlayerStatus.h"
#include "04_mapCustom.h"

int main()
{
    // 初始化自定义地图
    mapCustomIni(1 , 0) ;
    mapCustomIni(2 , 0) ;
    mapCustomIni(3 , 0) ;

    // 进入菜单
    menuControl();

    // 结束时再次初始化自定义地图
    mapCustomIni(1 , 0) ;
    mapCustomIni(2 , 0) ;
    mapCustomIni(3 , 0) ;
    return 0;
}