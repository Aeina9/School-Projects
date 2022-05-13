 // test machine: csel-kh1250-01
 // group number: G[38]
 // name: Amy Nguyen, Conor Hogan, Turner Gravin
 // x500: nguy2841, hogan386, gravi022 */

#include "myutils.h"

int main(int argc, char *argv[]) {

    if (argc < 2) {
        printf("Less number of arguments.\n");
        printf("./master InputFileName\n");
        fflush(stdout);
        exit(EXIT_FAILURE);
    }

    // Please keep this function call in the main.
    // This function initializes "output" folder
    // by deleting the folder and all its files,
    // and then creating a clean "output" folder.
    bookeepingCode();

    // Parse input file
    FILE * fp;                                                      // File pointer
    char *line = (char *)malloc(sizeof(char) * LineBufferSize);         // Line buffer where a new line is stored
    size_t len = LineBufferSize;                                        // The size of the line buffer
    ssize_t nread;                                                  // Length of a new line read

    char inputFileName[MaxFileNameLength];
    memset(inputFileName, '\0', MaxFileNameLength);
    sprintf(inputFileName, "input/%s", argv[1]);

    if ((fp = getFilePointer(inputFileName)) == NULL) {             // Open a file and return file pointer to the file
        exit(EXIT_FAILURE);
    }

    // Read the number of data and depth
    int nData;
    int depth = 0;
    if((nread = getLineFromFile(fp, line, len)) != -1) {            // Read next line and write it to line buffer
        sscanf(line, "%d %d\n", &nData, &depth);
    }

    // Read degrees of each level
    char strs[50];
    if((nread = getLineFromFile(fp, line, len)) != -1) {            // Read next line and write it to line buffer
        sscanf(line, "%s\n", strs);
    }

    //Degree string
    char d_str[LineBufferSize];
    strcpy(d_str, line);

    int degrees[depth];
    int counter = 0;
    char * pch;
    pch = strtok (line," ");

    while (pch != NULL)
    {
        degrees[counter++] = atoi(pch);
        pch = strtok (NULL, " ");
    }

    // Read input data
    int * input = (int *)malloc(sizeof(int) * nData);
    int aNumber;
    int idxInput = 0;
    while((nread = getLineFromFile(fp, line, len)) != -1) {
        sscanf(line, "%d\n", &aNumber);
        input[idxInput++] = aNumber;
    }

    free(line);
    fclose(fp);

    //Error checking cases
    if(nData == 0){
        printf("ERROR: Assumption violation: N. Data (%d) should be between 1 and 1000.\n", nData);
        exit(EXIT_FAILURE);
    }

    if(depth > 9){
        printf("ERROR: Assumption violation: Depth (%d) is greater than 9.\n", depth);
        exit(EXIT_FAILURE);
    }

    if(degrees[depth-1] > nData && depth != 0){
        printf("ERROR: Assumption violation: N. leaf nodes (%d) is greater than N. Data (5).\n", degrees[depth-1]);
        exit(EXIT_FAILURE);
    }

    for(int i = 0; i < depth; i++){
        if(degrees[i] > 9 || degrees[i] < 1){   
            printf("ERROR: Assumption violation: Degree (%d) of a depth (%d) should be between 1 and 9.\n", degrees[i], i);
            exit(EXIT_FAILURE);
        }
    }

    //Base case: depth = 0, no children 
    if(depth == 0){

        mergeMaster(input, nData);

        FILE *fptr = fopen("output/master.out","w");

        for(int i = 0; i < nData; i++){
            fprintf(fptr, "%d\n", input[i]); 
        }

        fclose(fptr);

        printf("Process [Master] - Merge Sort - Done\n");

        return 0;
    }
    // Spawn child processes and launch childProgram if necessary
    else{
        
        int child_id;
        int p_children = degrees[0];
        int data_size;
        int startIdx;
        int endIdx;

        for (int i = 0; i < p_children; ++i){
            pid_t pid_child = fork();
            if (pid_child == 0){
                child_id = i+1;

                if (i != p_children - 1){
                    data_size = floor(nData/p_children);
                    //floor(M/K)
                    startIdx = data_size * i;
                    endIdx = (startIdx + data_size) - 1;
                }
                else{
                    data_size = (nData - (p_children-1) * floor(nData/p_children));
                    //last child: (M – (K-1) * floor(M/K))
                    startIdx = nData - data_size;
                    endIdx = (startIdx + data_size) - 1;
                }

                //convert arguments into strings
                char c_id[10], s_idx[10], e_idx[10], dt_size[10], nums[10], dep[10], curr_depth[10];
                sprintf(c_id, "%d", child_id);
                sprintf(s_idx, "%d", startIdx);
                sprintf(e_idx, "%d", endIdx);
                sprintf(dt_size, "%d", data_size);
                sprintf(nums, "%d", nData);
                sprintf(dep, "%d", depth);
                sprintf(curr_depth, "%d", 0);

                printf("Parent [master] - Spawn Child [%d, %d, %d, %d, %d]\n", 1, child_id, startIdx, endIdx, data_size);

                execl("childProgram", "childProgram", c_id, s_idx, e_idx, dt_size, nums, dep, curr_depth, inputFileName, d_str, NULL);
                printf("Error executing execl()\n");
                exit(0);
            }
            else if (pid_child == -1){
                printf("Failure creating child process\n");
                exit(0);
            }
        }
    }

    // Wait for all child processes to terminate if necessary
    pid_t terminated_pid;
    if (terminated_pid < 0){
        printf("Wait failure\n");
        exit(0);
    }else{
        while((terminated_pid = wait(NULL)) > 0) {
            continue;
        }
    }

    //call final merge to create master file
    final_merge(degrees);
    printf("Process [master] - Merge Sort - Done\n");

    free(input);
    return EXIT_SUCCESS;
}