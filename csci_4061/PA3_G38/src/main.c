#include "header.h"

/**
 * Write final balance to a single file.
 * The path name should be output/result.txt
 */


pthread_t producer_thread;   // initialize producer thread
pthread_t consumer_thread[1000];  //initialize consumer threads

void writeBalanceToFiles(void) {
    // write balance for each customer 

    FILE * fp;
    fp = fopen("output/result.txt", "w"); //open file
    
    double cur_balance;
    char buffer[print_buff_size];
    double all_balance = 0;
    char all_buffer[print_buff_size];
    for(int i = 0; i < acctsNum; i++){
        
        //write balance to result
        cur_balance = balance[i];
        sprintf(buffer, "%d\t%lf\n", i, cur_balance);
        writeLineToFile("output/result.txt", buffer);
        
        //calc asset change of bank
        all_balance += balance[i];
    }
    
    sprintf(all_buffer, "All: \t%f\n", all_balance);
    writeLineToFile("output/result.txt", all_buffer);

    fclose(fp);
}

int main(int argc, char *argv[]){
    
    // Argument check
    int NTHREADS = atoi(argv[1]);  //get the number of consumers
    char* path = argv[2]; //get the file name
    num_consumers = NTHREADS; //set global for producer function with EOF's

    // handling of third (and buffer size if applicable) arguement
    if(argc >= 4){
        if(strcmp(argv[3], "-p") == 0){
            is_print = true;
        }
        else if(strcmp(argv[3], "-b") == 0){
            bounded_buffer = true;
            if(argc != 5){
                printf("No buffer size specified. Buffer will default to size 200\n");
                sem_init(&bounded_buffer_semaphore, 0, 200);
            }
            else{
                sem_init(&bounded_buffer_semaphore, 0, atoi(argv[4]));
            }
        }
        else if(strcmp(argv[3], "-bp") == 0){
            is_print = true;
            bounded_buffer = true;
            if(argc != 5){
                printf("No buffer size specified. Buffer will default to size 200\n");
                sem_init(&bounded_buffer_semaphore, 0, 200);
            }
            else{
                sem_init(&bounded_buffer_semaphore, 0, atoi(argv[4]));
            }
        }
    }

    bookeepingCode();
    
    //create producer thread
    if(pthread_create(&producer_thread, NULL, producer, (void*) path) != 0){
        fprintf(stderr,"Failed to create producer.\n");
    }

    //create consumer threads
    for(int i = 0; i < NTHREADS; i++){
        int *arg = malloc(sizeof(*arg));
        *arg = i;
        if(pthread_create(&consumer_thread[i], NULL, consumer, arg) != 0){
            fprintf(stderr,"Failed to create consumer %d.\n", i);
        }
    }

    //wait for all threads to complete execution
    pthread_join(producer_thread, NULL);

    for(int i = 0; i < NTHREADS; i++) {
        pthread_join(consumer_thread[i], NULL);
    }
    
    //Write the final output
    writeBalanceToFiles();
    
    return 0; 
}