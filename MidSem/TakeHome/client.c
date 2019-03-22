// Client side C/C++ program to demonstrate Socket programming 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h> 
#include <sys/time.h>
#define PORT 6000

int main(int argc, char const *argv[]) 
{ 
	struct sockaddr_in address; 
	int sock = 0, valread; 
	struct sockaddr_in serv_addr; 
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

	// int n = 10;

	FILE *fp = fopen ("csvfile.csv", "w");
	fprintf(fp,"TimeStamp, Temperature, Humidity,  Gas1,  Gas2,  Gas3\n");
	fclose(fp);
	printf("Start\n"); 


	while (1) {
		char *get = "Fetch data from server/sensor";
		sleep(2);
        struct timeval end, start;
		send(sock , get , strlen(get) , 0 ); 
		gettimeofday(&start, NULL); // Store time as soon as message sent

		char buffer[1024] = {0}; 
		char buff[1024] = {0}; 
        valread = read( sock , buffer, 1024); 
	   	fp = fopen("csvfile.csv","a");
		sprintf(buff,"%lu, %s",start.tv_sec,buffer);

	   	printf("Data received from server/sensor:%s\n",buff);
	   	fprintf(fp,"%s\n",buff);
	   	fclose(fp);


	}

	return 0;
} 
