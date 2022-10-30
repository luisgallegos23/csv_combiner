#include "combiner.h"
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXCHAR 512

/* Test file is designed to test the main.c program
 * this test only uses TWO small csv files,
 * file can be edited to test using bigger files*/

/* Function tests splitInput() allocates files to ptr csvfiles
 * returns true once both tests pass, breaks program if eather one or the other
 * fails*/
bool testFiles(char **csvfiles) {
  int check;
  bool pass_t;
  check =
      strncmp(csvfiles[0], "./tests/clothing_test.csv", strlen(csvfiles[0]));
  pass_t = (check == 0) ? true : false;
  printf("File1 Passed: ");
  printf("%s\n", pass_t ? "true" : "false");
  assert(pass_t);
  check =
      strncmp(csvfiles[1], "./tests/accessories_test.csv", strlen(csvfiles[1]));
  pass_t = (check == 0) ? true : false;
  printf("File2 Passed: ");
  printf("%s\n", pass_t ? "true" : "false");
  assert(pass_t);
  return true;
}

/* Function test weather getFileName()
 * the return value to ptr should be the name of the file ONLY
 * ptr should not have any '/' and not be the path to file
 * returns true if passed, breaks program if eather test fails*/
bool testFileName(char **csvfiles) {
  char *ptr, cpy1[MAXCHAR], cpy2[MAXCHAR];
  int check;
  bool pass_t;
  strcpy(cpy1, csvfiles[0]);
  strcpy(cpy2, csvfiles[1]);
  ptr = getFileName(cpy1);
  check = strncmp(ptr, "clothing_test.csv", strlen(ptr));
  pass_t = (check == 0) ? true : false;
  printf("Filename1 Passed: ");
  printf("%s\n", pass_t ? "true" : "false");
  assert(pass_t);
  ptr = getFileName(cpy2);
  check = strncmp(ptr, "accessories_test.csv", strlen(ptr));
  pass_t = (check == 0) ? true : false;
  printf("Filename2 Passed: ");
  printf("%s\n", pass_t ? "true" : "false");
  assert(pass_t);
  return true;
}

/*Function test weather the lines in the merge file are correct
 * compares a line from the merged file to line in a valid test file
 * compares character by character
 * returns true if passed, breaks program if test fails*/
bool checkLines(char *line, char *valid) {
  int check = 1;
  int index = 0;
  while (index <= strlen(valid)) {
    if (line[index] == '\0' && valid[index] == '\0') {
      check = 0;
      break;
    }
    index++;
  }
  bool pass_t;
  // check = strncmp(line, valid, strlen(valid));
  pass_t = (check == 0) ? true : false;
  printf("Line Passed: ");
  printf("%s\n", pass_t ? "true" : "false");
  assert(pass_t);
  return true;
}

/* function inteded to create a array of pointers
 * intended to simulate the **argv paramter in mian.c */
void tokenString(char *command, char **argv) {
  char *token;
  int index = 0;
  token = strtok(command, " ");
  while (token) {
    argv[index] = token;
    token = strtok(NULL, " ");
    index++;
  }
}

/* Test the functions in combiner.c  */
int main(int argc, char **argv) {
  int size = 5;
  char *csvfiles[2], *split[size], command[MAXCHAR];
  memset(command, 0, MAXCHAR);
  strcpy(command, "./csv_combiner ./tests/clothing_test.csv "
                  "./tests/accessories_test.csv -f ./tests/combined_test.csv");
  tokenString(command, split);
  splitInput(split, size, csvfiles);
  testFiles(csvfiles); // splitInput changes the original
  testFileName(csvfiles);
  char filename[MAXCHAR], testfile[MAXCHAR];
  memset(filename, 0, MAXCHAR);
  strcpy(filename, "./tests/combined_test.csv");
  strcpy(testfile, "./tests/output_test.csv");
  combineFiles(csvfiles, filename, size);
  FILE *merged_f = fopen(filename, "r");
  FILE *test_f = fopen(testfile, "r");
  char line[MAXCHAR], valid[MAXCHAR];
  // Reads the two files line by line
  while (feof(test_f) != true) {
    memset(line, 0,
           MAXCHAR); // sets the array to null before allocating new line
    memset(valid, 0, MAXCHAR);
    fgets(line, MAXCHAR, merged_f);
    fgets(valid, MAXCHAR, test_f);
    removeChar(valid); // helps check that the removeChar() function
    removeChar(line);  // properly replaces the cariage return and/or new line
                       // char to '\0'
    checkLines(line, valid);
  }
  fclose(merged_f);
  fclose(test_f);
  printf("Passed all Tests.\n");
  return 1;
}
