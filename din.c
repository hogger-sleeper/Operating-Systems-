#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 5
#define LEFT (i + N - 1) % N
#define RIGHT (i + 1) % N

#define THINKING 0
#define HUNGRY 1
#define EATING 2

int state[N];
sem_t mutex;
sem_t S[N];

void think(int i)
{
    printf("Philosopher %d is thinking!!!!!!!!!\n", i);
    sleep(1);
}

void eat(int i)
{
    printf("Philosopher %d is eating!!!!!!!!!\n", i);
    sleep(2);
}

void test(int i)
{
    if (state[i] == HUNGRY && state[LEFT] != EATING && state[RIGHT] != EATING)
    {
        state[i] = EATING;
        sem_post(&S[i]);
    }
}

void take_forks(int i)
{
    sem_wait(&mutex);
    state[i] = HUNGRY;
    test(i);
    sem_post(&mutex);
    sem_wait(&S[i]);
}

void put_forks(int i)
{
    sem_wait(&mutex);
    state[i] = THINKING;
    test(LEFT);
    test(RIGHT);
    sem_post(&mutex);
}

void *philosopher(void *num)
{
    int i = *(int *)num;
    while (1)
    {
        think(i);
        take_forks(i);
        eat(i);
        put_forks(i);
    }
}

int main()
{
    pthread_t thread_id[N];
    int phil[N];

    sem_init(&mutex, 0, 1);
    for (int i = 0; i < N; i++)
    {
        sem_init(&S[i], 0, 0);
        phil[i] = i;
    }

    for (int i = 0; i < N; i++)
    {
        pthread_create(&thread_id[i], NULL, philosopher, &phil[i]);
    }

    for (int i = 0; i < N; i++)
    {
        pthread_join(thread_id[i], NULL);
    }

    return 0;
}