 /*test machine: csel-kh1250-01
 * group number: G38
 * name: Amy Nguyen, Conor Hogan, Turner Gravin
 * x500: nguy2841, hogan386, gravi022 */

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
	
	//Use a counter variable to construct an array of fds to read from
	//Open root directory
	DIR* dir = opendir(path);
	int* read_pipes = (int *)malloc(MAX_ROOT_SUBDIRS);
	int counter = -1;
	int fstat_counter = 0;
	int inodes_visited[MAX_ROOT_SUBDIRS];
	for(int i = 0; i < MAX_ROOT_SUBDIRS; i++){
		inodes_visited[i] = -1;
	} 
	
	// Iterate through root dir and spawn children as neccessary
  struct dirent* entry;
	while ((entry = readdir(dir)) != NULL) {
		if (!strcmp(entry->d_name, ".") || !strcmp(entry->d_name, "..")) continue;

		//Create a child and pipe if the file is directory
		if (entry->d_type == DT_DIR){
			int fds[2];
			int pipe_result = pipe(fds);
			//error
			if(pipe_result < 0){
				fprintf(stderr, "Pipe failure.\n");
				exit(1);
			}
			counter++;
			pid_t child_pid = fork();

			if (child_pid == 0){
				//child pipe I/O STDOUT -> write end of pipe and close ends
				char entry_name[MAX_PATH_LENGTH] = {'\0'};
        snprintf(entry_name, sizeof(entry_name), "%s/%s", path, entry->d_name);
				
				int dupResult = dup2(fds[1], STDOUT_FILENO);
				if(dupResult < 0){
					fprintf(stderr, "Dup2 failed.\n");
					exit(1);
				}

				close(fds[1]);
				close(fds[0]);

				//Exec child
				execl("child", "child", entry_name, pattern, NULL);
				fprintf(stderr, "Error executing execl()\n");
				exit(1);
			}
			//error
			else if (child_pid < 0){
				fprintf(stderr, "Failure creating child process.\n");
				exit(1);
			}
			else{
				//Parent, store array of fds from each pipe created
				close(fds[1]);
				close(STDIN_FILENO);
				dup2(fds[0], STDIN_FILENO);
				read_pipes[counter] = fds[0];
			}
		}
		// if the entry is a symbolic link, do not parse and continue
		else if(entry->d_type == DT_LNK){
			continue;
		}
		//if the entry is a file, parent must print results after searching
		else if(entry->d_type == DT_REG){
			/* Attempt at extra credit, but is not working
	   		char file_path[1024];
			int file_pointer;
			sprintf(file_path, "%s/%s", entry, entry->d_name);
			file_pointer = open(file_path, "r");



			struct stat inode_buffer;
			int fstat_return;
			fstat_return = fstat(file_pointer, &inode_buffer);
			if(fstat_return < 0){
				fprintf(stderr, "fstat error");
				exit(1);
			}

			inodes_visited[fstat_counter] = inode_buffer.st_ino;
			fstat_counter++;
			int inode_visited = 0;

			for(int i; i < fstat_counter; i++){
				if(inode_buffer.st_ino == inodes_visited[i]){
					inode_visited == 1;
				}
			}
			if(inode_visited != 1){ */
				// same format as entry_name for path name
				char new_path[MAX_PATH_LENGTH] = {'\0'};
      			snprintf(new_path, sizeof(new_path), "%s/%s", path, entry->d_name);
				searchPatternInFile(new_path, pattern);
			//}
		}
		else{
			//error: terminate if invalid files are found
			fprintf(stderr, "File is not a directory, symbolic link, or hard link. Terminated.\n");
			exit(1);
		}
  }

	//Wait for all children to complete
	pid_t terminated_pid;
	while(terminated_pid == wait(NULL)) {
		if (terminated_pid < 0){
			fprintf(stderr, "Wait failure.\n");
			exit(1);
		}
	}

  closedir(dir);

	//reading entire buffer from the pipes and printing to terminal
	char read_buffer[MAX_READ_LENGTH];

	for(int i = 0; i < counter+1; i++){
		//debugging line for run4
		memset(read_buffer,'\0', MAX_READ_LENGTH);
		ssize_t count = read(read_pipes[i], read_buffer, MAX_READ_LENGTH);
		if(count == 0){
			continue;
		}
		//error
		else if (count < 0){
			fprintf(stderr, "ERROR: Failed to read\n");
		}
		else{
			printf("%s", read_buffer);
		}
		// close after reading
		close(read_pipes[i]);
	}

	return 0;
}