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
 */


// Takes a simple mathematical expression and constructs a syntax tree
// representation of it.
char* parse(char* expression);

// Takes a syntax tree of a simple mathematical expression and evaluates it.
char evaluate(char* syntax_tree);

void print_str(char* str);

int main() {
    char expression[MAX_EXPRESSION_SIZE] = "";
    printf("Available operations are +, -, *, /");
    scanf("%15s", expression);
    print_str(expression);

    char* syntax_tree = parse(expression);
    print_str(syntax_tree);

    printf("\n");
    getchar();
    return 0;
}

char* parse(char* expression)
{
    unsigned long len = strlen(expression);
    char* syntax_tree = malloc(len);
    syntax_tree[0] = 'a';
    syntax_tree[1] = 'b';
    return syntax_tree;
}

void print_str(char* str)
{
    printf("\nstr: %s\nstrlen: %lu", str, strlen(str));
}
