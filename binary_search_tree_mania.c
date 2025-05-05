#include <stdio.h>
#include <stdlib.h>

// basic treenode definition with treenode and root aliases
typedef struct TreeNode{
    int value;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode, *Root;

// function prototypes
/*
basic functionalities to include in program
1. main menu with options - maybe this time I should delegate the options thing to a separate function
2. print tree
3. insert node to tree
4. delete node with value
5. check if value exists in tree
6. traverse tree submenu - inorder, preorder, postorder, level order
7. structural check submenu - height of tree, number of nodes, is tree balanced?, is tree bst?
8. transformations/utilities (optional, because it seems complicated) - mirror tree, tree to array/list conversion, lowest common ancestor, path sum check
*/

int main() {

    return 0;
}