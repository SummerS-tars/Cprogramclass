# �˵������� Version 2.1

## 1. ��˼

**��������**��  

1. �淶�˵��������  
2. �˵���ʾ��ѡ���빦�ܷ���  
3. �򻯲˵������߼�  
4. �����˵�ѡ����Ⱦ��ʽ  
5. �ṩһЩͨ���߼������ⲿĳЩʱ��Ҳ����ʹ��  

**�����߼�**��  

```mermaid
graph LR;
   ����˵�-->��ʾ�˵�-->ѡ����-->ѡ��ĳһ��-->����ֵ-->��������
```  

## 2. ���

### 2.1 �˵�������������

1. `��ӭҳ��`
   1. �ڽ������ʱ��ʾ����������`���˵�`
   2. ��Ϸ��������ʾ�������ص�������Ϸ�Ĳ˵�  
2. `���˵�`  
   1. `��ʼ��Ϸ`������`��ͼ����ѡ��˵�`
   2. `��ȡ����`��չʾ�����ĵ�1��չʾ��Ϸ������Ϣ�������淨
   3. `�˳���Ϸ`
3. `��ͼ����ѡ��˵�`
   1. `Ĭ�Ϲؿ�`
   2. `�Զ���ؿ�`
   3. `�������˵�`
4. `Ĭ�Ϲؿ��˵�`
   1. `��ͼһ`��ʵ�ʿ�����ʾ���ǵ�ͼ���ƣ�Ȼ��������״̬����gameStart����ѡ����Ϸģʽ������ֱ��ѡ����Ϸģʽ
   2. `��ͼ��`
   3. `��ͼ��`
   4. `���ص�ͼ����ѡ��˵�`
5. `�Զ���ؿ��˵�`
   1. `�Զ����ͼһ`��ֱ�ӽ�������˵�
   2. `�Զ����ͼ��`
   3. `�Զ����ͼ��`
   4. `���ص�ͼ����ѡ��˵�`
6. `�Զ���ؿ������˵�`
   1. `��ʼ����`����������ǵ�ͼ�����ѱ༭״̬����ʾ��ѡ�ѡ����`Ĭ�Ϲؿ�`ѡ��ؿ���������һ��
   2. `��ʼ�༭`������õ�ͼ�ı༭ģʽ
   3. `���õ�ͼ`�����øõ�ͼ
   4. `�����˵�`
   5. `���ص�ͼ����ѡ��˵�`
7. `����ѡ��˵�`
   1. `�����ϴ���Ϸ`
   2. `��ʼ����Ϸ`
   3. `����浵`
   4. `����`
8. `��Ϸģʽѡ��˵�`
   1. `ʵʱģʽ`
   2. `���ģʽ`
   3. `�����˵�`
   4. `����`
9. `����ȷ�ϲ˵�`
   1. ��Ϸ��������ʱ�浵����ʱʹ��
   2. ��Ϸ��������ʱ��������ʹ��

### 2.2 �߼����

**�˵���Ҫ����**:  

1. `���ɲ˵�`  
2. `��֧�˵�`  

���ɲ˵����������У�ͨ�����Ĳ˵����������л�ҳ  
��֧�˵������ɲ˵��е��ã���ɹ��ܺ󷵻����ɲ˵�������  
��ˣ�����ͳһ��ڵĲ˵����Թ鵽���ɲ˵�֮�У�������Ҫ������ںͷ���ֵ�ͷ���λ�õĲ˵����Թ鵽��֧�˵���  

**����**:  

1. `���ɲ˵�`��  
   1. `���˵�`
   2. `��ͼ����ѡ��˵�`
   3. `Ĭ�Ϲؿ��˵�`
   4. `�Զ���ؿ��˵�`
2. `��֧�˵�`
   1. `�Զ���ؿ������˵�`
   2. `����ѡ��˵�`
   3. `��Ϸģʽѡ��˵�`

**�˵������߼��������**:  

1. ����ʼ������ֻ��һ��`���ɲ˵�`ʵ�������У������Ϳ��Կ�����һ�����������У����ǲ�����֮Ϊ`�˵����к���`
2. `���ɲ˵�`֮����һ���ν��߼�����`�˵����к���`���л��������е�`���ɺ���`
3. ��`���ɺ���`�ϣ�������Ҫ����`��֧�˵�`

### 2.3 �˵�����ʵ��

**�洢��**

1. ���в˵�ͳһ����`static char`��ά����洢ѡ���һάͳһ����40Ԫ�����ޣ����յڶ�ά����ѡ����������߿ɵ�����  
   1. `mainMenuList`
   2. `mapTypeMenuList`
   3. `defaultMapMenuList`
   4. `customMapMenuList`
   5. `customOperationMenuList`
   6. `saveLoadMenuList`
   7. `controlModeMenuList`
