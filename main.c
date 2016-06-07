#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE  1
#define FALSE 0
#define SYMBOL_TABLE_SIZE 16

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

struct SymbolTable
{
    struct Token* tokens[SYMBOL_TABLE_SIZE];
    int count;
};

struct SymbolTable* scanner(char* expression);
void print_symbol_table(struct SymbolTable* symbol_table);
/* struct Token** parser(struct Token* symbol_table); */

int main() {
    char expression[16] = "";
    printf("Available operations are +, -, *, /\n");
    scanf("%15s", expression);

    // creat the symbol table
    struct SymbolTable* symbol_table = scanner(expression);
    print_symbol_table(symbol_table);

    printf("\n");
    getchar();
    return 0;
}

// Lexical Analysis
// take the string of input characters and group them into meaningful chunks
// called 'lexemes'.
struct SymbolTable* scanner(char* expression) {
    struct SymbolTable* symbol_table = malloc(sizeof(struct SymbolTable));

    // scan through the expression and create tokens
    for(int c = 0; c < sizeof(expression); c++) {
        if(expression[c] == '+') {
            struct Token* t = malloc(sizeof(struct Token));
            char* token_name = "+";
            char* attribute_value = "+";
            t->token_name = token_name;
            t->attribute_value = attribute_value;
            symbol_table->tokens[symbol_table->count] = t;
            symbol_table->count+=1;
        } else if(expression[c] == '-') {
            struct Token* t = malloc(sizeof(struct Token));
            char* token_name = "-";
            char* attribute_value = "-";
            t->token_name = token_name;
            t->attribute_value = attribute_value;
            symbol_table->tokens[symbol_table->count] = t;
            symbol_table->count+=1;
        } else if(expression[c] == '1') {
            struct Token* t = malloc(sizeof(struct Token));
            char* token_name = "NUM";
            char* attribute_value = "1";
            t->token_name = token_name;
            t->attribute_value = attribute_value;
            symbol_table->tokens[symbol_table->count] = t;
            symbol_table->count+=1;
        }
    }
    return symbol_table;
}

void print_symbol_table(struct SymbolTable* symbol_table)
{
    printf("symbol_table\n");
    for(int i = 0; i < symbol_table->count; i++)
    {
        struct Token* symbol = symbol_table->tokens[i];
        printf("\t<%s, %s>\n", symbol->token_name, symbol->attribute_value);
    }
}
