# CSV Merger 

This program is designed to merge three or more csv files into one. The merged
file will have the same columns as the original files, with an extra column
titled "filename"

#bugs
The program still creates a new csv file even if "-f" flag not present.

#Example Run
---
$ ./csv_merger ./fixtures/accessories.csv ./fixtures/clothing.csv -f ./fixtures/combined.csv
---



