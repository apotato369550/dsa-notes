#include <stdio.h>
#include <stdlib.h>

// create required structs


// basic treenode definition with treenode and root aliases
typedef struct TreeNode{
    int value;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode, *Root;

// create queuenode
typedef struct QueueNode {
    TreeNode *node;
    struct QueueNode *next;
} QueueNode;

// create queue
typedef struct Queue {
    QueueNode *head;
    QueueNode *tail;
} Queue;

// function prototypes
// basic functionalities to include in program

// 1. main menu with options - maybe this time I should delegate the options thing to a separate function
void mainMenu();

// helper functions
TreeNode *createNode(int value);
void printTabs(int tabs);

// 1. main menu with options - maybe this time I should delegate the options thing to a separate function
void mainMenu();

// 2. print tree
void printTree(Root root, int tabs);

// 3. insert node to tree
void insertBST(Root *root, int value);


// 4. delete node with value
TreeNode *findInorderSuccessor(TreeNode *node);
void deleteNode(Root *root, int value);

// 5. check if value exists in tree
int doesValueExist(Root root, int value);

void populateTree(Root *root);

// 6. traverse tree submenu - inorder, preorder, postorder, level order
void traverseTreeInOrder(Root root);
void traverseTreePreOrder(Root root);
void traverseTreePostOrder(Root root);

void initializeQueue(Queue *queue);
void enqueue(Queue *queue, TreeNode *treeNode);
TreeNode *dequeue(Queue *queue);

void traverseTreeLevelOrder(Root root);

void traverseTreeSubmenu(Root root);

// 7. structural check submenu - height of tree, number of nodes, is tree balanced?
void structuralCheckSubmenu(Root *root);



int main() {
    printf("--- WELCOME TO BINARY TREE MANIA ---\nWhere trees are grown fresh every day!");
    mainMenu();
    return 0;
}

void mainMenu() {
    Root root = NULL;
    int input = -1;
    int value = -1;
    while (input != 0) {
        printf("Here are your choices: \n");
        printf("0 - Exit \n");
        printf("1 - Print tree \n");
        printf("2 - Insert node into tree \n");
        printf("3 - Delete node with value \n");
        printf("4 - Check if value exists in tree \n");
        printf("5 - Traverse tree \n");
        printf("6 - Perform structural checks on tree \n");
        printf("7 - Populate tree \n");

        printf("Please select an option: ");
        scanf("%d", &input);

        switch(input) {
            case 0:
                printf("See you next time! Bye:)\n");
                break;
            case 1:
                printf("Printing tree...\n");
                printTree(root, 0);
                break;
            case 2:
                printf("Inserting node into tree...\n");
                printf("Enter integer value to be inserted: ");
                scanf("%d", &value);
                insertBST(&root, value);
                break;
            case 3:
                printf("Deleting node with value...\n");
                printf("Enter integer value to be deleted: ");
                scanf("%d", &value);
                if (!doesValueExist(root, value)) {
                    printf("Value %d does not exist within the tree! Cancelling deletion\n", value);
                } else {
                    deleteNode(&root, value);
                }
                break;
            case 4:
                printf("Checking if value exists within tree...\n");
                printf("Please enter value to search: ");
                scanf("%d", &value);
                if (doesValueExist(root, value)) {
                    printf("Value %d exists within the tree!\n", value);
                } else {
                    printf("Failed to find %d within the tree\n", value);
                }
                break;
            case 5:
                printf("Entering tree traversal submenu...\n");
                traverseTreeSubmenu(root);
                break;
            case 6:
                printf("Entering structural checks submenu...\n");
                break;
            case 7:
                printf("Populating Tree...\n");
                populateTree(&root);
                break;
        }
    }
}

// helper function to create nodes and stuff
TreeNode *createTreeNode(int value) {
    TreeNode *newTreeNode = malloc(sizeof(TreeNode));
    if (newTreeNode != NULL) {
        newTreeNode->value = value;
        newTreeNode->left = NULL;
        newTreeNode->right = NULL;
    }
    return newTreeNode;
}

// prints tabs when printing tree
void printTabs(int tabs) {
    for (int i = 0 ; i < tabs; i++) {
        printf("\t");
    }
}

// 2. print tree
void printTree(Root root, int tabs) {
    if (root == NULL) {
        printTabs(tabs);
        printf("--- EMPTY ---\n");
    } else {
        // put it in else statement, otherwise
        // it crashes because it accesses null
        printTree(root->right, tabs + 1);
        printTabs(tabs);
        printf("%d\n", root->value);
        printTree(root->left, tabs + 1);
    }
}


void insertBST(Root *root, int value) {
    if (*root == NULL) {
        *root = createTreeNode(value);
        printf("Value %d has been inserted into tree!!!\n", value);
        return;
    }

    // always less than symbol
    if (value < (*root)->value) {
        // insert left
        insertBST(&(*root)->left, value);
    } else {
        // insert right
        insertBST(&(*root)->right, value);
    }
}

TreeNode *findInorderSuccessor(TreeNode *node) {
    while (node->left != NULL) {
        node = node->left;
    }
    return node;
}

// 4. delete node with value
// fix this function - done
void deleteNode(Root *root, int value) {
    // if root is empty, return null
    if ((*root) == NULL) {
        return;
    }

    // otherwise, we enter another conditional
    if (value < (*root)->value) {
        // if value is less than the value of root, call deleteNode on root's left child
        deleteNode(&(*root)->left, value);
    } else if (value > (*root)->value) {
        // otherwise if value is greater than the value of root, call deleteNode on the right child
        deleteNode(&(*root)->right, value);
    } else {
        // otherwise, you've hit the node you've tried to delete
        if ((*root)->left == NULL && (*root)->right == NULL) {
            // if both left and right child are null, free root and set it to null
            free(*root);
            *root = NULL;
        } else if ((*root)->left == NULL) {
            // if only left is null, set temp to the right child, free root, and re-assign it to temp
            TreeNode *temp = (*root)->right;
            free(*root);
            *root = temp;
        } else if ((*root)->right == NULL) {
            // do the same if right is null
            TreeNode *temp = (*root)->left;
            free(*root);
            *root = temp;
        } else {
            // if there are two children, find the inorder successor (using a helper function passing the address of root's right child)
            TreeNode *successor = findInorderSuccessor((*root)->right);
            // then assign root's value to the successor's value,
            (*root)->value = successor->value;
            // then call deleteNode, passing the address of root's right child, and the successor's value
            deleteNode(&(*root)->right, successor->value);
        }
    }
}

// 5. check if value exists in tree
int doesValueExist(Root root, int value) {
    // if value is found, return 1
    // recursively check if it exists in left and in right
    // if it exists in either, return 1, otherwise return 0

    // does not work. should try and handle NULL case
    // test this now.
    // LMAO I FORGOT TO FIX THIS
    if (root == NULL) {
        return 0;
    }

    if (root->value == value) {
        return 1;
    } else {
        int existsInLeft = root->left == NULL ? 0 : doesValueExist(root->left, value);
        int existsInRight = root->right == NULL ? 0 : doesValueExist(root->right, value);

        return existsInLeft || existsInRight;
    }
}

void populateTree(Root *root) {
    if (!doesValueExist((*root), 15)) {
        insertBST(root, 15);
    }
    if (!doesValueExist((*root), 7)) {
        insertBST(root, 7);
    }
    if (!doesValueExist((*root), 10)) {
        insertBST(root, 10);
    }
    if (!doesValueExist((*root), 20)) {
        insertBST(root, 20);
    }
    if (!doesValueExist((*root), 21)) {
        insertBST(root, 21);
    }
    if (!doesValueExist((*root), 35)) {
        insertBST(root, 35);
    }
}

void traverseTreeInOrder(Root root) {
    if (root != NULL) {
        traverseTreeInOrder(root->left);
        printf("%d ", root->value);
        traverseTreeInOrder(root->right);
    }
}

void traverseTreePreOrder(Root root) {
    if (root != NULL) {
        printf("%d ", root->value);
        traverseTreePreOrder(root->left);
        traverseTreePreOrder(root->right);
    }
}

void traverseTreePostOrder(Root root) {
    if (root != NULL) {
        traverseTreePostOrder(root->left);
        traverseTreePostOrder(root->right);
        printf("%d ", root->value);
    }
}

void initializeQueue(Queue *queue) {
    queue->head = NULL;
    queue->tail = NULL;
}

void enqueue(Queue *queue, TreeNode *treeNode) {
    QueueNode *newQueueNode = malloc(sizeof(QueueNode));
    newQueueNode->node = treeNode;
    newQueueNode->next = NULL;

    // if tail is not null, append to tail's next
    if (queue->tail != NULL) {
        queue->tail->next = newQueueNode;
    }
    // move tail pointer
    queue->tail = queue->tail->next;

    // if queue's head is null, set head to treenode
    if (queue->head == NULL) {
        queue->head = newQueueNode;
    }
}
TreeNode *dequeue(Queue *queue) {
    if (queue->head = NULL) {
        // if null, return null, which is queue->head
        TreeNode *nullNode = NULL;
        return nullNode;
    }

    // set a temp pointing to head
    QueueNode *temp = queue->head;
    // move head pointer
    queue->head = queue->head->next;
    // set a treenode whose value is that of temp
    TreeNode *dequeuedNode = temp->node;
    // free temp
    free(temp);

    // if head is null, tail must equal null as well
    if (queue->head == NULL) {
        queue->tail == NULL;
    }

    // return treenode  
    return dequeuedNode;
}


void traverseTreeLevelOrder(Root root) {
    if (root == NULL) {
        printf("Unable to traverse tree level-order. Tree has no values...\n");
    }
    Queue queue;
    initializeQueue(&queue);
    enqueue(&queue, root);
    TreeNode *dequeued = dequeue(&queue);
    while (dequeued != NULL) {
        printf("%d ", dequeued->value);
        if (dequeued->left != NULL) {
            enqueue(&queue, dequeued->left);
        }
        if (dequeued->right != NULL) {
            enqueue(&queue, dequeued->right);
        }
        dequeued = dequeue(&queue);
    }
}

// 6. traverse tree submenu - inorder, preorder, postorder, level order
void traverseTreeSubmenu(Root root) {
    int input = -1;
    printf("Welcome to the tree traversal submenu! Where we explore trees like it's nobody's business! How would you like your tree traversed?\n");
    while (input != 0) {
        printf("Here are your choices: \n");
        printf("0 - Exit \n");
        printf("1 - Traverse and Print Tree Inorder \n");
        printf("2 - Traverse and Print Tree Preorder \n");
        printf("3 - Traverse and Print Tree Postorder \n");
        printf("4 - Traverse and Print Tree Level Order \n");

        printf("Please select an option: ");

        scanf("%d", &input);

        switch(input) {
            case 0:
                printf("Going back to main menu...\n");
                break;
            case 1:
                printf("Traversing tree Inorder...\n");
                traverseTreeInOrder(root);
                printf("\n");
                break;
            case 2:
                printf("Traversing tree Preorder...\n");
                traverseTreePreOrder(root);
                printf("\n");
                break;
            case 3:
                printf("Traversing tree Postorder...\n");
                traverseTreePostOrder(root);
                printf("\n");
                break;
            case 4:
                printf("Traversing tree Level Order...\n");
                traverseTreeLevelOrder(root);
                printf("\n");
                break;
        }
    }
}

// 7. structural check submenu - height of tree, number of nodes, is tree balanced?, is tree bst?
void structuralCheckSubmenu(Root *root);
