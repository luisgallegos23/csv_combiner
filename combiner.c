#include "combiner.h"

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXCHAR 512

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
  bool first_line = true;
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
    FILE *curr_f = fopen(current_file, "r");
    // ends program if invalid input file
    if (!curr_f) {
      perror("Invalid Input File");
      exit(0);
    }
    strncpy(cpy_file, current_file, strlen(current_file));
    ptr = getFileName(cpy_file);
    fgets(line, MAXCHAR, curr_f); // reads the heading line
    if (first_line) {
      removeChar(line);
      fprintf(new_f, "%s%c\"%s\"\n", line, ',', "filename");
      first_line = false;
    }
    // reads each line form in the file from second to end
    while (fgets(line, MAXCHAR, curr_f)) {
      removeChar(line);
      fprintf(new_f, "%s%c\"%s\"\n", line, ',', ptr);
    }
    fclose(curr_f);
    free(cpy_file);
    index++;
  }
  fclose(new_f);
}

// returns the name of the file
char *getFileName(char *file) {
  char *token, *ptr;
  token = strtok(file, "/");
  if (!token) {
    ptr = file;
    return ptr;
  }
  while (token) {
    ptr = token;
    token = strtok(NULL, "/");
  }
  return ptr;
}

// removes invalid characters
void removeChar(char *line) {
  int index = 0;
  while (line[index]) {
    if (line[index] == '\r' || line[index] == '\n') {
      line[index] = '\0';
    }
    index++;
  }
}
