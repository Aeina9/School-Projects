 // test machine: csel-kh1250-01
 // group number: G[38]
 // name: Amy Nguyen, Conor Hogan, Turner Gravin
 // x500: nguy2841, hogan386, gravi022 */
 
#include "myutils.h"

void printArray(int arr[], int size) {
    int i;
    for (i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

void writeSortedResultToFile(char* myID, int arr[], int size) {
    char line[WriteBufferSize];
    char filepath[MaxFileNameLength];
    memset(line, '\0', WriteBufferSize);
    memset(filepath, '\0', MaxFileNameLength);
    sprintf(filepath, "output/%s.out", myID);

    int i;
    int idx = 0;
    idx += sprintf(&line[idx], "%d\n", size);
    for (i = 0; i < size; i++) {
        idx += sprintf(&line[idx], "%d\n", arr[i]);
    }
    writeLineToFile(filepath, line);                // Write data in the write buffer to the file
}

void merge_helper(int array[], int l, int m, int r){
    int left_array_indexes = m-l+1;
    int right_array_indexes = r-m;

    int left[left_array_indexes];
    int right[right_array_indexes];

    //Creating sub arrays
    for(int i = 0; i < left_array_indexes; i++){
        left[i] = array[l+i];
    }

    for(int j = 0; j < right_array_indexes; j++){
        right[j] = array[m+1+j];
    }

    int i = 0; //Left array index
    int j = 0; //Right array index
    int k = l; //Merged array index

    while(i < left_array_indexes && j < right_array_indexes){
        if(left[i] < right[j]){
            array[k] = left[i];
            i++;
        }
        else{
            array[k] = right[j];
            j++;
        }
        k++;
    }

    //Autofilling array with left array if right array is emptied first
    while(i < left_array_indexes){
        array[k] = left[i];
        i++;
        k++;
    }

    //Autofilling array with right array if left array is emptied first
    while(j < right_array_indexes){
        array[k] = right[j];
        j++;
        k++;
    }

}

void mergeSort(int array[], int l, int r){
    if(l<r){
        int m = (l+r)/2;
        mergeSort(array, l, m);
        mergeSort(array, m+1, r);
        merge_helper(array, l, m, r);
    }
}

void mergeMaster(int array[], int array_size){
    mergeSort(array, 0, array_size-1);
}


// Multiway Merge Sort with multiple data streams from intermediate files
// Final merge with level 1 children
void final_merge(int degrees[]) {
    
    char last_number = degrees[0] + '0';
    char last_number_string[] = {last_number, '\0'};
    char last_output_p[] = "output/";
    char last_out_p[] = ".out";
    strcat(last_output_p, last_number_string);
    strcat(last_output_p, last_out_p);
    
    
    char last_file_name[20];
    sprintf(last_file_name, "%s%d%s\n", "output/", degrees[0], ".out");
    FILE * lastFile = fopen(last_file_name, "r");

    //error check
    if(lastFile == NULL){
        printf("Failed to open file.\n");
        exit(0);
    }

    char* currentLine[5];
    char *line_ = (char *)malloc(sizeof(char) * LineBufferSize);         
    size_t len_ = LineBufferSize;                                        
    ssize_t nread_;
    int counter_ = 0;  
    while((nread_ = getLineFromFile(lastFile, line_, len_)) > 0){
        counter_ +=1;
    }
    fclose(lastFile);

    int sub_file_array[degrees[0]][counter_];

    //open parent's children files
    for(int i = 0; i < degrees[0]; i++){
        char current_file_name[20];
        sprintf(current_file_name, "%s%d%s\n", "output/", i+1, ".out");
        lastFile = fopen(current_file_name, "r");
        if(lastFile == NULL){
            printf("Failed to open file within for loop\n");
            exit(0);
        }
        int index = 0;
        while((nread_ = getLineFromFile(lastFile, line_, len_)) > 0){
            sub_file_array[i][index] = atoi(line_);
            index++;
        }
        while(index < counter_){
            sub_file_array[i][index] = -1;
            index++;
        }
        fclose(lastFile);
    }

    int currentValues[degrees[0]];
    for(int i = 0; i < degrees[0]; i++){
        currentValues[i] = 0;
    }

    FILE * master_file = fopen("output/master.out", "w");
    int stillValues = 1;
    int minimum;

    //write to master.out
    while(stillValues == 1){
        minimum = -1;
        int minimum_index = 0;
        for(int i = 0; i < degrees[0]; i++){
            if(currentValues[i]<counter_ && sub_file_array[i][currentValues[i]] != -1){
                if(sub_file_array[i][currentValues[i]] < minimum || minimum == -1){
                    minimum = sub_file_array[i][currentValues[i]];
                    minimum_index = i;
                }
            }
        }
        if(minimum == -1){
            stillValues = 0;
        }
        else{
            fprintf(master_file, "%d\n", sub_file_array[minimum_index][currentValues[minimum_index]]);
            currentValues[minimum_index]++;
        }

    }
    free(line_);
    fclose(master_file);

}

//Merge intermediate files
void inter_merge(int degrees[], FILE* fp_w, int curr_id, int curr_depth) {

    char last_number = degrees[curr_depth] + '0';
    char last_number_string[] = {last_number, '\0'};
    char last_output_p[] = "output/";
    char last_out_p[] = ".out";
    strcat(last_output_p, last_number_string);
    strcat(last_output_p, last_out_p);
   
    char last_file_name[20];
    int num = ((curr_id * 10) + 1) + (degrees[curr_depth] - 1);
    sprintf(last_file_name, "%s%d%s\n", "output/", num, ".out");
    
    FILE * lastFile = fopen(last_file_name, "r");
    
    //error check
    if(lastFile == NULL){
        printf("Failed to open file.\n");
        exit(0);
    }

    char* currentLine[5];
    char *line_ = (char *)malloc(sizeof(char) * LineBufferSize);         
    size_t len_ = LineBufferSize;                                        
    ssize_t nread_;
    int counter_ = 0;  
    while((nread_ = getLineFromFile(lastFile, line_, len_)) > 0){
        counter_ +=1;
    }
    fclose(lastFile);

    int sub_file_array[degrees[curr_depth]][counter_];

    //open parent's children files
    for(int i = 0; i < degrees[curr_depth]; i++){
        char current_file_name[20];
        sprintf(current_file_name, "%s%d%s\n", "output/", (curr_id*10) + i + 1, ".out");
        
        lastFile = fopen(current_file_name, "r");
        if(lastFile == NULL){
            printf("Failed to open file within for loop\n");
            exit(0);
        }
        int index = 0;
        while((nread_ = getLineFromFile(lastFile, line_, len_)) > 0){
            sub_file_array[i][index] = atoi(line_);
            index++;
        }
        while(index < counter_){
            sub_file_array[i][index] = -1;
            index++;
        }
        fclose(lastFile);
    }

    int currentValues[degrees[curr_depth]];
    for(int i = 0; i < degrees[curr_depth]; i++){
        currentValues[i] = 0;
    }

    int stillValues = 1;
    int minimum;

    //write to parent file
    while(stillValues == 1){
        minimum = -1;
        int minimum_index = 0;
        for(int i = 0; i < degrees[curr_depth]; i++){
            if(currentValues[i]<counter_ && sub_file_array[i][currentValues[i]] != -1){
                if(sub_file_array[i][currentValues[i]] < minimum || minimum == -1){
                    minimum = sub_file_array[i][currentValues[i]];
                    minimum_index = i;
                }
            }
        }
        if(minimum == -1){
            stillValues = 0;
        }
        else{
            fprintf(fp_w, "%d\n", sub_file_array[minimum_index][currentValues[minimum_index]]);
            currentValues[minimum_index]++;
        }

    }
    free(line_);

}
