#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include "cs3516sock.hpp"

int main(int argc, char *argv[]) {
    //if statement to cal client or server function
    int sockfd = create_cs3516_socket();
    char buffer[50] = {0};
printf("hi, %d", sockfd);

	socklen_t len = 0;
	
    
	int n = recvfrom(sockfd, (char *)buffer, 50, MSG_WAITALL,
		0, &len);
	buffer[n] = '\n';
	printf("%s", buffer);
	close(sockfd);

return 0;
}