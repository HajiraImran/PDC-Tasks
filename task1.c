#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>


float random_float() {
    return (float)rand() / (float)RAND_MAX;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <array_size>\n", argv[0]);
        return 1;
    }

    long long n = atoll(argv[1]); 
    float *arr = (float *)malloc(n * sizeof(float));
    if (arr == NULL) {
        printf("Memory allocation failed for size %lld\n", n);
        return 1;
    }

    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    
    #pragma omp parallel for
    for (long long i = 0; i < n; i++) {
        arr[i] = random_float();
    }

    clock_gettime(CLOCK_MONOTONIC, &end);

    double elapsed = (end.tv_sec - start.tv_sec) +
                     (end.tv_nsec - start.tv_nsec) / 1e9;

    printf("Array size: %lld, Execution time: %f seconds\n", n, elapsed);

    free(arr);
    return 0;
}
