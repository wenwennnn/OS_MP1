#include "syscall.h"

#define MAX_FILES 10  // 最大可打开的文件数

int main(void)
{
    char test[] = "abcdefghijklmnopqrstuvwxyz";
    int success, i;
    OpenFileId fid[MAX_FILES];  // 用于存储文件句柄的数组
    int fileCount = 0;  // 当前已打开文件的计数

    // 循环打开文件并写入数据
    for (i = 0; i < MAX_FILES; ++i) {
        char filename[20];
        sprintf(filename, "file%d.test", i);
        fid[i] = Open(filename);
        if (fid[i] < 0) {
            // 打开文件失败
            break;
        }
        ++fileCount;

        int count = Write(test, 26, fid[i]);
        if (count != 26) {
            // 写入文件失败
            break;
        }
    }

    // 关闭所有已打开的文件
    for (i = 0; i < fileCount; ++i) {
        Close(fid[i]);
    }

    // 输出成功或失败消息
    if (fileCount == MAX_FILES) {
        MSG("Success: All files created and written");
    } else {
        MSG("Failed: Some files could not be opened or written");
    }

    Halt();
}