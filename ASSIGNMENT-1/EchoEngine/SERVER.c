
// C Program for Message Queue (Reader Process) 
#include <stdio.h> 
#include <sys/ipc.h> 
#include <sys/msg.h> 
  
// structure for message queue 
struct mesg_buffer { 
    long mesg_type; 
    char mesg_text[100]; 
} message, message2; 
  
int main() 
{ 
    key_t key; 
    int msgid, msgid2; 
  
    // ftok to generate unique key 
    key = ftok("progfile", 65); 
  
    // msgget creates a message queue 
    // and returns identifier 
    msgid = msgget(1000, 0666 | IPC_CREAT); 
    msgid2 = msgget(1001, 0666 | IPC_CREAT); 
    message2.mesg_type = 1; 
  
    // msgrcv to receive message 
    msgrcv(msgid, &message, sizeof(message), 1, 0);

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
  
    // display the message 
    printf("Data Received is : %s \n",  
                    message.mesg_text); 
    printf("Data sent is : %s \n",  
                    message2.mesg_text); 
  
    // to destroy the message queue 
    //msgctl(msgid, IPC_RMID, NULL); 
  
    msgsnd(msgid2, &message2, sizeof(message2), 0); 
} 
