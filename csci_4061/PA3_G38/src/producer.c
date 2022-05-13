#include "producer.h"

/**
 *
 * Producer thread will read from the file and write data to 
 * the end of the shared queue
 */



void *producer(void *path_arg){

    if(is_print){
        char buffer[print_buff_size];
        strcpy(buffer, "Producer\n");
        writeLineToFile("output/log.txt", buffer);
    }
    

    char *path = (char*)path_arg; //get the file path
    int counter = 0;

    FILE * fp;
    fp = fopen(path, "r"); //open file
    if (fp == NULL){
		fprintf(stderr,"Error opening file: %s\n", path);
		return NULL;
	}

    char temp[1000];

    while(getLineFromFile(fp, temp, 1000) != -1){  //read its content line by line

        //wait if bounded buffer is full
        if(bounded_buffer){
            sem_wait(&bounded_buffer_semaphore);
        }

        pthread_mutex_lock(&lock);

        if(num_items == 0){         //if nothing is present in the queue
            tail = malloc(sizeof(struct node)); 
            strcpy(tail -> data, temp);
            tail->line_number = counter;
        }
        else{
            struct node *new_tail = malloc(sizeof(struct node)); 
            strcpy(new_tail -> data, temp);
            new_tail -> next = tail;
            new_tail->line_number = counter;
            tail = new_tail;
            
        }

        if(is_print){
            char buffer[print_buff_size];
            //flush
		    memset(buffer,'\0', print_buff_size);
            sprintf(buffer, "producer: line %d\n", counter);
            writeLineToFile("output/log.txt", buffer);
        }
        
        counter++;
        num_items++;
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&lock);
    }

    //When reaching the end of the file, send EOF message for however many consumer threads there are
    for(int i = 0; i < num_consumers; i++){
        
        pthread_mutex_lock(&lock);
        if(num_items == 0){
            tail = malloc(sizeof(struct node)); 
            strcpy(tail -> data, "-1");
            if(is_print){
                char eof_buffer[print_buff_size];
                //flush
		        memset(eof_buffer,'\0', print_buff_size);
                sprintf(eof_buffer, "producer: -1\n");
                writeLineToFile("output/log.txt", eof_buffer);
            }
            
        }else{
            struct node *new_tail = malloc(sizeof(struct node));
            strcpy(new_tail -> data, "-1");
            new_tail -> next = tail;
            tail = new_tail;


            if(is_print){
                char eof_buffer[print_buff_size];
                //flush
		        memset(eof_buffer,'\0', print_buff_size);
                sprintf(eof_buffer, "producer: -1\n");
                writeLineToFile("output/log.txt", eof_buffer);
            }     
        }
        num_items++;

        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&lock);
    }
    
    // cleanup and exit
    fclose(fp);
    return NULL; 
}