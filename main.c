#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

#define TRUE  1
#define FALSE 0
#define MAX_EXPRESSION_SIZE 16

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


struct Node* parse(char* expression);
int evaluate(struct Node*);
int sum(int x, int y);
int diff(int x, int y);
int multiply(int x, int y);
int divide(int x, int y);
struct Node {
    char value;
    struct Node* lchild;
    struct Node* rchild;
};

// Utility functions
void print_btree(struct Node* root);
void print_str(char* str);
char* maybeRemoveNewline(char *);

void print_str(char* str) {
    printf("str: %s\tstrlen: %lu\n", str, strlen(str));
}

void print_btree(struct Node* root) {
    assert(root != NULL);
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

// Takes a simple mathematical expression and constructs a syntax tree
// representation of it.
struct Node* parse(char* expression) {
    // Nothing left to parse so return null pointer
    if(strlen(expression) == 0) {
        return NULL;
    }

    print_str(expression);
    struct Node* root = malloc(sizeof(struct Node));
    root->value = -1;
    root->lchild = NULL;
    root->rchild = NULL;

    char* order_of_ops = "+-*/12";
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
            return root;
        }
    }
    printf("ERROR: failed parsing \"%s\"\n", expression);
    exit(EXIT_FAILURE);
}

int sum(int x, int y) {
    printf("sum %d, %d\n", x, y);
    return x + y;
}

int diff(int x, int y) {
    printf("diff %d, %d\n", x, y);
    return x - y;
}

int multiply(int x, int y) {
    printf("multiply %d, %d\n", x, y);
    return x * y;
}

int divide(int x, int y) {
    printf("divide %d, %d\n", x, y);
    return x / y;
}

// Takes a syntax tree of a simple expression and evaluates it.
int evaluate(struct Node* parent) {
    assert(parent != NULL);
    char val = parent->value;
    if(val == '+') {
        return sum(evaluate(parent->lchild), evaluate(parent->rchild));
    } else if(val == '-') {
        return diff(evaluate(parent->lchild), evaluate(parent->rchild));
    } else if(val == '*') {
        return multiply(evaluate(parent->lchild), evaluate(parent->rchild));
    } else if(val == '/') {
        return divide(evaluate(parent->lchild), evaluate(parent->rchild));
    } else if(isdigit(val) != FALSE) {
        if(val == '1') {
            return 1;
        } else if(val == '2') {
            return 2;
        } else if(val == '3') {
            return 3;
        } else if(val == '0') {
            return 0;
        }
    } else {
        printf("ERROR: unknown symbol \'%c\'\n", val);
        exit(EXIT_FAILURE);
    }
}

// Remove trailing newline, if there is one
char* maybeRemoveNewline(char *str) {
    if ((strlen(str) > 0) && (str[strlen (str) - 1] == '\n')) {
        str[strlen (str) - 1] = '\0';
    }
    return str;
}

int main(int argc, char *argv[]) {
    char expression[MAX_EXPRESSION_SIZE] = "";
    printf("Available operations are +, -, *, /\n");
    fgets(expression, MAX_EXPRESSION_SIZE, stdin);


    /* char** tokens = malloc(8); */
    /* char* stringp = expression; */
    /* const char* delim = " "; */
    /* char* token; */
    /* token = strsep(&stringp, delim); */
    /* printf("1st token: %s\n", token); */
    /*  */
    /* token = strsep(&stringp, delim); */
    /* printf("2nd token: %s\n", token); */
    /*  */
    /* while((token = strsep(&stringp, delim)) != NULL) { */
    /*     printf("Next: %s\n", token); */
    /* } */

    struct Node* syntax_tree = parse(expression);
    print_btree(syntax_tree);

    int ans = evaluate(syntax_tree);
    printf("expression evaluates to %d\n", ans);

    printf("\n");
    getchar();
    return 0;
}
