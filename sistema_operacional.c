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
    Process* new_process = create_process(id); // Cria novo processo
    if (*rear == NULL) { // Verifica se existe uma cauda
        *front = new_process; // Caso não tenha cauda coloca esse novo processo como cabeça
    } else {
        (*rear)->next = new_process; // Caso tenha uma cauda, coloca esse novo processo como seu next.
    }
    *rear = new_process; // Define o processo atual como a nova cauda
}

Process* dequeue(Process** front, Process** rear) {
    if (*front == NULL) { // Verifica se a pilha está vazia
        printf("Fila vazia.\n");
        return NULL;
    }
    Process* temp = *front; // Cria um ponteiro temporário para segurar o front
    *front = (*front)->next; // O novo front se tornará o next do front
    if (*front == NULL) { // Caso o next do front seja NULL a lista fica vazia
        *rear = NULL;
    }
    return temp; // Retorna o valor temporário.
}

void push(Process** stack, Process* process) {
    process->next = *stack; // Se a lista estiver vazia o próximo será null, caso não esteja será o último adicionado
    *stack = process; // Torna a cabeça a da pilha o novo processo.
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
    while (stack != NULL) { // Printar processos históricos até chegar no final da pilha.
        printf("Processo %d\n", stack->id);
        stack = stack->next;
    }
}

int main() {
    Process* queue_front = NULL; // Inicializa o processo cabeça da fila.
    Process* queue_rear = NULL; // Inicializa o processo cauda da fila.
    Process* stack = NULL; //Inicializa a pilha.

    enqueue(&queue_front, &queue_rear, 1); //Adiciona um processo na fila.
    enqueue(&queue_front, &queue_rear, 2); //Adiciona um processo na fila.
    enqueue(&queue_front, &queue_rear, 3); //Adiciona um processo na fila.

    printf("Movendo processos da fila para a pilha (simulando execução)...\n");
    Process* p; //Cria uma variável para segurar o processo que será tirado da fila.
    while ((p = dequeue(&queue_front, &queue_rear)) != NULL) { // Loop que irá rodar até a fila está vazia.
        printf("Processo %d foi executado.\n", p->id);
        push(&stack, p); // Adiciona o processo que foi retirado da fila em uma pilha.
    }

    display_stack(stack); //Mostra o histórico da pilha.

    return 0;
}
