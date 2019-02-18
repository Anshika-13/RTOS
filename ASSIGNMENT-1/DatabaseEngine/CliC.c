#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
  
// structure for message queue 
struct mesg_buffer { 
    long mesg_type; 
    char mesg_text[100]; 
    int cl;
} message, message2; 
  
int main() { 
    int msgid, msgid2; 
    char name[100];
    int n=10;

    // msgget creates a message queue and returns identifier 
    msgid = msgget(1000, 0666 | IPC_CREAT); //client A will use this to send
    msgid2 = msgget(1003, 0666 | IPC_CREAT); //server will use this to send
    message.mesg_type = 1;
    message.cl = msgid2;

    while (1) {
        printf("Client: %d\n", message.cl);
        printf("Give file name: %s", name);
        scanf(" %[^\n]",name);

        char get[5] = "GET ";
        strcat(get, name);
        // char get[10] = "GET three";
        strcpy(message.mesg_text, get);
        printf("name: %s\n", get);
        long s=0, m=0;

        // for (int i = 0; i<n; i++) {
            struct timeval end, start;
            // msgsnd to send message 
            msgsnd(msgid, &message, sizeof(message), 0); 
          
            gettimeofday(&start, NULL); // Store time as soon as message sent
            msgrcv(msgid2, &message2, sizeof(message2), 1, 0);
            gettimeofday(&end, NULL);

            // display the message 
            printf("Message sent is : %s \n", message.mesg_text); 
            printf("Contents of file received: %s\n", message2.mesg_text);

            long seconds = (end.tv_sec - start.tv_sec); //time when output recieved
            long micros = ((seconds * 1000000) + end.tv_usec) - (start.tv_usec);
            printf("Time elpased is %lu seconds and %lu micros\n", end.tv_sec - start.tv_sec, micros);//final time

            s = s+ seconds;
        //     m = m+ micros;
        // }
        // printf("Total time C = %lu seconds and %lu micros\n", s, m);
        // printf("Average time C = %lu seconds and %lu micros\n", s/n, m/n);


        //emptying the character buffers
        memset(message.mesg_text, 0, sizeof(message.mesg_text));
        memset(message2.mesg_text, 0, sizeof(message2.mesg_text));
        memset(name, 0, sizeof(name));

    }

  
} 



//ipcs -q
//ipcrm -a
