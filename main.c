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


char** scan(char*);
struct Node* parse(char** expression);
int evaluate(struct Node*);
int sum(int, int);
int diff(int, int);
int multiply(int, int);
int divide(int, int);
struct Node {
    char* value;
    struct Node* lchild;
    struct Node* rchild;
};
int list_length(char**);
int list_index(char** list, char* target);
int get_highest_precedence_op_idx(char** expression);
char** sublist(char**, int start, int end);

// Utility functions
void print_btree(struct Node*);
void print_str(char*);
void print_tokens(char**);
char* maybeRemoveNewline(char*);

void print_str(char* str) {
    printf("str: %s\tstrlen: %lu\n", str, strlen(str));
}

void print_btree(struct Node* root) {
    assert(root != NULL);
    printf("node: %p\t", root);
    printf("value: %s\t", root->value);
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

int list_index(char** list, char* target) {
    int idx = 0;
    while(*list != NULL) {
        if(strcmp(*list, target) == 0) {
            return idx;
        }
        list++;
        idx++;
    }
    return -1;
}

char** sublist(char** list, int start, int end) {
    // The last pointer must always be null
    char** sublist = calloc(end - start + 2, sizeof(void*));
    int count = 0;
    int pos = start;
    while(pos <= end) {
        sublist[count] = list[pos];
        count++;
        pos++;
    }
    return sublist;
}

int get_highest_precedence_op_idx(char** expression) {
    const char order_of_ops[] = "+-*/";
    for(int i = 0; i < strlen(order_of_ops); i++) {
        char op = order_of_ops[i];
        int op_idx = list_index(expression, &op);
        if(op_idx >= 0) {
            return op_idx;
        }
    }
    return -1;
}

// Takes a simple mathematical expression and constructs a syntax tree
// representation of it.
struct Node* parse(char** expression) {
    struct Node* node = malloc(sizeof(struct Node));
    node->lchild = NULL;
    node->rchild = NULL;

    int len = list_length(expression);
    if(len == 1) {
        node->value = expression[0];
    } else if(len > 1) {
        int op_idx = get_highest_precedence_op_idx(expression);
        printf("highest precedence op is %s\n", expression[op_idx]);
        if(op_idx >= 0) {
            node->value = expression[op_idx];
        }

        char** lexpr = sublist(expression, 0, op_idx - 1);
        node->lchild = parse(lexpr);

        char** rexpr = sublist(expression, op_idx + 1, len - 1);
        node->rchild = parse(rexpr);
    }
    return node;
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
    char* val = parent->value;
    if(strcmp(val, "+") == 0) {
        return sum(evaluate(parent->lchild), evaluate(parent->rchild));
    } else if(strcmp(val, "-") == 0) {
        return diff(evaluate(parent->lchild), evaluate(parent->rchild));
    } else if(strcmp(val, "*") == 0) {
        return multiply(evaluate(parent->lchild), evaluate(parent->rchild));
    } else if(strcmp(val, "/") == 0) {
        return divide(evaluate(parent->lchild), evaluate(parent->rchild));
    } else if(strcmp(val, "1") == 0) {
        return 1;
    } else {
        printf("ERROR: unknown symbol \'%s\'\n", val);
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

void print_tokens(char** tokens) {
    printf("tokens:\n");
    while(*tokens != NULL) {
        printf("%s\n", *tokens);
        tokens++;
    }
}

char** scan(char* expression) {
    char** tokens = calloc(MAX_EXPRESSION_SIZE*2-1, sizeof(void*));
    const char* delim = " ";
    char* token;
    char** pos = tokens;
    while((token = strsep(&expression, delim)) != NULL) {
        *pos = token;
        pos++;
    }
    return tokens;
}

int main(int argc, char *argv[]) {
    printf("Available operations are +, -, *, /\n");

    char input_buffer[MAX_EXPRESSION_SIZE] = "";
    fgets(input_buffer, MAX_EXPRESSION_SIZE, stdin);
    char* expression = maybeRemoveNewline(input_buffer);

    char** tokens;
    tokens = scan(expression);
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
