#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define SHM_SIZE 27  // Define shared memory size

int main() {
    int shmid;
    key_t key;
    char *shm, *s;

    key = 5678;

    // Get shared memory segment
    if ((shmid = shmget(key, SHM_SIZE, 0666)) < 0) {
        perror("shmget");
        exit(1);
    }

    // Attach shared memory
    if ((shm = shmat(shmid, NULL, 0)) == (char *)-1) {
        perror("shmat");
        exit(1);
    }

    // Read from shared memory and print
    for (s = shm; *s != '\0'; s++) {
        putchar(*s);
    }
    putchar('\n');

    // Indicate completion by writing '*' to shared memory
    *shm = '*';

    // Detach shared memory
    shmdt(shm);

    exit(0);
}
