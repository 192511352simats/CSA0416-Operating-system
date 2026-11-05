
#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

void *worker(void *arg)
{
    (void)arg;
    return NULL;
}

int main(void)
{
    const int count = 1000;
    pthread_t threads[count];
    struct timespec start, end;

    clock_gettime(CLOCK_MONOTONIC, &start);

    for (int i = 0; i < count; i++) {
        int result = pthread_create(&threads[i], NULL,
                                    worker, NULL);
        if (result != 0) {
            printf("Thread creation failed: %d\n", result);
            return 1;
        }
    }

    for (int i = 0; i < count; i++) {
        int result = pthread_join(threads[i], NULL);
        if (result != 0) {
            printf("Thread join failed: %d\n", result);
            return 1;
        }
    }

    clock_gettime(CLOCK_MONOTONIC, &end);

    double elapsed =
        (end.tv_sec - start.tv_sec) +
        (end.tv_nsec - start.tv_nsec) / 1e9;

    printf("Threads created: %d\n", count);
    printf("Total time: %.6f seconds\n", elapsed);

    return 0;
}
