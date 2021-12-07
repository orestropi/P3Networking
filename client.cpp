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
    char * helloWorld = "Hello world!";

printf("hi, %d", sock);	
    
int len = cs3516_send(sock, (char *)helloWorld, strlen(helloWorld),
		(in_addr_t) 0x00000000);
	if(len ==-1)
	{
		perror("failed to send");
	}
	close(sock);

return 0;
}