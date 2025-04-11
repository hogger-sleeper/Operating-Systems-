#include<stdio.h>
#include<stdlib.h>

int n, idle_time =0,cur_time =0;



struct process{
    int at,bt,ft,wt,tt,status;
}r[10];

int dispatcher(){
    int i , index =-1 , shortbt = 9999;
    printf("cur_time :%d",cur_time);
    back:
    for(i=0;i<n;i++){
        if(r[i].status !=1){
            if(r[i].at<=cur_time){
                if(r[i].bt < shortbt){
                    index =i;
                    shortbt = r[i].bt;
                }
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
    int i,pid;
    printf("enter the no. of process:");
    scanf("%d",&n);

    for(i=0;i<n;i++){
        printf("enter the arrival time of process %d:",i);
        scanf("%d",&r[i].at);
        printf("enter the burst time of process %d:",i);
        scanf("%d",&r[i].bt);
        r[i].status =0;
    }
    i=0;
    while(i<n){
        pid = dispatcher();
        r[pid].ft = cur_time + r[pid].bt;
        r[pid].tt = r[pid].ft - r[pid].at;
        r[pid].status =1;
        r[pid].wt = r[pid].tt - r[pid].bt;
        cur_time = r[pid].ft;
        i++;
    }

    printf("PID\tFT\tTT\tWT\n");
    printf("***********************\n");
    for(i=0;i<n;i++){
        printf("%d\t%d\t%d\t%d\n",i,r[i].ft,r[i].tt,r[i].wt);
    }
    return 0;
}
