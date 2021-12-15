// Server side implementation of UDP client-server model
#include <iostream>
#include <filesystem>
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
#define MAXLINE 3000
int PORT = 8080;

// Driver code from https://www.geeksforgeeks.org/udp-server-client-implementation-c/

#include <sys/stat.h>

long fileSize(std::string filename)
{
    struct stat sB;
    int rC = stat(filename.c_str(), &sB);
    return rC == 0 ? sB.st_size : -1;
}

 struct node {
	struct in_addr nextHopIP;
	bool isSet;
	struct node *zeroChild;
	struct node *oneChild;
};

// func setTree(char* RealIP, char* voerlayIP, node* root, bool setValue)
// takes overlay IP and set's it's next hop as the real next IP addr
// applies changes to BST of root node, common across entire device.
// if setValue is true, changes value of dest IP address. if not, gets current value for IP address

struct in_addr setTree(char realIP[], char overlayIP[], node* root, bool SetValue){
    
    // string we'll fill with info
  char * pch;
    
  // strtok to get prefix / ip
  printf ("Splitting string \"%s\" into tokens:\n", overlayIP);
  
  // getting ip in 4dot notation
  pch = strtok (overlayIP,"/");
  printf ("Here's the IP addr: %s\n",pch);
  // set router to proper number / direction
  int n = ntohl(inet_addr(pch));
  printf("This is the IP addr in decimal : %d\n", htonl(inet_addr(pch)));
  
  // get prefix length

   int prefixLength;
  pch = strtok (NULL,"/");
  if(pch == NULL){
      prefixLength=32;
  }
  else{
   printf ("This is the IP prefix length : %s\n",pch);
   prefixLength = atoi(pch);
  }
   
   //create array to display binary nums
  int binaryNum[32];
  // by default all are 0
  for(int i=0; i<32; i++){
    binaryNum[i]=0;
  }
  // counter for binary array
    int i = 0;
    while (n > 0) {
 
        // storing remainder in binary array
        binaryNum[i] = n % 2;
        n = n / 2;
        i++;
    }
 
    // printing binary array in reverse order (right order)
    for (int j = 31; j >= 32-prefixLength; j--)
        printf("%d", binaryNum[j]);
    printf (" <- IP addr in binary\n");
 
    struct node *currentNode = root;
    
    for(int j=31; j>= 32-prefixLength; j--){
	// determine if current ip number is bit 0 or 1
	 if(binaryNum[j]=0){
		// traverse and create node at zeroChild
		if(currentNode->zeroChild==NULL) {
		    // create a node same as before
			currentNode->zeroChild = (struct node *) malloc(sizeof(struct node));
			currentNode->zeroChild->isSet=0;
			currentNode->zeroChild->zeroChild=NULL;
			currentNode->zeroChild->oneChild=NULL;
			
			currentNode = currentNode->zeroChild;
			continue;
			}
		else {
		    // traverse to node currentNode = currentNode->zeroChild
		    currentNode = currentNode->zeroChild;
			continue;
	    	}
	 }
	else if (binaryNum[j]=1){
	// same as above, but with oneChild
	    if(currentNode->oneChild==NULL) {
		    // create a node same as before
			currentNode->oneChild = (struct node *) malloc(sizeof(struct node));
			currentNode->oneChild->isSet=0;
			currentNode->oneChild->zeroChild=NULL;
			currentNode->oneChild->oneChild=NULL;
			
			currentNode = currentNode->oneChild;
			continue;
			}
		else {
		    // traverse to node currentNode = currentNode->oneChild
		    currentNode = currentNode->oneChild;
			continue;
	    	}
	}
    }
    //set this IP address to the real address of destination
    currentNode->isSet=1;
    
    //actualNextHopIP comes from config file
    if(SetValue){
    struct in_addr realIPAddr;
    u_int32_t actualNextHopIP = inet_pton(AF_INET, realIP, &realIPAddr);
    currentNode->nextHopIP = realIPAddr;
    }
    else
    return currentNode->nextHopIP;
}

