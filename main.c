#include <stdio.h>
#include <string.h>
#include "linked_list.h"

#define TRUE  1
#define FALSE 0

/* Algorithm:
 * get the expression string
 * translate string into tokens (lexical analysis)
 * build a syntax tree using an inorder binary tree traversal (syntax analysis)
 * evaluate syntax tree by inorder traversal
 */

struct Token
{
    char* token_name;
    char* attribute_value;
};

char** scanner(char*);
struct Token** parser(struct Node* symbol_table);

int main() {
    char expression[16] = "";
    printf("Available operations are +, -, *, /\n");
    scanf("%15s", expression);
    scanner(expression);
    printf("\n");
    getchar();
    return 0;
}

    }
    return 0;
}
