// Joseph Murphy (jrmurphy)
// CS3516 Project 1 - Socket Programming

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
    char* url;
    char* path;
    char* serverPort;
    int socketID;

    char rsp[4096];

    struct timeval start, end;
    struct addrinfo *serverAddress;
    struct addrinfo hints;

    // 3 or 4 possible arguments
    // ./http_client [-options] server_url port_number
    if(!(argc == 3 || argc == 4))
    {
        usage();
        exit(1);
    }
    
    // check extra argument is "-p"
    if(argc == 4 && strcmp(argv[1], "-p")) // check if provided option is -p
    {
           printf("Invalid argument\n");
           usage();
           exit(1); 
    }
    
    // Copy url and port (position in array based on number of args)
    url = (argc == 3) ? argv[1] : argv[2];
    serverPort = (argc == 3) ? argv[2] : argv[3];

    // seperate path from domain name
    strtok_r(url, "/", &path);


    // hints struct
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    // get address info
    if(getaddrinfo(url, serverPort, &hints, &serverAddress) < 0)
    {
        printf("Failed to get address info\n");
        exit(1);
    }

    // create socket
    if((socketID = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("Failed to open socket\n");
        exit(1);
    }


    // start RTT measurement
    gettimeofday(&start, NULL);

    // connect to socket
    if (connect(socketID, serverAddress->ai_addr, serverAddress->ai_addrlen) < 0)
    {
        printf("Failed to connect to server\n");
        close(socketID);
        exit(1);
    }

    // end RTT measurement
    gettimeofday(&end, NULL);


    char req [4096];
    snprintf(req, sizeof(req), "GET /%s HTTP/1.1\r\nHost: %s\r\nContent-Type: text/html\r\nConnection: close\r\n\r\n", path, url);
    
    // write GET request to server
    send(socketID, req, strlen(req), 0);


    // receive response and store
    read(socketID, rsp, sizeof(rsp));
    printf("%s\n", rsp);

    // print RTT measure (if -p)
    if(argc == 4)
    {
        float sec  = ((end.tv_sec - start.tv_sec)*1000);
	    float usec = ((end.tv_usec - start.tv_usec)/1000);
	    float RTT  = (sec + usec);
	    printf("\nRTT: %f ms\n", RTT);
    } 


    // close socket
    close(socketID);
    return 0;
}


// print out program usage to console
void usage()
{
    printf("usage: ./HTTPClient [-options] <server url> <port number>\n");
    printf("[-options]:\n");
    printf("-p: prints the RTT for accessing the URL on the terminal before server's response\n");
}
