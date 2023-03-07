#include "../kernel/types.h"
#include "user.h"

int main(int argn, const char * argv[]) {
    if (argn != 2) {
        printf("you must input one interger argument only, for example 'sleep 10'.\n");
        exit(0);
    }
    // t >= 0
    int t = atoi(argv[1]);
    if (t > 0) {
        sleep(t);
    }
    exit(0);
}