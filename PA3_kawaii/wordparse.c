
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "wordparse.h"
/**
 * @name textToSubstrings
 * @brief Splits up the words inside of a text file and stores in an array.
 *
 * First splits up the words by "whitespaces" such as " \n\t\v\r\f"
 * Then cleans up the substrings by removing ".,?-;:()[]!\"\'" from the ends
 * Counts the number of words found and returns at the end.
 *
 * @param fp The file input.
 * @param list_2D The storage list.
 * @return The number of words in the file.
 */
int textToSubstrings(FILE *fp, char **list_2D)
{
	char *wb = NULL; // word buffer
	char *lb = NULL; // line buffer
	char *line = malloc(MAX_WORDS_LINE * MAX_WORD_LENGTH * sizeof(char)); // alloc mem
	int word_cnt = 0; // # of words found

	while (fgets(line, MAX_WORDS_LINE, fp) != NULL) { // get file line
		lb = line;
		while ((wb = strtok(lb, " \n\t\v\r\f")) != NULL) { // get word from the line
			lb = NULL; // after you strtok once lb can be NULL forever
			char *word_cleaned = malloc(MAX_WORD_LENGTH * sizeof(char));
			stripPunctuation(wb, word_cleaned); // cleans word
			strcpy(list_2D[word_cnt], word_cleaned);
			free(word_cleaned); // free mem
			word_cnt++;
		}
	}
	free(line); // free mem
	return word_cnt;
}
/**
 * @name stripPunctuation
 * @brief Cleans a substring's ends by removing punctuation.
 *
 * Creates a new string with cleaned ends then copies the string
 * into the given buffer pointer.
 *
 * @param c The string to be cleaned.
 * @param buf The pointer to where the cleaned string will be stored.
 * @return 0 if successful (means nothing for now).
 */
int stripPunctuation(char *c, char *buf) {
	size_t str_len = strlen(c); // find size of uncleaned word
	char *str_new = malloc(MAX_WORD_LENGTH * sizeof(char)); //alloc mem
	int index = 0; // index of first char
	int i = 0;
	int end_pt = 0;
	int start_pt = 0;
	int end_flag = 0;
	int start_flag = 0;
	while (!start_flag || !end_flag){
		if(!end_flag && strchr(".,?-;:()[]!\"\'", c[str_len - 1 - i]) != NULL){
		}
		else{
			end_pt = str_len - 1 - i;
			end_flag = 1;
		}
		if(!start_flag && strchr(".,?-;:()[]!\"\'", c[i]) != NULL){
		}
		else{
			start_pt = i;
			start_flag = 1;
		}
		i++;
	}
	for (i = start_pt; i < end_pt + 1 ; i++) {
			*(str_new + index) = tolower(c[i]);
			index++;
	}
	*(str_new + index) = '\0'; // remember to put this at the end for the string
//	// section removes punctuation chars at the ends of the string
//	if (strlen > 0) {
//		for (i = 0; i < str_len ; i++) {
//			if ((i == 0 || (i == str_len - 1)) && strchr(".,?-;:()[]!\"\'", c[i]) != NULL) {
//			}
//			else {
//				*(str_new + index) = tolower(c[i]);
//				index++;
//			}
//		}
//		*(str_new + index) = '\0'; // remember to put this at the end for the string
//	}
	strcpy(buf, str_new); // copy new string into buf
	free(str_new); // free mem
	return 0;
}
/**
 * @name alloc_mem_2D
 * @brief Allocates memory for a double pointer array.
 * @param arr The pointer for memory to be allocated to.
 * @return Void.
 */
void alloc_mem_2D(char ***arr) {
	*arr  = (char **)malloc(sizeof(char *) * MAX_WORDS);
	(*arr)[0] = (char *)malloc(sizeof(char) * MAX_WORD_LENGTH * MAX_WORDS);
	for (int i = 0; i < MAX_WORDS; i++)
		(*arr)[i] = (**arr + MAX_WORD_LENGTH * i);
}
