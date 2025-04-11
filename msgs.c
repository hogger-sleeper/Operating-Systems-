#include<sys/ipc.h>
#include<sys/msg.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>

#define max 10

struct mesg_buffer{
    long mesg_type;
    char mesg_text[100];
}message;

int main(){
    key_t key;
    int msgid;

    key = ftok("progfile",65);
    msgid = msgget(key,0666|IPC_CREAT);
   
    do{
        printf("enter the msg type:\n");
        scanf("%ld",&message.mesg_type);
        msgsnd(msgid,&message,sizeof(message.mesg_text),0);
        printf("Enter the message:\n");
        scanf("%s",message.mesg_text);

    }while(strcmp(message.mesg_text,"end")!=0);
    return 0;


}