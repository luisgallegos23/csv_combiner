#include "combiner.h"
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool testFiles(char **csvfiles, int size) {
  int check;
  bool pass_t;
  check =
      strncmp(csvfiles[0], "./tests/clothing_test.csv", strlen(csvfiles[0]));
  pass_t = (check == 0) ? false : true;
  printf("File1 Passed: ");
  printf("%s\n", pass_t ? "true" : "false");
  assert(pass_t);
  check =
      strncmp(csvfiles[1], "./tests/accessories_test.csv", strlen(csvfiles[1]));
  pass_t = (check == 0) ? false : true;
  printf("File2 : Pass");
  printf("%s\n", pass_t ? "true" : "false");
  assert(pass_t);
  return true;
}
bool testFileName(char **csvfiles) {
  char *ptr;
  int check;
  bool pass_t;
  ptr = getFileName(csvfiles[0]);
  check = strncmp(ptr, "clothing_test.csv", strlen(ptr));
  pass_t = (check == 0) ? false : true;
  printf("Filename1 Passed: ");
  printf("%s\n", pass_t ? "true" : "false");
  assert(pass_t);
  ptr = getFileName(csvfiles[1]);
  check = strncmp(ptr, "accessories_test.csv", strlen(ptr));
  pass_t = (check == 0) ? false : true;
  printf("Filename2 Passed: ");
  printf("%s\n", pass_t ? "true" : "false");
  assert(pass_t);
  return true;
}

int main() {
  char *csvfiles;
  int argc = 5;
}
