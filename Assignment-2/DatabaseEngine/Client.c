// Client side C/C++ program to demonstrate Socket programming 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h> 
#include <sys/time.h>
#define PORT 8000

int main(int argc, char const *argv[]) 
{ 
	struct sockaddr_in address; 
	int sock = 0, valread; 
	struct sockaddr_in serv_addr; 
	// char *hello = "Hello from client"; 
	char hello[100];
	char buffer[1024] = {0}; 
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
	{ 
		printf("\n Socket creation error \n"); 
		return -1; 
	} 

	memset(&serv_addr, '0', sizeof(serv_addr)); 

	serv_addr.sin_family = AF_INET; 
	serv_addr.sin_port = htons(PORT); 
	
	// Convert IPv4 and IPv6 addresses from text to binary form 
	if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0) 
	{ 
		printf("\nInvalid address/ Address not supported \n"); 
		return -1; 
	} 

	if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
	{ 
		printf("\nConnection Failed \n"); 
		return -1; 
	} 

	while (1) {
		printf("Give a character : "); 
		// fgets(hello, sizeof(hello), stdin);
		scanf(" %[^\n]",hello);
		long s=0, m=0;
	        
	    // for (int i = 0; i<n; i++) {
	        struct timeval end, start;

		    char get[5] = "GET ";
		    printf("stuff\n");
		    strcat(get, hello);
		    // char get[8] = "GET one";
		    // // strcpy(hello, get);
			printf("name: %s\n", get);
		    printf("Character given is : %s\n", get);

			send(sock , get , strlen(get) , 0 ); 
			// printf("%ld\n", send(sock , hello , strlen(hello) , 0 ));
		    printf("Character sent is : %s", get);
			// printf("Hello message sent\n"); 
			gettimeofday(&start, NULL); // Store time as soon as message sent
            valread = read( sock , buffer, 1024); 
            gettimeofday(&end, NULL); 
			// display the message 
		    // printf("\nCharacter sent is : %s", hello);
			printf("\nCharacter received: %s\n", buffer);
			// printf("%s\n",buffer ); 
			// close(sock);

			long seconds = (end.tv_sec - start.tv_sec); //time when output recieved
            long micros = ((seconds * 1000000) + end.tv_usec) - (start.tv_usec);
            printf("Time elpased is %lu seconds and %lu micros\n", end.tv_sec - start.tv_sec, micros);//final time

            s = s+ seconds;
            m = m+ micros;
		// }
	}

	return 0;
} 