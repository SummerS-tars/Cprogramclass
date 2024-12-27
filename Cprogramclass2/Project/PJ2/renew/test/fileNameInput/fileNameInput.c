#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

char mapName[10][64];
char mapProgressSave[10][64];
static int mapNumbers;

void mapNameGet() 
{
    memset(mapName, 0, sizeof(mapName));
    memset(mapProgressSave, 0, sizeof(mapProgressSave));
    mapNumbers = 0;

    char *mapPath = "./map";
    char *progressPath = "./save";
    struct dirent *entry;

    DIR *dp = opendir(mapPath);
    if (dp == NULL) {
        perror("opendir");
        return;
    }

    int fileCount = 0;
    while ( entry = readdir(dp) ) {
        char fullPath[1024];
        snprintf(fullPath, sizeof(fullPath), "%s/%s", mapPath , entry->d_name);
        struct stat fileStat;
        if (stat(fullPath, &fileStat) == 0 && S_ISREG(fileStat.st_mode)) {
            char *dot = strrchr(entry->d_name, '.');
            if (dot) {
                *dot = '\0';
            }
            snprintf(mapName[fileCount], sizeof(mapName[fileCount]), "./map/%s.map", entry->d_name);
            snprintf(mapProgressSave[fileCount], sizeof(mapProgressSave[fileCount]), "./save/%s.save", entry->d_name);

            printf("%s\n", entry->d_name);
            fileCount++;
        }
    }

    closedir(dp);
    mapNumbers = fileCount;
}

void mapNameChange( int mapOrder )
{
    mapOrder--;
    char oldMapPath[64] = {0};
    char oldProgressSavePath[64] = {0};
    char newMapPath[64] = {0};
    char newProgressSavePath[64] = {0};

    snprintf(oldMapPath, sizeof(oldMapPath), "%s", mapName[mapOrder]);
    snprintf(oldProgressSavePath, sizeof(oldProgressSavePath), "%s", mapProgressSave[mapOrder]);

    printf("��ǰ��ͼ����: %s\n", oldMapPath);
    printf("��ǰ���ȱ�������: %s\n", oldProgressSavePath);

    char newMapName[40] = {0};
    printf("�������µĵ�ͼ����: ");
    scanf("%39s", newMapName);
    
    snprintf(newMapPath, sizeof(newMapPath), "./map/%s.map", newMapName);
    snprintf(newProgressSavePath, sizeof(newProgressSavePath), "./save/%s.save", newMapName );

    for (int i = 0; i < mapNumbers; i++) {
        if (strcmp(mapName[i], newMapPath) == 0) {
            printf("��ͼ�����Ѵ��ڣ������벻ͬ�����ơ�\n");
            return;
        }
    }

    if (rename(oldMapPath, newMapPath) == 0) {
        snprintf(mapName[mapOrder], sizeof(mapName[mapOrder]), "%s", newMapPath);
        printf("��ͼ�����Ѹ���Ϊ: %s\n", newMapPath);
    } else {
        perror("��ͼ���Ƹ���ʧ��");
    }

    if (rename(oldProgressSavePath, newProgressSavePath) == 0) {
        snprintf(mapProgressSave[mapOrder], sizeof(mapProgressSave[mapOrder]), "%s", newProgressSavePath);
        printf("���ȱ��������Ѹ���Ϊ: %s\n", newProgressSavePath);
    } else {
        perror("���ȱ������Ƹ���ʧ��");
    }
}

int main() {

    mapNameGet();

    mapNameChange(1);

    return 0;
}