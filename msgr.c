#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/msg.h>
#include<unistd.h>
#include<string.h>
#define max 10

struct message{
    long mesg_type;
    char mesg_text[10];
}message;

int main(){
    int msgid,type;
    key_t key;
    char choice[10];

    key = ftok("progfile",65);
    msgid = msgget(key,0666|IPC_CREAT);
    printf("read message\n");
    do{
        printf("enter the message type:");
        scanf("%d",&type);
        msgrcv(msgid,&message,sizeof(message.mesg_text),type,0);
        printf("The message is :%s\n",message.mesg_text);
        printf("do you want to continue:");
        scanf("%s",&choice);



    }while(strcmp(choice,"no")!=0);
    return 0;
    
}

