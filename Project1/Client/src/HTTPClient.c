// Joseph Murphy (jrmurphy)
// CS3516 Project 1 - Socket Programming

#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>

#include "HTTPClient.h"

int main(int argc, char** argv)
{

    char* rawUrl, formatUrl;
    int socketID;


    // 3 or 4 possible arguments
    // ./http_client [-options] server_url port_number
    if(!(argc == 3 || argc == 4))
    {
        usage();
        exit(1);
    }
    
    if(argc == 4)
    {
        if(strcmp(argv[1], "-p")) // check if provided option is -p
        {
           printf("Invalid argument\n");
           usage();
           exit(1); 
        }

        rawUrl = argv[2];
    }
    else if(argc == 3)
    {
        rawUrl = argv[1];
    }
    
    if((socketID = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("Failed to open socket");
        exit(2);
    }

}

// print out program usage to console
void usage()
{
    printf("usage: ./HTTPClient [-options] server_url port_number\n");
    // printf("\n");
    printf("[-options]:\n");
    printf("-p: prints the RTT for accessing the URL on the terminal before server's response\n");
}
