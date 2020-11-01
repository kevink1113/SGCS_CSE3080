#include <stdio.h>
#include <stdlib.h>

#define STACK_MAX 1111
#define EXPR_MAX 1111

typedef enum {
    lparen, rparen, plus, minus, times, divide, mod, eos, operand, end
} precedence;

precedence stack[STACK_MAX];
int top = -1;


void push(precedence item);
precedence pop(void);
precedence getToken(char *symbol, int *n, char *expr);

int eval(void);
void printToken(precedence token);
void postfix(void);
char expr[EXPR_MAX];
char POSTFIX[EXPR_MAX];
int isp[] = {0, 19, 12, 12, 13, 13, 13, 0};
int icp[] = {20, 19, 12, 12, 13, 13, 13, 0};
int j;

int main(void) {
    scanf("%s", expr);
    postfix();
    printf("%s\n", POSTFIX);

    return 0;
}

void push(precedence item) {
    if (top >= STACK_MAX - 1){
        fprintf(stderr, "\n수식을 너무 길게 적은 것 아닐까요?\n스택이 꽉 찼습니다.\n");
        exit(EXIT_FAILURE);
    }
    stack[++top] = item;
}

precedence pop(void) {
    if (top == -1){
        fprintf(stderr, "\nSTACK_POP_ERROR (empty stack)\n");
        exit(EXIT_FAILURE);
    }
    return stack[top--];
}

precedence getToken(char *symbol, int *n, char *expr) {
    *symbol = expr[(*n)++];
    switch (*symbol) {
        case '(' :
            return lparen;
        case ')' :
            return rparen;
        case '+' :
            return plus;
        case '-' :
            return minus;
        case '/' :
            return divide;
        case '*' :
            return times;
        case '%' :
            return mod;
        case ' ' :
            return eos;
        case '\0':
            return end;
        default :
            return operand;
    }
}

void printToken(precedence token) {
    switch (token) {
        case lparen :
            POSTFIX[j++] = '(';
            break;
        case rparen :
            POSTFIX[j++] = ')';
            break;
        case plus :
            POSTFIX[j++] = '+';
            break;
        case minus :
            POSTFIX[j++] = '-';
            break;
        case divide :
            POSTFIX[j++] = '/';
            break;
        case times :
            POSTFIX[j++] = '*';
            break;
        case mod :
            POSTFIX[j++] = '%';
            break;
        case eos :
            POSTFIX[j++] = ' ';
            return;
    }
}

void postfix(void) {
    char symbol;
    precedence token;
    int n = 0;
    j = 0;
    top = 0;
    stack[0] = eos;
    for (token = getToken(&symbol, &n, expr); token != end; token = getToken(&symbol, &n, expr)) {
        if (token == eos)
            continue;
        if (token == operand) {
            POSTFIX[j++] = symbol;
            while ((token = getToken(&symbol, &n, expr)) == operand)
                POSTFIX[j++] = symbol;
            n--;
        } else if (token == rparen) {
            while (stack[top] != lparen)
                printToken(pop());
            pop();
        } else {
            while (isp[stack[top]] >= icp[token])
                printToken(pop());
            push(token);
        }
    }
    while ((token = pop()) != eos)
        printToken(token);
}
