 // test machine: csel-kh1250-01
 // group number: G[38]
 // name: Amy Nguyen, Conor Hogan, Turner Gravin
 // x500: nguy2841, hogan386, gravi022 */

#include "myutils.h"

int main(int argc, char *argv[]) {

    if (argc < 10) {
        printf("Less number of arguments.\n");
        printf("childProgram childID startIdx endIdx dataSize nData depth currentDepth inputFileName, degreeString\n");
        fflush(stdout);
        exit(EXIT_FAILURE);
    }

    int child_ID = atoi(argv[1]);
    int startIdx = atoi(argv[2]);
    int endIdx = atoi(argv[3]);
    int data_size = atoi(argv[4]);
    int nData = atoi(argv[5]);
    int depth = atoi(argv[6]);
    int curr_depth = atoi(argv[7]);
    char* inputFileName = argv[8];
    char* d_str = argv[9];
    
    //make copy d_str to d_str2 so the it can be parsed to make degrees[] while keeping original d_str
    char d_str2[LineBufferSize];
    strcpy(d_str2, d_str);

    int degrees[depth];
    int counter = 0;
    char * pch;
    pch = strtok (d_str2," ");

    while (pch != NULL)
    {
        degrees[counter++] = atoi(pch);
        pch = strtok (NULL, " ");
    }

    // Opening input file
    FILE *fp_r;
    fp_r = fopen(inputFileName, "r");
    
    //putting input from file into an array-- Line 2 = degree string; Lines after 2 are inputs
    char buff[20];
    int line_num = 1;
    int input[nData]; 
    int i = 0;

    while(fgets(buff, 20, fp_r)!= NULL){
        if (line_num > 2) {
            input[i] = atoi(buff);
            ++i;
        }
        else{
            ++line_num;
        }
    }

    curr_depth +=1;

    //For recursed internal nodes
    int new_startIdx = startIdx;
    int new_endIdx = endIdx;
    int new_nData = data_size;
    int curr_ID;
        
    //Start and end Index computation
    if (curr_depth != depth){
        int children_tobe_made = degrees[curr_depth];
        for (int i = 0; i < children_tobe_made; ++i){
            pid_t pid_child = fork();
            if (pid_child == 0){
                curr_ID = child_ID;
                child_ID = (child_ID * 10) + i + 1;

                if (i != children_tobe_made - 1){
                    data_size = floor(new_nData/children_tobe_made);
                    //floor(M/K)
                    new_startIdx = startIdx + (data_size * i);
                    new_endIdx = (new_startIdx + data_size) - 1;
                }
               else{
                    data_size = (new_nData - (children_tobe_made-1) * floor(new_nData/children_tobe_made));
                    //last child: (M – (K-1) * floor(M/K))
                    new_startIdx = startIdx + (new_nData - data_size);
                    new_endIdx = (new_startIdx + data_size) - 1;
                }
 
                char c_id[10], s_idx[10], e_idx[10], dt_size[10], nums[10], dep[10], c_depth[10];
                sprintf(c_id, "%d", child_ID);
                sprintf(s_idx, "%d", new_startIdx);
                sprintf(e_idx, "%d", new_endIdx);
                sprintf(dt_size, "%d", data_size);
                sprintf(nums, "%d", nData);
                sprintf(dep, "%d", depth);
                sprintf(c_depth, "%d", curr_depth);

                printf("Parent [%d] - Spawn Child [%d, %d, %d, %d, %d]\n", curr_ID, curr_depth + 1, child_ID, new_startIdx, new_endIdx, data_size);

                execl("childProgram", "childProgram", c_id, s_idx, e_idx, dt_size, nums, dep, c_depth, inputFileName, d_str, NULL);
                printf("Error executing execl()\n");
                exit(0);
            }
            else if (pid_child == -1){
                printf("Failure creating child process\n");
                exit(0);
            }
        }
    }

    // Create the child_ID.out file
    char output_name[20];
    sprintf(output_name, "%s%d%s\n", "output/", child_ID, ".out" );

    FILE* fp_w = fopen(output_name, "w");

    //Start multi-way merges
    if(curr_depth == depth){
        mergeSort(input, new_startIdx, new_endIdx); //sort the leaf nodes

        for(int i = 0; i < data_size; i++){ //write the data to corresponding files
            fprintf(fp_w, "%d\n", input[new_startIdx+i]); 
        }
        printf("Process [%d] - Leaf Node Merge Sort - Done\n", child_ID);
    }else{
        
        pid_t terminated_pid;
        if (terminated_pid < 0){
            printf("Wait failure\n");
            exit(0);
        }else{
            while((terminated_pid = wait(NULL)) > 0) {
                continue;
            }
        }

        //call merge for intermidiate files
        inter_merge(degrees, fp_w, child_ID, curr_depth); //merges files below it and adds the sorted data to the current file
        printf("Process [%d] - Merge Sort - Done\n", child_ID);
    }

    fclose(fp_w);
    return EXIT_SUCCESS;
}
