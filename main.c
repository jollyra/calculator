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
void symbol_table_add(struct SymbolTable* symbol_table, struct Token* t);
void symbol_table_print(struct SymbolTable* symbol_table);

struct Token* token_new(char* token_name, char* attribute_value);
/* struct Token** parser(struct SymbolTable* symbol_table); */

int main() {
    char expression[16] = "";
    printf("Available operations are +, -, *, /\n");
    scanf("%15s", expression);

    // creat the symbol table
    struct SymbolTable* symbol_table = scanner(expression);
    symbol_table_print(symbol_table);

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
            struct Token* t = token_new("+", "+");
            symbol_table_add(symbol_table, t);
        } else if(expression[c] == '-') {
            struct Token* t = token_new("-", "-");
            symbol_table_add(symbol_table, t);
        } else if(expression[c] == '*') {
            struct Token* t = token_new("*", "*");
            symbol_table_add(symbol_table, t);
        } else if(expression[c] == '/') {
            struct Token* t = token_new("/", "/");
            symbol_table_add(symbol_table, t);
        } else if(expression[c] == '1') {
            struct Token* t = token_new("NUM", "1");
            symbol_table_add(symbol_table, t);
        } else if(expression[c] == '2') {
            struct Token* t = token_new("NUM", "2");
            symbol_table_add(symbol_table, t);
        } else if(expression[c] == '3') {
            struct Token* t = token_new("NUM", "3");
            symbol_table_add(symbol_table, t);
        } else if(expression[c] == '4') {
            struct Token* t = token_new("NUM", "4");
            symbol_table_add(symbol_table, t);
        } else if(expression[c] == '5') {
            struct Token* t = token_new("NUM", "5");
            symbol_table_add(symbol_table, t);
        } else if(expression[c] == '6') {
            struct Token* t = token_new("NUM", "6");
            symbol_table_add(symbol_table, t);
        } else if(expression[c] == '7') {
            struct Token* t = token_new("NUM", "7");
            symbol_table_add(symbol_table, t);
        } else if(expression[c] == '8') {
            struct Token* t = token_new("NUM", "8");
            symbol_table_add(symbol_table, t);
        } else if(expression[c] == '9') {
            struct Token* t = token_new("NUM", "9");
            symbol_table_add(symbol_table, t);
        } else if(expression[c] == '0') {
            struct Token* t = token_new("NUM", "0");
            symbol_table_add(symbol_table, t);
        }
    }
    return symbol_table;
}

struct Token* token_new(char* token_name, char* attribute_value)
{
    struct Token* t = malloc(sizeof(struct Token));
    t->token_name = token_name;
    t->attribute_value = attribute_value;
    return t;
}

void symbol_table_add(struct SymbolTable* symbol_table, struct Token* t)
{
    symbol_table->tokens[symbol_table->count] = t;
    symbol_table->count+=1;
}

void symbol_table_print(struct SymbolTable* symbol_table)
{
    printf("symbol_table\n");
    for(int i = 0; i < symbol_table->count; i++)
    {
        struct Token* symbol = symbol_table->tokens[i];
        printf("\t<%s, %s>\n", symbol->token_name, symbol->attribute_value);
    }
}
