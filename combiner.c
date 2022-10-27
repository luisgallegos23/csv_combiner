#include "combiner.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXCHAR 1000
// the command line is split, the arguments are then stored into an array
// the array serves to store multiple csv file names
void splitInput(char **commandline, int num_arg, char **csvfiles) {
  int index = 0;
  for (int x = 1; x < (num_arg - 2); x++) {
    csvfiles[index] = commandline[x];
    printf("%s", commandline[x]);
  }
}

// reades the csv files and combines them into a newfile
void combineFiles(char **csvfiles, char *newfile) {
  FILE *new_f = fopen(newfile, "w+");
  if (new_f == NULL) {
    printf("%s: Invalid FIle", newfile);
    exit(1);
  }
  int index = 0;
  while (csvfiles[index]) {
    FILE *curr_f = fopen(csvfiles[index], "a+");
    if (curr_f == NULL) {
      printf("%s: Invalid FIle", csvfiles[index]);
      exit(1);
    }
    char line[MAXCHAR];
    while (fgets(line, MAXCHAR, curr_f)) {
      printf("%s", line);
    }
    fclose(curr_f);
    index++;
  }
  fclose(new_f);
}

int main(int argc, char *argv[]) {
  char *csvfiles[50];
  splitInput(argv, argc, csvfiles);
  combineFiles(csvfiles, argv[argc - 1]);
  return 0;
}
