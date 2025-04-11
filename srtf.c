#include<stdio.h>
#include<stdlib.h>

int n, cur_time = 0, idle_time = 0;

struct process {
    int at, bt, ft, wt, tt, rt, status;
} r[10];

int dispatcher() {
    int i, index = -1, shortbt = 9999;
    for (i = 0; i < n; i++) {
        if (r[i].status != 1 && r[i].at <= cur_time && r[i].rt < shortbt) {
            index = i;
            shortbt = r[i].rt;
        }
    }
    return index;
}

int main() {
    int i, pid, completed = 0;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        printf("Enter arrival time of process %d: ", i);
        scanf("%d", &r[i].at);
        printf("Enter burst time of process %d: ", i);
        scanf("%d", &r[i].bt);
        r[i].rt = r[i].bt;
        r[i].status = 0;
    }

    while (completed < n) {
        pid = dispatcher();
        if (pid == -1) {
            cur_time++;
            idle_time++;
            continue;
        }
        
        cur_time++;
        r[pid].rt--;
        
        if (r[pid].rt == 0) {
            r[pid].ft = cur_time;
            r[pid].tt = r[pid].ft - r[pid].at;
            r[pid].wt = r[pid].tt - r[pid].bt;
            r[pid].status = 1;
            completed++;
        }
    }

    printf("\nPID\tFT\tTT\tWT\n");
    printf("****************************\n");
    for (i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\n", i, r[i].ft, r[i].tt, r[i].wt);
    }
    
    return 0;
}

/* srtf*/
#include <stdio.h>

struct process {
    int pid;  // Process ID
    int at;   // Arrival Time
    int bt;   // Burst Time
    int rt;   // Remaining Time (for SRTF)
    int ft;   // Finish Time
    int tt;   // Turnaround Time (FT - AT)
    int wt;   // Waiting Time (TT - BT)
};

int main() {
    int n, i, j, time = 0, completed = 0;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct process p[n];
    for (i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter Arrival Time for Process %d: ", p[i].pid);
        scanf("%d", &p[i].at);
        printf("Enter Burst Time for Process %d: ", p[i].pid);
        scanf("%d", &p[i].bt);
        p[i].rt = p[i].bt;  // Set remaining time to burst time initially
        p[i].ft = p[i].tt = p[i].wt = 0;  // Initialize other times
    }

    while (completed < n) {
        int shortest = -1, min_rt = 10000;

        // Find process with shortest remaining time that has arrived
        for (i = 0; i < n; i++) {
            if (p[i].at <= time && p[i].rt > 0 && p[i].rt < min_rt) {
                min_rt = p[i].rt;
                shortest = i;
            }
        }

        if (shortest == -1) {
            // If no process is ready to run, increment time
            time++;
        } else {
            // Execute the process with shortest remaining time
            p[shortest].rt--;  // Decrease the remaining time by 1
            time++;  // Increment the time

            // If the process is completed
            if (p[shortest].rt == 0) {
                p[shortest].ft = time;  // Finish Time = current time
                p[shortest].tt = p[shortest].ft - p[shortest].at;  // Turnaround Time
                p[shortest].wt = p[shortest].tt - p[shortest].bt;  // Waiting Time
                completed++;  // Increment the completed processes count
            }
        }
    }

    // Output the results
    printf("\nPId\tAT\tBT\tFT\tTT\tWT\n");
    printf("**************\n");
    for (i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].at, p[i].bt, p[i].ft, p[i].tt, p[i].wt);
    }

    return 0;
}
