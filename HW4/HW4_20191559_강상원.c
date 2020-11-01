#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int key;
} element;

typedef struct stack *stackPointer;
typedef struct stack {
    element data;
    stackPointer link;
} stack;

typedef struct queue *queuePointer;
typedef struct queue {
    element data;
    queuePointer link;
} queue;
stackPointer top;
queuePointer front, rear;
/////////////////////////////
void stack_push(int input) {
    stackPointer tmp = top;
    stackPointer NOVEL = (stackPointer) malloc(sizeof(stackPointer));
    NOVEL->data.key = input;
    NOVEL->link = tmp;

    top = NOVEL;
}

int stack_pop(int *input) {
    if (top == NULL) return 0;
    *input = top->data.key;
    stackPointer tmp = top;
    top = top->link;

    free(tmp);
    return 1;
}

void queue_push(int input) {
    queuePointer NOVEL = (queuePointer) malloc(sizeof(queuePointer));
    NOVEL->link = NULL;
    NOVEL->data.key = input;

    if (front == NULL) {
        front = NOVEL;
        rear = NOVEL;
    } else {
        rear->link = NOVEL;
        rear = NOVEL;
    }
}

int queue_pop(int *input) {
    if (front == NULL) return 0;
    *input = front->data.key;
    queuePointer tmp = front;
    front = front->link;
    free(tmp);
    return 1;
}

int main() {
    FILE *fp = fopen("input.txt", "r");

    int option, input;
    while (~fscanf(fp, "%d", &option)) {
        if (option == 0) {
            fscanf(fp, "%d", &input);
            stack_push(input);
            queue_push(input);
        } else {
            stack_pop(&input);
            queue_pop(&input);
        }
    }

    while (stack_pop(&input))
        printf("%d ", input);

    printf("\n");
    while (queue_pop(&input))
        printf("%d ", input);

    return 0;
}
