#ifndef SERVER_H
#define SERVER_H

#include "utils.h"

// skeleton of a struct to hold account information
// this should contain information passed with each 
// new account that is registered (see REGISTER in 
// the writeup...)
// 
// add any other fields you feel are necessary to 
// for implementing the extra credit history or
// for maintaining synchronization among threads
struct account{

    pthread_mutex_t mutex;
    int account_num;
    char name[MAX_STR];
    char username[MAX_STR];
    time_t birthday;
    float balance;
    float all_transactions[MAX_TRANSACTIONS];
    int current_index;
    
};

// array of structs to store account information
struct account balances[MAX_ACC];
// ALT: you may declare it as a pointer and malloc
// struct account * balances;

void *handle_message(void *arg);

void BALANCE_RESPONSE (int sockfd, msg_enum response_type, int account_number);
void ACCOUNT_INFO_RESPONSE(int sockfd, msg_enum response_type, int account_number);
void CASH_RESPONSE(int sockfd, msg_enum response_type, float cash);
void HISTORY_RESPONSE(int sockfd, msg_enum response_type, int account_number, int index);

void printSyntax();

#endif

