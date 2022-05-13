#include "server.h"

#define SA struct sockaddr

pthread_t log_thread;

pthread_mutex_t main_lock = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t thread_lock = PTHREAD_MUTEX_INITIALIZER;

float server_cash = CASH_AMOUNT;
int current_account_number = 0; //make the first account at index 1 (make sure to lock when accessing this variable and increment it after creating a new account)

struct account accounts[MAX_ACC];
msg_enum response_type;
float cash;

// EC Part 1 Attempt
// void *handle_accepts(void *arg) {

//     int connfd, len;

//     struct sockaddr_in cli;

//     len = sizeof(cli);

//     int sockfd = *((int *) arg);
//     free(arg);
    

//     while(1){
//         pthread_mutex_lock(&thread_lock);
        
//         connfd = accept(sockfd, (SA *) &cli, &len);  //returns a new socket for IO with the specific client
//         if (connfd < 0) {
//             printf("Server accept failed...\n");
//             exit(0);
//         } else{
//             printf("Server accept the client...\n");
//             int *arg = malloc(sizeof(*arg));
//             *arg = connfd;
//             handle_message(arg);
//             }
//         pthread_mutex_unlock(&thread_lock);
//     }
// }

void *log_file() {

    //make to wait for the latest account numbers before making the log file
    
    FILE * fp;

    while(1){

        fp = fopen("output/balances.csv", "w"); //open file
        if (fp == NULL){
            fprintf(stderr,"Error opening file");
            exit(1);
        }

        int temp;
        pthread_mutex_lock(&main_lock);
        temp = current_account_number;
        pthread_mutex_unlock(&main_lock);
    
        for(int i = 0; i < temp; i++){ //loop through all existing accounts
            char line[200];
            pthread_mutex_lock(&accounts[i].mutex);
            fprintf(fp, "%d,%.2f,%s,%s,%ld\n", accounts[i].account_num, accounts[i].balance, accounts[i].name, accounts[i].username, accounts[i].birthday);
            fflush(fp);
            pthread_mutex_unlock(&accounts[i].mutex);
        }

        for(int i = 0; i < temp; i++){ //loop through all existing accounts
            FILE * acc;
            char line[80];
            sprintf(line, "output/account%d.csv", i);
            acc = fopen(line, "w"); //open file
            if (acc == NULL){
                fprintf(stderr,"Error opening file");
                exit(1);
            }

            for(int j = 0; j < accounts[i].current_index; j++){
                pthread_mutex_lock(&accounts[i].mutex);
                fprintf(acc, "%.2f\n", accounts[i].all_transactions[j]);
                fflush(acc);
                pthread_mutex_unlock(&accounts[i].mutex);
            }
            fclose(acc);
        }
        fclose(fp);
        sleep(5);
    }
    
}

void BALANCE_RESPONSE (int sockfd, msg_enum response_type, int account_number){
    if (write(sockfd, &response_type, sizeof(msg_enum)) < 0){
        perror("Cannot write");
        exit(1);
    }

    if (write(sockfd, &accounts[account_number].account_num, sizeof(int)) < 0){
        perror("Cannot write");
        exit(1);
    }

    if (write(sockfd, &accounts[account_number].balance, sizeof(float)) < 0){
        perror("Cannot write");
        exit(1);
    }
}

void ACCOUNT_INFO_RESPONSE(int sockfd, msg_enum response_type, int account_number){
    if (write(sockfd, &response_type, sizeof(msg_enum)) < 0){
        perror("Cannot write");
        exit(1);
    }

    if (write(sockfd, &accounts[account_number].username, sizeof(char)*MAX_STR) < 0){
        perror("Cannot write");
        exit(1);
    }
    if (write(sockfd, &accounts[account_number].name, sizeof(char)*MAX_STR) < 0){
        perror("Cannot write");
        exit(1);
    }
    if (write(sockfd, &accounts[account_number].birthday, sizeof(time_t)) < 0){ 
        perror("Cannot write");
        exit(1);
    }
}

