#ifndef BINARY_SEARCH_TREE
#define BINARY_SEARCH_TREE

#include "tree.h"
#include <stdbool.h>
#include <stdlib.h>

void insertNode(BinaryTreeNodePointer *root, int data);
void deleteNode(BinaryTreeNodePointer *root, int data);
bool isMember(BinaryTreeNodePointer *root, int data);
int getMin(BinaryTreeNodePointer root);
int getMax(BinaryTreeNodePointer root);

#endif