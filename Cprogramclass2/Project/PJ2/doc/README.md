# 迷宫探险记（第二版）

作者：朱文凯  
学号：23307110192

思考题：

1. 为什么这??Player，?不是指向Player的指针?
    因为此处实际上是需要一个Player类型变量来存储部分的玩家状态，作为类似快照的存储节点  
2. 我们现在在每次响应?户输?时刷新UI。假设游戏?有?个会??周期性移动的NPC，那怎么刷新界?效果才会好呢?  
    可以通过设置一个独立的线程来控制NPC的周期性移动，并在每次NPC移动后刷新UI。这样不仅能确保UI的实时更新，还不会影响用户输入的响应速度。  
3. 结构化UI设计一定好吗？会不会在某些情况下，我们不得不做出一些非结构化设计呢？
    结构化UI设计通常能够提供一致性和可预测性，提升用户体验。然而，在某些特定情况下，非结构化设计可能更为适合。例如，当需要展示创意内容或艺术作品时，非结构化设计可以提供更多的自由度和表现力。因此，选择结构化还是非结构化设计应根据具体需求和场景来决定。

## 1 背景介绍

**编写编译环境背景：**

1. 操作系统：Windows 11
2. IDE工具：Visual Studio Code
3. 编译器：gcc (GCC) 14.1.0
4. 编码模式：GBK *(可以在控制台中不乱码)*

**使用介绍：**

1. 在终端中打开PJ2文件夹
2. 输入`make`命令编译`src`中的源文件至`build`中生成`main.exe`可执行文件
3. 输入`./build/main`运行程序

**注意事项：**

1. 请勿随意对[map](../build/map)或[save](../build/save)中的文件进行删除和引入等操作  
2. 请尽量使用全屏终端运行程序，否则可能会出现显示问题  
3. 祝你幸福

## 2 完成功能

### 2.1 必做部分

1. PJ1既有功能  
    1. 菜单
    2. 游戏本体
2. 撤销重做功能  
    1. 撤销
    2. 重做
3. 地图读入功能  
    1. 可变菜单选项
    2. 实时检测地图文件信息

### 2.2 选做部分

1. 自定义地图设计系统
2. 地图其他操作
    1. 新建地图
    2. 重置地图
    3. 删除地图
    4. 重命名地图  

### 2.3 主要提升

1. **菜单**
    1. 优化刷新显示方式  
    2. 功能和显示拆分  
    3. 逻辑统一化  
    4. 借助枚举和多级指针等方式，优化代码结构，提升源文件可读性  
2. **地图**  
    1. 地图自定义设计功能  
        1. 支持完成度检测和编辑保存
        2. 信息显示优化  
        3. 运行逻辑和设计结构优化，有效提升显示流畅度  
        4. 自定义功能源文件可读性提升  
    2. 地图处理  
        1. 新建、重置、删除、重命名等功能  
        2. 借助菜单逻辑优化，实现地图处理类函数的入口统一且实时可变  
    3. 地图状态
        1. 通过更改地图存储方式，为地图
3. **游戏运行**
    1. 撤销和重做功能
        1. 实际PJ1已经实现过，此处优化了逻辑，但总体不变
    2. 存档功能
        1. 新建自定义的`.save`类文件，用于存储对应地图游玩存档
        2. 围绕`.save`文件，实现了存档的初始化、保存、载入、重置等功能

## 3 具体介绍

以下将按照文件主要功能区分分别介绍

### 3.1 主程序

源程序：[main.c](../src/00_main.c)  
平平无奇的主程序，引用`runMenu()`函数进入程序运行  

### 3.2 菜单

源程序：  

1. 头文件：[menuUpdate.h](../src/01_menuUpdate.h)  
2. 实现文件：[menuUpdate.c](../src/01_menuUpdate.c)  

#### 3.2.1 运行逻辑

总共历经三个版本的菜单更新，形成了现在的样式  

主要思想：  

1. 菜单分类思想
    1. 分类：`主干菜单`和`支干菜单`
    2. 运行逻辑：

          ```mermaid
          graph LR;
                进入程序-->运行体-->菜单序号判断
                菜单序号判断-->主干菜单1-->更改菜单序号
                菜单序号判断-->主干菜单2-->更改菜单序号
                菜单序号判断-->|退出条件|退出程序
                更改菜单序号-->运行体
                主干菜单1-->分支菜单1-->主干菜单1
                主干菜单1-->分支菜单2-->主干菜单1
                主干菜单2-->分支菜单3-->主干菜单2
                主干菜单2-->分支菜单4-->主干菜单2
          ```

          简单来说就是`运行体`中始终有一个`主干菜单`在运行，`直干菜单`在`主干菜单`中被调用  
2. 菜单本体运行一般逻辑

     ```mermaid
     graph LR;
          菜单调用-->打印菜单信息-->进入选项控制函数-->|挑选选项|维护菜单显示-->|选中|返回选项值-->菜单选项逻辑映射处理
     ```

3. 特殊的`地图选择菜单`

     实时维护地图信息，存入数组备用（实际上存了`mapName`,`mapPath`,`savePath`三个）  
     借助以上信息可以本菜单数量和显示的变化  

