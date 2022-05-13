#include "server.h"

#define MAX 516
#define PORT 9473
#define NCLIENTS 5
#define SA struct sockaddr

void handle_message(int sockfd) {
    char clientid[MAX];
    memset(clientid, 0, MAX);
    int size = read(sockfd, clientid, sizeof(clientid));
    if (size < 0) {
        perror("read error");
        exit(1);
    }

    char buffer[MAX + sizeof(clientid)];
    memset(buffer, 0, sizeof(buffer));
    sprintf(buffer, "%s", clientid);
    if (write(sockfd, buffer, strlen(buffer)) < 0) {
        perror("write error");
        exit(1);
    }
    printf("%s\n", buffer);

    if(strcmp(buffer, "TERMINATE : 9") == 0){
        close(sockfd);
        exit(0);
    }
}

int main(int argc, char **argv) {
    int sockfd, connfd, len;
    struct sockaddr_in servaddr, cli;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("Socket creation failed...\n");
        exit(0);
    } else
        printf("Socket successfully created..\n");
    bzero(&servaddr, sizeof(servaddr));

    // assign IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);

     if ((bind(sockfd, (SA *) &servaddr, sizeof(servaddr))) != 0) {
        printf("Socket bind failed...\n");
        exit(0);
    } else
        printf("Socket successfully binded..\n");

    if ( (listen(sockfd, 5)) != 0) {
        printf("Listen failed...\n");
        exit(0);
    } else
        printf("Server listening..\n");
    len = sizeof(cli);

    while(1) {
        connfd = accept(sockfd, (SA *) &cli, &len);
        if (connfd < 0) {
            printf("Server accept failed...\n");
            exit(0);
        } else
            printf("Server accept the client...\n");

        // Function for chatting between client and server
        handle_message(connfd);
    }

    // Server never shut down
    close(sockfd);
    return 0;
}

