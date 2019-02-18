#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
   
// structure for message queue 
struct mesg_buffer { 
    long mesg_type; 
    char mesg_text[100];
    int cl; 
} message, message2; 
  
int main() 
{ 
    int msgid, msgid2, msgid3, msgid4, msgid5, msgid6;  
  
    // msgget creates a message queue and returns identifier 
    msgid = msgget(1000, 0666 | IPC_CREAT); //server will use this to receive
    msgid2 = msgget(1011, 0666 | IPC_CREAT); //client will use this to receive
    msgid3 = msgget(1012, 0666 | IPC_CREAT); //client will use this to receive
    msgid4 = msgget(1013, 0666 | IPC_CREAT); //client will use this to receive
    msgid5 = msgget(1014, 0666 | IPC_CREAT); //client will use this to receive
    msgid6 = msgget(1015, 0666 | IPC_CREAT); //client will use this to receive
    message2.mesg_type = 1; 

    while (1) {
        // msgrcv to receive message 
        msgrcv(msgid, &message, sizeof(message), 1, 0);
        // display the message 
        printf("Character Received is : %s", message.mesg_text);

        if (*(message.mesg_text) >= 65 && *(message.mesg_text) <=90) {
            printf("U\n");
            *(message2.mesg_text) = *(message.mesg_text) + 32;
        }
        else if (*(message.mesg_text) >= 97 && *(message.mesg_text) <= 122) {
            printf("L\n");
                // *(mq2.mesg_text) = tolower( *(mq1.mesg_text) );
            *(message2.mesg_text) = *(message.mesg_text) - 32;
        }
        else {
            *(message2.mesg_text) = *(message.mesg_text) ;
        }
       
        printf("Character sent is : %s \n\n", message2.mesg_text); 
      
      
        if (message.cl == 1) {
            printf("cl= %d\n", message.cl);
            msgsnd(msgid2, &message2, sizeof(message2), 0); 
        }
        else if (message.cl == 2) {
            printf("cl= %d\n", message.cl);
            msgsnd(msgid3, &message2, sizeof(message2), 0);
        }
        else if (message.cl == 3) {
            printf("cl= %d\n", message.cl);
            msgsnd(msgid4, &message2, sizeof(message2), 0);
        }
        else if (message.cl == 4) {
            printf("cl= %d\n", message.cl);
            msgsnd(msgid5, &message2, sizeof(message2), 0);
        }
        else if (message.cl == 5) {
            printf("cl= %d\n", message.cl);
            msgsnd(msgid6, &message2, sizeof(message2), 0);
        }

        //emptying the character buffers
        memset(message.mesg_text, 0, sizeof(message.mesg_text));
        memset(message2.mesg_text, 0, sizeof(message2.mesg_text));
    }
} 




//ipcs -q
//ipcrm -a