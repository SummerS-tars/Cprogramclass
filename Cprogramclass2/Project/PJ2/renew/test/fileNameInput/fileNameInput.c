#include <stdio.h>      // 标准输入输出库
#include <stdlib.h>     // 标准库，包含了malloc, free, exit等函数
#include <dirent.h>     // 目录操作库，包含了DIR, opendir, readdir, closedir等函数
#include <sys/stat.h>   // 文件状态库，包含了stat, struct stat等函数
#include <string.h>     // 字符串操作库，包含了strrchr等函数

// 列出指定路径下的所有文件
void listFiles(const char *path) {
    struct dirent *entry;  // 用于存储目录项信息
    DIR *dp = opendir(path);  // 打开目录

    if (dp == NULL) {  // 如果目录打开失败
        perror("opendir");  // 输出错误信息
        return;
    }

    int fileCount = 0;  // 文件计数器
    printf("Files in directory %s:\n", path);
    while ((entry = readdir(dp))) {  // 读取目录中的每一项
        char fullPath[1024];  // 存储文件的完整路径
        snprintf(fullPath, sizeof(fullPath), "%s/%s", path, entry->d_name);  // 生成完整路径
        struct stat fileStat;  // 用于存储文件状态信息
        if (stat(fullPath, &fileStat) == 0 && S_ISREG(fileStat.st_mode)) {  // 检查文件状态，确保是常规文件
            char *dot = strrchr(entry->d_name, '.');  // 查找文件名中的最后一个点
            if (dot) {
                *dot = '\0';  // 去掉文件名中的后缀
            }
            printf("%s\n", entry->d_name);  // 输出文件名
            fileCount++;  // 文件计数器加1
        }
    }

    closedir(dp);  // 关闭目录
    printf("Total number of files: %d\n", fileCount);  // 输出文件总数
}

// 更改文件名
void renameFile(const char *oldName, const char *newName) {
    if (rename(oldName, newName) == 0) {
        printf("File renamed successfully from %s to %s\n", oldName, newName);
    } else {
        perror("rename");
    }
}

int main() {
    const char *path = "./map"; // 替换为你的目录路径
    listFiles(path);  // 列出指定路径下的所有文件

    // 示例：更改文件名
    const char *oldName = "./map/oldfile.txt"; // 替换为旧文件名
    const char *newName = "./map/newfile.txt"; // 替换为新文件名
    renameFile(oldName, newName);

    return 0;
}