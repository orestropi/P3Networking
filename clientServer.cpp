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
#include <iostream>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h> 
#include <netinet/ip.h>
#include <netinet/udp.h> 
#include <fstream>
#include <string>
using namespace std;
#define PORT     8080
#define MAXLINE 3000
   
// Driver code from https://www.geeksforgeeks.org/udp-server-client-implementation-c/

#include <sys/stat.h>

long fileSize(std::string filename)
{
    struct stat sB;
    int rC = stat(filename.c_str(), &sB);
    return rC == 0 ? sB.st_size : -1;
}

int main(int argc, char* argv[]) {
    std::ifstream infile("send_config.txt");

string n1, idType, QUEUE_LENGTH, DEFAULT_TTL_VALUE;

if (!(infile >> n1)) { /* error, could not read first line! Abort. */ }

while (infile >> idType >> QUEUE_LENGTH >> DEFAULT_TTL_VALUE)
{
    // successfully extracted one line, data is in x1, ..., x4, c.
}
    printf("idType: %s", idType);
    printf("queue length: %s", QUEUE_LENGTH);
    printf("DEFAULT_TTL_VALUE: %s", DEFAULT_TTL_VALUE);

int n2, idTypeLine2, ROUTER_ID;
char* REAL_NETWORK_IP;

if (!(infile >> n1 >> n2)) { /* error, could not read first line! Abort. */ }

while (infile >> idTypeLine2 >> ROUTER_ID >> REAL_NETWORK_IP)
{
    // successfully extracted one line, data is in x1, ..., x4, c.
}
    printf("ROUTER_ID: %d", ROUTER_ID);
    printf("REAL_NETWORK_IP: %d", REAL_NETWORK_IP);


    if(argc < 2){
    printf("server here\n");

    int sockfd;
    char dest_buffer[MAXLINE];
    char *hello = "Hello world";
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

    while(1){

    n = recvfrom(sockfd, (char *)dest_buffer, MAXLINE, 
                MSG_WAITALL, ( struct sockaddr *) &cliaddr,
                fromlen2);
    dest_buffer[n] = '\0';
    printf("Client : %s\n", dest_buffer);

    //part 2 of roadmap generating random packet for transmission
    struct ip *bob = (struct ip *)dest_buffer;
    struct udphdr *sally = (struct udphdr *)(dest_buffer+20);
    char* data = (dest_buffer + 28);

    in_addr myaddress2 = {.s_addr = inet_addr("10.0.2.104")};
    bob->ip_dst = myaddress2;
    sally->uh_sport = ntohs(5950);
    strncpy(data,"hello world", 12);

    

    //part 4 of roadmap incrementing ttl and logging it
    bob->ip_ttl--;
    if (bob->ip_ttl < 1){continue;}
    printf("ttl incremented.\n"); 


    sendto(sockfd, (const char *)hello, strlen(hello), 
        MSG_CONFIRM, (const struct sockaddr *) &cliaddr,
            len);
    printf("Hello message sent.\n"); }}




    else{
    printf("client here\n");

    //reading send_body
    fstream newfile;
    
       newfile.open("send_body.txt",ios::in); //open a file to perform read operation using file object
   if (newfile.is_open()){ //checking whether the file is open
      string tp;
      while(getline(newfile, tp)){ //read data from file object and put it into string.
         cout << "<--->" << tp << "<--->\n"; //print the data of the string, we can store this later
      }
      newfile.close(); //close the file object.
   }
   fprintf(stdout, "The size of our file is: %d \n", fileSize("send_body.txt"));
    
    
    
    int sockfd;
    char buffer[MAXLINE];
    char *hello = "Hello World";
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

    //part 2 of roadmap generating random packet for transmission
    struct ip *bob = (struct ip *)buffer;
    struct udphdr *sally = (struct udphdr *)(buffer+20);
    char* data = (buffer + 28);

    in_addr myaddress2 = {.s_addr = inet_addr("10.0.2.104")};
    bob->ip_dst = myaddress2;
    sally->uh_sport = ntohs(5950);
    strncpy(data,"hello world", 12);

    printf("Server : %s\n", buffer);
   
    close(sockfd);
    }   
    return 0;
}