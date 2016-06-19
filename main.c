#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE  1
#define FALSE 0
#define MAX_EXPRESSION_SIZE 16
#define NO_NODE -1

/* Algorithm:
 * ☑ get the expression string
 * - build a syntax tree using an inorder binary tree traversal with operator
 * precedence (syntax analysis)
 * - evaluate syntax tree
 *
 * The Syntax Tree
 * For my chosen operators +, -, *, / an array representation of the syntax
 * tree would be sufficient because the syntax tree is binary. The more
 * general solution would require a data structure that can handle an n-ary
 * tree due to having operators that can have more than two operators. In this
 * case a linked list would work.
 *
 * The linked list tree structure makes it simpler to build the syntax tree.
 */


// Takes a simple mathematical expression and constructs a syntax tree
// representation of it.
struct Node* parse(char* expression);

// Takes a syntax tree of a simple mathematical expression and evaluates it.
char evaluate(char* syntax_tree);

void print_str(char* str);

// Node that comprises a binary tree
struct Node {
    char value;
    struct Node* lchild;
    struct Node* rchild;
};

char* order_of_ops = "+1";

void print_btree(struct Node* root);

int main() {
    char expression[MAX_EXPRESSION_SIZE] = "";
    printf("Available operations are +, -, *, /\n");
    scanf("%15s", expression);

    struct Node* syntax_tree = parse(expression);
    print_btree(syntax_tree);

    printf("\n");
    getchar();
    return 0;
}

struct Node* parse(char* expression) {
    // Nothing left to parse so return null pointer
    if(strlen(expression) == 0)
    {
        return NULL;
    }

    print_str(expression);
    struct Node* root = malloc(sizeof(struct Node));
    root->value = -1;
    root->lchild = NULL;
    root->rchild = NULL;

    unsigned long len = strlen(expression);
    int i;
    for(i = 0; i < strlen(order_of_ops); i++) {
        char op = order_of_ops[i];
        char* op_index = index(expression, op);
        if(op_index) {
            // Split the expression on the operator and recurse
            char* lexpr = malloc(sizeof(expression));
            lexpr = strcpy(lexpr, expression);
            op_index[0] = '\0';
            lexpr = expression;
            char* rexpr = op_index + 1;

            root->value = op;
            root->lchild = parse(lexpr);
            root->rchild = parse(rexpr);
        }
    }
    return NULL;
}



void print_str(char* str) {
    printf("str: %s\tstrlen: %lu\n", str, strlen(str));
}

void print_btree(struct Node* root) {
    if(!root) { return; }
    printf("node: %p\t", root);
    printf("value: %c\t", root->value);
    printf("lchild: %p \trchild: %p\n", root->lchild, root->rchild);
    if(root->lchild) {
        print_btree(root->lchild);
    }
    if(root->rchild) {
        print_btree(root->rchild);
    }
}