void CASH_RESPONSE(int sockfd, msg_enum response_type, float cash){
    if (write(sockfd, &response_type, sizeof(msg_enum)) < 0){
        perror("Cannot write");
        exit(1);
    }

    if (write(sockfd, &cash, sizeof(float)) < 0){
        perror("Cannot write");
        exit(1);
    }
}

void HISTORY_RESPONSE(int sockfd, msg_enum response_type, int account_number, int index){
    if (write(sockfd, &response_type, sizeof(msg_enum)) < 0){
        perror("Cannot write");
        exit(1);
    }
    if (write(sockfd, &account_number, sizeof(int)) < 0){
        perror("Cannot write");
        exit(1);
    }

    int serialized_transactions = htonl(index);

    if (write(sockfd, &serialized_transactions, sizeof(int)) < 0){
        perror("Cannot write");
        exit(1);
    }

    for(int i = 0; i < index; i++){

        float num = accounts[account_number].all_transactions[i];

        if (write(sockfd, &num, sizeof(float)) < 0){
            perror("Cannot write");
            exit(1);
        }
    }
}

void *handle_message(void *arg) {
    int tmp, protocol_num, sockfd;

    msg_enum message_type;
    msg_enum unserialized_message_type;
    msg_enum rsp_type;
    
    int account_number;
    char name[MAX_STR];
    char username[MAX_STR];
    time_t birthday;
    float amount;
    float balance;

    int num_transactions;

    int unserialized_account_number;
    time_t unserialized_birthday;
    int unserialized_num_transactions;


    sockfd = *((int *) arg); //get the file descriptor into sockfd
    free(arg);
    while(1){

        int size = read(sockfd, &message_type, sizeof(msg_enum)); //first read in the protocol (4 bytes), this will tell us how much more to read in
        if (size < 0) {
            perror("read error");
            exit(1);
        }
        unserialized_message_type = ntohl(message_type);

        switch(unserialized_message_type){ //determine which protocol to execute based on the protocol number (enum type)

            case REGISTER:
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
                unserialized_birthday = ntohl(birthday);
        

                //create the account here
                pthread_mutex_lock(&main_lock);

                accounts[current_account_number].mutex = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;

                pthread_mutex_lock(&accounts[current_account_number].mutex);

                accounts[current_account_number].account_num = current_account_number;
                strcpy(accounts[current_account_number].username, username);
                strcpy(accounts[current_account_number].name, name);
                accounts[current_account_number].birthday = unserialized_birthday;
                accounts[current_account_number].balance = 0.00;
                accounts[current_account_number].current_index = 0;

                pthread_mutex_unlock(&accounts[current_account_number].mutex);
                
                //write account num back to the client
                rsp_type = BALANCE;
                BALANCE_RESPONSE(sockfd, rsp_type, accounts[current_account_number].account_num);
                current_account_number++;

                pthread_mutex_unlock(&main_lock);

                break;

            case GET_ACCOUNT_INFO: 
                if (read(sockfd, &account_number, sizeof(int)) < 0){
                    perror("Cannot read");
                    exit(1);
                }
                
                unserialized_account_number = ntohl(account_number);

                pthread_mutex_lock(&main_lock);
                pthread_mutex_lock(&accounts[unserialized_account_number].mutex);

                ACCOUNT_INFO_RESPONSE(sockfd, rsp_type, unserialized_account_number);

                pthread_mutex_unlock(&accounts[unserialized_account_number].mutex);
                pthread_mutex_unlock(&main_lock);
                
                break;

            case TRANSACT: 
                if (read(sockfd, &account_number, sizeof(float)) < 0){
                    perror("Cannot read");
                    exit(1);
                }
                unserialized_account_number = ntohl(account_number);

                if (read(sockfd, &amount, sizeof(float)) < 0){
                    perror("Cannot read");
                    exit(1);
                }

                //Do some calculation
                
                pthread_mutex_lock(&accounts[unserialized_account_number].mutex);
                
                accounts[unserialized_account_number].balance += amount;
                accounts[unserialized_account_number].all_transactions[accounts[unserialized_account_number].current_index] = amount;
                accounts[unserialized_account_number].current_index++;

                pthread_mutex_unlock(&accounts[unserialized_account_number].mutex);

                // Write back to client
                rsp_type = BALANCE;
                BALANCE_RESPONSE(sockfd, rsp_type, unserialized_account_number);

                break;
                
            case GET_BALANCE: 
                if (read(sockfd, &account_number, sizeof(float)) < 0){
                    perror("Cannot read");
                    exit(1);
                }
                
                rsp_type = BALANCE;
                unserialized_account_number = ntohl(account_number);
                BALANCE_RESPONSE(sockfd, rsp_type, unserialized_account_number);

                break;

            case REQUEST_CASH: 
                if (read(sockfd, &amount, sizeof(float)) < 0){
                    perror("Cannot read");
                    exit(1);
                }
                
                // cash == amount
                rsp_type = CASH;
                CASH_RESPONSE(sockfd, rsp_type, amount);

                break;

            case ERROR:
                if(read(sockfd, &rsp_type, sizeof(msg_enum)) < 0){
                    perror("Cannot read");
                    exit(1);
                }
                
                perror("enumerated message type does not match any within the protocol\n");

                break;
                
            case REQUEST_HISTORY:
                if(read(sockfd, &account_number, sizeof(int)) < 0){
                    perror("Cannot read");
                    exit(1);
                }
                if(read(sockfd, &num_transactions, sizeof(int)) < 0){
                    perror("Cannot read");
                    exit(1);
                }
                unserialized_account_number = ntohl(account_number);

                int index = accounts[unserialized_account_number].current_index; 

                rsp_type = HISTORY;
                HISTORY_RESPONSE(sockfd, rsp_type, unserialized_account_number, index);
                break;

            case TERMINATE: 
                return NULL;
                
            default:
                break;
        } //end switch case
    }//end while    
}//end handle_message

