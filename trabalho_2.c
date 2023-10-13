#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct Processo {
    char nome[30];
    int prioridade;
    float taxaCompleto;
    float taxaPorCiclo;
    int tempoProcessamento;
    struct Processo *prox;
} Processo;

// Função para criar um novo processo
Processo* criarProcesso(char nome[30], int prioridade, float taxaPorCiclo, int tempoProcessamento) {
    Processo *novoProcesso = (Processo*)malloc(sizeof(Processo));
    strcpy(novoProcesso->nome, nome);
    novoProcesso->prioridade = prioridade;
    novoProcesso->taxaCompleto = 0.0;
    novoProcesso->taxaPorCiclo = taxaPorCiclo;
    novoProcesso->tempoProcessamento = tempoProcessamento;
    novoProcesso->prox = NULL;
    return novoProcesso;
}

// Função para inserir um processo na lista
void inserirProcesso(Processo **inicio, Processo *novoProcesso) {
    if (*inicio == NULL) {
        *inicio = novoProcesso;
        novoProcesso->prox = *inicio;
    } else {
        Processo *temp = *inicio;
        while (temp->prox != *inicio) {
            temp = temp->prox;
        }
        temp->prox = novoProcesso;
        novoProcesso->prox = *inicio;
    }
}

// Função para remover um processo da lista
void removerProcesso(Processo **inicio, Processo *processo) {
    if (*inicio == NULL) {
        return;
    }

    Processo *anterior = NULL;
    Processo *atual = *inicio;

    while (atual->prox != *inicio && atual != processo) {
        anterior = atual;
        atual = atual->prox;
    }

    if (atual == processo) {
        if (anterior == NULL) {
            *inicio = atual->prox;
        } else {
            anterior->prox = atual->prox;
        }
        free(atual);
    }
}

// Função para simular o processamento
void simularProcessamento(Processo *processo) {
    printf("%s entrou no processador\n", processo->nome);
    for (int i = 0; i < processo->tempoProcessamento; i++) {
        sleep(1);
        processo->taxaCompleto += processo->taxaPorCiclo;
    }
    printf("%s saiu do processador com taxa de %.2f%%\n", processo->nome, processo->taxaCompleto);

    if (processo->taxaCompleto >= 100.0) {
        printf("%s foi finalizado\n", processo->nome);
        removerProcesso(&processo->prox, processo);
        free(processo);
    }
}

// Função para imprimir a lista de processos
void imprimirLista(Processo *inicio) {
    if (inicio == NULL) {
        printf("Lista vazia.\n");
        return;
    }

    Processo *atual = inicio;
    do {
        printf("Nome: %s, Prioridade: %d, Taxa Completo: %.2f%%, Taxa Por Ciclo: %.2f%%, Tempo Processamento: %d\n",
               atual->nome, atual->prioridade, atual->taxaCompleto, atual->taxaPorCiclo, atual->tempoProcessamento);
        atual = atual->prox;
    } while (atual != inicio);
}

int main() {
    Processo *listaProcessos = NULL;

    // Exemplo com dois processos
    Processo *proc1 = criarProcesso("Proc1", 1, 5.0, 5);
    Processo *proc2 = criarProcesso("Proc2", 2, 10.0, 5);

    // Inserir processos na lista
    inserirProcesso(&listaProcessos, proc1);
    inserirProcesso(&listaProcessos, proc2);

    // Simular o processamento dos processos
    int numCiclos = 5; // Número de ciclos para simulação
    for (int i = 0; i < numCiclos; i++) {
        Processo *atual = listaProcessos;
        do {
            simularProcessamento(atual);
            atual = atual->prox;
        } while (atual != listaProcessos);
    }

    // Liberar memória alocada para os processos e a lista
    while (listaProcessos != NULL) {
        Processo *temp = listaProcessos;
        listaProcessos = listaProcessos->prox;
        free(temp);
    }

    return 0;
}
