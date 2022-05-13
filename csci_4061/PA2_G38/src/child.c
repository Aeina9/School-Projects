 /*test machine: csel-kh1250-01
 * group number: G38
 * name: Amy Nguyen, Conor Hogan, Turner Gravin
 * x500: nguy2841, hogan386, gravi022 */

#include<stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include<sys/wait.h>
#include <unistd.h>
#include <dirent.h>
#include<string.h>
#include<stdlib.h>
#include "utils.h"

/*
	Traverse the directory recursively and search for pattern in files.
	@params:
		name - path to the directory
		pattern - pattern to be recusrively searched in the directory
		
	Note: Feel free to modify the function header if neccessary
	
*/
void dirTraverse(char *name, char * pattern)
{
	DIR* dir = opendir(name);
	struct dirent *entry;

	while ((entry = readdir(dir)) != NULL) {
		if (!strcmp(entry->d_name, ".") || !strcmp(entry->d_name, "..")) continue;

		char entry_name[MAX_PATH_LENGTH] = {'\0'};
    snprintf(entry_name, sizeof(entry_name), "%s/%s", name, entry->d_name);
		
		if (entry->d_type == DT_DIR){
			//iterate until hard link
			dirTraverse(entry_name, pattern);
		}
		else if(entry->d_type == DT_LNK){
			//ignore symbolic links
			continue;
		}
		else if(entry->d_type == DT_REG){
			//send hard links to be searched
			searchPatternInFile(entry_name, pattern);
		}
		else{
			//terminate if invalid files are found
			fprintf(stderr, "File is not a directory, symbolic link, or hard link. Terminated.\n");
			exit(1);
		}
	}
}

int main(int argc, char** argv){

	if(argc !=3){
	
		fprintf(stderr,"Child process : %d recieved %d arguments, expected 3 \n",getpid(), argc);
		fprintf(stderr,"Usage child.o [Directory Path] [Pattern] \n");
		exit(EXIT_FAILURE);
	}
	
	char* path = argv[1];
	char* pattern = argv[2];
	
	close(STDIN_FILENO);

	//begin looking through top level directories
	dirTraverse(path, pattern);
	
	close(STDOUT_FILENO);
	exit(EXIT_SUCCESS);
}