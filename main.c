#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "combiner.h"

/* Program is designed to merge two or more CSV Files ONLY
 * the command line program should be structured in this way:
 * "./csv_combiner file1 file2 ... -f mergedfile" */

int main(int argc, char **argv) {
  char *csvfiles[argc - 3], *new_file;
  if (strcmp(argv[argc - 2], "-f") != 0) { // required flag
    bool invalid_flag = false;
    assert(invalid_flag);
  }
  new_file = argv[argc - 1];
  splitInput(argv, argc, csvfiles);
  combineFiles(csvfiles, new_file, argc);
  return 0;
}
