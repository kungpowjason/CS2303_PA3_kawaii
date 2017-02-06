/*
 * PA4.c
 *
 *  Created on: Jan 25, 2017
 *      Author: dominic
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"

//Allocates memory for a node on the tree. Returns pointer to allocated space.
struct tnode *mallocNode(){
	struct tnode *root = (struct tnode *) malloc(sizeof(struct tnode));

	if(!root)
		exit(UNABLE_TO_ALLOCATE_MEMORY);
	return root;
}//struct tnode *mallocNode()

//Frees memory allocated for tree
void freeTree(Tnode *root){
	if(root == NULL){
		return;
	}
	freeTree(root->left);
	root->left = NULL;
	freeTree(root->left);
	root->right = NULL;
	freeTree(root->right);

	free(root);
}//void freeTree(Tnode *root)

//Adds a word to the tree. Returns a pointer to the root to the tree.
struct tnode *addWord(char* string, struct tnode *root){
	if(root == NULL){
		root = mallocNode();
		root->word = strdup(string);
		root->left = NULL;
		root->right = NULL;
		root->count = 1;
		return root;
	}


	int comparison = strcmp( string, root->word);

	if(comparison < 0){
		root->left = addWord(string, root->left);
	}
	else if(comparison > 0){
		root->right = addWord(string, root->right);
	}
	else
		root->count++;
	return root;
}//struct tnode *addWord(char* string, struct tnode *root)

//Returns the count of a given word
int getWordCount(struct tnode *root, char* string){
	int size = strcmp(string, root->word);

	if(root == NULL)
		return 0;
	if(size < 0)// string is smaller than the one at the current node
		return getWordCount(root->left,string);
	else if(size == 0)// word found
		return root->count;
	else // string is larger
		return getWordCount(root->right, string);
}//int getWordCount(struct tnode * root, char* word)

//checks to see if tree contains a word
int containsWord(struct tnode * root, char* string){
	int size = strcmp(string, root->word);
	if(root == NULL)
		return 0;
	if(size < 0)// word is smaller than the one at the current node
		return getWordCount(root->left, string);
	else if(size == 0)// word found
		return 1;
	else // word is larger
		return getWordCount(root->right, string);
}//int containsWord(struct tnode * root, char* word)

/**
 * @brief Prints the tree of the given node
 * @param root
 */
void printTree(struct tnode *root){
   if(root == NULL)
     return;
   printTree(root -> left);
   printf("%20.20s %d\n",root -> word, root -> count);
   printTree(root ->right);
}
