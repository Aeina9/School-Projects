 /*test machine: csel-kh1250-01
 * group number: G38
 * name: Amy Nguyen, Conor Hogan, Turner Gravin
 * x500: nguy2841, hogan386, gravi022 */

#include<stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include<string.h>
#include "utils.h"


/*
	Searches for pattern in file and writes the entire line containing the pattern to STDOUT
	Format for print: [path to file] : Line in the file
	@Params:
		path - path to the file
		pattern : pattern to be searched
*/
void searchPatternInFile(char* path, char* pattern){
	FILE * fp;

	fp = fopen(path, "r");
	if (fp == NULL){
		fprintf(stderr,"Error opening file: %s\n", path);
		return;
	}

	//Read file line by line. If pattern exists print to STDOUT
	char buff[MAX_READ_LENGTH];	
	while(fgets(buff, MAX_READ_LENGTH, fp)){
		if (strstr(buff, pattern) != NULL){

			char line[strlen(buff) + strlen(path) + 1];
			sprintf(line, "%s:%s", path, buff);
      int line_written = write(STDOUT_FILENO, line, strlen(line));

			//error
			if (line_written < 0) {
				fprintf(stderr, "ERROR: Failed to write\n");
			}
		}
	}
	//Close fp
	fclose(fp);
}
