#include "combiner.h"

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXCHAR 1000
// the command line is split, the arguments are then stored into an array
// the array serves to store multiple csv file names
void splitInput(char **argv, int argc, char **csvfiles) {
  int index = 0;
  for (int x = 1; x < argc - 2; x++) {
    csvfiles[index] = argv[x];
    index++;
  }
}

// reades the csv files and combines them into a newfile
void combineFiles(char **csvfiles, char *newfile, int size) {
  FILE *new_f = fopen(newfile, "w+");
  if (!new_f) {
    perror("Invalid Merge File");
    exit(0);
  }
  int index = 0;
  while (index < size - 3) {
    char line[MAXCHAR], *ptr, *cpy_file, *current_file;
    current_file = csvfiles[index];
    cpy_file = calloc(200, sizeof(char));
    assert(cpy_file);
    ptr = malloc(sizeof(char *));
    FILE *curr_f = fopen(current_file, "r");
    // ends program if invalid input file
    if (!curr_f) {
      perror("Invalid Input File");
      exit(0);
    }
    strncpy(cpy_file, current_file, strlen(current_file));
    getFileName(ptr, cpy_file);
    printf("file: %s\n", ptr);
    // reads each line form the file until end
    while (feof(curr_f) != true) {
      fgets(line, MAXCHAR, curr_f);
      fputs(line, new_f); // fix
      // fprintf(new_f, "%s,%s", line, ptr);
      printf("%s\n", line);
    }
    fclose(curr_f);
    free(ptr);
    free(cpy_file);
    index++;
  }
  fclose(new_f);
}

void getFileName(char *ptr, char *file) {
  char *token;
  token = strtok(file, "/");
  if (!token) {
    ptr = file;
    return;
  }
  while (token) {
    ptr = token;
    printf("ptr: %s\n", ptr);
    token = strtok(NULL, "/");
  }
  printf("file#: %s\n", ptr);
}
