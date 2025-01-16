# README

## 1. 背景介绍

1. 操作系统：Windows 11
2. IDE工具：Visual Studio Code
3. 编译器：gcc (GCC) 14.1.0
4. 编码模式：GBK *(可以在控制台中不乱码)*

## 2. 完成部分

1. **基础部分**
   1. 菜单
   2. 地图信息
   3. 玩家信息
   4. 运行页面打印
   5. 实时模式
   6. 编程模式
2. **额外部分**
   1. 自定义地图
   2. 回退功能
   3. 重做功能

## 3. 使用说明

1. 打开`build`文件夹中`main.exe`食用即可，其余见菜单`帮助`内容
2. 注意事项：
   1. 保持`map1.txt`,`map2.txt`,`map3.txt`文件夹与`main.exe`在**同一级文件夹**之中
   2. 自定义地图在程序运行结束时默认进行初始化
3. 可能**只能**通过主菜单`退出游戏`或者是关掉终端退出

## 4. 结构说明

采用了**多文件程序**的结构  
共有5个`.c`程序  

### 4.1. main

[main.c](../src/00_main.c)  
人如其名  
是个简单的**主程序**  

### 4.2. menu

[menu.c](../src/01_menu.c)  
同样人如其名  
用来实现**菜单**的功能  

通过分级菜单，在最主要的`void menuControl()`函数中通过循环以及菜单级数变量  
展示不同级别的菜单  

### 4.3. cursorOperation

放置了一些用于**终端光标操作**的函数  
在[mapAndPlayerStatus.c](../src/03_mapAndPlayerStatus.c)中有大量使用  

| 函数名             | 返回值类型 | 参数类型           | 功能               |
| ------------------ | ---------- | ------------------ | ------------------ |
| MoveCursorTo       | void       | int nRows, int nCols | 在任意位置移动光标 |
| GetCursorPosition  | void       | int\*nRows, int\*nCols | 获取当前光标位置   |
| ClearPartialScreen | void       | int Row, int Col   | 清空屏幕           |
| HideConsoleCursor  | void       | 无                 | 隐藏光标           |
| ShowConsoleCursor  | void       | 无                 | 显示光标           |

### 4.4. mapAndPlayerStatus

[mapAndPlayerStatus.c](../src/03_mapAndPlayerStatus.c)  
[mapAndPlayerStatus.h](../src/03_mapAndPlayerStatus.h)  
整个程序中**最为核心和最为重要**的部分  

`mapAndPlayerStatus.h`包含`struct mapInfo`与`struct playerInfo`两种最主要的结构类型  
分别用来存储运行时的地图信息与玩家信息  

`mapAndPlayerStatus.c`包含了绝大多数有关游戏实现的功能函数  
具体分两部分来看：

1. mapOperation

   | 函数名   | 返回值类型 | 参数类型              | 功能               |
   | -------- | ---------- | --------------------- | ------------------ |
   | mapIni   | void       | struct mapInfo \*      | 初始化地图         |
   | mapInput | int        | struct mapInfo \*, int | 从文本文件导入地图 |
   | mapPrint | void       | struct mapInfo \*      | 打印地图           |

2. playerOperation

   | 函数名              | 返回值类型 | 参数类型                                    | 功能                             |
   | ------------------- | ---------- | --------------------------- | ------------------------------- |
   | playerIni           | void       | struct playerInfo \*, struct mapInfo \*     | 初始化玩家人物                   |
   | playerInfoPrint     | void       | struct playerInfo \*, int                   | 打印玩家信息                     |
   | **playerMoveJudge** | int        | struct playerInfo \*, struct mapInfo \*, char | 最核心的函数之一，集成了较多功能 |
   | moveBack            | void       | struct playerInfo \*, struct mapInfo \*     | 撤回功能                         |
   | moveRedo            | char       | struct playerInfo \*, struct mapInfo \*     | 重做功能                         |
   | exitInfoPrint       | void       | struct playerInfo \*                        | 成就结算函数                     |
   | playerMove          | void       | struct playerInfo \*, struct mapInfo \*     | 实时模式下游戏运行函数           |
   | playerMovePro       | void       | struct playerInfo \*, struct mapInfo \*     | 编程模式下游戏运行函数           |

### 4.5. mapCustom

[mapCustom.c](../src/04_mapCustom.c)  
包含**自定义地图**相关函数  

实际上只有两个函数`void mapCustomIni()`与`void mapCustomEdit()`  
自定义地图进行游戏的入口与普通地图一致，进行了复用  

### 4.6. else

1. 地图文件  
   **地图文件**包含在build文件之中  
   自定义地图可以实际上可以删掉，初始化时会自动生成  
2. 其他文件  
   包含了在vscode中编译时使用的`tasks.json`文件  

## 5. 功能实现及创新点介绍

1. 结构  
   多文件程序，大致根据功能进行分开，比较简单易懂
2. 菜单  
   1. 分级式，复用性比较高  
   2. 采用多维数组的方式打印选项  
   3. 进入游戏的入口比较简单，且复用性高
3. 游戏数据  
   1. 地图与玩家数据分离  
   2. 地图采用固定导入方式与存储方式，使得入口可以很单一，自定义也更简单
   3. 操作函数比较简单明了，复用率高
   4. 信息简单明了，利用率高
4. 游戏进行  
   1. 游戏进行入口单一
   2. 大量采用光标移动覆盖输出，避免了地图反复输出造成的延迟  
   3. 数据更新及时，反馈效果较好
5. 自定义地图  
   1. 得益于地图导入方式，可以通过用与普通地图相同的存储方式，而使用一样的游戏函数
   2. 支持检测地图是否编辑，以判断是否可供进行游戏
   3. 实时编辑模式，简单明了
