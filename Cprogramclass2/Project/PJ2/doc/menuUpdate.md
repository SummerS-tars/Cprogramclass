# 菜单升级版 Version 2.1

## 1. 构思

**整体设想**：  

1. 规范菜单函数入口  
2. 菜单显示、选择与功能分离  
3. 简化菜单调用逻辑  
4. 升级菜单选择渲染方式  
5. 提供一些通用逻辑，供外部某些时候也可以使用  

**总体逻辑**：  

```mermaid
graph LR;
   进入菜单-->显示菜单-->选择功能-->选择某一项-->返回值-->分流出口
```  

## 2. 设计

### 2.1 菜单功能需求详述

1. `欢迎页面`
   1. 在进入程序时显示，点击后进入`主菜单`
   2. 游戏结束后显示，点击后回到进入游戏的菜单  
2. `主菜单`  
   1. `开始游戏`，进入`地图类型选择菜单`
   2. `获取帮助`，展示帮助文档1，展示游戏背景信息，大致玩法
   3. `退出游戏`
3. `地图类型选择菜单`
   1. `默认关卡`
   2. `自定义关卡`
   3. `返回主菜单`
4. `默认关卡菜单`
   1. `地图一`，实际可能显示的是地图名称；然后已游玩状态则先gameStart，后选择游戏模式；否则直接选择游戏模式
   2. `地图二`
   3. `地图三`
   4. `返回地图类型选择菜单`
5. `自定义关卡菜单`
   1. `自定义地图一`，直接进入操作菜单
   2. `自定义地图二`
   3. `自定义地图三`
   4. `返回地图类型选择菜单`
6. `自定义关卡操作菜单`
   1. `开始游玩`，设想最好是地图处于已编辑状态才显示此选项；选择后和`默认关卡`选择关卡后续流程一致
   2. `开始编辑`，进入该地图的编辑模式
   3. `重置地图`，重置该地图
   4. `帮助菜单`
   5. `返回地图类型选择菜单`
7. `读档选择菜单`
   1. `继续上次游戏`
   2. `开始新游戏`
   3. `清除存档`
   4. `返回`
8. `游戏模式选择菜单`
   1. `实时模式`
   2. `编程模式`
   3. `帮助菜单`
   4. `返回`
9. `保存确认菜单`
   1. 游戏主动结束时存档保存时使用
   2. 游戏正常结束时保存排名使用

### 2.2 逻辑设计

**菜单主要分类**:  

1. `主干菜单`  
2. `分支菜单`  

主干菜单不叠加运行，通过更改菜单级数，进行换页  
分支菜单在主干菜单中调用，完成功能后返回主干菜单运行流  
因此，方便统一入口的菜单可以归到主干菜单之中，可能需要特殊入口和返回值和返回位置的菜单可以归到分支菜单中  

**归类**:  

1. `主干菜单`：  
   1. `主菜单`
   2. `地图类型选择菜单`
   3. `默认关卡菜单`
   4. `自定义关卡菜单`
2. `分支菜单`
   1. `自定义关卡操作菜单`
   2. `读档选择菜单`
   3. `游戏模式选择菜单`

**菜单整体逻辑运行设计**:  

1. 场上始终有且只有一个`主干菜单`实体在运行，这样就可以控制在一个函数中运行，我们不妨称之为`菜单运行函数`
2. `主干菜单`之间有一定衔接逻辑，在`菜单运行函数`中切换正在运行的`主干函数`
3. 在`主干函数`上，根据需要调用`分支菜单`

### 2.3 菜单具体实现

**存储：**

1. 所有菜单统一采用`static char`二维数组存储选项，第一维统一设置40元素上限，留空第二维（即选项数），提高可调整性  
   1. `mainMenuList`
   2. `mapTypeMenuList`
   3. `defaultMapMenuList`
   4. `customMapMenuList`
   5. `customOperationMenuList`
   6. `saveLoadMenuList`
   7. `controlModeMenuList`