#### 3.2.2 程序介绍

1. 函数说明  

     | 函数名称            | 返回值类型 | 参数类型            | 简述作用                           |
     |---------------------|------------|---------------------|------------------------------------|
     | runMenu             | void       | void                | 菜单运行控制主函数                 |
     | boolSelectMenu      | int        | void                | 是否状态获取菜单函数               |
     | mainMenu            | void       | MENU *              | 主菜单函数                         |
     | mapChooseMenu       | void       | MENU *              | 地图选择菜单函数                   |
     | mapOperationMenu    | void       | int                 | 地图操作菜单函数                   |
     | saveLoadMenu        | int        | int                 | 存档读取菜单函数                   |
     | controlModeMenu     | int        | void                | 控制模式菜单函数                   |
     | editProgressMenu    | int        | void                | 编辑进度菜单函数                   |
     | mapNameGet          | void       | void                | 获取地图名称并维护相关数组和数量   |
     | mapNewCreate        | void       | void                | 新建地图函数                       |
     | mapNameChange       | void       | int                 | 地图名称更改函数                   |
     | mapRemove           | void       | int                 | 删除地图函数                       |
     | getMapStatus        | int        | int                 | 获取地图状态                       |
     | startGame           | void       | int                 | 游戏开始函数                       |
     | printMenu           | void       | MENU, int           | 打印菜单                           |
     | cursorChoose        | int        | COORD, int          | 菜单光标移动控制                   |
     | freshCursor         | void       | COORD, int, int     | 菜单光标移动显示与控制             |
     | printFile           | void       | int                 | 打印文档（集合比较繁杂的打印操作） |

2. 变量说明

    | 变量名称            | 类型            | 简述作用                           |
    |---------------------|-----------------|------------------------------------|
    | mapName             | char\[10\]\[64\]    | 存储地图名称                       |
    | mapPath             | char\[10\]\[64\]    | 存储地图文件路径                   |
    | savePath            | char\[10\]\[64\]    | 存储地图进度文件路径               |
    | mapNumbers          | int             | 存储地图数量                       |

### 3.3 光标操作

源程序：

1. 头文件：[02_cursorOperation.h](../src/02_cursorOperation.h)  
2. 实现文件：[02_cursorOperation.c](../src/02_cursorOperation.c)  

#### 3.3.1 运行逻辑

这是本程序优化的核心，部分刷新显示优化方式的基石  

光标操作主要用于控制台界面的显示优化，通过控制光标的位置和显示状态，实现更流畅的用户体验。  

主要功能：

1. 移动光标到指定位置
2. 获取当前光标位置
3. 清空指定位置之后的屏幕内容
4. 隐藏光标
5. 显示光标

#### 3.3.2 程序介绍

1. 函数说明  

     | 函数名称            | 返回值类型 | 参数类型            | 简述作用                           |
     |---------------------|------------|---------------------|------------------------------------|
     | MoveCursorTo        | void       | int, int            | 移动光标到指定位置                 |
     | GetCursorPosition   | void       | int*, int*          | 获取当前光标位置                   |
     | ClearPartialScreen  | void       | int, int            | 清空指定位置之后的屏幕内容         |
     | HideConsoleCursor   | void       | void                | 隐藏光标                           |
     | ShowConsoleCursor   | void       | void                | 显示光标                           |

2. 变量说明

     本模块不涉及全局变量，仅在函数内部使用局部变量。

#### 3.3.3 使用示例

1. 移动光标到指定位置：

     ```c
     MoveCursorTo(10, 5); // 将光标移动到第10行，第5列
     ```

2. 获取当前光标位置：

     ```c
     int row, col;
     GetCursorPosition(&row, &col); // 获取当前光标位置，存储在row和col中
     ```

3. 清空指定位置之后的屏幕内容：

     ```c
     ClearPartialScreen(5, 0); // 清空从第5行，第0列开始之后的屏幕内容
     ```

4. 隐藏和显示光标：

     ```c
     HideConsoleCursor(); // 隐藏光标
     ShowConsoleCursor(); // 显示光标
     ```

### 3.4 地图和玩家状态

源程序：

1. 头文件：[mapAndPlayerStatus.h](../src/03_mapAndPlayerStatus.h)  
2. 实现文件：[mapAndPlayerStatus.c](../src/03_mapAndPlayerStatus.c)  

#### 3.4.1. 运行逻辑

地图和玩家状态模块负责初始化和管理游戏中的地图和玩家状态，包括地图的加载、保存、打印以及玩家的移动和状态更新。

主要功能：

1. 初始化地图和玩家状态
2. 加载和保存地图和玩家状态
3. 打印地图和玩家状态
4. 判断玩家移动是否合法
5. 撤销和重做玩家操作

#### 3.4.2 程序介绍

