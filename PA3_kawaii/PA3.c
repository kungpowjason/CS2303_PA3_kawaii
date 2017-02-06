#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include <string.h>
#include "timestamp.h"
#include "wordparse.h"
#include "AVLTree.h"
//#include "tree.h"

int main(int argc, char *argv[]) {

	FILE *file_input; // declare file pointer
	FILE *file_output; // declare file pointer

	char **word_arr; // declare 2D pointer bin
	struct tnode *proot = NULL;
	int word_cnt = 0;

	struct timeval start_time; // time stamps for start and end of sorting
	struct timeval end_time;
	struct timeval job_time; // Elapsed time while doing the job

	alloc_mem_2D(&word_arr); // allocate memory for word_arr

	/* Argument Handling Section*/
	if (argc < 3) { // expect at least an output file and file_input file.
		printf("Error: Too Few Arguments\n");
		exit(EXIT_FAILURE);
	} else {
		// argument format:
		// program(0) outputfile(1) inputfile(2) ...
		// file input starts at index 2.
		for (int i = 2; i < argc; i++) {
			file_input = fopen(argv[i], "r"); // argv[0] is program name argv[1] is the start of arguments
			if (!file_input) { // error handling for file unable to be open
				printf("Error: Unable To Open File\n");
				exit(EXIT_FAILURE);
			}
			// split text file into substrings and puts into word_arr
			// word_cnt is the returned number of words found.
			word_cnt = textToSubstrings(file_input, word_arr);
			// print all the words found.
			fclose(file_input);
		}
	}
	// adds all the words into a binary tree
	gettimeofday(&start_time, NULL); // Get timestamp at start
	for (int i = 0; i < word_cnt; i++) {
		proot = addWord(word_arr[i], proot);
	}
	gettimeofday(&end_time, NULL); // Get timestamp at end
	printTree(proot);
	file_output = fopen(argv[1], "w");
	// print tree
	if (!file_output) {
		printf("Error: Unable To Open File\n");
		exit(EXIT_FAILURE);
	} else {
		writeOutFileTree(proot, file_output);
	}
	printf("--------------------------------\n");
	printf("%10d Distinct words\n", numNodes(proot, 0));
	printf("%10d Total words counted (including duplicates)\n\n", word_cnt);
	fprintf(file_output, "--------------------------------\n");
	fprintf(file_output, "%10d Distinct words\n", numNodes(proot, 0));
	fprintf(file_output, "%10d Total words counted (including duplicates)\n\n", word_cnt);
	fclose(file_output);

	/** PRINT TIME STAMP INFORMATION **/

	printf("Timestamp before: ");
	print_timeval(start_time);
	printf("Timestamp after: ");
	print_timeval(end_time);

	/* This next line fills in the fields of a timeval struct
	 with the difference between the two timestamps. */
	job_time = timediff(start_time, end_time);
	printf("Time difference: ");
	print_timeval(job_time);

	freeTree(proot);
	proot = NULL;
}

