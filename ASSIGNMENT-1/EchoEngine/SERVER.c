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
      
        msgid2 = message.cl; //client will use this to receive
        msgsnd(msgid2, &message2, sizeof(message2), 0);

        //emptying the character buffers
        memset(message.mesg_text, 0, sizeof(message.mesg_text));
        memset(message2.mesg_text, 0, sizeof(message2.mesg_text));
    }
} 




//ipcs -q
//ipcrm -a