2. ���ò���`static char (*[])[40]`���͵�`menuList`�洢ָ��˵�ѡ��洢�����ָ��  
3. ʹ��`enum`Ϊÿ���˵�������`menuList`�е�˳�����ö������`MENU`�Ķ��壬���ں������ã���߳���ɶ���  

   ```c
   typedef enum _MENU{   // �˵�ö��
      MAIN_MENU = 0,
      MAP_TYPE_MENU,
      DEFAULT_MAP_MENU,
      CUSTOM_MAP_MENU,
      CUSTOM_OPERATION_MENU,
      SAVE_LOAD_MENU,
      CONTROL_MODE_MENU
   } MENU;
   ```

**����ʵ�֣�**

* **��Ҫ�˵�����**

1. **��������**  

   1. **���ɲ˵���**
      1. `mainMenu`
      2. `mapTypeMenu`
      3. `defaultMapMenu`
      4. `customMapMenu`
   2. **��֧�˵���**
      1. `customOperationMenu`
      2. `saveLoadMenu`
      3. `controlModeMenu`  

2. **�����Լ�������**

   ```c
   static void mainMenu( MENU *pmenu ) ;                // ���˵�����
   static void mapTypeMenu( MENU *pmenu ) ;             // ��ͼ����ѡ��˵�����
   static void defaultMapMenu( MENU *pmenu ) ;          // Ĭ�ϵ�ͼ�˵�����
   static void customMapMenu( MENU *pmenu ) ;           // �Զ����ͼ�˵�����
   static void customOperationMenu( int mapOrder ) ;             // �Զ����ͼ�����˵�����
   static int saveLoadMenu( int mapOrder ) ;                    // �浵��ȡ�˵�����
   static int controlModeMenu() ;                 // ����ģʽ�˵�����
   ```

* **���幦������ʵ��**

1. **�˵�������߼���**  

   ���ɲ˵�����`runMenu`�����н�������
   ���������ڼ��κ�ʱ������ֻ��һ�����ɲ˵�����������

   1. `runMenu`

      ```mermaid
      graph LR;
         runMenu-->menu�ж�
         menu�ж�-->|MAIN_MENU|mainMenu
         menu�ж�-->|MAP_TYPE_MENU|mapTypeMenu
         menu�ж�-->|DEFAULT_MAP_MENU|defaultMapMenu
         menu�ж�-->|CUSTOM_MAP_MENU|customMapMenu
         mainMenu-->menu�ٴ��ж�
         mapTypeMenu-->menu�ٴ��ж�
         defaultMapMenu-->menu�ٴ��ж�
         customMapMenu-->menu�ٴ��ж�
         menu�ٴ��ж�-->|-1|��������
         menu�ٴ��ж�-->menu�ж�
      ```

   2. `mainMenu`

      ```mermaid
      graph LR;
         mainMenu-->��ʼ��Ϸ
         mainMenu-->��ȡ����
         mainMenu-->�˳���Ϸ
         ��ʼ��Ϸ-->|�޸�menu|MAP_TYPE_MENU
         ��ȡ����-->չʾ�����ĵ�1
         �˳���Ϸ-->|�޸�menu|-1
      ```

   3. `mapTypeMenu`

      ```mermaid
      graph LR;
         mapTypeMenu-->Ĭ�Ϲؿ�
         mapTypeMenu-->�Զ���ؿ�
         mapTypeMenu-->�������˵�
         Ĭ�Ϲؿ�-->|�޸�menu|DEFAULT_MAP_MENU
         �Զ���ؿ�-->|�޸�menu|CUSTOM_MAP_MENU
         �������˵�-->|�޸�menu|MAIN_MENU
      ```

   4. `defaultMapMenu`

      ```mermaid
      graph LR;
         defaultMapMenu-->��ͼһ
         defaultMapMenu-->��ͼ��
         defaultMapMenu-->��ͼ��
         defaultMapMenu-->���ص�ͼ����ѡ��˵�
         ��ͼһ-->**gameStart**
         ��ͼ��-->**gameStart**
         ��ͼ��-->**gameStart**
         **gameStart**-->|������|�ص���ͼѡ��˵�
         ���ص�ͼ����ѡ��˵�-->|�޸�menu|MAP_TYPE_MENU
      ```

   5. `customMapMenu`

      ```mermaid
      graph LR;
         customMapMenu-->�Զ����ͼһ
         customMapMenu-->�Զ����ͼ��
         customMapMenu-->�Զ����ͼ��
         customMapMenu-->���ص�ͼ����ѡ��˵�
         �Զ����ͼһ-->|ֱ�ӵ���|customOperationMenu
         �Զ����ͼ��-->|ֱ�ӵ���|customOperationMenu
         �Զ����ͼ��-->|ֱ�ӵ���|customOperationMenu
         ���ص�ͼ����ѡ��˵�-->|�޸�menu|MAP_TYPE_MENU
      ```

   6. `customOperation`

      ```mermaid
      graph LR;
         customOperationMenu-->|�ѱ༭��ѡ|**gameStart**
         customOperationMenu-->��ʼ�༭
         customOperationMenu-->���õ�ͼ
         customOperationMenu-->�����Զ���˵�
         ��ʼ�༭-->|������|����customMapMenu
         ���õ�ͼ-->|������|����customMapMenu
         **gameStart**-->|������|�ص���ͼѡ��˵�
         �����Զ���˵�-->����customMapMenu
      ```

   7. `gameStart`
      ���а�����`saveLoadMenu`��`controlModeMenu`�������߼�

      ```mermaid
      graph LR;
         gameStart-->|mapStatus==SAVED|saveLoadMenu
         saveLoadMenu-->�����ϴ���Ϸ-->controlModeMenu
         saveLoadMenu-->��ʼ����Ϸ-->controlModeMenu
         saveLoadMenu-->����浵-->���ص�ͼѡ��˵�
         saveLoadMenu-->����-->���ص�ͼѡ��˵�
         gameStart-->|mapStatus==UNSAVED|controlModeMenu
         controlModeMenu-->ʵʱģʽ-->��Ϸ����
         controlModeMenu-->���ģʽ-->��Ϸ����
         controlModeMenu-->��ȡ����-->controlModeMenu
         controlModeMenu-->����
         ��Ϸ����-->|���н���|���ص�ͼѡ��˵�
      ```

