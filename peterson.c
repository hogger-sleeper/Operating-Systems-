#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>

#define NUM_ITERATIONS 5

int flag[2] = {0, 0}; // Flags to indicate if a process wants to enter critical section
int turn = 0;         // Variable to decide whose turn it is

void *process_0(void *arg) {
    for (int i = 0; i < NUM_ITERATIONS; i++) {
        flag[0] = 1;
        turn = 1;
        while (flag[1] && turn == 1);

        // Critical Section
        printf("Process 0 is in the critical section.\n");
        sleep(1);

        // Exit Section
        flag[0] = 0;
        printf("Process 0 is leaving the critical section.\n");
        sleep(1);
    }
    return NULL;
}

void *process_1(void *arg) {
    for (int i = 0; i < NUM_ITERATIONS; i++) {
        flag[1] = 1;
        turn = 0;
        while (flag[0] && turn == 0);

        // Critical Section
        printf("Process 1 is in the critical section.\n");
        sleep(1);

        // Exit Section
        flag[1] = 0;
        printf("Process 1 is leaving the critical section.\n");
        sleep(1);
    }
    return NULL;
}

int main() {
    pthread_t t0, t1;

    // Create two threads simulating two processes
    pthread_create(&t0, NULL, process_0, NULL);
    pthread_create(&t1, NULL, process_1, NULL);

    // Wait for both threads to complete
    pthread_join(t0, NULL);
    pthread_join(t1, NULL);

    return 0;
}