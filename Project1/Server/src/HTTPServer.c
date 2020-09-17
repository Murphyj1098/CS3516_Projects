// Joseph Murphy (jrmurphy)
// CS3516 Project 1 - Socket Programming

#include "HTTPServer.h"

int main(int argc, char** argv)
{
    if(argc != 2)
    {
        usage();
        exit(1);
    }

    

    while(1)
    {

    }
}

// print out program usage to console
void usage() 
{
    printf("usage: ./HTTPServer <port number>\n");
    printf("Port number should be above 5000\n");
}