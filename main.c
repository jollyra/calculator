#include <stdio.h>
#include <string.h>

int calculate(char*);

int main() {
    char expression[16] = "";
    printf("Available operations are +, -, *, /\n");
    scanf("%15s", expression);
    calculate(expression);
    printf("\n");
    getchar();
    return 0;
}

int calculate(char* expression) {
    printf("%s", expression);
    for(int i = 0; i++; i < sizeof(expression)) {
        printf("%c", i);
    }
    return 0;
}
