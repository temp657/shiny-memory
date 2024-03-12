#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>

#define MAX 80
#define PORT 8080
#define SA struct sockaddr

void func(int connfd)
{
    char buff[MAX];
    int n;
    for(;;)
    {
        bzero(buff, MAX);
        read(connfd, buff, sizeof(buff));
        printf("From client: %s\nTo client: ", buff);
        bzero(buff, MAX);
        n=0;
        while((buff[n++]=getchar())!= '\n')
            ;
        write(connfd, buff, sizeof(buff));

        if((strncmp(buff, "exit", 4))==0)
        {
            printf("Server exit\n");
            break;
        }

    }
}

int main()
{
    int sockfd, connfd, len;
    struct sockaddr_in servaddr, cli;

    sockfd=socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd == -1)
    {
        printf("Socket creation unsuccessful\n");
        exit(0);
    }
    else    
        printf("Socket creation successful\n");
    bzero(&servaddr, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);

    if((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0)
    {
        printf("Socket bind unsuccessful\n");
        exit(0);
    }
    else    
        printf("Socket bind successful\n");

    if((listen(sockfd, 5)) != 0)
    {
        printf("Listen unsuccessful\n");
        exit(0);
    }
    else    
        printf("Server listening\n");

    len = sizeof(cli);
    connfd = accept(sockfd, (SA*)&cli, &len);
    if (connfd < 0)
    {
        printf("Server accept failed\n");
        exit(0);
    }
    else    
        printf("Server accepts client\n");

    func(connfd);
    close(sockfd);

}
