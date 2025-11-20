#ifndef GENERAL_TREE
#define GENERAL_TREE

#include "tree.h"
#include <stdlib.h>
#include <stdbool.h>


void initialize(Tree *root);
void printPreOrder(Tree root);
void printPostOrder(Tree root);
void printInOrder(Tree root);
bool isMember(Tree root, int data);
void insertNode(Tree *root, int data);
void deleteNode(Tree *root, int data);
int getMin(Tree root);
int getMax(Tree root);

#endif