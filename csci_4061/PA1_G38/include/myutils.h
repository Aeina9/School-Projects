#ifndef MYUTILS_H
#define MYUTILS_H

#include "utils.h"
#define debug 0

// You can modify these functions as you need

/**
 * Print all elements in the array (space separation)
 *
 * @param arr   integer array
 * @param line  size of elements in the array
 * @return None
 */
void printArray(int arr[], int size);

/**
 * Write sorted numbers to a file
 *
 * @param myID  process's ID which is a part of output filename
 * @param arr   integer array storing sorted numbers
 * @param size  size of element in the array
 * @return None
 */
void writeSortedResultToFile(char* myID, int arr[], int size);

/**
 * Helper function to merge two sorted array into one sorted array
 * 
 * @param array array being sorted, within array must have two sorted lists
 * @param l the left bound of the array being merged
 * @param m the middle of the array being merged. Usually (l+r)/2
 * @param r the right bound of the array being merged
 * @return None
 */
void merge_helper(int array[], int l, int m, int r);

/**
* MergeSort algorithm to apply traditional merge sort process to an array
*
* @param array the array being sorted
* @param l left bound of array being put through merge sort process
* @param r right bound of array being put through merge sort process
* @return None
*/
void mergeSort(int array[], int l, int r);

/**
 * Master funciton to handle leaf sorting algorithm
 * 
 * @param array the array being sorted
 * @param array_size the number of elements within the array
 * @return None
 */

void mergeMaster(int array[], int array_size);


void final_merge(int degrees[]);
void inter_merge(int degrees[], FILE* fp_w, int id, int curr_depth);

#endif //MYUTILS_H
