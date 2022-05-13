#ifndef UTILS_H
#define UTILS_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <semaphore.h>

#define chunkSize 1024
#define acctsNum 1000

//arbitrary max length of a printed line
#define print_buff_size 50

extern pthread_mutex_t lock;
extern pthread_cond_t cond;
sem_t bounded_buffer_semaphore;

int num_items;
int num_consumers;
bool is_print;
bool bounded_buffer;

struct node { //defines a node for the queue
    char data[1000];
    struct node* next;
    int line_number;
};


struct node* head;
struct node* tail;

/* shared array definition */
extern double balance[acctsNum];

/* file I/O */
/**
 * Get a pointer to a opened file based on the file name
 * @param *inputFileName  the file path
 * @return a file pointer pointing to the file
 */
FILE * getFilePointer(char *inputFileName);

/**
 * Read an entire line from a file
 * @param  *fp    the file to be read
 * @param  *line  contain the line content
 * @param  len    the size of the line
 * @return the number of character reads (including the newline \n, but not including terminator)
           -1 when reaching the end of file or error occurs
 */
ssize_t getLineFromFile(FILE *fp, char *line, size_t len);

/**
 * Open a file, and write a line to the file
 * @param *filepath  the file path
 * @param *line      the line content
 */
void writeLineToFile(char *filepath, char *line);

/* directory */
void bookeepingCode();

#endif