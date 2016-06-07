#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

struct Token** scanner(struct Token** symbol_table, int*, char*);
/* struct Token** parser(struct Token* symbol_table); */

int main() {
    char expression[16] = "";
    printf("Available operations are +, -, *, /\n");
    scanf("%15s", expression);

    // symbol table
    struct Token* symbol_table[16];
    int* size = malloc(sizeof(int));
    scanner(symbol_table, size, expression);

    printf("\n");
    getchar();
    return 0;
}

// Lexical Analysis
// take the string of input characters and group them into meaningful chunks
// called 'lexemes'.
struct Token** scanner(struct Token** symbol_table, int* size, char* expression) {
    for(int c = 0; c < sizeof(expression); c++) {
        printf("%c", expression[c]);
        if(expression[c] == '+') {
            struct Token* t = malloc(sizeof(struct Token));
            char* token_name = "+";
            char* attribute_value = "+";
            t->token_name = token_name;
            t->attribute_value = attribute_value;
            symbol_table[*size] = t;
            (*size)+=1;
        } else if(expression[c] == '-') {
            struct Token* t = malloc(sizeof(struct Token));
            char* token_name = "-";
            char* attribute_value = "-";
            t->token_name = token_name;
            t->attribute_value = attribute_value;
            symbol_table[*size] = t;
            (*size)+=1;
        } else if(expression[c] == '1') {
            struct Token* t = malloc(sizeof(struct Token));
            char* token_name = "NUM";
            char* attribute_value = "1";
            t->token_name = token_name;
            t->attribute_value = attribute_value;
            symbol_table[*size] = t;
            (*size)+=1;
        }
    }
    return symbol_table;
}
