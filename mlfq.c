#include <stdio.h>

struct Process {
    int at, bt, ft, tt, rt, status;
} process_queue[10];

int current_time = 0;
int tq[] = {2, 4}; // Time quantum for Queue 1 and Queue 2
int n;

// Function to simulate MLFQ scheduling
void dispatch() {
    int i, j;

    // Loop through each queue (0 = Highest Priority, 1 = Medium, 2 = Lowest)
    for (i = 0; i <= 2; i++) {
        for (j = 0; j < n; j++) {
            if (process_queue[j].status != 1) { // If process is not completed
                if (i != 2) { // Queue 1 & 2 use time slicing
                    if (process_queue[j].rt > tq[i]) {
                        process_queue[j].rt -= tq[i]; // Reduce remaining time
                        current_time += tq[i];       // Increase system time
                    } else { // Process finishes within time quantum
                        current_time += process_queue[j].rt;
                        process_queue[j].rt = 0;
                        process_queue[j].status = 1;
                        process_queue[j].ft = current_time;
                        process_queue[j].tt = process_queue[j].ft - process_queue[j].at;
                    }
                } else { // Queue 3 (Runs Until Completion)
                    current_time += process_queue[j].rt;
                    process_queue[j].rt = 0;
                    process_queue[j].status = 1;
                    process_queue[j].ft = current_time;
                    process_queue[j].tt = process_queue[j].ft - process_queue[j].at;
                }
            }
        }
    }
}

int main() {
    int i;
    
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    
    for (i = 0; i < n; i++) {
        printf("Process %d\n", i + 1);
        printf("Enter Burst Time: ");
        scanf("%d", &process_queue[i].bt);
        
        process_queue[i].at = 0;  // Assuming all arrive at time 0
        process_queue[i].tt = 0;
        process_queue[i].ft = 0;
        process_queue[i].rt = process_queue[i].bt; // Remaining time = Burst time initially
        process_queue[i].status = 0; // Not completed
    }

    dispatch();

    printf("\nPID\tFinish Time\tTurnaround Time\n");
    for (i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\n", i + 1, process_queue[i].ft, process_queue[i].tt);
    }

    return 0;
}