2. 再用采用`static char (*[])[40]`类型的`menuList`存储指向菜单选项存储数组的指针  
3. 使用`enum`为每个菜单按照在`menuList`中的顺序进行枚举类型`MENU`的定义，用于后续调用，提高程序可读性  

   ```c
   typedef enum _MENU{   // 菜单枚举
      MAIN_MENU = 0,
      MAP_TYPE_MENU,
      DEFAULT_MAP_MENU,
      CUSTOM_MAP_MENU,
      CUSTOM_OPERATION_MENU,
      SAVE_LOAD_MENU,
      CONTROL_MODE_MENU
   } MENU;
   ```

**功能实现：**

* **主要菜单部分**

1. **函数名：**  

   1. **主干菜单：**
      1. `mainMenu`
      2. `mapTypeMenu`
      3. `defaultMapMenu`
      4. `customMapMenu`
   2. **分支菜单：**
      1. `customOperationMenu`
      2. `saveLoadMenu`
      3. `controlModeMenu`  

2. **类型以及参数：**

   ```c
   static void mainMenu( MENU *pmenu ) ;                // 主菜单函数
   static void mapTypeMenu( MENU *pmenu ) ;             // 地图类型选择菜单函数
   static void defaultMapMenu( MENU *pmenu ) ;          // 默认地图菜单函数
   static void customMapMenu( MENU *pmenu ) ;           // 自定义地图菜单函数
   static void customOperationMenu( int mapOrder ) ;             // 自定义地图操作菜单函数
   static int saveLoadMenu( int mapOrder ) ;                    // 存档读取菜单函数
   static int controlModeMenu() ;                 // 控制模式菜单函数
   ```

* **具体功能流程实现**

1. **菜单间关联逻辑：**  

   主干菜单放在`runMenu`函数中进行运行
   程序运行期间任何时间有且只有一个主干菜单函数在运行

   1. `runMenu`

      ```mermaid
      graph LR;
         runMenu-->menu判断
         menu判断-->|MAIN_MENU|mainMenu
         menu判断-->|MAP_TYPE_MENU|mapTypeMenu
         menu判断-->|DEFAULT_MAP_MENU|defaultMapMenu
         menu判断-->|CUSTOM_MAP_MENU|customMapMenu
         mainMenu-->menu再次判断
         mapTypeMenu-->menu再次判断
         defaultMapMenu-->menu再次判断
         customMapMenu-->menu再次判断
         menu再次判断-->|-1|结束程序
         menu再次判断-->menu判断
      ```

   2. `mainMenu`

      ```mermaid
      graph LR;
         mainMenu-->开始游戏
         mainMenu-->获取帮助
         mainMenu-->退出游戏
         开始游戏-->|修改menu|MAP_TYPE_MENU
         获取帮助-->展示帮助文档1
         退出游戏-->|修改menu|-1
      ```

   3. `mapTypeMenu`

      ```mermaid
      graph LR;
         mapTypeMenu-->默认关卡
         mapTypeMenu-->自定义关卡
         mapTypeMenu-->返回主菜单
         默认关卡-->|修改menu|DEFAULT_MAP_MENU
         自定义关卡-->|修改menu|CUSTOM_MAP_MENU
         返回主菜单-->|修改menu|MAIN_MENU
      ```

   4. `defaultMapMenu`

      ```mermaid
      graph LR;
         defaultMapMenu-->地图一
         defaultMapMenu-->地图二
         defaultMapMenu-->地图三
         defaultMapMenu-->返回地图类型选择菜单
         地图一-->**gameStart**
         地图二-->**gameStart**
         地图三-->**gameStart**
         **gameStart**-->|结束后|回到地图选择菜单
         返回地图类型选择菜单-->|修改menu|MAP_TYPE_MENU
      ```

   5. `customMapMenu`

      ```mermaid
      graph LR;
         customMapMenu-->自定义地图一
         customMapMenu-->自定义地图二
         customMapMenu-->自定义地图三
         customMapMenu-->返回地图类型选择菜单
         自定义地图一-->|直接调用|customOperationMenu
         自定义地图二-->|直接调用|customOperationMenu
         自定义地图三-->|直接调用|customOperationMenu
         返回地图类型选择菜单-->|修改menu|MAP_TYPE_MENU
      ```

   6. `customOperation`

      ```mermaid
      graph LR;
         customOperationMenu-->|已编辑可选|**gameStart**
         customOperationMenu-->开始编辑
         customOperationMenu-->重置地图
         customOperationMenu-->返回自定义菜单
         开始编辑-->|结束后|返回customMapMenu
         重置地图-->|结束后|返回customMapMenu
         **gameStart**-->|结束后|回到地图选择菜单
         返回自定义菜单-->返回customMapMenu
      ```

   7. `gameStart`
      其中包含了`saveLoadMenu`和`controlModeMenu`的运行逻辑

      ```mermaid
      graph LR;
         gameStart-->|mapStatus==SAVED|saveLoadMenu
         saveLoadMenu-->继续上次游戏-->controlModeMenu
         saveLoadMenu-->开始新游戏-->controlModeMenu
         saveLoadMenu-->清除存档-->返回地图选择菜单
         saveLoadMenu-->返回-->返回地图选择菜单
         gameStart-->|mapStatus==UNSAVED|controlModeMenu
         controlModeMenu-->实时模式-->游戏本体
         controlModeMenu-->编程模式-->游戏本体
         controlModeMenu-->获取帮助-->controlModeMenu
         controlModeMenu-->返回
         游戏本体-->|运行结束|返回地图选择菜单
      ```

