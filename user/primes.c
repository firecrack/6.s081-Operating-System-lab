#include "../kernel/types.h"
#include "user.h"

#define RD_END 0
#define WR_END 1


void prime(int pipeIn[2]) {
    int first;
    close(pipeIn[WR_END]);
    if (read(pipeIn[RD_END], &first, sizeof(int)) == sizeof(int)) {
        printf("prime %d\n", first);
        int pipeOut[2];
        pipe(pipeOut);
        int num = 0;
        while (read(pipeIn[RD_END], &num, sizeof(int)) == sizeof(int)) {
            if (num % first != 0) {
                write(pipeOut[WR_END], &num, sizeof(int));
            }
        }
        close(pipeIn[RD_END]);
        int pid = fork();
        if (pid > 0) {
            close(pipeOut[WR_END]);
            close(pipeOut[RD_END]);
            wait(0);
        } else if (pid == 0) {
            prime(pipeOut);
        } else {
            printf("fork error.\n");
        }
    }
    exit(0);
}

int main(int argn) {
    int fd[2];
    pipe(fd);
    int pid = fork();
    if (pid == 0) { //child process
        prime(fd);
    } else if (pid > 0) { // parent process
        for (int i = 2; i <= 35; i++) {
            write(fd[WR_END], (void*)&i, sizeof(int));
        }
        close(fd[RD_END]);
        close(fd[WR_END]);
        wait(0);
        

    } else {
        printf("fork error.\n");
    }
    exit(0);
}