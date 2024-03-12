#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <netdb.h>
#include <sys/socket.h>
#include <unistd.h>

#define MAX 80
#define PORT 8080
#define SA struct sockaddr

void func(int sockfd)
{
    char buff[MAX];
    int n;
    for(;;)
    {
        bzero(buff, sizeof(buff));
        n=0;
        printf("Enter string: ");
        while((buff[n++]=getchar())!='\n')
            ;
        write(sockfd,buff, sizeof(buff));
        bzero(buff, sizeof(buff));
        read(sockfd,buff, sizeof(buff));
        printf("Socket: %s", buff);
        if(strncmp(buff, "exit", 4)==0)
        {
            printf("Client exited \n");
            break;
        }
    }
}

int main()
{
    int sockfd, connfd;
    struct sockaddr_in servaddr,cli;

    sockfd=socket(AF_INET, SOCK_STREAM,0);
    if(sockfd == -1)
    {
        printf("Socket creation failed \n");
        exit(0);
    }
    else
    {
        printf("Socket creation success \n");
    }
    bzero(&servaddr, sizeof(servaddr));

    servaddr.sin_family=AF_INET;
    servaddr.sin_addr.s_addr=inet_addr("127.0.0.1");
    servaddr.sin_port=htons(PORT);

    if(connect(sockfd, (SA*)&servaddr, sizeof(servaddr))!= 0)
    {
        printf("Connection failed \n");
        exit(0);
    }
    else
        printf("Connection success \n");
    
    func(sockfd);
    close(sockfd);
}
