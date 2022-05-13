#include "header.h"

/**
 * Write final balance to a single file.
 * The path name should be output/result.txt
 */


// HARD CODE NUM OF CONSUMER THREADS = 3
pthread_t producer_thread;
pthread_t consumer_thread[3];

void writeBalanceToFiles(void) {
    // TODO: write balance for each customer 
    
    // TODO: write total balance change
}

int main(int argc, char *argv[]){
    
    //TODO: Argument check

    bookeepingCode();
    
    //TODO: Initialize global variables, like shared queue
    int *interim_nums = (int*)malloc((3)*sizeof(int));
    for(int i = 0; i < 3 ; i++){
        interim_nums[i] = i;
    }
    
    //create producer thread
    pthread_create(&producer_thread, NULL, &producer, NULL);
    printf("Launching producer\n");

    //TODO: create consumer threads

    for(int i = 0; i < 3; i++) {
      pthread_create(&(consumer_thread[i]), NULL, &consumer, (void*) &interim_nums[i]);
      printf("Launching consumer %d\n", i);
    }

    //TODO: wait for all threads to complete execution
    pthread_join(producer_thread, NULL);
    for(int i = 0; i < 3; i++) {
        pthread_join(consumer_thread[i], NULL);
    }
        
    free(interim_nums);
    //Write the final output
    writeBalanceToFiles();
    
    return 0; 
}