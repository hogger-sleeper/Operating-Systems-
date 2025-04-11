#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 5 // Define the number of threads

// Function to be executed by each thread
void *print_hello(void *thread_id) {
    long tid = (long)thread_id;
    printf("Hello from thread %ld\n", tid);
    pthread_exit(NULL); // Exit the thread
}

int main() {
    int rc;
    long t;
    pthread_t threads[NUM_THREADS];

    // Creating threads
    for (t = 0; t < NUM_THREADS; t++) {
        printf("Creating Thread %ld\n", t);
        rc = pthread_create(&threads[t], NULL, print_hello, (void *)t);

        // Check if thread creation was successful
        if (rc) {
            printf("ERROR: Unable to create thread %d\n", rc);
            exit(-1);
        }
    }

    // Waiting for all threads to finish execution
    for (t = 0; t < NUM_THREADS; t++) {
        pthread_join(threads[t], NULL);
    }

    printf("All threads completed execution\n");

    return 0;
}
