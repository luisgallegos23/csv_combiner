#include <stdio.h>
#include <stdlib.h>

#include "combiner.h"
int main(int argc, char **argv) {
  char *csvfiles[argc - 3], *new_file;
  new_file = argv[argc - 1];
  splitInput(argv, argc, csvfiles);
  combineFiles(csvfiles, new_file, argc);
  return 0;
}
