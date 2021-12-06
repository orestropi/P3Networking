#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include "cs3516sock.h"

int main(int argc, char *argv[]) {
printf("hi, %d", create_cs3516_socket());
return 0;
}