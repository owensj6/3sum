/*
 * Author: Scott Owens
 * Program: 3Sum
 * Purpose: Object of program is to find all combinations of numbers
 *          in an array where three numbers together add up to zero.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

int** threeSum(int* nums, int numsSize, int* returnSize, int printCombinationsFlag);
void printSolution(int** returnedArrayOfSetsOfThree, int* returnSize, int** returnColumnSizes);
void printSolutionToFile(int** returnedArrayOfSetsOfThree, int* returnSize, int** returnColumnSizes);
long long comb(int n, int r);
long long factorial(int n);

int main(int argc, char* argv[]) {
  printf("Working program.\n");
  int nums[] = { -7, -4, 3, 9, 12, 14, 1, 11, -4 };
  int numsSize = sizeof(nums) / sizeof(nums[0]);
  int* returnSize = malloc(sizeof(int));
  int** returnColumnSizes = malloc(sizeof(int*));
  int** returnedArrayOfSetsOfThree;
  printf("The number of elements you have entered is: %d\n", numsSize);
  if (argc > 2 && strcmp(argv[2], "y") == 0)
    returnedArrayOfSetsOfThree = threeSum(nums, numsSize, returnSize, 1);
  else
    returnedArrayOfSetsOfThree = threeSum(nums, numsSize, returnSize, 0);
  printf("Back from test function.\n");
  // Loop to print out tuples
  if (argc > 1 && strcmp(argv[1], "print") == 0)
    printSolution(returnedArrayOfSetsOfThree, returnSize, returnColumnSizes);
  else if (argc > 1 && strcmp(argv[1], "print_to_file") == 0) {
    printSolutionToFile(returnedArrayOfSetsOfThree, returnSize, returnColumnSizes);
  }
  // Cleanup
  free(returnSize);

  return 0;
}

int** threeSum(int* nums, int numsSize, int* returnSize, int printCombinationsFlag) {
  // R is the sample size you choose from the population. "n choose r".
  const int R = 3;
  int** ptr;

  // Determine the number of combinations
  long long totalNumberOfCombinations = comb(numsSize, R);

  // Create the array of pointers. This array is the total number
  // of combinations possible.
  ptr = malloc(sizeof(int*) * totalNumberOfCombinations);

  // Loop through entire array allocating memory for 4 digit arrays
  for (int i = 0; i < totalNumberOfCombinations; i++) {
    ptr[i] = malloc(sizeof(int) * (R + 1));
  }

  // Now data structure is built. Fill in elements with number combinations
  int iterator = 0;
  int count = 0;
  while (1) {
    for (int i = 0; i < numsSize - 2; ++i) {
      for (int j = i + 1; j < numsSize - 1; ++j) {
        for (int k = j + 1; k < numsSize; ++k) {
          if (nums[i] + nums[j] + nums[k] == 0) {
              ptr[iterator][0] = 1;
              ++count;
          }
          else
              ptr[iterator][0] = 0;
          ptr[iterator][1] = nums[i];
          ptr[iterator][2] = nums[j];
          ptr[iterator][3] = nums[k];
          ++iterator;
          if (printCombinationsFlag)
            printf("[ %d, %d, %d ],\n", nums[i], nums[j], nums[k]);
        }
      }
    }
    break;
  }

  // The data structure is filled with the possible combinations.
  // The arrays satisfying the requirement is marked with a '1'
  // The number of arrays is held by the "count" variable
  *returnSize = count;
  int** returnPtr = malloc(sizeof(int*) * count);
  for (int i = 0; i < count; ++i) {
    returnPtr[i] = malloc(sizeof(int) * R);
  }
  int counter = 0;
  for (int i = 0; i < totalNumberOfCombinations; ++i) {
    if (ptr[i][0] == 1) {
      returnPtr[counter][0] = ptr[i][1];
      returnPtr[counter][1] = ptr[i][2];
      returnPtr[counter][2] = ptr[i][3];
      ++counter;
    }
  }

  // clean up ptr
  for (int i = 0; i < totalNumberOfCombinations; ++i) {
    free(ptr[i]);
  }
  free(ptr);
  return returnPtr;
}

void printSolution(int** returnedArrayOfSetsOfThree, int* returnSize, int** returnColumnSizes) {
  int i, j;
  printf("A solution set is:\n[\n");
  for (i = 0; i < *returnSize; i++) {
    printf("  [ ");
    for (j = 0; j < 3; j++) {
      printf("%d", returnedArrayOfSetsOfThree[i][j]);
      if (j < 2) { printf(", "); }
      else { printf(" "); }
    }
    if (i < *returnSize - 1) { printf("],\n"); }
    else { printf("]\n"); }
  }
  printf("]\n");
}

void printSolutionToFile(int** returnedArrayOfSetsOfThree, int* returnSize, int** returnColumnSizes) {
  int i, j;
  FILE* out = fopen("solution.txt", "w");
  fprintf(out, "A solution set is:\n[\n");
  for (i = 0; i < *returnSize; i++) {
    fprintf(out, "  [ ");
    for (j = 0; j < 3; j++) {
      fprintf(out, "%d", returnedArrayOfSetsOfThree[i][j]);
      if (j < 2) { fprintf(out, ", "); }
      else { fprintf(out, " "); }
    }
    if (i < *returnSize - 1) { fprintf(out, "],\n"); }
    else { fprintf(out, "]\n"); }
  }
  fprintf(out, "]\n");
  fclose(out);
}

long long comb(int n, int r) {
  return factorial(n) / ((factorial(r) * (factorial((n - r)))));
}

long long factorial(int n) {
  if (n == 1) { return 1; }
  return n * factorial(n - 1);
}
