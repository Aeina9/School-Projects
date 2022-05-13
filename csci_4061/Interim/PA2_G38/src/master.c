#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include "utils.h"



int main(int argc, char** argv){

	if(argc != 3){
		 
		fprintf(stderr,"Usage ./a.out [Path to Directory] [Pattern to search] \n");
		exit(EXIT_FAILURE);
	}
	char* path = argv[1];
	char* pattern = argv[2];
	
	//Declare any other neccessary variables
	//Open root directory
	DIR* dir = opendir(path);
	
	
	// Iterate through root dir and spawn children as neccessary
	// Process each file/directory in the root dir
  struct dirent* entry;
	while ((entry = readdir(dir)) != NULL) {
		if (!strcmp(entry->d_name, ".") || !strcmp(entry->d_name, "..")) continue;

		//Create a child if the file is directory
		if (entry->d_type == DT_DIR){
			pid_t child_pid = fork();

			if (child_pid == 0){
				path = strcat(path, "/");
				path = strcat(path, entry->d_name);
				//Exec child
				execl("child", "child", path, pattern, NULL);
			}
			else if (child_pid < 0){
				printf("Failure creating child process.");
				exit(0);
			}
			else{
				continue;
			}
		}
  }

	//Wait for all children to complete
	pid_t terminated_pid;
	while(terminated_pid == wait(NULL)) {
		if (terminated_pid < 0){
			printf("Wait Failure.\n");
			exit(0);
		}
	}
  closedir(dir);
	
	
	//Assumption : Pipe never gets full
	
	return 0;
}
