#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "wordparse.h"

int main(int argc, char *argv[]) {

	FILE *file_input;

	char **word_arr;
	alloc_mem_2D(&word_arr);

	/* Argument Handling Section*/
	if (argc < 3) { // expect at least an output file and file_input file.
		printf("Error: Too Few Arguments\n");
		exit(EXIT_FAILURE);
	}
	else {
		for (int i = 2; i < argc; i++) {
			file_input = fopen(argv[i], "r"); // argv[0] is program name argv[1] is the start of arguments
			if (!file_input) {
				printf("Error: Unable To Open File\n");
				exit(EXIT_FAILURE);
			}
			int word_cnt = textToSubstrings(file_input, &word_arr);
			for (int i = 0; i < word_cnt; i++) {
				printf("%s\n", word_arr[i]);
			}
			//fclose(file_input);
		}
	}
}