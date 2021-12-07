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
    int sock = 3;
    char * helloWorld = "Hello world!";

printf("hi, %d", sock);	
    unsigned long hi = 0;
int len = cs3516_send(sock, (char *)helloWorld, strlen(helloWorld),
		hi);
	if(len ==-1)
	{
		perror("failed to send");
	}
	close(sock);

return 0;
}