#include "client.h"

#define LOCALHOST "127.0.0.1"
#define MAX 516
#define PORT 9473
#define NCLIENTS 5
#define SA struct sockaddr

void printSyntax(){
    printf("incorrect usage syntax! \n");
    printf("usage: $ ./client input_filename server_addr server_port\n");
}

void recieve(int sockfd) {
    char recv[1024];
    memset(recv, 0, sizeof(recv));
    if (read(sockfd, recv, sizeof(recv)) < 0) {
        perror("cannot read");
        exit(1);
    }
    printf("%s\n", recv);

    if(strcmp(recv, "TERMINATE") == 0){
        close(sockfd);
        exit(0);
    }
}

int main(int argc, char *argv[]){
    // argument handling
    if(argc != 4)
    {
        printSyntax();
        return 0;
    }
    char const* enums[] = {"REGISTER", "GET_ACCOUNT_INFO", "TRANSACT", "GET_BALANCE", "ACCOUNT_INFO", "BALANCE", "REQUEST_CASH", "CASH", "ERROR", "TERMINATE"};

    for (int i = 0; i < 10; i++) {
        int sockfd, connfd;
        struct sockaddr_in servaddr, cli;

        sockfd = socket(AF_INET, SOCK_STREAM, 0); //create socket
        if (sockfd == -1) {
            printf("Socket creation failed...\n");
            exit(0);
        } else
            printf("Socket successfully created..\n");
        bzero(&servaddr, sizeof(servaddr)); //initialize struct to all 0's

        // assign IP, PORT
        servaddr.sin_family = AF_INET;
        servaddr.sin_addr.s_addr = inet_addr(LOCALHOST);
        servaddr.sin_port = htons(PORT);

        if (connect(sockfd, (SA *) &servaddr, sizeof(servaddr)) != 0) { //try to connect to the server
            printf("Connection with the server failed...\n");
            exit(0);
        } else
            printf("Connected to the server..\n");
        
        char interim_buff[25];
        sprintf(interim_buff, "%s : %d", enums[i], i);
        if (write(sockfd, interim_buff, MAX) < 0){
            perror("Cannot write");
            exit(1);
        }else {
            recieve(sockfd);
        }
    }

    
    while(wait(NULL) > 0);
    return 0; 
}