inline bool fileExist (const std::string& name) {
  struct stat buffer;   
  return (stat (name.c_str(), &buffer) == 0); 
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



int meshNum = atoi(argv[2]);    // which machine are we dealing with? (1,2,3 are routers. 4,5,6 are hosts)

    // create starting node of tree
    struct node *root = (struct node *) malloc(sizeof(struct node));
    root->isSet=0;
    root->zeroChild=NULL;
    root->oneChild=NULL;

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
            //setTree(router1[realIP], router1[realIP], root)
             setTree(strcpy(new char[router1[2].length() + 1], router1[2].c_str()), strcpy(new char[router1[2].length() + 1], router1[2].c_str()), root, true);
        }
        if(counter==2){
            router2 = split(line, ' ');
            printf("line 3: ");
            setTree(strcpy(new char[router2[2].length() + 1], router2[2].c_str()), strcpy(new char[router2[2].length() + 1], router2[2].c_str()), root, true);
        }
        if(counter==3){
            router3 = split(line, ' ');
            printf("line 4: ");
            setTree(strcpy(new char[router3[2].length() + 1], router3[2].c_str()), strcpy(new char[router3[2].length() + 1], router3[2].c_str()), root, true);
        }
        if(counter==4){
            host1 = split(line, ' ');
            printf("line 5: ");
            //setTree(host1[realIP], host1[overlayIP], root)
             setTree(strcpy(new char[host1[2].length() + 1], host1[2].c_str()), strcpy(new char[host1[3].length() + 1], host1[3].c_str()), root, true);
        }
        if(counter==5){
            host2 = split(line, ' ');
            printf("line 6: ");
            setTree(strcpy(new char[host2[2].length() + 1], host2[2].c_str()), strcpy(new char[host2[3].length() + 1], host2[3].c_str()), root, true);
        }
        if(counter==6){
            host3 = split(line, ' ');
            printf("line 7: ");
            setTree(strcpy(new char[host3[2].length() + 1], host3[2].c_str()), strcpy(new char[host3[3].length() + 1], host3[3].c_str()), root, true);
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
            
            // if this is router 1 set host 4's overlay address to host 4's real address.
            if(meshNum == stoi(link21[1])){
                 setTree(strcpy(new char[host1[2].length() + 1], host1[2].c_str()), strcpy(new char[link21[3].length() + 1], link21[3].c_str()), root, true);
            }
            // if not router 1 set host 4's overlay address to router 1's real address
            else
                 setTree(strcpy(new char[router1[2].length() + 1], router1[2].c_str()), strcpy(new char[link21[3].length() + 1], link21[3].c_str()), root, true);
            
        }
        if(counter==11){
            link22 = split(line, ' ');
            printf("line 12: ");
            
            // if this is router 2 set host 5's overlay address to host 5's real address.
             if(meshNum ==  stoi(link22[1]))
                 setTree(strcpy(new char[host2[2].length() + 1], host2[2].c_str()), strcpy(new char[link22[3].length() + 1], link22[3].c_str()), root, true);
            // if not router 2 set host 5's overlay address to router 2's real address
            else
                setTree(strcpy(new char[router2[2].length() + 1], router2[2].c_str()), strcpy(new char[link22[3].length() + 1], link22[3].c_str()), root, true);
        }
        if(counter==12){
            link23 = split(line, ' ');
            printf("line 13: ");
            
            // if this is router 3 set host 6's overlay address to host 6's real address.
             if(meshNum ==  stoi(link23[1])){
                 // converting strings into char*s, running through tree like that
                 setTree(strcpy(new char[host3[2].length() + 1], host3[2].c_str()), strcpy(new char[link23[3].length() + 1], link23[3].c_str()), root, true);
             }
            // if not router 3 set host 6's overlay address to router 3's real address
            else
                setTree(strcpy(new char[router3[2].length() + 1], router3[2].c_str()), strcpy(new char[link23[3].length() + 1], link23[3].c_str()), root, true);
        }         
    	cout << line << endl;
        counter++;
    }
}
in_addr_t ourRouterAddress = INADDR_ANY;
char* router1sw = "1";
char* router2sw = "2";
char* router3sw = "3";
if(strcmp(argv[2], router1sw) == 0){
    ourRouterAddress = inet_addr(strcpy(new char[router1[2].length()+1], router1[2].c_str()));
}
if(strcmp(argv[2], router2sw) == 0){
    ourRouterAddress = inet_addr(strcpy(new char[router2[2].length()+1], router2[2].c_str()));
}
if(strcmp(argv[2], router3sw) == 0){
    ourRouterAddress = inet_addr(strcpy(new char[router3[2].length()+1], router3[2].c_str()));
}



    // at lines 5 6 7 fill tree with faux data
    // at lines 11 12 13 fill tree with real data

