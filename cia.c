#include<stdio.h>
#include<unistd.h>

int main(){
    printf("Parent process pid:%d,ppid:%d",getpid(),getppid());
    int pid;
    pid= fork();
    if(pid!=0){
        printf("Parent process pid:%d,ppid:%d",getpid(),getppid());
        printf("child process pid:%d",pid);

    }

    else if(pid==0){
        printf("child process pid:%d,ppid:%d",getpid(),getppid());

    }
    else{
        printf("fork failed");
    }
}