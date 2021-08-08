/* message queue in version parent-child */
#ifdef __linux
char os[50] = "Apollo 13 successfully landed on the moon";
#else
char os[50] = "Houston, we have a problem";
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>

#define BUFSIZE 49

// message queue structure
// msgbuf definition is located in sys/msg.h
    struct msgbuf {
    long msg_type;
    char msg_text[50];
    } message;

int main() {
key_t key;
int msgid;
char buf[BUFSIZ];

//key=1234;
key=ftok("kolejkiKomunikatow.c",2020);

    // msgget creates message queue and returns it ID
    msgid = msgget(key, 0666 | IPC_CREAT);
    message.msg_type = 1;
    
int pid = fork();
if (pid == 0) { /* child process */
/* message to queue is sent */
    strcpy(message.msg_text,os);
    msgsnd(msgid, &message, sizeof(message), 0);
    
system("ipcs -q | head -3");
sprintf(buf, "ipcs -q | grep %d", msgid);
system(buf);
} 
else { /* parent process */
sleep(3);
/* message is read (using msgrcv) */
    msgrcv(msgid, &message, sizeof(message), 1, 0);
    
    printf("\033[1;31m"); /*message is printed in red*/
    printf("\033[1;31m"); /*message is printed in red*/
    printf("Data Received is : %s\n", message.msg_text);
    printf("\033[0m"); /*reverse to classic colors*/
    
printf("\033[0m"); /*reverse to classic colors*/

// message queue is destroyed
    msgctl(msgid, IPC_RMID, NULL);
}
return 0;
}