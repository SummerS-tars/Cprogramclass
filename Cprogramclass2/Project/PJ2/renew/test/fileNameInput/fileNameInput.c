#include <stdio.h>      // ��׼���������
#include <stdlib.h>     // ��׼�⣬������malloc, free, exit�Ⱥ���
#include <dirent.h>     // Ŀ¼�����⣬������DIR, opendir, readdir, closedir�Ⱥ���
#include <sys/stat.h>   // �ļ�״̬�⣬������stat, struct stat�Ⱥ���
#include <string.h>     // �ַ��������⣬������strrchr�Ⱥ���

// �г�ָ��·���µ������ļ�
void listFiles(const char *path) {
    struct dirent *entry;  // ���ڴ洢Ŀ¼����Ϣ
    DIR *dp = opendir(path);  // ��Ŀ¼

    if (dp == NULL) {  // ���Ŀ¼��ʧ��
        perror("opendir");  // ���������Ϣ
        return;
    }

    int fileCount = 0;  // �ļ�������
    printf("Files in directory %s:\n", path);
    while ((entry = readdir(dp))) {  // ��ȡĿ¼�е�ÿһ��
        char fullPath[1024];  // �洢�ļ�������·��
        snprintf(fullPath, sizeof(fullPath), "%s/%s", path, entry->d_name);  // ��������·��
        struct stat fileStat;  // ���ڴ洢�ļ�״̬��Ϣ
        if (stat(fullPath, &fileStat) == 0 && S_ISREG(fileStat.st_mode)) {  // ����ļ�״̬��ȷ���ǳ����ļ�
            char *dot = strrchr(entry->d_name, '.');  // �����ļ����е����һ����
            if (dot) {
                *dot = '\0';  // ȥ���ļ����еĺ�׺
            }
            printf("%s\n", entry->d_name);  // ����ļ���
            fileCount++;  // �ļ���������1
        }
    }

    closedir(dp);  // �ر�Ŀ¼
    printf("Total number of files: %d\n", fileCount);  // ����ļ�����
}

// �����ļ���
void renameFile(const char *oldName, const char *newName) {
    if (rename(oldName, newName) == 0) {
        printf("File renamed successfully from %s to %s\n", oldName, newName);
    } else {
        perror("rename");
    }
}

int main() {
    const char *path = "./map"; // �滻Ϊ���Ŀ¼·��
    listFiles(path);  // �г�ָ��·���µ������ļ�

    // ʾ���������ļ���
    const char *oldName = "./map/oldfile.txt"; // �滻Ϊ���ļ���
    const char *newName = "./map/newfile.txt"; // �滻Ϊ���ļ���
    renameFile(oldName, newName);

    return 0;
}