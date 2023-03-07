#include "../kernel/types.h"
#include "user.h"
int main(int argn) {
    if (argn != 1) {
        printf("usage: pingpong\n");
        exit(0);
    }
    int fd[2];
    pipe(fd);
    char byte = '0';
    int pid = fork();
    if (pid == 0) { //child process
        read(fd[0], &byte, 1);
        close(fd[0]);
        printf("%d: received ping\n", getpid());
        write(fd[1], &byte, 1);
        close(fd[1]);
    } else if (pid > 0) { // parent process
        write(fd[1], &byte, 1);
        close(fd[1]);

        wait(0);

        read(fd[0], &byte, 1);
        close(fd[0]);
        printf("%d: received pong\n", getpid());

    } else {
        printf("fork error.\n");
    }
    exit(0);
}