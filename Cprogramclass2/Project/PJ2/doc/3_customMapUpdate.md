# 自定义地图功能 Version 2.2

## 1. 构思

之前的功能其实已经够用，但是第一个是不好看，第二个是没有防溢出等，第三个是不够直观  
因此决定在主要方式不变的情况下进行结构调整和完善  

1. **功能：**
    主要还是两个  
    1. `自定义地图初始化`
    2. `自定义地图编辑`
2. **实现设想：**

    第一个见名思意，也没啥需要改的  
    第二个基本功能足够  
    流程如下：  

    ```mermaid
    graph LR;
        mapCustomEdit-->检测地图状态-->已编辑
        已编辑-->继续编辑
        已编辑-->重新编辑
        继续编辑-->|存储在运行地图结构中|从文件读入地图-->|选择保存|存入地图文件中
        检测地图状态-->未编辑-->输入地图参数
        重新编辑-->输入地图参数-->|存储在运行地图结构中|初始化地图-->实时编辑-->|选择保存|存入地图文件中
    ```

    其中大部分已经实现  
    1. 重构的目的在于：  
       1. 结构化，使逻辑更简明
       2. 安全化，限制输入  
       3. 直观化，完善编辑时的信息显示等

    2. 新功能在于：  
       1. 编辑保存功能  
       2. 继续编辑功能  
       3. 那么菜单可能还需要继续维护更新一下...

## 2. 具体实现更新内容

1. 实时编辑信息：

    ```txt
    正在编辑xxx
    实时编辑信息显示

    地图

    操作命令提示
    ```

## 3. bug

TODO:  

1. 似乎横纵坐标反了？
    需要调整:`editOrderInput`,`editInfoPrintFresh`,`editMapInplace
    已修复
2. 光标的跳转还是有问题，大概是在`editPrint`  
    已修复和优化
3. 第一次没有打出`Y`  
    已修复
4. 地图进度输入时有问题，猜想可能是哪里不正常打开过，导致的文件再次打开失败  
    已修复
5. 地图赋值位置选中错误导致的异常行为  
    已修复
6. 不保存退出应该怎么做呢？有点歧义，是保留上次编辑的结果，还是直接清空？倾向于前者  
    已按前者重新编写
    已实现
7. 还有就是编辑已游玩的地图，存档刷新似乎不起效  
    已修复  
8. 更换地块时玩家位置不正常刷新  
    已修复  
9. BUG8或许由玩家位置后续编辑时存储错误导致  
   1. 发现在03.c文件中就有错误，对玩家初始化时横纵坐标错误  
    已修复  
   2. 存储时应该也有错误  
    已修复
10. 防溢出输出控制似乎有问题,也可能时显示的问题  
    已修复  
11. 玩家位置刷新似乎还有问题  
    已修复  
12. 已编辑未完成状态可以开始游戏的错误
    可以确认问题出在菜单显示上，可能时状态获取失败  
    已修复
13. 玩家设置位置被替代时显示信息不更新，也有可能是完全没改  
    事实说明是原来地块检测时有问题  
    再次测试发现只有用空地替换时有问题？  
    最后发现是命令执行函数的优化检测逻辑有问题  
    已修复
