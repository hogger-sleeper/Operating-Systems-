#include<stdio.h>
#include<stdlib.h>

struct process{
    int at,bt,tt,ft,status,rt;
}r[10];

int t[]={2,3};
int cur_time =0;
int n;

int dispatcher(){
    int index =-1;
    int i ,j,k;

    for(i=0;i<=2;i++){
        for(j=0;j<n;j++){
            if(r[i].status!=1){
                if(i!=2){
                if(r[j].rt>t[i]){
                    
                    r[j].rt -= t[i];
                    cur_time +=t[i];
                    

                }
                else{
                    cur_time += r[j].rt;
                    r[j].rt  =0 ;
                    r[j].status =1;
                    r[j].ft = cur_time;
                    r[j].tt = r[j].ft - r[j].at;

                }

            }
            else{
                int shortbt =9999;
                
               
                    if(r[j].status!=1){
                        if(r[j].at<=cur_time){
                            if(r[j].bt< shortbt){
                                index =i;
                                shortbt = r[k].bt;
                            }
                        }
                    }
                
                if(index ==-1){
                    cur_time++;
                    

                }
                
               
        
            }

            }
            
        }
    }
    

}

int main(){
    int i;
    printf("enter the no. of processes");
    scanf("%d",&n);

    for(i=0;i<n;i++){
        printf("enter the burst time:");
        scanf("%d",&r[i].bt);
        r[i].at =0;
        r[i].status =0;
        r[i].tt=0;
        r[i].rt = r[i].bt;
    }

    dispatcher();
    printf("\nPID\tFinish Time\tTurnaround Time\n");
    for (i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\n", i + 1, r[i].ft, r[i].tt);
    }

    return 0;
    return 0;
}
