/*Program 6: Create two child processes and communicate between parent and children
using pipe*/

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

int main(){
    int pid1,pid2;
    int outbuf[10],inbuf[10];
    int p[2];
    pipe(p);

    pid1 = fork();
    if(pid1!=0){
        pid2=fork();
        if(pid2!=0){
                printf("in parent");
               
                read(p[0],inbuf,sizeof(inbuf));
                printf("msg:%s",inbuf);

        }
        else{
                printf("child2");
                printf("enter msg");
                scanf("%d",outbuf);
                write(p[1],outbuf,sizeof(outbuf));
                

        }
    }

    

    else{
        printf("child2");
        printf("enter msg");
        scanf("%d",outbuf);
        write(p[1],outbuf,sizeof(outbuf));

    }
    
}