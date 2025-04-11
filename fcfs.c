#include<stdio.h>
#include<stdlib.h>

struct process{
    int at,bt,ft,wt,status,tt;
} ready[10];

int n, cur_time=0,idle_time =0;

int dispatcher(){
    int i, index =-1;
    printf("Cur_time:%d\n",cur_time);
    back:
    for(i=0;i<n;i++){
        if(ready[i].status!=1){
            if(ready[i].at<=cur_time){
                index = i ;
                break;
            }
        }
    }
    if(index ==-1){
        cur_time++;
        idle_time++;
        goto back;
    }
    printf("Index:%d\n",index);
    return index;
}

int main(){
    int i;
    printf("Enter the no. of process:");
    scanf("%d",&n);

    for(i=0;i<n;i++){
        printf("Enter the arrival time of process %d:",i);
        scanf("%d",&ready[i].at);
        printf("Enter the burst time of process %d:",i);
        scanf("%d",&ready[i].bt);
        ready[i].status=0;
    }

    i=0;
    int pid;
    while(i<n){
        pid = dispatcher();
        ready[pid].ft = cur_time + ready[pid].bt;
        ready[pid].status =1 ;
        ready[pid].tt = ready[pid].ft - ready[pid].at;
        ready[pid].wt = ready[pid].tt - ready[pid].bt;
        cur_time = ready[pid].ft;
        i++;
    }

    printf("PID\tFT\tTT\tWT\n");
    printf("********************\n");
    for(i=0;i<n;i++){
        printf("%d\t%d\t%d\t%d\n",i,ready[i].ft,ready[i].tt,ready[i].wt);
    }

    return 0;
}

/*#include<stdio.h>
#include<stdlib.h>

struct process{
    int at,bt,tt,wt,status,ft;
}r[10];

int n, cur_time =0, idle_time=0;

int dispatcher(){
    int i, index=-1;
    printf("the cur_time time:%d",cur_time);
    back:
    for(i=0;i<n;i++){
        if(r[i].status!=1){
            if(r[i].at<= cur_time){
                index=i;
                break;
            }
        }
    }
    if(index==-1){
        cur_time++;
        idle_time++;
        goto back;
    }
    printf("the index is :%d",index);
    return index;
}

int main(){
    int i;
    printf("enter no. of processes:");
    scanf("%d",&n);

    for(i=0;i<n;i++){
        printf("enter the arrival time of process %d:",i);
        scanf("%d",&r[i].at);
        printf("enter the burst time of process %d:",i);
        scanf("%d",&r[i].bt);
        r[i].status =0;

    }
    i=0;
    int pid;
    while(i<n){
        pid = dispatcher();
        r[pid].ft = cur_time + r[pid].bt;
        r[pid].tt = r[pid].ft - r[i].at;
        r[pid].wt = r[pid].tt - r[pid].bt; 
        r[pid].status =1 ;
        cur_time = r[pid].ft;
        i++;

    }

    printf("PID\tFT\tTT\tWT\n");
    printf("***********************\n");
    for(i=0;i<n;i++){
        printf("%d\t%d\t%d\t%d\n",i,r[i].ft,r[i].tt,r[i].wt);
    }
    return 0;

}*/


