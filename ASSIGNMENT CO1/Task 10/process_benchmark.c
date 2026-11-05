
#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

int main(void)
{
    const int count = 1000;
    struct timespec start, end;

    clock_gettime(CLOCK_MONOTONIC, &start);

    for (int i = 0; i < count; i++) {
        pid_t pid = fork();

        if (pid < 0) {
            perror("fork");
            return 1;
        }

        if (pid == 0)
            _exit(0);

        int status;
        if (waitpid(pid, &status, 0) < 0) {
            perror("waitpid");
            return 1;
        }
    }

    clock_gettime(CLOCK_MONOTONIC, &end);

    double elapsed =
        (end.tv_sec - start.tv_sec) +
        (end.tv_nsec - start.tv_nsec) / 1e9;

    printf("Processes created: %d\n", count);
    printf("Total time: %.6f seconds\n", elapsed);

    return 0;
}
