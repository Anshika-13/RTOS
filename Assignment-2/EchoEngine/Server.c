// Server side C/C++ program to demonstrate Socket programming 
#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#define PORT 8000
int main(int argc, char const *argv[]) 
{ 
	int server_fd, new_socket, valread; 
	struct sockaddr_in address; 
	int opt = 1; 
	int addrlen = sizeof(address); 
	char buffer[1024] = {0}; 
	// char *buffer = "Hello from server";
	char *hello; 
	
	// Creating socket file descriptor 
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
	{ 
		perror("socket failed"); 
		exit(EXIT_FAILURE); 
	} 
	
	// Forcefully attaching socket to the port 8080 
	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, 
												&opt, sizeof(opt))) 
	{ 
		perror("setsockopt"); 
		exit(EXIT_FAILURE); 
	} 
	address.sin_family = AF_INET; 
	address.sin_addr.s_addr = INADDR_ANY; 
	address.sin_port = htons( PORT ); 
	
	// Forcefully attaching socket to the port 8080 
	if (bind(server_fd, (struct sockaddr *)&address, 
								sizeof(address))<0) 
	{ 
		perror("bind failed"); 
		exit(EXIT_FAILURE); 
	} 
	if (listen(server_fd, 13) < 0) 
	{ 
		perror("listen"); 
		exit(EXIT_FAILURE); 
	} 
	if ((new_socket = accept(server_fd, (struct sockaddr *)&address, 
					(socklen_t*)&addrlen))<0) 
	{ 
		perror("accept"); 
		exit(EXIT_FAILURE); 
	}
	// printf("stuff\n");

	if (fork() ==0) {
		while (1) {
			valread = read( new_socket , buffer, 1024); 
			// printf("%d\n",valread );  //0
		        // display the message 
			printf("Character Received is : %s", buffer);
			if (*(buffer) >= 65 && *(buffer) <=90) {
		        printf("U\n");
		        *(buffer) = *(buffer) + 32;
		    }
		    else if (*(buffer) >= 97 && *(buffer) <= 122) {
		        printf("L\n");
		            // *(mq2.mesg_text) = tolower( *(mq1.mesg_text) );
		        *(buffer) = *(buffer) - 32;
		    }
		    else {
		        *(buffer) = *(buffer) ;
		    }
		       
			printf("Character sent is : %s \n\n", buffer);
			send(new_socket , buffer , strlen(buffer) , 0 ); 
			// printf("Hello message sent\n"); 
		}
	}


	close(server_fd);
	return 0; 
} 
