#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "wordparse.h"

int textToSubstrings(FILE *fp, char ***list_2D)
{
	char *cp = NULL;
	char *bp = NULL;
	char *line = malloc(MAX_WORDS_LINE * MAX_WORD_LENGTH * sizeof(char));
	int index = 0;

	while (fgets(line, MAX_WORDS_LINE, fp) != NULL) {
		bp = line;
		while ((cp = strtok(bp, " \n\t\v\r\f")) != NULL) {
			bp = NULL;
			char *word_cleaned = malloc(MAX_WORD_LENGTH * sizeof(char));
			stripPunctuation(cp, word_cleaned);
			strcpy((*list_2D)[index], word_cleaned);
			free(word_cleaned);
			index++;
		}
	}
	free(line);
	return index;
}

int stripPunctuation(char *c, char *buf) {
	size_t str_len = strlen(c);
	char *str_new = malloc(MAX_WORD_LENGTH * sizeof(char));
	int index = 0;
	int i = 0;
	if (strlen > 0) {
		for (i = 0; i < str_len ; i++) {
			if ((i == 0 || (i == str_len - 1)) && strchr(".,?-;:()[]!\"\'", c[i]) != NULL) {
			}
			else {
				*(str_new + index) = c[i];
				index++;
			}
		}
		*(str_new + index) = '\0';
	}
	strcpy(buf, str_new);
	free(str_new);
	return 0;
}

void alloc_mem_2D(char ***arr) {
	*arr  = (char **)malloc(sizeof(char *) * MAX_WORDS);
	(*arr)[0] = (char *)malloc(sizeof(char) * MAX_WORD_LENGTH * MAX_WORDS);
	for (int i = 0; i < MAX_WORDS; i++)
		(*arr)[i] = (**arr + MAX_WORD_LENGTH * i);
}