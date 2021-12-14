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
#include <sstream>
#include <vector>
#include <iterator>
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

//Part of parsing code from Evan Teran
template <typename Out>
void split(const std::string &s, char delim, Out result) {
    std::istringstream iss(s);
    std::string item;
    while (std::getline(iss, item, delim)) {
        *result++ = item;
    }
}

std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, std::back_inserter(elems));
    return elems;
}


int main(int argc, char* argv[]) {
// ifstream inFile;
// inFile.open("send_config.txt");

// int n1, idType, QUEUE_LENGTH, DEFAULT_TTL_VALUE;
// inFile >> idType >> QUEUE_LENGTH >> DEFAULT_TTL_VALUE;
//     // successfully extracted one line, data is in x1, ..., x4, c.  
//     printf("idType: %d", idType);
//     printf("queue length: %d", QUEUE_LENGTH);
//     printf("DEFAULT_TTL_VALUE: %d", DEFAULT_TTL_VALUE);


// int n2, idTypeLine2, ROUTER_ID;
// char* REAL_NETWORK_IP;

// inFile >> idTypeLine2 >> ROUTER_ID >> REAL_NETWORK_IP;
//     printf("idTypeLine2: %d", idTypeLine2);
//     printf("ROUTER_ID: %d", ROUTER_ID);
//     printf(REAL_NETWORK_IP);
std::vector<std::string> globalConfigOptions;
std::vector<std::string> router1;
std::vector<std::string> router2;
std::vector<std::string> router3;
std::vector<std::string> host1;
std::vector<std::string> host2;
std::vector<std::string> host3;
std::vector<std::string> link11;
std::vector<std::string> link12;
std::vector<std::string> link13;
std::vector<std::string> link21;
std::vector<std::string> link22;
std::vector<std::string> link23;

ifstream file("config.txt");
if (file.is_open())
{
	string line;
    int counter = 0;
	while (getline(file, line))
    {
    	// note that the newline character is not included
        // in the getline() function
        if(counter==0){
            globalConfigOptions = split(line, ' ');
            printf("line 1: ");
        }
        if(counter==1){
            router1 = split(line, ' ');
            printf("line 2: ");
        }
        if(counter==2){
            router2 = split(line, ' ');
            printf("line 3: ");
        }
        if(counter==3){
            router3 = split(line, ' ');
            printf("line 4: ");
        }
        if(counter==4){
            host1 = split(line, ' ');
            printf("line 5: ");
        }
        if(counter==5){
            host2 = split(line, ' ');
            printf("line 6: ");
        }
        if(counter==6){
            host3 = split(line, ' ');
            printf("line 7: ");
        }
        if(counter==7){
            link11 = split(line, ' ');
            printf("line 8: ");
        }
        if(counter==8){
            link12 = split(line, ' ');
            printf("line 9: ");
        }
        if(counter==9){
            link13 = split(line, ' ');
            printf("line 10: ");
        }
        if(counter==10){
            link21 = split(line, ' ');
            printf("line 11: ");
        }
        if(counter==11){
            link22 = split(line, ' ');
            printf("line 12: ");
        }
        if(counter==12){
            link23 = split(line, ' ');
            printf("line 13: ");
        }         
    	cout << line << endl;
        counter++;
    }
}
std::cout << "hi just test: "<<globalConfigOptions[1];
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
    string dataToBeSent;
    char buffer[1000];
    fstream newfile;
    
    //part 2 of roadmap generating random packet for transmission
    struct ip *bob = (struct ip *)buffer;
    struct udphdr *sally = (struct udphdr *)(buffer+20);
    char* data = (buffer + 28);

    in_addr myaddress2 = {.s_addr = inet_addr("10.0.2.104")};
    bob->ip_dst = myaddress2;
    sally->uh_sport = ntohs(5950);  

    newfile.open("send_body.txt",ios::in);
   if (newfile.is_open()){
      string tp;
      while(getline(newfile, tp)){
         cout << "<--->" << tp << "<--->\n";
         dataToBeSent = tp;
      }
      newfile.close();
   }
   fprintf(stdout, "The size of our file is: %d \n", fileSize("send_body.txt"));

    strncpy(data, dataToBeSent.c_str(), dataToBeSent.size());
    //reading send_body

    

    
    
    
    int sockfd;
    struct sockaddr_in servaddr;
    // char buffer[MAXLINE];
    // char *hello = "Hello World";
    // struct sockaddr_in     servaddr;
   
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
  
    sendto(sockfd, (const char *)data, strlen(data),
        MSG_CONFIRM, (const struct sockaddr *) &servaddr, 
            sizeof(servaddr));
    printf("Hello message sent.\n");
           
    n = recvfrom(sockfd, (char *)buffer, MAXLINE, 
                MSG_WAITALL, (struct sockaddr *) &servaddr,
                fromlen2);
    

    printf("Server : %s\n", buffer);
   
    close(sockfd);
    }   
    return 0;
}