int main(int argc, char **argv) {

    //arg handling
    char *ipAddress = argv[1];
    int port_num = atoi(argv[2]);
    int num_clients = atoi(argv[3]);

    int sockfd, connfd, len;
    struct sockaddr_in servaddr, cli;

    pthread_t extra_credit_threads[num_clients];

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
    servaddr.sin_port = htons(port_num);

     if ((bind(sockfd, (SA *) &servaddr, sizeof(servaddr))) != 0) { //bind the socket to be a server socket
        printf("Socket bind failed...\n");
        exit(0);
    } else
        printf("Socket successfully binded..\n");

    if ( (listen(sockfd, num_clients)) != 0) { //start listening through the server socket
        printf("Listen failed...\n");
        exit(0);
    } else
        printf("Server listening..\n");
    

    if(pthread_create(&log_thread, NULL, log_file, NULL) != 0){ //create the thread for the log file
        fprintf(stderr,"Failed to create log file thread.\n");
    }

    if(pthread_detach(log_thread) != 0){ //create the thread for the log file
        fprintf(stderr,"Failed to create log file thread.\n");
    }

    // EC Part 1 attempt
    // for(int i = 0; i < num_clients; i++){
    //     int *arg = malloc(sizeof(*arg));
    //     *arg = sockfd;
    //     if (pthread_create(&extra_credit_threads[i], NULL, handle_accepts, arg) != 0){ //create the thread for the client (calls the handle message function)
    //             fprintf(stderr,"Failed to create client thread.\n");
    //         }
    // }

    // for (int i = 0; i < num_clients; i++) {    //wait on the server threads
    //     pthread_join(extra_credit_threads[i], NULL);  
    // }
    
    while(1) {
        connfd = accept(sockfd, (SA *) &cli, &len);  //returns a new socket for IO with the specific client
        if (connfd < 0) {
            printf("Server accept failed...\n");
            exit(0);
        } else{
            
            int *arg = malloc(sizeof(*arg));
            *arg = connfd;
            pthread_t client_thread;
            if(pthread_create(&client_thread, NULL, handle_message, (void*) arg) != 0){ //create the thread for the client (calls the handle message function)
                fprintf(stderr,"Failed to create client thread.\n");
            }
        }
    }

    close(sockfd);
    bookeepingCode();

    return 0; 
}