2. **菜单内部功能实现：**
   1. 通用逻辑：

      ```mermaid
      graph LR;
         打印与存储菜单信息-->进入菜单选择函数-->返回option值-->进入option功能选择
      ```

   2. 打印与存储菜单信息：  
      1. 打印功能实现

         ```c
         static void printMenu( MENU menu , int num ) ;
         ```

      2. 菜单信息存储
         1. 基础信息：

            ```c
            int listNum ; // 存储当前菜单的选项数
            COORD loc ; // 用于存储光标在控制台的打印开始位置
            ```

         2. 特殊信息：

            ```c
            int mapStatus ; // 用于defaultMapMenu与customOperationMenu中补充地图信息
            ```

         3. 功能实现：
            `listNum`使用`listNumCount`计算得到  
            `loc`通过`GetCursorPosition`在特定运行进程得到  
            `mapStatus`通过`getMapStatus`得到  

            部分声明：  

            ```c
            // 计算菜单选项数量
            static int listNumCount( MENU menu ) ;
            // 获取菜单打印补充信息（依赖于以下两个函数）
            static int getMapStatus( int mapOrder ) ;
            // 默认地图存档状态显示
            static void defaultMapStatus( int mapOrder , int *status ) ;
            // 自定义地图存档状态显示
            static void customMapStatus( int customMapOrder , int *status ) ;
            ```

   3. 菜单选择功能实现  ：
      `cursorChoose`控制选中选项，通过调用`freshCursor`刷新显示  

      部分声明：  

      ```c
      // 菜单光标移动控制
      static int cursorChoose( COORD loc , int num ) ;                  
      // 菜单光标移动显示与控制
      static void freshCursor( COORD loc , int num , int pos ) ;        
      ```

   4. 功能选择：  
      根据`cursorChoose`返回的值与具体逻辑的对应设计每个菜单独有的功能映射  

   5. 备注：  
      1. 以上只是各个菜单函数的通用理解逻辑，具体因为菜单功能需要，会有部分特殊设计  
      2. 最终运行游戏的入口都是接入`gameStart`

## 3. 总结

[menuUpdate](../src/01_menuUpdate.c)经过优化，作为Version 2.1 的菜单，极大提升了菜单界面的性能  
封装程度更高，减少了不安全全局变量的使用  
逻辑更加统一和清晰  
