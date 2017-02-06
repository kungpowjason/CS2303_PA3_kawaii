/*
 * PA4.c
 *
 *  Created on: Jan 25, 2017
 *      Author: dominic
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AVLTree.h"

#define UNABLE_TO_ALLOCATE_MEMORY 1

struct tnode{
	struct tnode *left; //left child
	struct tnode *right;//right child
	char *word;
	int count;
	int leftLength;// length of left subtree
	int rightLength; // length of right subtree
};

typedef struct tnode Tnode;

//Allocates memory for a node on the tree. Returns pointer to allocated space.
Tnode *mallocNode(){
	Tnode *root = (Tnode *) malloc(sizeof(Tnode));

	if(!root)
		exit(UNABLE_TO_ALLOCATE_MEMORY);
	return root;
}//Tnode *mallocNode()

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

//returns 1 if node has atleast 1 child
int hasChildren(Tnode *root){
	if(root->left || root->right)
		return 1;
	else
		return 0;
}//int hasChildren(Tnode *root

//Balances unbalanced subtree of 3 elements
Tnode *balanceSubTreeType1(Tnode *root){
	Tnode *left, *right, *temp1, *temp2;
	temp1 = root;
	temp1->rightLength = 0;
	temp1->leftLength = 0;

	left = root->left;
	right = root->right;

	if(right == NULL){
		if((temp2 = left->right) != NULL){
			root->left = NULL;
			root = temp2;
			left->right = NULL;
			left->rightLength = 0;
			root->left = left;
			root->leftLength = 1;
			root->right = temp1;
			root->rightLength = 1;
			return root;
		}
		else{
			root->left = NULL;
			root->leftLength = 0;
			root = left;
			root->right = temp1;
			return root;
		}
	}else if(left == NULL){
		if((temp2 = right->left) != NULL){
			root->right = NULL;
			root = temp2;
			left->left = NULL;
			left->leftLength = 0;
			root->right = left;
			root->rightLength = 1;
			root->left = temp1;
			root->leftLength = 1;
			return root;
		}
		else{
			root->right = NULL;
			root->rightLength = 0;
			root = right;
			root->leftLength = 1;
			root->left = temp1;
			return root;
		}
	}
	exit(INCORECT_SUBTREE_TYPE);
}//Tnode *balanceSubTreeType1(Tnode *root)

//Balances unbalanced subtree of 5 elements
Tnode *balanceSubTreeType2(Tnode *root){
	Tnode *left, *right;

	left = root->left;
	right = root->right;

	if(!hasChildren(right)){
		root->left = balanceSubTreeType1(left);
		root->leftLength--;
	}else if(!hasChildren(left)){
		root->right = balanceSubTreeType1(right);
		root->rightLength--;
	}
	return root;
}//Tnode *balanceSubTreeType2(Tnode *root)

Tnode *balanceSubTreeType3(Tnode *root){
	Tnode *left, *right, *temp1, *temp2;

	int length = 0;
	temp1 = root;

	left = root->left;
	right = root->right;

	if(hasChildren(left)){
		length = left->rightLength;
		temp2 = left->right;
		left->right = NULL;
		right->left = temp2;
		right->leftLength = length;
		root->left = NULL;
		root = left;
		root->right = temp1;
		root->rightLength = length + 1;
	}
	else if(hasChildren(right)){
		length = right->leftLength;
		temp2 = right->left;
		right->left = NULL;
		left->right = temp2;
		left->rightLength = length;
		root->right = NULL;
		root = right;
		root->left = temp1;
		root->leftLength = length + 1;
	}else
		return NULL;

	return root;
}// Tnode *balanceSubTreeType3(Tnode *root)

Tnode *balanceTree(Tnode *root){
	Tnode *left, *right;
	int sideDifference = root->rightLength - root->leftLength;

	if(sideDifference < -1){// leftside is unbalanced
		left = root->left;
		if(root->leftLength < 3){// is a subtree type 1
			root = balanceSubTreeType1(root);
			return root;
		}
		else if(root->leftLength < 4){// is a subtree type2 or type3
			if(root->left->left && root->left->right)
				root = balanceSubTreeType3(root);
			else
				root = balanceSubTreeType2(root);
		}
		else
			left = balanceTree(left);
	}
	else if(sideDifference > 1){// rightside is unbalanced
		right = root->right;
		if(root->rightLength < 3){// is a subtree typ31
			root = balanceSubTreeType1(root);
		}
		else if(root->rightLength < 4){// is a subtree type2 or type3
			if(root->right->right && root->right->left)
				root = balanceSubTreeType3(root);
			else
				root = balanceSubTreeType2(root);
		}
		else
			right = balanceTree(right);
	}

	return root;
}

//Adds a word to the tree. Returns a pointer to the root to the tree.
Tnode *oldAddWord(char* string, Tnode *root, int *addedNew){

	if(root == NULL){
		root = mallocNode();
		root->word = strdup(string);
		root->left = NULL;
		root->right = NULL;
		root->leftLength = 0;
		root->rightLength = 0;
		root->count = 1;
		*addedNew = 1;
		return root;
	}


	int comparison = strcmp(string, root->word);

	if(comparison < 0){
		root->left = addWord(string, root->left, addedNew);
		if(*addedNew)
			root->leftLength++;
	}
	else if(comparison > 0){
		root->right = addWord(string, root->right, addedNew);
		if(*addedNew)
			root->rightLength++;
	}
	else
		root->count++;
	//root = balanceTree(root);
	return root;
}//Tnode *addWord(char* string, Tnode *root)

//Returns the count of a given word
int getWordCount(Tnode *root, char* string){
	int size = strcmp(string, root->word);

	if(root == NULL)
		return 0;
	if(size < 0)// string is smaller than the one at the current node
		return getWordCount(root->left,string);
	else if(size == 0)// word found
		return root->count;
	else // string is larger
		return getWordCount(root->right, string);
}//int getWordCount(Tnode * root, char* word)

//checks to see if tree contains a word
int containsWord(Tnode * root, char* string){
	int size = strcmp(string, root->word);
	if(root == NULL)
		return 0;
	if(size < 0)// word is smaller than the one at the current node
		return getWordCount(root->left, string);
	else if(size == 0)// word found
		return 1;
	else // word is larger
		return getWordCount(root->right, string);
}//int containsWord(Tnode * root, char* word)

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
}//int printGraph(Tnode *root)

//adding a new word for AVL tree
Tnode *addWord(char *string, Tnode *root){
	int addedNew = 0;

	root = oldAddWord(string, root, &addedNew);
	root = balanceTree(root);
	return root;
}//Tnode *addWord(char *string, Tnode *root)
int test1(){
	Tnode *root = NULL;

	root = addWord("a", root);
	root = addWord("b", root);
	root = addWord("c", root);
	printf("Left: %d, Right:%d\n",root->leftLength, root->rightLength);
	printTree(root);
	printf("\n");
	return 0;
}
int test2(){
	Tnode *root = NULL;

	root = addWord("d", root);
	root = addWord("e", root);
	root = addWord("c", root);
	root = addWord("b", root);
	root = addWord("a", root);
	root = balanceTree(root);
	printf("Left: %d, Right:%d\n",root->leftLength, root->rightLength);
	printTree(root);
	printf("\n");
	return 0;
}
int test3() {
	Tnode *root = NULL;
	root = addWord("e", root);
	root = addWord("b", root);
	root = addWord("c", root);
	root = addWord("b", root);
	root = addWord("a", root);
	//root = balanceTree(root);
	printf("Left: %d, Right:%d\n",root->leftLength, root->rightLength);
	printTree(root);
	printf("\n");
	return 0;
}
int test4() {
	Tnode *root = NULL;
	root = addWord("e", root);
	root = addWord("f", root);
	root = addWord("c", root);
	root = addWord("d", root);
	root = addWord("b", root);
	root = addWord("a", root);
	root = addWord("a", root);
	root = addWord("a", root);
	root = addWord("a", root);
	printf("Left: %d, Right:%d\n",root->leftLength, root->rightLength);
	printTree(root);
	printf("\n");
	return 0;
}
/*int main(){
	test1();
	test2();
	test3();
	test4();

}*/