2. **�˵��ڲ�����ʵ�֣�**
   1. ͨ���߼���

      ```mermaid
      graph LR;
         ��ӡ��洢�˵���Ϣ-->����˵�ѡ����-->����optionֵ-->����option����ѡ��
      ```

   2. ��ӡ��洢�˵���Ϣ��  
      1. ��ӡ����ʵ��

         ```c
         static void printMenu( MENU menu , int num ) ;
         ```

      2. �˵���Ϣ�洢
         1. ������Ϣ��

            ```c
            int listNum ; // �洢��ǰ�˵���ѡ����
            COORD loc ; // ���ڴ洢����ڿ���̨�Ĵ�ӡ��ʼλ��
            ```

         2. ������Ϣ��

            ```c
            int mapStatus ; // ����defaultMapMenu��customOperationMenu�в����ͼ��Ϣ
            ```

         3. ����ʵ�֣�
            `listNum`ʹ��`listNumCount`����õ�  
            `loc`ͨ��`GetCursorPosition`���ض����н��̵õ�  
            `mapStatus`ͨ��`getMapStatus`�õ�  

            ����������  

            ```c
            // ����˵�ѡ������
            static int listNumCount( MENU menu ) ;
            // ��ȡ�˵���ӡ������Ϣ����������������������
            static int getMapStatus( int mapOrder ) ;
            // Ĭ�ϵ�ͼ�浵״̬��ʾ
            static void defaultMapStatus( int mapOrder , int *status ) ;
            // �Զ����ͼ�浵״̬��ʾ
            static void customMapStatus( int customMapOrder , int *status ) ;
            ```

   3. �˵�ѡ����ʵ��  ��
      `cursorChoose`����ѡ��ѡ�ͨ������`freshCursor`ˢ����ʾ  

      ����������  

      ```c
      // �˵�����ƶ�����
      static int cursorChoose( COORD loc , int num ) ;                  
      // �˵�����ƶ���ʾ�����
      static void freshCursor( COORD loc , int num , int pos ) ;        
      ```

   4. ����ѡ��  
      ����`cursorChoose`���ص�ֵ������߼��Ķ�Ӧ���ÿ���˵����еĹ���ӳ��  

   5. ��ע��  
      1. ����ֻ�Ǹ����˵�������ͨ������߼���������Ϊ�˵�������Ҫ�����в����������  
      2. ����������Ϸ����ڶ��ǽ���`gameStart`

## 3. �ܽ�

[menuUpdate](../src/01_menuUpdate.c)�����Ż�����ΪVersion 2.1 �Ĳ˵������������˲˵����������  
��װ�̶ȸ��ߣ������˲���ȫȫ�ֱ�����ʹ��  
�߼�����ͳһ������  
