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

int main(int argc, char *argv[]) {
    //if statement to cal client or server function
    int sock = create_cs3516_socket();
    char buffer[40];
    struct ip *bob = (struct ip *)buffer;
    struct udphdr *sally = (struct udphdr *)(buffer+20);
    char* data = (buffer + 28);

    printf("Hi I am this socket, %d", sock);	
    
    //5 is next_hop
    cs3516_send(sock, buffer, 40, 5);

    //router
    while(1){
    char dest_buffer[3000];

    int actual = cs3516_recv(sock, dest_buffer, 3000);
    struct ip *bob = (struct ip *)dest_buffer;
    struct udphdr *sally = (struct udphdr *)(dest_buffer+20);
    char* data = (dest_buffer + 28);

    //dont change addresses in Bob
    bob->ip_ttl--;
    if (bob->ip_ttl < 1){continue;}
    //where 5 is a real address
    in_addr myaddress = {.s_addr = inet_addr("10.0.0.1")};
    if(bob->ip_dst.s_addr == myaddress.s_addr){
        // then send to host X
        cs3516_send(sock, dest_buffer, 40, (unsigned long)inet_ntoa(bob->ip_dst));//[5's real IP]);
    }
        else{
            //send to host y
        }
}
	close(sock);
return 0;
}