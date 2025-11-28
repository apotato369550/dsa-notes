#include "expression_tree.h"

// ============================================================================
// Basic Operations
// ============================================================================

void initExprTree(ExprTree *T) {
    /* TODO: Initialize expression tree to NULL */
}

ExprTreeNode* createOperandNode(double value) {
    /* TODO: Create a leaf node containing a numeric value
     * Set isOperator = false
     * Set content.value = value
     * Set left and right to NULL
     */
    return NULL;
}

ExprTreeNode* createOperatorNode(char op, ExprTree left, ExprTree right) {
    /* TODO: Create an operator node with two operands
     * Set isOperator = true
     * Set content.op = op
     * Set left and right children
     */
    return NULL;
}

// ============================================================================
// Tree Construction from Expressions
// ============================================================================

ExprTree buildFromPostfix(char *postfix) {
    /* TODO: Build expression tree from postfix notation
     * Algorithm (from Aho Section 3.6):
     * 1. Use a stack to store expression trees
     * 2. Scan postfix expression left to right
     * 3. For each token:
     *    - If operand: create leaf node, push onto stack
     *    - If operator: pop two trees, create operator node with them as children,
     *                   push result back onto stack
     * 4. Final tree on stack is the expression tree
     *
     * Example: "3 4 + 2 *"
     * - Push 3, push 4
     * - See +: pop 4 and 3, create (3+4), push it
     * - Push 2
     * - See *: pop 2 and (3+4), create ((3+4)*2), push it
     */
    return NULL;
}

ExprTree buildFromPrefix(char *prefix) {
    /* TODO: Build expression tree from prefix notation
     * Algorithm:
     * 1. Scan prefix expression RIGHT to LEFT
     * 2. Use a stack to store expression trees
     * 3. For each token:
     *    - If operand: create leaf node, push onto stack
     *    - If operator: pop two trees, create operator node with them as children
     *                   (note: first pop is RIGHT child, second is LEFT child)
     *                   push result back onto stack
     * 4. Final tree on stack is the expression tree
     *
     * Example: "* + 3 4 2" (represents (3+4)*2)
     */
    return NULL;
}

ExprTree buildFromInfix(char *infix) {
    /* TODO: Build expression tree from fully parenthesized infix
     * Algorithm:
     * 1. Convert infix to postfix first (using Shunting Yard algorithm)
     * 2. Then use buildFromPostfix
     *
     * OR use recursive descent parsing if fully parenthesized
     */
    return NULL;
}

// ============================================================================
// Expression Evaluation
// ============================================================================

double evaluate(ExprTree T) {
    /* TODO: Evaluate expression tree and return result
     * Algorithm (uses postorder traversal):
     * 1. If node is operand (leaf), return its value
     * 2. If node is operator:
     *    - Recursively evaluate left subtree
     *    - Recursively evaluate right subtree
     *    - Apply operator to results
     *    - Return result
     *
     * Example: For tree representing (3+4)*2:
     * - Evaluate left: 3+4 = 7
     * - Evaluate right: 2
     * - Apply *: 7*2 = 14
     */
    return 0.0;
}

bool isValidExpression(ExprTree T) {
    /* TODO: Check if expression tree is valid
     * Valid expression tree:
     * - Every leaf is an operand
     * - Every interior node is an operator with exactly 2 children
     */
    return false;
}

// ============================================================================
// Expression Output (Tree to Notation Conversion)
// ============================================================================

void toPrefix(ExprTree T) {
    /* TODO: Print expression in prefix notation (preorder traversal)
     * Algorithm:
     * 1. Print operator (current node)
     * 2. Recursively print left subtree
     * 3. Recursively print right subtree
     *
     * Example: (3+4)*2 becomes "* + 3 4 2"
     */
}

void toPostfix(ExprTree T) {
    /* TODO: Print expression in postfix notation (postorder traversal)
     * Algorithm:
     * 1. Recursively print left subtree
     * 2. Recursively print right subtree
     * 3. Print operator (current node)
     *
     * Example: (3+4)*2 becomes "3 4 + 2 *"
     */
}

void toInfix(ExprTree T) {
    /* TODO: Print expression in infix notation with minimal parentheses
     * Algorithm (inorder traversal with smart parentheses):
     * 1. Add opening paren if needed (based on operator precedence)
     * 2. Recursively print left subtree
     * 3. Print operator (current node)
     * 4. Recursively print right subtree
     * 5. Add closing paren if needed
     *
     * Example: (3+4)*2 stays as "(3+4)*2"
     */
}

void toInfixFull(ExprTree T) {
    /* TODO: Print expression in fully parenthesized infix notation
     * Algorithm (inorder traversal):
     * 1. If operator node, print "("
     * 2. Recursively print left subtree
     * 3. Print operator (current node)
     * 4. Recursively print right subtree
     * 5. If operator node, print ")"
     *
     * Example: (3+4)*2 becomes "((3+4)*2)"
     */
}

// ============================================================================
// Tree Display and Utilities
// ============================================================================

void displayExprTree(ExprTree T) {
    /* TODO: Display expression tree structure visually
     * Show operators and operands in tree format
     */
}

int countExprNodes(ExprTree T) {
    /* TODO: Count total nodes (operators + operands) */
    return 0;
}

int exprTreeHeight(ExprTree T) {
    /* TODO: Calculate height of expression tree */
    return -1;
}

bool isExprTreeEmpty(ExprTree T) {
    /* TODO: Check if expression tree is empty */
    return true;
}

int countOperators(ExprTree T) {
    /* TODO: Count number of operator nodes (interior nodes) */
    return 0;
}

int countOperands(ExprTree T) {
    /* TODO: Count number of operand nodes (leaves) */
    return 0;
}

// ============================================================================
// Advanced Operations
// ============================================================================

ExprTree copyExprTree(ExprTree T) {
    /* TODO: Create a deep copy of the expression tree
     * Use postorder traversal to copy nodes
     */
    return NULL;
}

ExprTree simplifyConstants(ExprTree T) {
    /* TODO: Simplify constant expressions
     * Example: If subtree is (3+4), replace with 7
     * Algorithm:
     * 1. Recursively simplify left and right subtrees
     * 2. If current node is operator and both children are constants,
     *    evaluate and replace with result
     */
    return NULL;
}

bool areEquivalent(ExprTree T1, ExprTree T2) {
    /* TODO: Check if two expression trees are structurally equivalent
     * Two trees are equivalent if:
     * 1. Both are NULL, OR
     * 2. Both have same operator/operand, and
     * 3. Left subtrees are equivalent, and
     * 4. Right subtrees are equivalent
     */
    return false;
}

void freeExprTree(ExprTree *T) {
    /* TODO: Free all nodes in expression tree using postorder traversal */
}
