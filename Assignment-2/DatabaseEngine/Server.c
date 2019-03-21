// Server side C/C++ program to demonstrate Socket programming 
#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#define PORT 6000
int main(int argc, char const *argv[]) 
{ 
	int server_fd, new_socket, valread; 
	struct sockaddr_in address; 
	int opt = 1; 
	int addrlen = sizeof(address); 
	// char buffer[1024] = {0}; 
	// char *buffer = "Hello from server";
	char *hello; 
	char content[100];
	
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


	while(1) {
		if ((new_socket = accept(server_fd, (struct sockaddr *)&address, 
						(socklen_t*)&addrlen))>=0) 
		{ 
			// 	perror("accept"); 
			// 	exit(EXIT_FAILURE); 
			// }
			// // printf("stuff\n");

			if (fork() ==0) {
				while (1) {
					char buffer[1024] = {0}; 
					valread = read( new_socket , buffer, 1024); 
					// printf("%d\n",valread );  //0
				        // display the message 
					printf("Text Received is : %s\n", buffer);
					char *name = buffer +4;
					printf("Name of file: %s\n", name);
				    int fd = open(name, O_RDONLY);

				    if (fd==-1) {
				    	printf("File not found\n");
						strcat(buffer,"Data not found.");
				    }
				    else { 
				    	read (fd, &content, 100);
				    	strcpy(buffer, content);
						printf("File content sent : %s \n", buffer); 
					       
						// printf("Character sent is : %s \n\n", buffer);
						// send(new_socket , buffer , strlen(buffer) , 0 );
						send(new_socket , buffer , 6 , 0 );
				    	// close(fd);
				    }

					// printf("File content sent : %s \n", buffer); 
				       
					// // printf("Character sent is : %s \n\n", buffer);
					// send(new_socket , buffer , strlen(buffer) , 0 ); 
					// printf("Hello message sent\n"); 
				}
			}
		}
	}


	// close(server_fd);
	return 0; 
} 
