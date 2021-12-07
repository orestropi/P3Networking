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
    struct ip_hdr *bob = (struct ip_hdr *)buffer;
    struct upd_hdr *sally = (struct upd_hdr *)(buffer+20);
    char* data = (buffer + 28);

    printf("Hi I am this socket, %d", sock);	
    
cs3516_send(sock, buffer, 40, next_hop);

    //router
    while(1){
    char dest_buffer[3000];

    int actual = cs3516_recv(sock, dest_buffer, 3000);
    struct ip_hdr *bob = (struct ip_hdr *)dest_buffer;
    struct upd_hdr *sally = (struct upd_hdr *)(dest_buffer+20);
    char* data = (dest_buffer + 28);

    bob->ttl--:
    if (bob->ttl < 1){continue:}

    if(bob->ip_dst == 5){
        // then send to host X
        cs3516_send(sock, buffer, 40, next_hop);
    }
        else{}
}
	close(sock);
return 0;
}