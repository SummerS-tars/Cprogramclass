# �Թ�̽�ռǣ��ڶ��棩

���ߣ����Ŀ�  
ѧ�ţ�23307110192

˼���⣺

1. Ϊʲô��??Player��?����ָ��Player��ָ��?
    ��Ϊ�˴�ʵ��������Ҫһ��Player���ͱ������洢���ֵ����״̬����Ϊ���ƿ��յĴ洢�ڵ�  
2. ����������ÿ����Ӧ?����?ʱˢ��UI��������Ϸ?��?����??�������ƶ���NPC������ôˢ�½�?Ч���Ż����?  
    ����ͨ������һ���������߳�������NPC���������ƶ�������ÿ��NPC�ƶ���ˢ��UI������������ȷ��UI��ʵʱ���£�������Ӱ���û��������Ӧ�ٶȡ�  
3. �ṹ��UI���һ�����𣿻᲻����ĳЩ����£����ǲ��ò�����һЩ�ǽṹ������أ�
    �ṹ��UI���ͨ���ܹ��ṩһ���ԺͿ�Ԥ���ԣ������û����顣Ȼ������ĳЩ�ض�����£��ǽṹ����ƿ��ܸ�Ϊ�ʺϡ����磬����Ҫչʾ�������ݻ�������Ʒʱ���ǽṹ����ƿ����ṩ��������ɶȺͱ���������ˣ�ѡ��ṹ�����Ƿǽṹ�����Ӧ���ݾ�������ͳ�����������

## 1 ��������

**��д���뻷��������**

1. ����ϵͳ��Windows 11
2. IDE���ߣ�Visual Studio Code
3. ��������gcc (GCC) 14.1.0
4. ����ģʽ��GBK *(�����ڿ���̨�в�����)*

**ʹ�ý��ܣ�**

1. ���ն��д�PJ2�ļ���
2. ����`make`�������`src`�е�Դ�ļ���`build`������`main.exe`��ִ���ļ�
3. ����`./build/main`���г���

**ע�����**

1. ���������[map](../build/map)��[save](../build/save)�е��ļ�����ɾ��������Ȳ���  
2. �뾡��ʹ��ȫ���ն����г��򣬷�����ܻ������ʾ����  
3. ף���Ҹ�

## 2 ��ɹ���

### 2.1 ��������

1. PJ1���й���  
    1. �˵�
    2. ��Ϸ����
2. ������������  
    1. ����
    2. ����
3. ��ͼ���빦��  
    1. �ɱ�˵�ѡ��
    2. ʵʱ����ͼ�ļ���Ϣ

### 2.2 ѡ������

1. �Զ����ͼ���ϵͳ
2. ��ͼ��������
    1. �½���ͼ
    2. ���õ�ͼ
    3. ɾ����ͼ
    4. ��������ͼ  

### 2.3 ��Ҫ����

1. **�˵�**
    1. �Ż�ˢ����ʾ��ʽ  
    2. ���ܺ���ʾ���  
    3. �߼�ͳһ��  
    4. ����ö�ٺͶ༶ָ��ȷ�ʽ���Ż�����ṹ������Դ�ļ��ɶ���  
2. **��ͼ**  
    1. ��ͼ�Զ�����ƹ���  
        1. ֧����ɶȼ��ͱ༭����
        2. ��Ϣ��ʾ�Ż�  
        3. �����߼�����ƽṹ�Ż�����Ч������ʾ������  
        4. �Զ��幦��Դ�ļ��ɶ�������  
    2. ��ͼ����  
        1. �½������á�ɾ�����������ȹ���  
        2. �����˵��߼��Ż���ʵ�ֵ�ͼ�����ຯ�������ͳһ��ʵʱ�ɱ�  
    3. ��ͼ״̬
        1. ͨ�����ĵ�ͼ�洢��ʽ��Ϊ��ͼ
3. **��Ϸ����**
    1. ��������������
        1. ʵ��PJ1�Ѿ�ʵ�ֹ����˴��Ż����߼��������岻��
    2. �浵����
        1. �½��Զ����`.save`���ļ������ڴ洢��Ӧ��ͼ����浵
        2. Χ��`.save`�ļ���ʵ���˴浵�ĳ�ʼ�������桢���롢���õȹ���

## 3 �������

���½������ļ���Ҫ�������ֱַ����

### 3.1 ������

Դ����[main.c](../src/00_main.c)  
ƽƽ���������������`runMenu()`���������������  

