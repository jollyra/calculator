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
int lexemes_len(int* lexemes);
int list_index(int* list, int target);
int get_highest_precedence_op_idx(int* lexemes);
int* sublist(int*, int start, int end);

int PLUS = 100;
int MINUS = 101;
int MUL = 102;
int DIVIDE = 103;
int ONE = 1;

// Utility functions
void print_btree(struct Node*);
void print_str(char*);
void print_tokens(char**);
void print_lexemes(int*);


char** read_input(char* expression) {
    char** tokens = calloc(MAX_EXPRESSION_SIZE*2, sizeof(void*));
    const char* delim = " ";
    char* token;
    char** pos = tokens;
    while((token = strsep(&expression, delim)) != NULL) {
        *pos = token;
        pos++;
    }
    return tokens;
}

// Remove trailing newline, if there is one
char* maybeRemoveNewline(char *str) {
    if ((strlen(str) > 0) && (str[strlen (str) - 1] == '\n')) {
        str[strlen (str) - 1] = '\0';
    }
    return str;
}

int* scan(char** tokens) {
    int num_tokens = list_length(tokens);
    int* lexemes = calloc(num_tokens + 1, sizeof(int));
    lexemes[num_tokens + 1] = 0;  // Unique terminating signal
    for(int i = 0; i < num_tokens; i++) {
        if(strcmp(tokens[i], "+") == 0) {
            lexemes[i] = PLUS;
        } else if(strcmp(tokens[i], "-") == 0) {
            lexemes[i] = MINUS;
        } else if(strcmp(tokens[i], "1") == 0) {
            lexemes[i] = ONE;
        } else {

        }
    }
    return lexemes;
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

int lexemes_len(int* lexemes) {
    int count = 0;
    while(*lexemes != 0) {
        count++;
        lexemes++;
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

int get_highest_precedence_op_idx(int* lexemes) {
    int order_of_ops[] = {PLUS, MINUS, MUL, DIVIDE};
    for(int i = 0; i < 4; i++) {  // TODO: Use a general list iteration with a unique terminating sentinal
        int op = order_of_ops[i];
        int op_idx = list_index(lexemes, op);
        if(op_idx >= 0) {
            return op_idx;
        }
    }
    return -1;
}

// Takes a simple mathematical expression and constructs a syntax tree
// representation of it.
struct Node* parse(int* lexemes) {
    int len = lexemes_len(lexemes);
    struct Node* node = malloc(sizeof(struct Node));
    node->lchild = NULL;
    node->rchild = NULL;

    if(len == 1) {
        node->value = lexemes[0];
    } else if(len > 1) {
        int op_idx = get_highest_precedence_op_idx(lexemes);
        printf("highest precedence op is %d\n", lexemes[op_idx]);
        if(op_idx >= 0) {
            node->value = lexemes[op_idx];
        }

        int* lexpr = sublist(lexemes, 0, op_idx - 1);
        node->lchild = parse(lexpr);

        int* rexpr = sublist(lexemes, op_idx + 1, len - 1);
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
    } else if(val == MUL) {
        return multiply(evaluate(parent->lchild), evaluate(parent->rchild));
    } else if(val == DIVIDE) {
        return divide(evaluate(parent->lchild), evaluate(parent->rchild));
    } else if(val == ONE) {
        return 1;
    } else {
        printf("ERROR: unknown symbol \'%d\'\n", val);
        exit(EXIT_FAILURE);
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

void print_tokens(char** tokens) {
    printf("tokens:\n");
    while(*tokens != NULL) {
        printf("%s\n", *tokens);
        tokens++;
    }
}

void print_lexemes(int* lexemes) {
    int i = 0;
    printf("lexemes:\n");
    while(*lexemes != 0) {
        printf("%d\n", *lexemes);
        lexemes++;
    }
}

int main(int argc, char *argv[]) {
    printf("Available operations are +, -, *, /\n");

    char input_buffer[MAX_EXPRESSION_SIZE] = "";
    fgets(input_buffer, MAX_EXPRESSION_SIZE, stdin);
    char* expression = maybeRemoveNewline(input_buffer);

    char** tokens;
    tokens = read_input(expression);
    int len = list_length(tokens);
    print_tokens(tokens);

    int* lexemes;
    lexemes = scan(tokens);
    print_lexemes(lexemes);

    struct Node* syntax_tree;
    syntax_tree = parse(lexemes);
    print_btree(syntax_tree);

    int ans = evaluate(syntax_tree);
    printf("expression evaluates to %d\n", ans);

    printf("\n");
    getchar();
    return 0;
}
