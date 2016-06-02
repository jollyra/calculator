#include <stdio.h>
#include <string.h>

int calculate(char*);

int main() {
    char expression[4] = "";
    printf("Available operations are +, -, *, /. End your expression with a $ character\n");
    scanf("%3s", expression);
    printf("%s", expression);
    printf("len of expression: %lu\n", strlen(expression));
    calculate(expression);
    printf("\n");
    getchar();
    return 0;
}

int calculate(char* expression) {
    printf("%s", expression);
    char c = (char) expression;
    while(strcmp(&c, "\0")) {
        printf("%c", c);
        c++;
    }
    return 0;
}
