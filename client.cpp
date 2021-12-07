#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <arpa/inet.h> 
#include <string.h>
#include "cs3516sock.hpp"

int main(int argc, char *argv[]) {
    //if statement to cal client or server function
    int sock = create_cs3516_socket();
    char * helloWorld = "Hello world!";
    int sock = create_cs3516_socket();

printf("hi, %d", sock);

	socklen_t len = 0;
	
    
int len = sendto(sock, (const char *)helloWorld, strlen(helloWorld),
		0, (const struct sockaddr *)&sock, sizeof(sock));
	if(len ==-1)
	{
		perror("failed to send");
	}
	close(sock);

return 0;
}