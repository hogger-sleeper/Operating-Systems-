#include<stdio.h>
#include<stdlib.h>



struct process{
    int at,bt,tt,status,wt,ft;
}ready[10];

int n, t, com=0;
int dispatch(int cur_time){
    int i , index =-1,high_at =0,high_status=0;
    int m=n;
    for(i=0;i<n;i++){
        if(ready[i].at > high_at){
            high_at = ready[i].at;
        }
    } 
    for(i=0;i<n;i++){
        if(ready[i].status>high_status){
            high_status = ready[i].status;
        }
    }
    for(i=0;i<n;i++){
        if(ready[i].status!=2){
            if(ready[i].at<=cur_time){
                index =i;
                high_at = ready[i].at;
            }
            if(ready[i].at==high_at){
                if(ready[i].status<high_status){
                    index=i;
                    high_status = ready[i].status;
                }
                else if(ready[i].status == high_status){
                    if(i<m){
                        index = i;
                        m=i;
                    }
                }
            }
        }
    }
    return index;

}

int main(){
    int i;
    printf("ENTER THE NO. OF PROCESS");
    scanf("%d",&n);
    printf("ENTER TIME QUANTUM");
    scanf("%d",&t);

    for(i=0;i<n;i++){
        printf("ENTER THE ARRIVAL TIME:");
        scanf("%d",&ready[i].at);
        printf("ENTER THE BURST TIME:");
        scanf("%d",&ready[i].bt);
        ready[i].status=0;

    }

    int a[10],b[10];
    for(i=0;i<n;i++){
        a[i]= ready[i].at;
        b[i] = ready[i].bt;
    }

    int pid, cur_time =0;
    while(com<n){
        pid = dispatch(cur_time);
        if(ready[pid].bt<=t){
            cur_time +=ready[pid].bt;
            ready[pid].ft = cur_time; 
            ready[pid].status =2;
            com++;
        }
        else{
            cur_time +=t;
            ready[pid].at +=cur_time;
            ready[pid].bt = ready[pid].bt -t;
            ready[pid].status=1;
        }
    }
    printf("pid\tft\ttt\twt\n");
    for(i=0;i<n;i++){
        printf("%d\t%d\t%d\t%d\n",i,ready[i].ft,ready[i].ft -a[i],((ready[i].ft-a[i])-b[i]));
    }


getchar();    
}
