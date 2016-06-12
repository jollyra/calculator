#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
 */


// Takes a simple mathematical expression and constructs a syntax tree
// representation of it.
void parse(char** expression);

// Takes a syntax tree of a simple mathematical expression and evaluates it.
char evaluate(void);

int main() {
    char expression[MAX_EXPRESSION_SIZE] = "";
    printf("Available operations are +, -, *, /\n");
    scanf("%15s", expression);

    printf("\n");
    getchar();
    return 0;
}
