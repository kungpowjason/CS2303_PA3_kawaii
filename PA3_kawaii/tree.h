/*
 * tree.h
 *
 *  Created on: Feb 1, 2017
 *      Author: ywu
 */
#ifndef TREE_H_
#define TREE_H_

#define INCORECT_SUBTREE_TYPE 2
#define UNABLE_TO_ALLOCATE_MEMORY 1

struct tnode{
	struct tnode *left; //left child
	struct tnode *right;//right child
	char *word;
	int count;
};

void printTree(struct tnode *root);
void writeOutFileTree(struct tnode *root, FILE *f_out);
int containsWord(struct tnode * root, char* string);
int getWordCount(struct tnode *root, char* string);
struct tnode *mallocNode();
void freeTree(struct tnode *root);
struct tnode *addWord(char* string, struct tnode *root);


#endif /* TREE_H_ */
