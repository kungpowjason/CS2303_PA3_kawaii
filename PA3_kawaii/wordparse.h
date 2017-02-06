#ifndef WORDPARSE_H_   /* Include guard */
#define WORDPARSE_H_

#define MAX_WORDS_LINE 200
#define MAX_WORD_LENGTH 20
#define MAX_WORDS 10000

int textToSubstrings(FILE *fp, char **list_2D);
int stripPunctuation(char *c, char *buf);
void alloc_mem_2D(char ***arr);

#endif // WORDPASE_H_
