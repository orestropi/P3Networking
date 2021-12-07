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
    int sockN = create_cs3516_socket();
    char buffer[50] = {0};
printf("hi, %d", sockN);

	socklen_t len = 0;
	
    while(true){int n = cs3516_recv(sockN, (char *)buffer, 50);
	buffer[n] = '\n';
	printf("%s", buffer);}
	
	close(sockN);

return 0;
}