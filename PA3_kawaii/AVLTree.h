/*
 * tree.h
 *
 *  Created on: Feb 1, 2017
 *      Author: ywu
 *
 *  Edited on: Feb 2, 2017
 *
 */
#ifndef TREE_H_
#define TREE_H_

#define UNABLE_TO_ALLOCATE_MEMORY 1
#define INCORECT_SUBTREE_TYPE 2
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tnode Tnode;

void printTree(struct tnode *root);
int containsWord(struct tnode * root, char* string);
int getWordCount(struct tnode *root, char* string);
struct tnode *mallocNode();
void freetnode();
struct tnode *addWord(char* string, struct tnode *root);


#endif /* TREE_H_ */
