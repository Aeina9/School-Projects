#include "consumer.h"
#include <ctype.h>

/**
 * parse lines from the queue, calculate balance change
 * and update to global array
 */
void parse(char *line){
    char* data = strtok(line, ",");

    int id = atoi(data);
    double transaction = 0.0;

    data = strtok(NULL, ",");

    while(data != NULL){
        transaction = atof(data);
        balance[id] += transaction;
        data = strtok(NULL, ",");

    }
}

// consumer function
void *consumer(void *arg){

    int thread_num = *((int *) arg);

    if(is_print){
        char buffer[print_buff_size];
        sprintf(buffer, "consumer %d\n", thread_num);        
        writeLineToFile("output/log.txt", buffer);
    }

    free(arg); //free the allocated space for the pointer

    while(1){ //break out of the loop when EOF is found -- break every thread

        pthread_mutex_lock(&lock);

        while (num_items == 0){ //wait for the queue to have at least one element inside of it
            pthread_cond_wait(&cond, &lock);
        }
        
        struct node *temp = tail;
        struct node *before = NULL;
        while(temp -> next != NULL){ //get to the last element in the queue
            before = temp;
            temp = temp -> next;
        }

        if(strcmp(temp -> data, "-1") != 0){
            parse(temp -> data);
            if(is_print){
                char line_buffer[print_buff_size];
                //flush
		        memset(line_buffer,'\0', print_buff_size);
                sprintf(line_buffer, "consumer %d: line %d\n", thread_num, temp->line_number);
                writeLineToFile("output/log.txt", line_buffer);
            }
        }
        
        if(strcmp(temp -> data, "-1") == 0){
            num_items--;
            if(is_print){
                char eof_buffer[print_buff_size];
                //flush
		        memset(eof_buffer,'\0', print_buff_size);
                sprintf(eof_buffer, "consumer %d: line -1\n", thread_num);
                writeLineToFile("output/log.txt", eof_buffer);
            }

            pthread_mutex_unlock(&lock);
            pthread_exit(0);
        } 

        if(num_items == 1){
            temp = NULL;
            free(temp);
        }else{
            before -> next = NULL; //cut the link to the last element (delete the head)
            free(temp);
        }
        
        num_items--;    
        pthread_mutex_unlock(&lock);

        //wait for items to be in bounded buffer
        if(bounded_buffer){
            sem_post(&bounded_buffer_semaphore);
        }   
    }
    
    return NULL; 
}