#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Process {
    int id;
    struct Process* next;
} Process;

Process* create_process(int id) {
    Process* new_process = (Process*)malloc(sizeof(Process));
    new_process->id = id;
    new_process->next = NULL;
    return new_process;
}

void enqueue(Process** front, Process** rear, int id) {
    Process* new_process = create_process(id);
    if (*rear == NULL) {
        *front = new_process;
    } else {
        (*rear)->next = new_process;
    }
    *rear = new_process;
}

Process* dequeue(Process** front, Process** rear) {
    if (*front == NULL) {
        printf("Fila vazia.\n");
        return NULL;
    }
    Process* temp = *front;
    *front = (*front)->next;
    if (*front == NULL) {
        *rear = NULL;
    }
    return temp;
}

void push(Process** stack, Process* process) {
    process->next = *stack;
    *stack = process;
}

Process* pop(Process** stack) {
    if (*stack == NULL) {
        printf("Pilha vazia.\n");
        return NULL;
    }
    Process* temp = *stack;
    *stack = (*stack)->next;
    return temp;
}

void display_stack(Process* stack) {
    printf("Histórico de processos finalizados (Pilha):\n");
    while (stack != NULL) {
        printf("Processo %d\n", stack->id);
        stack = stack->next;
    }
}

int main() {
    Process* queue_front = NULL;
    Process* queue_rear = NULL;
    Process* stack = NULL;

    enqueue(&queue_front, &queue_rear, 1);
    enqueue(&queue_front, &queue_rear, 2);
    enqueue(&queue_front, &queue_rear, 3);

    printf("Movendo processos da fila para a pilha (simulando execução)...\n");
    Process* p;
    while ((p = dequeue(&queue_front, &queue_rear)) != NULL) {
        printf("Processo %d foi executado.\n", p->id);
        push(&stack, p);
    }

    display_stack(stack);

    return 0;
}
