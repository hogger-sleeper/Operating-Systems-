#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t wrt;            // Semaphore to allow only one writer at a time
pthread_mutex_t mutex; // Mutex to protect read_count
int read_count = 0;    // Number of active readers
int shared_data = 0;   // Shared resource

// Reader function
void *reader(void *arg) {
    int id = *(int *)arg;
    
    pthread_mutex_lock(&mutex);
    read_count++;
    if (read_count == 1) // If first reader, block writers
        sem_wait(&wrt);
    pthread_mutex_unlock(&mutex);

    // Reading section
    printf("Reader %d is reading data: %d\n", id, shared_data);
    sleep(1);

    pthread_mutex_lock(&mutex);
    read_count--;
    if (read_count == 0) // If last reader, allow writers
        sem_post(&wrt);
    pthread_mutex_unlock(&mutex);

    return NULL;
}

// Writer function
void *writer(void *arg) {
    int id = *(int *)arg;

    sem_wait(&wrt); // Only one writer at a time
    // Writing section
    shared_data++;
    printf("Writer %d updated data to: %d\n", id, shared_data);
    sleep(2);
    sem_post(&wrt); // Allow other writers and readers

    return NULL;
}

int main() {
    pthread_t readers[5], writers[2];
    int reader_ids[5] = {1, 2, 3, 4, 5};
    int writer_ids[2] = {1, 2};

    // Initialize semaphore and mutex
    sem_init(&wrt, 0, 1);
    pthread_mutex_init(&mutex, NULL);

    // Create reader threads
    for (int i = 0; i < 5; i++)
        pthread_create(&readers[i], NULL, reader, &reader_ids[i]);

    // Create writer threads
    for (int i = 0; i < 2; i++)
        pthread_create(&writers[i], NULL, writer, &writer_ids[i]);

    // Wait for all threads to complete
    for (int i = 0; i < 5; i++)
        pthread_join(readers[i], NULL);
    for (int i = 0; i < 2; i++)
        pthread_join(writers[i], NULL);

    // Destroy semaphore and mutex
    sem_destroy(&wrt);
    pthread_mutex_destroy(&mutex);

    return 0;
}
