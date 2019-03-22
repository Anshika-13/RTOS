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
#include <sys/time.h> 
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
					FILE *fp;
					struct timeval end, start;
					char temperature[5], humidity[5], gas1[5], gas2[5], gas3[5];
					char buffer[1024] = {0}; 
					// char content[100];

			    	gettimeofday(&start, NULL);
					valread = read( new_socket , buffer, 1024); 

					if (strcmp(buffer,"Fetch data from server/sensor")==0) {

			      		fp = fopen("sensor1.txt", "r");
			      		fscanf(fp, "%s", temperature);
			      		fclose(fp);
			     
			      		fp = fopen("sensor2.txt", "r");
			      		fscanf(fp, "%s", humidity);
			      		fclose(fp);
			      
			      		fp = fopen("sensor3.txt", "r");
			      		fscanf(fp, "%s", gas1);
			     		fclose(fp);
			      
			      		fp = fopen("sensor4.txt", "r");
			      		fscanf(fp, "%s", gas2);
			      		fclose(fp);
			      
			      		fp = fopen("sensor5.txt", "r");
			      		fscanf(fp, "%s", gas3);
			      		fclose(fp);

			      		// sprintf(buffer,"%lu, %s, %s, %s, %s, %s",start.tv_usec,temperature,humidity,gas1,gas2,gas3);
						sprintf(buffer, "%s, %s, %s, %s, %s",temperature,humidity,gas1,gas2,gas3);

			      		send(new_socket , buffer , strlen(buffer) , 0 );
				 		printf("\nData sent to client: %s", buffer);
			      	}
				}
			}
		}
	}


	// close(server_fd);
	return 0; 
} 
