#ifndef __Combiner_H__
#define __Combiner_H__

// the command line is split, the arguments are then stored into an array
// the array serves to store multiple csv file names
void splitInput(char *argv[], int num_arg, char **csvfiles);

// reades the csv files and combines them into a newfile
void combineFiles(char **csvfiles, char *newfile, int argc);

// returns the pointer of the name of the file being read
char *getFileName(char *file);

#endif
