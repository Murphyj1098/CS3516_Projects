// Joseph Murphy (jrmurphy)
// CS3516 Project 1 - Socket Programming

#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

#include "HTTPClient.h"

int main(int argc, char** argv)
{
    char* rawUrl;
    int socketID;
    char* serverPort;

    char rsp[800];

    struct timeval start, end;
    struct addrinfo *serverAddress;

    // 3 or 4 possible arguments
    // ./http_client [-options] server_url port_number
    if(!(argc == 3 || argc == 4))
    {
        usage();
        exit(1);
    }
    
    // check extra argument is "-p"
    if(argc == 4)
    {
        if(strcmp(argv[1], "-p")) // check if provided option is -p
        {
           printf("Invalid argument\n");
           usage();
           exit(1); 
        }
    }
    
    // Copy url and port (position in array based on number of args)
    rawUrl = (argc == 3) ? argv[1] : argv[2];
    serverPort = (argc == 3) ? argv[2] : argv[3];
    

    // get address info
    if(getaddrinfo(rawUrl, serverPort, /*TODO: hints array?*/ 0, &serverAddress) < 0)
    {
        printf("Failed to get address info\n");
        exit(1);
    }
    printf("Got address info\n");

    if((socketID = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("Failed to open socket\n");
        exit(1);
    }
    printf("Opened socket\n");

    // start RTT measurement
    gettimeofday(&start, NULL);

    // connect to socket
    if (connect(socketID, serverAddress->ai_addr, serverAddress->ai_addrlen) < 0)
    {
        printf("Failed to connect to server\n");
        exit(1);
    }
    printf("Connected to server\n");

    gettimeofday(&end, NULL);

    // write GET request to server
    write(socketID, "GET ~yli15/courses/CS3516Fall20A//index.html HTTP1.1\r\n", 100);
    write(socketID, "Host: users.wpi.edu\r\n", 100);
    write(socketID, "Content-Type: text/html\r\n", 100);
    write(socketID, "Connection: close\r\n", 100);
    write(socketID, "\r\n", 100);

    // receive response and store
    printf("reading\n");
    read(socketID, rsp, sizeof(rsp));

    printf("%s", rsp);


    // print RTT measure (if -p)


    // close socket
    close(socketID);
    exit(0);
}



// print out program usage to console
void usage()
{
    printf("usage: ./HTTPClient [-options] server_url port_number\n");
    // printf("\n");
    printf("[-options]:\n");
    printf("-p: prints the RTT for accessing the URL on the terminal before server's response\n");
}
