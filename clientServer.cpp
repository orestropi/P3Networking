/*#include <sys/types.h>
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
#include <iostream>
#include <pcap.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netinet/if_ether.h>
#include <time.h>
#include <map>
#include <set>
#include <linux/if_ether.h>
#include <netinet/ether.h>
#include <netinet/ip.h>
#include <netinet/udp.h>
#include <arpa/inet.h>

int main(int argc, char** argv) {
    //if statement to cal client or server function
    
    if(argc == 0){
    printf("Hi I am this socket");	
    int sock = create_cs3516_socket(inet_addr("10.0.2.104"));
    char buffer[40];
    struct ip *bob = (struct ip *)buffer;
    struct udphdr *sally = (struct udphdr *)(buffer+20);
    char* data = (buffer + 28);
    strncpy(data,"hello world", 12);

    printf("Hi I am this socket, %d", sock);	
    
    //5 is next_hop
    cs3516_send(sock, buffer, 40, (unsigned long)("1.2.3.1"));//("10.0.2.104", "1.2.3.1"));
    }


    if(argc >= 1){
    //router
    int sock = create_cs3516_socket(inet_addr("10.0.2.105"));
    while(1){
    char dest_buffer[3000];

    int actual = cs3516_recv(sock, dest_buffer, 3000);
    struct ip *bob = (struct ip *)dest_buffer;
    struct udphdr *sally = (struct udphdr *)(dest_buffer+20);
    char* data = (dest_buffer + 28);

    in_addr myaddress2 = {.s_addr = inet_addr("10.0.2.104")};
    bob->ip_dst = myaddress2;
    sally->uh_sport = ntohs(5950);
    printf(data);
    strncpy(data,"hello world", 12);

    //dont change addresses in Bob
    bob->ip_ttl--;
    if (bob->ip_ttl < 1){continue;}
    //where 5 is a real address
    in_addr myaddress = {.s_addr = inet_addr("10.0.2.104")};
    if(bob->ip_dst.s_addr == myaddress.s_addr){
        // then send to host X
        cs3516_send(sock, dest_buffer, 40, (unsigned long)inet_ntoa(bob->ip_dst));//[5's real IP]);
    }
        else{
            //send to host y
        }	
        
        close(sock);
}
}
return 0;
}*/
// Server side implementation of UDP client-server model
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
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
#include <iostream>
#include <pcap.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netinet/if_ether.h>
#include <time.h>
#include <map>
#include <set>
#include <linux/if_ether.h>
#include <netinet/ether.h>
#include <netinet/ip.h>
#include <netinet/udp.h>
#include <arpa/inet.h>   
#define PORT     8080
#define MAXLINE 1024
   
// Driver code from https://www.geeksforgeeks.org/udp-server-client-implementation-c/

int main(int argc, char** argv) {
    
    if(argv[0] == "client"){
            printf("server here");

    int sockfd;
    char buffer[MAXLINE];
    char *hello = "Hello from server";
    struct sockaddr_in servaddr, cliaddr;
       
    // Creating socket file descriptor
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }
       
    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));
       
    // Filling server information
    servaddr.sin_family    = AF_INET; // IPv4
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);
       
    // Bind the socket with the server address
    if ( bind(sockfd, (const struct sockaddr *)&servaddr, 
            sizeof(servaddr)) < 0 )
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
       
    int len, n;
   
    len = sizeof(cliaddr);  //len is value/resuslt
    socklen_t * fromlen2 = (socklen_t*)sizeof(cliaddr);//added

    n = recvfrom(sockfd, (char *)buffer, MAXLINE, 
                MSG_WAITALL, ( struct sockaddr *) &cliaddr,
                fromlen2);
    buffer[n] = '\0';
    printf("Client : %s\n", buffer);
    sendto(sockfd, (const char *)hello, strlen(hello), 
        MSG_CONFIRM, (const struct sockaddr *) &cliaddr,
            len);
    printf("Hello message sent.\n"); }




    else{
    printf("client here");
        int sockfd;
    char buffer[MAXLINE];
    char *hello = "Hello from client";
    struct sockaddr_in     servaddr;
   
    // Creating socket file descriptor
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }
   
    memset(&servaddr, 0, sizeof(servaddr));
       
    // Filling server information
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = INADDR_ANY;
       
    int n, len;
    socklen_t * fromlen2;//added
  
    sendto(sockfd, (const char *)hello, strlen(hello),
        MSG_CONFIRM, (const struct sockaddr *) &servaddr, 
            sizeof(servaddr));
    printf("Hello message sent.\n");
           
    n = recvfrom(sockfd, (char *)buffer, MAXLINE, 
                MSG_WAITALL, (struct sockaddr *) &servaddr,
                fromlen2);
    buffer[n] = '\0';
    printf("Server : %s\n", buffer);
   
    close(sockfd);
    }   
    return 0;
}