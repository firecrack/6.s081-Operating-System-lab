#include "kernel/types.h"
#include "kernel/param.h"
#include "user.h"

#define STDIN 0
#define STDOUT 1
#define NEWLINE_FLAG '\n'

int main(int argc, char* argv[]) {
    if (argc < 2) {
        fprintf(2, "error!\n");
        exit(1);
    }
    if (argc - 1 > MAXARG) {
        fprintf(2, "error: too many arguments!\n");
        exit(1);
    }
    const char* const command = argv[1];
    char* args[MAXARG];
    int argn = argc - 1;
    // copy arg
    for (int i = 1; i < argc; i++) {
        args[i - 1] = argv[i];
    }
    // 从标准输入读取其他参数
    char buf[32];
    int n = 0; //实际读取字节数
    char arg[512];
    int k = 0; //从标准输入读取的参数长度
    while ((n = read(STDIN, buf, 32)) > 0) {
        for (int j = 0; j < n; j++) {
            if (buf[j] != NEWLINE_FLAG) {
                arg[k++] = buf[j];
            } else { // 读完一行参数执行命令
                arg[k++] = '\0';
                args[argn++] = arg;
                if (fork() == 0) {
                    exec(command, args);
                    exit(0);
                } else {
                    wait(0);
                    k = 0;
                    argn = argc - 1;
                }
            }
        }
    }

    exit(0);
}