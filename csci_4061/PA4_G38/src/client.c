#include "client.h"

#define MAX 516
#define SA struct sockaddr

void printSyntax(){
    printf("incorrect usage syntax! \n");
    printf("usage: $ ./client input_filename server_addr server_port\n");
}

//Elapsed time, piazza post reference
float time_diff(struct timespec *start, struct timespec *end){
    return (end->tv_sec - start->tv_sec) + 1e-9*(end->tv_nsec - start->tv_nsec);
}

void loopFunc(size_t num)
{
    int tmp = 0;
    for (int i = 0; i < num; ++i) {
        tmp += 1;
    }
}

int main(int argc, char *argv[]){
    
    // argument handling
    char *filename = argv[1];
    char *ipAddress = argv[2];
    int server_port = atoi(argv[3]);
    
    if(argc != 4)
    {
        printSyntax();
        return 0;
    }
    //begin time recording
    struct timespec start;
    struct timespec end;
    clock_gettime(CLOCK_REALTIME, &start);


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
    servaddr.sin_addr.s_addr = inet_addr(ipAddress);
    servaddr.sin_port = htons(server_port);

    if (connect(sockfd, (SA *) &servaddr, sizeof(servaddr)) != 0) { //try to connect to the server
        printf("Connection with the server failed...\n");
        exit(0);
    } else
        printf("Connected to the server..\n");

    FILE * fp;
    
    char filename_buff[50];
    sprintf(filename_buff, "input/%s", filename);
    fp = fopen(filename_buff, "r"); //open file
    if (fp == NULL){
        fprintf(stderr,"Error opening file: %s\n", filename);
        exit(1);
    }

    bool create_new_connection;
    char line[100];
    char* token;

    msg_enum message_type;
    msg_enum serialized_message_type;
    msg_enum response_type;
    msg_enum serialized_response;

    int account_number;
    int serialized_account_number;

    char name[MAX_STR];
    char username[MAX_STR];

    time_t birthday;
    time_t serialized_birthday;

    float amount;

    int num_transactions;
    int serialized_num_transactions;

    float client_balance;
    float client_cash;

    msg_enum request_cash_message = htonl(REQUEST_CASH);
    msg_enum get_balance_message = htonl(GET_BALANCE);
    msg_enum error_message = htonl(ERROR);
    float cash_request = CASH_AMOUNT;
    float cash_return;



    // Loop through the file and write data sequentially
    while(fgets(line, 100, fp) != NULL){

        if(create_new_connection){ //if we need to reconnect the client due to a termination but there are more lines
            close(sockfd);
            sockfd = socket(AF_INET, SOCK_STREAM, 0); //create socket
            if (connect(sockfd, (SA *) &servaddr, sizeof(servaddr)) != 0) { //try to connect to the server
                printf("Connection with the server failed...\n");
                exit(0);
            } else
                printf("Connected to the server..\n");
            create_new_connection = false;
        }

        //set all file variables
        sscanf(line, "%x,%d,%[^,],%[^,],%ld,%f,%d", &message_type, &account_number, name, username, &birthday, &amount, &num_transactions);

        //EC: request_history == 16???
        if (message_type == 16){
            message_type -= 6;
        }

        serialized_message_type = htonl(message_type);
        serialized_account_number = htonl(account_number);
        serialized_birthday = htonl(birthday);
        serialized_num_transactions = htonl(num_transactions);


        switch(message_type){
            
            case REGISTER: 
                //Writing to socket
                if (write(sockfd, &serialized_message_type, sizeof(msg_enum)) < 0){ //write the protocol number
                    perror("Cannot write");
                    exit(1);
                }

                if (write(sockfd, &username, sizeof(char)*MAX_STR) < 0){
                    perror("Cannot write");
                    exit(1);
                }
                if (write(sockfd, &name, sizeof(char)*MAX_STR) < 0){
                    perror("Cannot write");
                    exit(1);
                }
                if (write(sockfd, &serialized_birthday, sizeof(time_t)) < 0){
                    perror("Cannot write");
                    exit(1);
                }

                //Reading from socket
                if (read(sockfd, &response_type, sizeof(msg_enum)) < 0){ 
                    perror("Cannot read");
                    exit(1);
                }
                // ERROR checking
                if (response_type != BALANCE){
                    serialized_response = htonl(response_type);
                    if (write(sockfd, &error_message, sizeof(msg_enum)) < 0){
                        perror("Cannot write");
                        exit(1);
                    }
                    if (write(sockfd, &serialized_response, sizeof(msg_enum)) < 0){
                        perror("Cannot write");
                        exit(1);
                    }
                    break;
                }

                if (read(sockfd, &account_number, sizeof(int)) < 0){ 
                    perror("Cannot read");
                    exit(1);
                }
                if (read(sockfd, &client_balance, sizeof(float)) < 0){ 
                    perror("Cannot read");
                    exit(1);
                }
                break;

            case GET_ACCOUNT_INFO:
                //Writing to Socket
                
                if (write(sockfd, &serialized_message_type, sizeof(msg_enum)) < 0){ //write the protocol number
                    perror("Cannot write");
                    exit(1);
                }

                if (write(sockfd, &serialized_account_number, sizeof(int)) < 0){
                    perror("Cannot write");
                    exit(1);
                }

                //Reading from socket
                if (read(sockfd, &response_type, sizeof(msg_enum)) < 0){ 
                    perror("Cannot read");
                    exit(1);
                }
                //ERROR checking
                if (response_type != ACCOUNT_INFO){
                    serialized_response = htonl(response_type);
                    if (write(sockfd, &error_message, sizeof(msg_enum)) < 0){
                        perror("Cannot write");
                        exit(1);
                    }
                    if (write(sockfd, &serialized_response, sizeof(msg_enum)) < 0){
                        perror("Cannot write");
                        exit(1);
                    }
                    break;
                }

                if (read(sockfd, &username, sizeof(char)*MAX_STR) < 0){
                    perror("Cannot read");
                    exit(1);
                }

                if (read(sockfd, &name, sizeof(char)*MAX_STR) < 0){
                    perror("Cannot read");
                    exit(1);
                }
                
                if (read(sockfd, &birthday, sizeof(time_t)) < 0){ 
                    perror("Cannot read");
                    exit(1);
                }
                break;

            case TRANSACT:
                //Writing to socket
                if(write(sockfd, &get_balance_message, sizeof(msg_enum)) < 0){
                    perror("Cannot write");
                    exit(1);
                }

                if(write(sockfd, &serialized_account_number, sizeof(int)) < 0){
                    perror("Cannot write");
                    exit(1);
                }

                //Reading from Socket
                if (read(sockfd, &response_type, sizeof(msg_enum)) < 0){ 
                    perror("Cannot read");
                    exit(1);
                }
                // ERROR checking
                if (response_type != BALANCE){
                    serialized_response = htonl(response_type);
                    if (write(sockfd, &error_message, sizeof(msg_enum)) < 0){
                        perror("Cannot write");
                        exit(1);
                    }
                    if (write(sockfd, &serialized_response, sizeof(msg_enum)) < 0){
                        perror("Cannot write");
                        exit(1);
                    }
                    break;
                }


                if(read(sockfd, &account_number, sizeof(int)) < 0){
                    perror("Cannot read");
                    exit(1);
                }

                if(read(sockfd, &client_balance, sizeof(float)) < 0){
                    perror("Cannot read");
                    exit(1);
                }

                // Withdraw from account
                if (amount < 0.0){
                    if (client_balance + amount < 0.0){
                        break;
                    }
                }

                // Client cash request
                while(amount > cash){
                    // Writing to socket
                    if(write(sockfd, &request_cash_message, sizeof(msg_enum)) < 0){
                        perror("Cannot write");
                        exit(1);
                    }
                    if(write(sockfd, &cash_request, sizeof(float)) < 0){
                        perror("Cannot write");
                        exit(1);
                    }
                    //Reading from Socket
                    if (read(sockfd, &response_type, sizeof(msg_enum)) < 0){ 
                        perror("Cannot read");
                        exit(1);
                    }
                    //ERROR checking
                    if (response_type != CASH){
                        serialized_response = htonl(response_type);
                        if (write(sockfd, &error_message, sizeof(msg_enum)) < 0){
                        perror("Cannot write");
                        exit(1);
                        }
                        if (write(sockfd, &serialized_response, sizeof(msg_enum)) < 0){
                            perror("Cannot write");
                            exit(1);
                        }
                        break;
                    }

                    if(read(sockfd, &cash_return, sizeof(float)) < 0){
                        perror("Cannot read");
                        exit(1);
                    }
                    // Update client's cash on hand
                    cash += cash_return;
                }

                //If all checks clear, write to socket
                
                if (write(sockfd, &serialized_message_type, sizeof(msg_enum)) < 0){ //write the protocol number
                    perror("Cannot write");
                    exit(1);
                }

                if (write(sockfd, &serialized_account_number, sizeof(int)) < 0){
                    perror("Cannot write");
                    exit(1);
                }
                if (write(sockfd, &amount, sizeof(float)) < 0){
                    perror("Cannot write");
                    exit(1);
                }

                //Reading from socket
                if (read(sockfd, &response_type, sizeof(msg_enum)) < 0){ 
                    perror("Cannot read");
                    exit(1);
                }
                //ERROR checking
                if (response_type != BALANCE){
                    serialized_response = htonl(response_type);
                    if (write(sockfd, &error_message, sizeof(msg_enum)) < 0){
                        perror("Cannot write");
                        exit(1);
                    }
                    if (write(sockfd, &serialized_response, sizeof(msg_enum)) < 0){
                        perror("Cannot write");
                        exit(1);
                    }
                    break;
                }

                if (read(sockfd, &account_number, sizeof(int)) < 0){ 
                    perror("Cannot read");
                    exit(1);
                }
                
                if (read(sockfd, &client_balance, sizeof(float)) < 0){ 
                    perror("Cannot read");
                    exit(1);
                }
                //Update client cash after customer transaction
                cash -= amount;
                
                break;
                
            case GET_BALANCE:
                //Writing to socket
                
                if (write(sockfd, &serialized_message_type, sizeof(msg_enum)) < 0){ //write the protocol number
                    perror("Cannot write");
                    exit(1);
                }

                if (write(sockfd, &serialized_account_number, sizeof(int)) < 0){
                    perror("Cannot write");
                    exit(1);
                }
                //Reading from socket
                if (read(sockfd, &response_type, sizeof(msg_enum)) < 0){ 
                    perror("Cannot read");
                    exit(1);
                }
                //ERROR checking
                if (response_type != BALANCE){
                    serialized_response = htonl(response_type);
                    if (write(sockfd, &error_message, sizeof(msg_enum)) < 0){
                        perror("Cannot write");
                        exit(1);
                    }
                    if (write(sockfd, &serialized_response, sizeof(msg_enum)) < 0){
                        perror("Cannot write");
                        exit(1);
                    }
                    break;
                }

                if (read(sockfd, &account_number, sizeof(int)) < 0){ 
                    perror("Cannot read");
                    exit(1);
                }

                if (read(sockfd, &client_balance, sizeof(float)) < 0){ 
                    perror("Cannot read");
                    exit(1);
                }
                
                break;

            case REQUEST_CASH:
                
                if (write(sockfd, &serialized_message_type, sizeof(msg_enum)) < 0){ //write the protocol number
                    perror("Cannot write");
                    exit(1);
                }

                if (write(sockfd, &amount, sizeof(float)) < 0){
                    perror("Cannot write");
                    exit(1);
                }

                // Response
                if (read(sockfd, &response_type, sizeof(msg_enum)) < 0){ 
                    perror("Cannot read");
                    exit(1);
                }
                if (response_type != CASH){
                    if (write(sockfd, &error_message, sizeof(msg_enum)) < 0){
                        perror("Cannot write");
                        exit(1);
                    }
                    if (write(sockfd, &response_type, sizeof(msg_enum)) < 0){
                        perror("Cannot write");
                        exit(1);
                    }
                }

                if (read(sockfd, &client_cash, sizeof(float)) < 0){ 
                    perror("Cannot read");
                    exit(1);
                }

                break;
                
            case ERROR:
                
                if (write(sockfd, &serialized_message_type, sizeof(msg_enum)) < 0){
                    perror("Cannot write");
                    exit(1);
                }

                
                if (write(sockfd, &serialized_message_type, sizeof(msg_enum)) < 0){
                    perror("Cannot write");
                    exit(1);
                }

                break;

            case TERMINATE: 
                
                
                if (write(sockfd, &serialized_message_type, sizeof(msg_enum)) < 0){
                    perror("Cannot write");
                    exit(1);
                }

                create_new_connection = true; //create the new connection on the next go (if the file is done it will exit loop)
                    
                break;
                
            case REQUEST_HISTORY:
                
                if (write(sockfd, &serialized_message_type, sizeof(msg_enum)) < 0){
                    perror("Cannot write");
                    exit(1);
                }
                if (write(sockfd, &serialized_account_number, sizeof(int)) < 0){
                    perror("Cannot write");
                    exit(1);
                }
                if (write(sockfd, &serialized_num_transactions, sizeof(int)) < 0){
                    perror("Cannot write");
                    exit(1);
                }

                if (read(sockfd, &response_type, sizeof(msg_enum)) < 0){ 
                    perror("Cannot read");
                    exit(1);
                }

                if (response_type != HISTORY){
                    serialized_response = htonl(response_type);
                    if (write(sockfd, &serialized_response, sizeof(msg_enum)) < 0){
                        perror("Cannot write");
                        exit(1);
                    }
                    if (write(sockfd, &serialized_response, sizeof(msg_enum)) < 0){
                        perror("Cannot write");
                        exit(1);
                    }
                }

                if (read(sockfd, &account_number, sizeof(int)) < 0){ 
                    perror("Cannot read");
                    exit(1);
                }
                
                printf("Account Number: %d\n", account_number);

                if (read(sockfd, &num_transactions, sizeof(int)) < 0){ 
                    perror("Cannot read");
                    exit(1);
                }

                int index = ntohl(num_transactions);

                for(int i = 0; i < index; i++){
                    float temp;
                    if (read(sockfd, &temp, sizeof(float)) < 0){ 
                        perror("Cannot read");
                        exit(1);
                    }
                    printf("%.2f\n", temp);
                }

                break;

            default: //send msg_enums that aren't 0-9 to ERROR
                
                if (write(sockfd, &error_message, sizeof(msg_enum)) < 0){
                    perror("Cannot write");
                    exit(1);
                }
                if(write(sockfd, &serialized_message_type, sizeof(msg_enum))<0){
                    perror("Cannot write");
                    exit(1);
                }

                break;
                
        }//end switch case 
    }//end while
    message_type = 9;
    serialized_message_type = htonl(message_type);
    if (write(sockfd, &serialized_message_type, sizeof(msg_enum)) < 0){ //if the last line of the file is not a 9, this is where we send the terminate message
        perror("Cannot write");
        exit(1);
    }
    
    close(sockfd);
    fclose(fp);
    
    //end of time recording
    clock_gettime(CLOCK_REALTIME, &end);
    printf("Elapsed Time: %.2f\n",time_diff(&start, &end));

    return 0; 
}