//std::cout << "hi just test: "<<globalConfigOptions[1];
char* routerCheck = "router";
    if(strcmp(argv[1], routerCheck) == 0){
    printf("server here\n");
    //fprintf(stdout, "Waiting for send_config.txt .... (so I know the port number all the routers and hosts will be using)\n ");
//reading send_body    
//int indicator = 0;
// std::vector<std::string> sendConfig;
//     while(indicator == 0){
//     if(fileExist("send_config.txt")){
//     ifstream file("send_config.txt");
// if (file.is_open())
// {
// 	string line;
// 	while (getline(file, line))
//     {
//             sendConfig = split(line, ' ');
    
//     }}}}
//setting port to what is on send_config file
    //printf("Our port number is: %d\n", stoi(sendConfig[2]));
    //PORT = stoi(sendConfig[2]);
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
    servaddr.sin_addr.s_addr = ourRouterAddress;
    servaddr.sin_port = htons(PORT);
       

       // this is failing because it's attempting to bind to a non-existant address
       // what this means for us is that we have to have "real" addresses given to us
       // or somehow make 10.0.2.1 (and the others) "real"
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
    //bob->ip_dst; our ip destination


    

    //part 4 of roadmap incrementing ttl and logging it
    bob->ip_ttl--;
    if (bob->ip_ttl < 1){continue;}
    printf("ttl incremented.\n"); 


    sendto(sockfd, (const char *)hello, strlen(hello), 
        MSG_CONFIRM, (const struct sockaddr *) &cliaddr,
            len);
    printf("Hello message sent.\n"); }}
















    else{
    cout << argv[1] << "\n";
    printf("client here\n");
    string dataToBeSent;
    char buffer[1000];
    fstream newfile;
    int indicator = 0; 
    fprintf(stdout, "Waiting for send_config.txt ....\n");
    //part 2 of roadmap generating random packet for transmission
    struct ip *bob = (struct ip *)buffer;
    struct udphdr *sally = (struct udphdr *)(buffer+20);
    char* data = (buffer + 28);
//reading send_body    
std::vector<std::string> sendConfig;
    while(indicator == 0){
   if(fileExist("send_config.txt")){
    ifstream file("send_config.txt");
if (file.is_open())
{
	string line;
	while (getline(file, line))
    {
            sendConfig = split(line, ' ');
    
    }}
    //printf("Our port number is: %d\n", stoi(sendConfig[2]));
    //PORT = stoi(sendConfig[2]);
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
   indicator++;
   }
    }



    in_addr myaddress2 = {.s_addr = inet_addr(strcpy(new char[sendConfig[0].length()+1], sendConfig[0].c_str()))};
    bob->ip_dst = myaddress2;
    bob->ip_p =17;
    bob->ip_ttl = stoi(globalConfigOptions[2]);
    //source and destination port
    sally->uh_sport = htons(stoi(sendConfig[1]));
    sally->uh_dport = htons(stoi(sendConfig[2]));

    
    
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
    servaddr.sin_addr.s_addr = ourRouterAddress;
       
    int n, len;
    socklen_t * fromlen2;//added
  
    sendto(sockfd, buffer, 1000,
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