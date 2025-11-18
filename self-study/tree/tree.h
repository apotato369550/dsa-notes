#ifndef TREE
#define TREE

typedef struct node {
    int data;
    struct node* left;
    struct node* right;
} *TreeNodePointer, *Tree, TredNode;

#endif