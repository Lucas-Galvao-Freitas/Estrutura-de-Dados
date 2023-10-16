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
        while (temp->prox != *inicio && temp->prox->prioridade > novoProcesso->prioridade) {
            temp = temp->prox;
        }
        if(temp->prox == *inicio && novoProcesso->prioridade > temp->prox->prioridade)
        {
            *inicio = novoProcesso;
        }
        novoProcesso->prox = temp->prox;
        temp->prox = novoProcesso;
    }
}

// Função para remover um processo da lista
void removerProcesso(Processo **inicio, Processo *processo) {
    if (*inicio == NULL) {
        return;
    }

    Processo *anterior = NULL;
    Processo *atual = *inicio;

    while (atual->prox != *inicio && atual->prox != processo) {
        anterior = atual;
        atual = atual->prox;
    }

    anterior = atual;
    atual = atual->prox;

    if (atual == processo) {

        if (atual == *inicio) {
            *inicio = atual->prox;
            anterior->prox = *inicio;
        } else {
            anterior->prox = atual->prox;
        }
        atual = NULL;
        free(atual);
    }
}

// Função para simular o processamento
void simularProcessamento(Processo *processo) {
    printf("%s entrou no processador\n", processo->nome);

    sleep(processo->tempoProcessamento);
    processo->taxaCompleto += processo->taxaPorCiclo;

    if(processo->taxaCompleto > 100)
        processo->taxaCompleto = 100;

    //quando um processo tiver taxaPorCiclo não divisivel por 100, ele completa com 100% ou com a taxa que ele alcançar?
    printf("%s saiu do processador com taxa de %.2f%%\n", processo->nome, processo->taxaCompleto);

    if (processo->taxaCompleto >= 100.0) {
        printf("%s foi finalizado\n", processo->nome);
        removerProcesso(&processo->prox, processo);
        free(processo);
        //acho que esse free nn é necessario
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
    Processo *proc1 = criarProcesso("Proc1", 1, 25, 5);
    Processo *proc2 = criarProcesso("Proc2", 3, 50, 5);
    Processo *proc3 = criarProcesso("Proc3", 2, 75, 2);

    // Inserir processos na lista
    inserirProcesso(&listaProcessos, proc1);
    inserirProcesso(&listaProcessos, proc2);
    inserirProcesso(&listaProcessos, proc3);

    // Simular o processamento dos processos
    Processo *atual = listaProcessos;
    do {
        if(atual->taxaCompleto >= 100 && atual == atual->prox)
        {
            break;
        }
        simularProcessamento(atual);
        atual = atual->prox;
    } while (atual != NULL);

    //Tambem acho que nn é necessario, essas memorias ja foram liberadas
    // Liberar memória alocada para os processos e a lista
    while (listaProcessos != NULL) {
        Processo *temp = listaProcessos;
        listaProcessos = listaProcessos->prox;
        free(temp);
    }

    return 0;
}
