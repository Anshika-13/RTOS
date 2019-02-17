// C Program for Message Queue (Writer Process)
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <string.h> 
  
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
    key = ftok("progfile", 66); 
  
    // msgget creates a message queue 
    // and returns identifier 
    msgid = msgget(1000, 0666 | IPC_CREAT); 
    msgid2 = msgget(1001, 0666 | IPC_CREAT); 
    message.mesg_type = 1; 
  
    printf("Write Data : "); 
    fgets(message.mesg_text, sizeof(message.mesg_text), stdin);
  
    // msgsnd to send message 
    msgsnd(msgid, &message, sizeof(message), 0); 
  
    // display the message 
    printf("Data send is : %s \n", message.mesg_text); 
  

    msgrcv(msgid2, &message2, sizeof(message2), 1, 0);

    printf("Message received: %s\n", message2.mesg_text);
} 
