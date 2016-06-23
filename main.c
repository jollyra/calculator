#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

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


char* maybeRemoveNewline(char*);
char** read_input(char*);
int* scan(char**);
struct Node* parse(int* lexemes);
int evaluate(struct Node*);
int sum(int, int);
int diff(int, int);
int multiply(int, int);
int divide(int, int);

struct Node {
    int value;
    struct Node* lchild;
    struct Node* rchild;
};

int list_length(char**);
int tokens_len(int* tokens);
int list_index(int* list, int target);
int get_highest_precedence_op_idx(int* lexemes);
int* sublist(int*, int start, int end);

int PLUS = 100;
int MINUS = 101;
int MULTIPLY = 102;
int DIVIDE = 103;

// Utility functions
void print_btree(struct Node*);
void print_str(char*);
void print_lexemes(char**);
void print_tokens(int*);


char** read_input(char* expression) {
    char** lexemes = calloc(MAX_EXPRESSION_SIZE*2, sizeof(void*));
    const char* delim = " ";
    char* lexeme;
    char** pos = lexemes;
    while((lexeme = strsep(&expression, delim)) != NULL) {
        *pos = lexeme;
        pos++;
    }
    return lexemes;
}

// Remove trailing newline, if there is one
char* maybeRemoveNewline(char *str) {
    if ((strlen(str) > 0) && (str[strlen (str) - 1] == '\n')) {
        str[strlen (str) - 1] = '\0';
    }
    return str;
}

/*
 * The lexeme can either be:
 * 1. a supported operator, or
 * 2. a valid string representation of an integer
 * If the lexeme is not recognized the process will exit with an error.
 */
int* scan(char** lexemes) {
    int num_lexemes = list_length(lexemes);
    int* tokens = calloc(num_lexemes + 1, sizeof(int));
    tokens[num_lexemes + 1] = 0;  // Unique terminating signal
    for(int i = 0; i < num_lexemes; i++) {
        if(strcmp(lexemes[i], "+") == 0) {
            tokens[i] = PLUS;
        } else if(strcmp(lexemes[i], "-") == 0) {
            tokens[i] = MINUS;
        } else if(strcmp(lexemes[i], "*") == 0) {
            tokens[i] = MULTIPLY;
        } else if(strcmp(lexemes[i], "/") == 0) {
            tokens[i] = DIVIDE;
        } else if(isdigit(lexemes[i][0])) {
            int num = atoi(lexemes[i]);
            tokens[i] = num;
        } else {
            printf("ERROR: unknown symbol \'%s\'\n", lexemes[i]);
            exit(EXIT_FAILURE);
        }
    }
    return tokens;
}

void print_str(char* str) {
    printf("str: %s\tstrlen: %lu\n", str, strlen(str));
}

void print_btree(struct Node* root) {
    assert(root != NULL);
    printf("node: %p\t", root);
    printf("value: %d\t", root->value);
    printf("lchild: %p \trchild: %p\n", root->lchild, root->rchild);
    if(root->lchild) {
        print_btree(root->lchild);
    }
    if(root->rchild) {
        print_btree(root->rchild);
    }
}

int list_length(char** list) {
    int count = 0;
    while(*list != NULL) {
        count++;
        list++;
    }
    return count;
}

int list_index(int* list, int target) {
    int idx = 0;
    while(*list != 0) {
        if(*list == target) {
            return idx;
        }
        list++;
        idx++;
    }
    return -1;
}

int tokens_len(int* tokens) {
    int count = 0;
    while(*tokens != 0) {
        count++;
        tokens++;
    }
    return count;
}

int* sublist(int* list, int start, int end) {
    // The last pointer must always be null
    int* sublist = calloc(end - start + 2, sizeof(void*));
    int count = 0;
    int pos = start;
    while(pos <= end) {
        sublist[count] = list[pos];
        count++;
        pos++;
    }
    return sublist;
}

int get_highest_precedence_op_idx(int* tokens) {
    int order_of_ops[] = {PLUS, MINUS, MULTIPLY, DIVIDE};
    for(int i = 0; i < 4; i++) {
        int op = order_of_ops[i];
        int op_idx = list_index(tokens, op);
        if(op_idx >= 0) {
            return op_idx;
        }
    }
    return -1;
}

// Takes a simple mathematical expression and constructs a syntax tree
// representation of it.
struct Node* parse(int* tokens) {
    int len = tokens_len(tokens);
    struct Node* node = malloc(sizeof(struct Node));
    node->lchild = NULL;
    node->rchild = NULL;

    if(len == 1) {
        node->value = tokens[0];
    } else if(len > 1) {
        int op_idx = get_highest_precedence_op_idx(tokens);
        if(op_idx >= 0) {
            node->value = tokens[op_idx];
        }

        int* lexpr = sublist(tokens, 0, op_idx - 1);
        node->lchild = parse(lexpr);

        int* rexpr = sublist(tokens, op_idx + 1, len - 1);
        node->rchild = parse(rexpr);
    }
    return node;
}

// Takes a syntax tree of a simple expression and evaluates it.
int evaluate(struct Node* parent) {
    assert(parent != NULL);
    int val = parent->value;
    if(val == PLUS) {
        return sum(evaluate(parent->lchild), evaluate(parent->rchild));
    } else if(val == MINUS) {
        return diff(evaluate(parent->lchild), evaluate(parent->rchild));
    } else if(val == MULTIPLY) {
        return multiply(evaluate(parent->lchild), evaluate(parent->rchild));
    } else if(val == DIVIDE) {
        return divide(evaluate(parent->lchild), evaluate(parent->rchild));
    } else {
        return val;
    }
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

void print_lexemes(char** lexemes) {
    printf("lexemes:\n");
    while(*lexemes != NULL) {
        printf("%s\n", *lexemes);
        lexemes++;
    }
}

void print_tokens(int* tokens) {
    int i = 0;
    printf("tokens:\n");
    while(*tokens != 0) {
        printf("%d\n", *tokens);
        tokens++;
    }
}

int main(int argc, char *argv[]) {
    printf("Available operations are +, -, *, /\n");

    char input_buffer[MAX_EXPRESSION_SIZE] = "";
    fgets(input_buffer, MAX_EXPRESSION_SIZE, stdin);
    char* expression = maybeRemoveNewline(input_buffer);

    char** lexemes;
    lexemes = read_input(expression);
    int len = list_length(lexemes);
    print_lexemes(lexemes);

    int* tokens;
    tokens = scan(lexemes);
    print_tokens(tokens);

    struct Node* syntax_tree;
    syntax_tree = parse(tokens);
    print_btree(syntax_tree);

    int ans = evaluate(syntax_tree);
    printf("expression evaluates to %d\n", ans);

    printf("\n");
    getchar();
    return 0;
}