1. 函数说明  

     | 函数名称            | 返回值类型 | 参数类型            | 简述作用                           |
     |---------------------|------------|---------------------|------------------------------------|
     | mapIni              | void       | struct mapInfo*     | 初始化迷宫                         |
     | mapInput            | int        | struct mapInfo*, int| 输入迷宫                           |
     | mapPrint            | void       | struct mapInfo*     | 打印迷宫                           |
     | playerIni           | void       | struct playerInfo*, struct mapInfo* | 初始化玩家信息         |
     | playerInfoPrint     | void       | struct playerInfo*, int | 打印玩家信息                     |
     | exitInfoPrint       | void       | struct playerInfo*  | 打印退出信息                       |
     | playerMoveJudge     | int        | struct playerInfo*, struct mapInfo*, char | 玩家移动判断       |
     | moveBack            | void       | struct playerInfo*, struct mapInfo* | 撤销操作               |
     | moveRedo            | char       | struct playerInfo*, struct mapInfo* | 重做操作               |
     | playerMove          | void       | struct playerInfo*, struct mapInfo*, int | 玩家移动实时模式     |
     | playerMovePro       | void       | struct playerInfo*, struct mapInfo*, int | 玩家移动编程模式     |
     | progressAutoSave    | void       | struct playerInfo*, struct mapInfo*, int, int, int | 自动保存游戏进度 |
     | progressExitSave    | void       | struct playerInfo*, struct mapInfo*, int | 退出时保存游戏进度   |
     | progressSaveInit    | void       | int                | 初始化存档信息                     |
     | saveOperation       | void       | struct playerInfo*, struct mapInfo*, int | 保存游戏进度具体操作 |
     | progressLoad        | void       | struct playerInfo*, struct mapInfo*, int | 加载存档             |

2. 变量说明

     | 变量名称            | 类型            | 简述作用                           |
     |---------------------|-----------------|------------------------------------|
     | map                 | char\[50][50]    | 地图信息                           |
     | mapRow              | int             | 地图行数                           |
     | mapCol              | int             | 地图列数                           |
     | treasureNum         | int             | 宝藏数量                           |
     | trapNum             | int             | 陷阱数量                           |
     | pRow, pCol          | int             | 玩家位置                           |
     | px, py              | int             | 玩家位置信息                       |
     | energyCost          | int             | 体力消耗                           |
     | getTreasure         | int             | 获得宝物数量                       |
     | isTrapped           | int             | 是否触发陷阱                       |
     | moveMemory          | char[1000]      | 移动路径                           |
     | moveResult          | int[1000]       | 移动结果（回退时使用）             |
     | tt                  | int             | moveMemory与moveResult的长度       |

### 3.5 自定义地图

源程序：

1. 头文件：[mapCustomUpdate.h](../src/04_mapCustomUpdate.h)  
2. 实现文件：[mapCustomUpdate.c](../src/04_mapCustomUpdate.c)  

#### 3.5.1 运行逻辑

自定义地图模块允许用户设计和编辑自己的地图，并将其保存以供后续使用。该模块提供了地图的创建、编辑、保存和删除等功能。

主要功能：

1. 创建新地图
2. 编辑现有地图
3. 保存地图
4. 删除地图
5. 重命名地图

#### 3.5.2 程序介绍

对外接口只有`地图初始化`和`地图编写`两个  
需要[menuUpdate](#322-程序介绍)中的地图路径和存档路径信息支持  

1. 函数说明  

    | 函数名称            | 返回值类型 | 参数类型            | 简述作用                           |
    |---------------------|------------|---------------------|------------------------------------|
    | mapCustomIni        | void       | int, int            | 初始化随机迷宫                     |
    | mapCustomEdit       | void       | int, int            | 编辑随机迷宫                       |
    | editProgressLoad    | void       | struct mapInfo*, int, int*, int*, int* | 编辑进度读取       |
    | editMapSave         | void       | struct mapInfo*, int, int, int, int | 编辑地图存储       |
    | editInfoPrintFresh  | void       | struct mapInfo*, COORD*, int, int, int, int, int, int | 地图信息显示刷新 |
    | editMapReplace      | void       | struct mapInfo*, COORD, int, int, int*, int*, int*, int | 地块替换         |
    | editOrderInput      | void       | struct mapInfo*, COORD, int*, int*, int*, int*, int*, int | 编辑命令处理     |
    | editOrderGet        | int        | void                | 编辑命令获取                       |
    | editMap             | int        | struct mapInfo*, COORD*, int*, int*, int* | 编辑地图函数       |
    | editPrint           | void       | int, struct mapInfo*, COORD*, int, int, int | 编辑界面打印与信息存储 |
    | editInit            | void       | struct mapInfo*     | 编辑地图时初始化地图信息           |
    | acceptNumSet        | void       | int*, int*, int**, int | 可接受数值范围设置               |
    | mapInfoSet          | void       | struct mapInfo*     | 设置地图参数                       |

2. 变量说明

    | 变量名称            | 类型            | 简述作用                           |
    |---------------------|-----------------|------------------------------------|
    | mapInfo             | struct mapInfo  | 地图信息结构体                     |
    | loc                 | COORD[5]        | 光标位置数组                       |
    | Tnum                | int             | 宝藏数量                           |
    | Dnum                | int             | 陷阱数量                           |
    | playerSetFlag       | int             | 玩家位置设置标志                   |
