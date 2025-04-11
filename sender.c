#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define SHM_SIZE 27  // Define shared memory size

int main() {
    char c;
    int shmid;
    key_t key;
    char *shm, *s;

    key = 5678;

    // Get shared memory segment
    if ((shmid = shmget(key, SHM_SIZE, IPC_CREAT | 0666)) < 0) {
        perror("shmget");
        exit(1);
    }

    // Attach shared memory
    if ((shm = shmat(shmid, NULL, 0)) == (char *)-1) {
        perror("shmat");
        exit(1);
    }

    s = shm;

    // Write lowercase letters a-z to shared memory
    for (c = 'a'; c <= 'z'; c++) {
        *s++ = c;
    }
    *s = '\0';  // Null terminate the string

    // Wait until another process sets *shm to '*'
    while (*shm != '*') {
        sleep(1);
    }

    // Detach shared memory
    shmdt(shm);

    exit(0);
}
















