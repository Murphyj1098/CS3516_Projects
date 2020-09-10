// Joseph Murphy (jrmurphy)
// CS3516 Project 1 - Socket Programming

#include <stdio.h>
#include <stdlib.h>

#include "HTTPClient.h"

int main(int argc, char** argv)
{
    // 3 or 4 possible arguments
    // ./http_client [-options] server_url port_number
    if(!(argc == 3 || argc == 4))
    {
        usage();
        exit(1);
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