### 3.2 �˵�

Դ����  

1. ͷ�ļ���[menuUpdate.h](../src/01_menuUpdate.h)  
2. ʵ���ļ���[menuUpdate.c](../src/01_menuUpdate.c)  

#### 3.2.1 �����߼�

�ܹ����������汾�Ĳ˵����£��γ������ڵ���ʽ  

��Ҫ˼�룺  

1. �˵�����˼��
    1. ���ࣺ`���ɲ˵�`��`֧�ɲ˵�`
    2. �����߼���

          ```mermaid
          graph LR;
                �������-->������-->�˵�����ж�
                �˵�����ж�-->���ɲ˵�1-->���Ĳ˵����
                �˵�����ж�-->���ɲ˵�2-->���Ĳ˵����
                �˵�����ж�-->|�˳�����|�˳�����
                ���Ĳ˵����-->������
                ���ɲ˵�1-->��֧�˵�1-->���ɲ˵�1
                ���ɲ˵�1-->��֧�˵�2-->���ɲ˵�1
                ���ɲ˵�2-->��֧�˵�3-->���ɲ˵�2
                ���ɲ˵�2-->��֧�˵�4-->���ɲ˵�2
          ```

          ����˵����`������`��ʼ����һ��`���ɲ˵�`�����У�`ֱ�ɲ˵�`��`���ɲ˵�`�б�����  
2. �˵���������һ���߼�

     ```mermaid
     graph LR;
          �˵�����-->��ӡ�˵���Ϣ-->����ѡ����ƺ���-->|��ѡѡ��|ά���˵���ʾ-->|ѡ��|����ѡ��ֵ-->�˵�ѡ���߼�ӳ�䴦��
     ```

3. �����`��ͼѡ��˵�`

     ʵʱά����ͼ��Ϣ���������鱸�ã�ʵ���ϴ���`mapName`,`mapPath`,`savePath`������  
     ����������Ϣ���Ա��˵���������ʾ�ı仯  

#### 3.2.2 �������

1. ����˵��  

     | ��������            | ����ֵ���� | ��������            | ��������                           |
     |---------------------|------------|---------------------|------------------------------------|
     | runMenu             | void       | void                | �˵����п���������                 |
     | boolSelectMenu      | int        | void                | �Ƿ�״̬��ȡ�˵�����               |
     | mainMenu            | void       | MENU *              | ���˵�����                         |
     | mapChooseMenu       | void       | MENU *              | ��ͼѡ��˵�����                   |
     | mapOperationMenu    | void       | int                 | ��ͼ�����˵�����                   |
     | saveLoadMenu        | int        | int                 | �浵��ȡ�˵�����                   |
     | controlModeMenu     | int        | void                | ����ģʽ�˵�����                   |
     | editProgressMenu    | int        | void                | �༭���Ȳ˵�����                   |
     | mapNameGet          | void       | void                | ��ȡ��ͼ���Ʋ�ά��������������   |
     | mapNewCreate        | void       | void                | �½���ͼ����                       |
     | mapNameChange       | void       | int                 | ��ͼ���Ƹ��ĺ���                   |
     | mapRemove           | void       | int                 | ɾ����ͼ����                       |
     | getMapStatus        | int        | int                 | ��ȡ��ͼ״̬                       |
     | startGame           | void       | int                 | ��Ϸ��ʼ����                       |
     | printMenu           | void       | MENU, int           | ��ӡ�˵�                           |
     | cursorChoose        | int        | COORD, int          | �˵�����ƶ�����                   |
     | freshCursor         | void       | COORD, int, int     | �˵�����ƶ���ʾ�����             |
     | printFile           | void       | int                 | ��ӡ�ĵ������ϱȽϷ��ӵĴ�ӡ������ |

2. ����˵��

    | ��������            | ����            | ��������                           |
    |---------------------|-----------------|------------------------------------|
    | mapName             | char\[10\]\[64\]    | �洢��ͼ����                       |
    | mapPath             | char\[10\]\[64\]    | �洢��ͼ�ļ�·��                   |
    | savePath            | char\[10\]\[64\]    | �洢��ͼ�����ļ�·��               |
    | mapNumbers          | int             | �洢��ͼ����                       |

### 3.3 ������

Դ����

1. ͷ�ļ���[02_cursorOperation.h](../src/02_cursorOperation.h)  
2. ʵ���ļ���[02_cursorOperation.c](../src/02_cursorOperation.c)  

