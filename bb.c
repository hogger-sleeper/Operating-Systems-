#include <stdio.h>
#define MAX_PROCESS 4
#define MAX_RES 3

int max[MAX_PROCESS][MAX_RES];
int need[MAX_PROCESS][MAX_RES];
int allocation[MAX_PROCESS][MAX_RES];
int RESOURCE[MAX_RES];
int available[MAX_RES];
int FINISHED[MAX_PROCESS] = {0};

int canAllallocate(int process)
{
    for (int i = 0; i < MAX_RES; i++)
    {
        if (need[process][i] > available[i])
        {
            return 0;
        }
    }
    return 1;
}

void safesequence()
{
    int safeseq[MAX_PROCESS];
    int count = 0;
    int finished_copy[MAX_PROCESS];
    for (int i = 0; i < MAX_PROCESS; i++)
        finished_copy[i] = FINISHED[i]; // Keep original FINISHED state

    while (count < MAX_PROCESS)
    {
        int found = 0;
        for (int i = 0; i < MAX_PROCESS; i++)
        {
            if (!FINISHED[i] && canAllallocate(i))
            {
                for (int j = 0; j < MAX_RES; j++)
                {
                    available[j] += allocation[i][j];
                }
                safeseq[count++] = i;
                FINISHED[i] = 1;
                found = 1;
            }
        }
        if (!found)
        {
            printf("It's leading to unsafe state.\n");
            for (int i = 0; i < MAX_PROCESS; i++)
                FINISHED[i] = finished_copy[i]; // Rollback
            return;
        }
    }
    printf("Safe sequence is: ");
    for (int i = 0; i < MAX_PROCESS; i++)
    {
        printf("P%d\t", safeseq[i]);
    }
    printf("\n");
}

int main()
{
    int sum = 0;
    int i, j;

    printf("Enter the claim matrix:\n");
    for (i = 0; i < MAX_PROCESS; i++)
    {
        for (j = 0; j < MAX_RES; j++)
        {
            scanf("%d", &max[i][j]);
        }
    }

    printf("Enter the allocation matrix:\n");
    for (i = 0; i < MAX_PROCESS; i++)
    {
        for (j = 0; j < MAX_RES; j++)
        {
            scanf("%d", &allocation[i][j]);
        }
    }

    printf("The need matrix calculation:\n");
    for (i = 0; i < MAX_PROCESS; i++)
    {
        for (j = 0; j < MAX_RES; j++)
        {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    printf("The need matrix is:\n");
    for (i = 0; i < MAX_PROCESS; i++)
    {
        for (j = 0; j < MAX_RES; j++)
        {
            printf("\t%d\t", need[i][j]);
        }
        printf("\n\n");
    }

    printf("Enter the resource vector:\n");
    for (int i = 0; i < MAX_RES; i++)
    {
        scanf("%d", &RESOURCE[i]);
    }

    printf("The available vector calculation:\n");
    for (int i = 0; i < MAX_RES; i++)
    {
        sum = 0;
        for (int j = 0; j < MAX_PROCESS; j++)
        {
            sum += allocation[j][i];
        }
        available[i] = RESOURCE[i] - sum;
        printf("Resource %d: %d\n", i, available[i]);
    }

    // ADDITION: Handle dynamic resource request
    int req_process;
    int request[MAX_RES];

    printf("\nEnter the process number making the request (0 to %d): ", MAX_PROCESS - 1);
    scanf("%d", &req_process);

    printf("Enter the additional resource request (R1 R2 R3): ");
    for (int i = 0; i < MAX_RES; i++)
    {
        scanf("%d", &request[i]);
    }

    // Check if request is valid
    int valid = 1;
    for (int i = 0; i < MAX_RES; i++)
    {
        if (request[i] > need[req_process][i])
        {
            valid = 0;
            printf("Error: Process has exceeded its maximum claim.\n");
            break;
        }
        if (request[i] > available[i])
        {
            valid = 0;
            printf("Resources are not available. Process must wait.\n");
            break;
        }
    }

    if (valid)
    {
        // Temporarily allocate
        for (int i = 0; i < MAX_RES; i++)
        {
            available[i] -= request[i];
            allocation[req_process][i] += request[i];
            need[req_process][i] -= request[i];
        }

        printf("\nChecking system state after resource request...\n");
        safesequence(); // Check system safety

        // Rollback (optional: only if not safe, here we leave it as-is)
    }

    return 0;
}