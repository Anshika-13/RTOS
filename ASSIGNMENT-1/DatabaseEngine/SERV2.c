#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
  
// structure for message queue 
struct mesg_buffer { 
    long mesg_type; 
    char mesg_text[100]; 
    int cl;
} message, message2; 
  
int main() { 
    int msgid, msgid2; 
    char content[100];
  
    // msgget creates a message queue and returns identifier 
    msgid = msgget(1000, 0666 | IPC_CREAT); //server will use this to receive
    message2.mesg_type = 1; 

    while (1) {
	    // msgrcv to receive message 
	    msgrcv(msgid, &message, sizeof(message), 1, 0);
	    printf("Client: %d\n", message.cl);
	    printf("Message received: %s\n", message.mesg_text);

	    char* name = message.mesg_text+4;

	    printf("Name of file: %s\n", name);
	    int fd = open(name, O_RDONLY);

	    if (fd==-1) {
	    	printf("File not found\n");
			strcat(message2.mesg_text,"Data not found.");
	    }
	    else { 
	    	read (fd, &content, 100);
	    	strcpy(message2.mesg_text, content);
	    	close(fd);
	    }

	    printf("File content sent : %s \n", message2.mesg_text); 
 
	   
	    msgid2 = message.cl;
	    msgsnd(msgid2, &message2, sizeof(message2), 0); 

		//emptying the character buffers
		memset(message.mesg_text, 0, sizeof(message.mesg_text));
		memset(message2.mesg_text, 0, sizeof(message2.mesg_text));
	}
} 




//ipcs -q
//ipcrm -a