#### 3.3.1 �����߼�

���Ǳ������Ż��ĺ��ģ�����ˢ����ʾ�Ż���ʽ�Ļ�ʯ  

��������Ҫ���ڿ���̨�������ʾ�Ż���ͨ�����ƹ���λ�ú���ʾ״̬��ʵ�ָ��������û����顣  

��Ҫ���ܣ�

1. �ƶ���굽ָ��λ��
2. ��ȡ��ǰ���λ��
3. ���ָ��λ��֮�����Ļ����
4. ���ع��
5. ��ʾ���

#### 3.3.2 �������

1. ����˵��  

     | ��������            | ����ֵ���� | ��������            | ��������                           |
     |---------------------|------------|---------------------|------------------------------------|
     | MoveCursorTo        | void       | int, int            | �ƶ���굽ָ��λ��                 |
     | GetCursorPosition   | void       | int*, int*          | ��ȡ��ǰ���λ��                   |
     | ClearPartialScreen  | void       | int, int            | ���ָ��λ��֮�����Ļ����         |
     | HideConsoleCursor   | void       | void                | ���ع��                           |
     | ShowConsoleCursor   | void       | void                | ��ʾ���                           |

2. ����˵��

     ��ģ�鲻�漰ȫ�ֱ��������ں����ڲ�ʹ�þֲ�������

#### 3.3.3 ʹ��ʾ��

1. �ƶ���굽ָ��λ�ã�

     ```c
     MoveCursorTo(10, 5); // ������ƶ�����10�У���5��
     ```

2. ��ȡ��ǰ���λ�ã�

     ```c
     int row, col;
     GetCursorPosition(&row, &col); // ��ȡ��ǰ���λ�ã��洢��row��col��
     ```

3. ���ָ��λ��֮�����Ļ���ݣ�

     ```c
     ClearPartialScreen(5, 0); // ��մӵ�5�У���0�п�ʼ֮�����Ļ����
     ```

4. ���غ���ʾ��꣺

     ```c
     HideConsoleCursor(); // ���ع��
     ShowConsoleCursor(); // ��ʾ���
     ```

### 3.4 ��ͼ�����״̬

Դ����

1. ͷ�ļ���[mapAndPlayerStatus.h](../src/03_mapAndPlayerStatus.h)  
2. ʵ���ļ���[mapAndPlayerStatus.c](../src/03_mapAndPlayerStatus.c)  

#### 3.4.1. �����߼�

��ͼ�����״̬ģ�鸺���ʼ���͹�����Ϸ�еĵ�ͼ�����״̬��������ͼ�ļ��ء����桢��ӡ�Լ���ҵ��ƶ���״̬���¡�

��Ҫ���ܣ�

1. ��ʼ����ͼ�����״̬
2. ���غͱ����ͼ�����״̬
3. ��ӡ��ͼ�����״̬
4. �ж�����ƶ��Ƿ�Ϸ�
5. ������������Ҳ���

#### 3.4.2 �������

1. ����˵��  

     | ��������            | ����ֵ���� | ��������            | ��������                           |
     |---------------------|------------|---------------------|------------------------------------|
     | mapIni              | void       | struct mapInfo*     | ��ʼ���Թ�                         |
     | mapInput            | int        | struct mapInfo*, int| �����Թ�                           |
     | mapPrint            | void       | struct mapInfo*     | ��ӡ�Թ�                           |
     | playerIni           | void       | struct playerInfo*, struct mapInfo* | ��ʼ�������Ϣ         |
     | playerInfoPrint     | void       | struct playerInfo*, int | ��ӡ�����Ϣ                     |
     | exitInfoPrint       | void       | struct playerInfo*  | ��ӡ�˳���Ϣ                       |
     | playerMoveJudge     | int        | struct playerInfo*, struct mapInfo*, char | ����ƶ��ж�       |
     | moveBack            | void       | struct playerInfo*, struct mapInfo* | ��������               |
     | moveRedo            | char       | struct playerInfo*, struct mapInfo* | ��������               |
     | playerMove          | void       | struct playerInfo*, struct mapInfo*, int | ����ƶ�ʵʱģʽ     |
     | playerMovePro       | void       | struct playerInfo*, struct mapInfo*, int | ����ƶ����ģʽ     |
     | progressAutoSave    | void       | struct playerInfo*, struct mapInfo*, int, int, int | �Զ�������Ϸ���� |
     | progressExitSave    | void       | struct playerInfo*, struct mapInfo*, int | �˳�ʱ������Ϸ����   |
     | progressSaveInit    | void       | int                | ��ʼ���浵��Ϣ                     |
     | saveOperation       | void       | struct playerInfo*, struct mapInfo*, int | ������Ϸ���Ⱦ������ |
     | progressLoad        | void       | struct playerInfo*, struct mapInfo*, int | ���ش浵             |

