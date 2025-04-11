#include<stdio.h>
#include<unistd.h>
#include <stdlib.h> 

int main(){
    int p[2];
    int pid;
    char inbuf[10], outbuf[10];
    pipe(p);
    pid = fork();

    if(pid>0){
        printf("Parent process:%d",getpid());
        printf("type the message to be sent to child:");
        scanf("%s",outbuf);
        write(p[1],outbuf,sizeof(outbuf));
        //sleep(2);

    }
    else if (pid==0){
        printf("in child process");
        read(p[0],inbuf,sizeof(inbuf));
        printf("the data received is :%s",inbuf);
        //sleep(5);
    }
    else{
        perror("fork failes");
        exit(1);
    }
    return 0;
}