2. ����˵��

     | ��������            | ����            | ��������                           |
     |---------------------|-----------------|------------------------------------|
     | map                 | char\[50][50]    | ��ͼ��Ϣ                           |
     | mapRow              | int             | ��ͼ����                           |
     | mapCol              | int             | ��ͼ����                           |
     | treasureNum         | int             | ��������                           |
     | trapNum             | int             | ��������                           |
     | pRow, pCol          | int             | ���λ��                           |
     | px, py              | int             | ���λ����Ϣ                       |
     | energyCost          | int             | ��������                           |
     | getTreasure         | int             | ��ñ�������                       |
     | isTrapped           | int             | �Ƿ񴥷�����                       |
     | moveMemory          | char[1000]      | �ƶ�·��                           |
     | moveResult          | int[1000]       | �ƶ����������ʱʹ�ã�             |
     | tt                  | int             | moveMemory��moveResult�ĳ���       |

### 3.5 �Զ����ͼ

Դ����

1. ͷ�ļ���[mapCustomUpdate.h](../src/04_mapCustomUpdate.h)  
2. ʵ���ļ���[mapCustomUpdate.c](../src/04_mapCustomUpdate.c)  

#### 3.5.1 �����߼�

�Զ����ͼģ�������û���ƺͱ༭�Լ��ĵ�ͼ�������䱣���Թ�����ʹ�á���ģ���ṩ�˵�ͼ�Ĵ������༭�������ɾ���ȹ��ܡ�

��Ҫ���ܣ�

1. �����µ�ͼ
2. �༭���е�ͼ
3. �����ͼ
4. ɾ����ͼ
5. ��������ͼ

#### 3.5.2 �������

����ӿ�ֻ��`��ͼ��ʼ��`��`��ͼ��д`����  
��Ҫ[menuUpdate](#322-�������)�еĵ�ͼ·���ʹ浵·����Ϣ֧��  

1. ����˵��  

    | ��������            | ����ֵ���� | ��������            | ��������                           |
    |---------------------|------------|---------------------|------------------------------------|
    | mapCustomIni        | void       | int, int            | ��ʼ������Թ�                     |
    | mapCustomEdit       | void       | int, int            | �༭����Թ�                       |
    | editProgressLoad    | void       | struct mapInfo*, int, int*, int*, int* | �༭���ȶ�ȡ       |
    | editMapSave         | void       | struct mapInfo*, int, int, int, int | �༭��ͼ�洢       |
    | editInfoPrintFresh  | void       | struct mapInfo*, COORD*, int, int, int, int, int, int | ��ͼ��Ϣ��ʾˢ�� |
    | editMapReplace      | void       | struct mapInfo*, COORD, int, int, int*, int*, int*, int | �ؿ��滻         |
    | editOrderInput      | void       | struct mapInfo*, COORD, int*, int*, int*, int*, int*, int | �༭�����     |
    | editOrderGet        | int        | void                | �༭�����ȡ                       |
    | editMap             | int        | struct mapInfo*, COORD*, int*, int*, int* | �༭��ͼ����       |
    | editPrint           | void       | int, struct mapInfo*, COORD*, int, int, int | �༭�����ӡ����Ϣ�洢 |
    | editInit            | void       | struct mapInfo*     | �༭��ͼʱ��ʼ����ͼ��Ϣ           |
    | acceptNumSet        | void       | int*, int*, int**, int | �ɽ�����ֵ��Χ����               |
    | mapInfoSet          | void       | struct mapInfo*     | ���õ�ͼ����                       |

2. ����˵��

    | ��������            | ����            | ��������                           |
    |---------------------|-----------------|------------------------------------|
    | mapInfo             | struct mapInfo  | ��ͼ��Ϣ�ṹ��                     |
    | loc                 | COORD[5]        | ���λ������                       |
    | Tnum                | int             | ��������                           |
    | Dnum                | int             | ��������                           |
    | playerSetFlag       | int             | ���λ�����ñ�־                   |
