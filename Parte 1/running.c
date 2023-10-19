#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Aluno
{
    char nome[30];
    int matricula;
    int idade;
    int nroDisciplinas;
    struct Aluno *prox;
} Aluno;

typedef struct Universidade
{
    char nome[30];
    int qtdAlunos;
    struct Universidade *prox;
    struct Aluno *inicioAluno;
} Universidade;

void InsereUniversidade(Universidade **inicio, char nomeUniversidade[30]);
void InsereAluno(Universidade **inicio, char nomeUniversidade[30]);
Universidade *BuscaUniversidade(Universidade *listaUniversidades, char nomeUniversidade[30]);
void BuscaAluno(Universidade *listaUniversidades, int matricula);
void RemoveUniversidade(Universidade **listaUniversidades, char nomeUniversidade[30]);
void RemoveAluno(Universidade **listaUniversidades, int matricula);
void salvaDados(Universidade *inicio);
Universidade *recuperaDados(Universidade **inicio);
void imprimeUniversidade(Universidade *head);
void imprimeAlunos(Universidade*);
void FecharPrograma(Universidade*);

int main()
{
    Universidade *inicio = NULL;
    recuperaDados(&inicio);
    int op, matricula;
    char nome_universidade[30];
    
    while (1)
    {   
        printf("------- MENU -------\n");
        printf("1) Insere Universidade\n");
        printf("2) Insere Aluno\n");
        printf("3) Busca Universidade\n");
        printf("4) Busca Aluno\n");
        printf("5) Remove Universidade\n");
        printf("6) Remove Aluno\n");
        printf("0) Fechar\n");
        printf("Insira o comando desejado: ");
        scanf("%d", &op);

        fflush(stdin);

        switch (op)
        {
        case 1:
            printf("Digite o nome da Universidade: ");
            scanf(" %[^\n]s", nome_universidade);
            InsereUniversidade(&inicio, nome_universidade);
            break;

        case 2:
            printf("Digite o nome da Universidade: ");
            scanf(" %[^\n]s", &nome_universidade);
            InsereAluno(&inicio, nome_universidade);
            break;

        case 3:
            printf("Digite o nome da Universidade: ");
            scanf(" %[^\n]s", nome_universidade);
            BuscaUniversidade(inicio, nome_universidade);
            break;

        case 4:
            printf("Digite a matricula do aluno: ");
            scanf("%d", &matricula);
            BuscaAluno(inicio, matricula);
            break;

        case 5:
            printf("Digite o nome da Universidade: ");
            scanf(" %[^\n]s", nome_universidade);
            RemoveUniversidade(&inicio, nome_universidade);
            break;

        case 6:
            printf("Digite a matricula do aluno: ");
            scanf("%d", &matricula);
            RemoveAluno(&inicio, matricula);
            break;

        case 0:
            FecharPrograma(inicio);
            break;

        default:
            printf("Opcao invalida!\n");
            break;
        }
    }
    
    if (inicio != NULL)
    {
        imprimeUniversidade(inicio);
        printf("\n\nDeseja inserir mais? (1 - sim / 0 - não): ");
        scanf("%d", &op);
    }


    imprimeUniversidade(inicio);
    salvaDados(inicio);

    return 0;
}

void InsereUniversidade(Universidade **inicio, char nomeUniversidade[30])
{
    Universidade *nova_uni = malloc(sizeof(Universidade));
    strcpy(nova_uni->nome, nomeUniversidade);
    nova_uni->qtdAlunos = 0;
    nova_uni->prox = NULL;
    nova_uni->inicioAluno = NULL;

    if (*inicio == NULL)
    {
        *inicio = nova_uni;
        return;
    }
    
    Universidade *aux = *inicio;
    int nomeExiste = 0;

    while(aux->prox != NULL)
    {
        if(strcmp(aux->nome, nova_uni->nome) == 0)
        {
            nomeExiste = 1;
            break;
        }
        aux = aux->prox;
    }

    if (nomeExiste)
    {
        printf("Ja existe uma universidade com o mesmo nome. Insercao incompleta.\n");
        free(nova_uni);
        return;
    }

    aux = *inicio;
    Universidade *anterior = NULL;
    while (aux != NULL && strcmp(nova_uni->nome, aux->nome) > 0)
    {
        anterior = aux;
        aux = aux->prox;
    }

    if(aux == *inicio)
    {
        nova_uni->prox = *inicio;
        *inicio = nova_uni;
        return;
    }
    nova_uni->prox = aux;
    anterior->prox = nova_uni;
}

void InsereAluno(Universidade **inicio, char nomeUniversidade[30])
{
    Universidade *universidade = BuscaUniversidade(*inicio, nomeUniversidade);

    int escolha = 0;

    // se ela não existir
    while (universidade == NULL)
    {
        printf("A universidade %s nao foi encontrada.\n", nomeUniversidade);
        printf("Deseja cadastrar o aluno em outra universidade? (1 para sim / 0 para nao) ");
        
        scanf("%d", &escolha);

        if (escolha == 1)
        {
            printf("Insira a universidade: ");
            scanf(" %[^\n]s", nomeUniversidade);
            universidade = BuscaUniversidade(*inicio, nomeUniversidade);
        }
        else
        {
            printf("Insercao de aluno cancelada.\n");
            return;
        }
    }
    
    Aluno *novo_aluno = malloc(sizeof(Aluno));

    printf("Digite o nome do aluno: ");
    scanf(" %[^\n]s", novo_aluno->nome);
    fflush(stdin);

    printf("Matricula: ");
    scanf("%d", &novo_aluno->matricula);

    printf("Idade: ");
    scanf("%d", &novo_aluno->idade);

    printf("Numero de disciplinas: ");
    scanf("%d", &novo_aluno->nroDisciplinas);

    novo_aluno->prox = NULL;

    Aluno *aux = universidade->inicioAluno;
    int matriculaExiste = 0;

    while (aux != NULL)
    {
        if (aux->matricula == novo_aluno->matricula)
        {
            matriculaExiste = 1;
            break;
        }
        aux = aux->prox;
    }

    if (matriculaExiste)
    {
        printf("Ja existe um aluno, nessa universidade, com esse numero de matricula. Insercao incompleta.\n");
        free(novo_aluno);
        return;
    }

    universidade->qtdAlunos++;

    if (universidade->inicioAluno == NULL)
    {
        universidade->inicioAluno = novo_aluno;
        return;
    }
    
    aux = universidade->inicioAluno;
    Aluno *anterior = NULL;
    while(aux != NULL && novo_aluno->matricula > aux->matricula)
    {
        anterior = aux;
        aux = aux->prox;
    }

    if(aux == universidade->inicioAluno)
    {
        novo_aluno->prox = universidade->inicioAluno;
        universidade->inicioAluno = novo_aluno;
        return;
    }

    novo_aluno->prox = aux;
    anterior->prox = novo_aluno;
    
}

Universidade *BuscaUniversidade(Universidade *listaUniversidades, char nomeUniversidade[30])
{
    Universidade *universidade_atual = listaUniversidades;

    while (universidade_atual != NULL)
    {
        if (strcmp(universidade_atual->nome, nomeUniversidade) == 0)
        {
            printf("Universidade cadastrada! Busca concluida.\n");
            return universidade_atual;
        }
       
        universidade_atual = universidade_atual->prox;
    }

    printf("Nao existe uma universidade cadastrada com esse nome!\n");
    return NULL;
}

void BuscaAluno(Universidade *listaUniversidades, int matricula)
{
    Universidade *universidadeAtual = listaUniversidades;

    while (universidadeAtual != NULL)
    {
        Aluno *alunoAtual = universidadeAtual->inicioAluno;

        while (alunoAtual != NULL)
        {
            if (alunoAtual->matricula == matricula)
            {
                printf("O aluno com a matricula %d foi encontrado na universidade %s.\n", matricula, universidadeAtual->nome);
                return;
            }
            alunoAtual = alunoAtual->prox;
        }

        universidadeAtual = universidadeAtual->prox;
    }

    printf("Aluno com a matricula %d nao encontrado em nenhuma universidade.\n", matricula);
}

void RemoveUniversidade(Universidade **listaUniversidades, char nomeUniversidade[30])
{
    Universidade *anterior = NULL;
    Universidade *universidadeAtual = *listaUniversidades;

    while (universidadeAtual != NULL)
    {
        if (strcmp(universidadeAtual->nome, nomeUniversidade) == 0)
        {
            Aluno *alunoAtual = universidadeAtual->inicioAluno;
            while (alunoAtual != NULL)
            {
                Aluno *temp = alunoAtual;
                alunoAtual = alunoAtual->prox;
                free(temp);
            }

            if (anterior == NULL)
            {
                *listaUniversidades = universidadeAtual->prox;
            }
            else
            {
                anterior->prox = universidadeAtual->prox;
            }

            free(universidadeAtual);
            printf("Universidade %s removida.\n", nomeUniversidade);
            return;
        }

        anterior = universidadeAtual;
        universidadeAtual = universidadeAtual->prox;
    }

    printf("Universidade %s nao encontrada.\n", nomeUniversidade);
}

void RemoveAluno(Universidade **listaUniversidades, int matricula)
{
    Universidade *universidadeAtual = *listaUniversidades;

    while (universidadeAtual != NULL)
    {
        Aluno *anterior = NULL;
        Aluno *alunoAtual = universidadeAtual->inicioAluno;

        while (alunoAtual != NULL)
        {
            if (alunoAtual->matricula == matricula)
            {
                if (anterior == NULL)
                {
                    universidadeAtual->inicioAluno = alunoAtual->prox;
                }
                else
                {
                    anterior->prox = alunoAtual->prox;
                }

                free(alunoAtual);
                universidadeAtual->qtdAlunos--;
                printf("Aluno com a matricula %d foi removido.\n", matricula);
                return;
            }

            anterior = alunoAtual;
            alunoAtual = alunoAtual->prox;
        }

        universidadeAtual = universidadeAtual->prox;
    }
    printf("Aluno nao encontrado.\n");
}

void salvaDados(Universidade *inicio)
{
    FILE *file = fopen("lista_uni.txt", "w");
    if (file == NULL)
    {
        printf("Erro ao criar o arquivo.\n");
        return;
    }

    Universidade *auxUniv = inicio;
    while (auxUniv != NULL)
    {
        fprintf(file, "%s\n", auxUniv->nome);
        fprintf(file, "%d\n", auxUniv->qtdAlunos);

        Aluno *auxAluno = auxUniv->inicioAluno;
        while (auxAluno != NULL)
        {
            fprintf(file, "%s\n", auxAluno->nome);
            fprintf(file, "%d\n", auxAluno->matricula);
            fprintf(file, "%d\n", auxAluno->idade);
            fprintf(file, "%d\n", auxAluno->nroDisciplinas);
            auxAluno = auxAluno->prox;
        }

        fprintf(file, "\n");
        auxUniv = auxUniv->prox;
    }

    fclose(file);
}

Universidade *recuperaDados(Universidade **inicio)
{
    FILE *file = fopen("lista_uni.txt", "r");
    if (file == NULL)
    {
        printf("Arquivo inexistente, sera criado.\n");
        return inicio;
    }

    Universidade *auxUniv = NULL;
    Aluno *auxAluno = NULL;
    char line[30];

    while (fgets(line, sizeof(line), file) != NULL)
    {
        line[strcspn(line, "\n")] = '\0';

        if (strlen(line) == 0)
        {
            auxUniv->prox = NULL;
            auxUniv = NULL;
            auxAluno = NULL;
        }
        else if (auxUniv == NULL)
        {
            // Cria uma nova entrada de universidade
            Universidade *nova_uni = malloc(sizeof(Universidade));
            strcpy(nova_uni->nome, line);

            fgets(line, sizeof(line), file);
            nova_uni->qtdAlunos = atoi(line);

            nova_uni->prox = NULL;
            nova_uni->inicioAluno = NULL;

            if (*inicio == NULL)
            {
                *inicio = nova_uni;
            }
            else
            {
                auxUniv = *inicio;
                while (auxUniv->prox != NULL)
                {
                    auxUniv = auxUniv->prox;
                }
                auxUniv->prox = nova_uni;
            }
            auxUniv = nova_uni;
        }
        else
        {
            // Cria uma nova entrada de aluno
            Aluno *novo_aluno = malloc(sizeof(Aluno));
            strcpy(novo_aluno->nome, line);

            fgets(line, sizeof(line), file);
            novo_aluno->matricula = atoi(line);

            fgets(line, sizeof(line), file);
            novo_aluno->idade = atoi(line);

            fgets(line, sizeof(line), file);
            novo_aluno->nroDisciplinas = atoi(line);

            novo_aluno->prox = NULL;

            if (auxUniv->inicioAluno == NULL)
            {
                auxUniv->inicioAluno = novo_aluno;
            }
            else
            {
                novo_aluno->prox = auxUniv->inicioAluno;
                auxUniv->inicioAluno = novo_aluno;
            }
        }
    }

    fclose(file);
    return *inicio;
}

void imprimeUniversidade(Universidade *head)
{
    if (head == NULL)
    {
        printf("Lista vazia\n");
        return;
    }

    Universidade *aux = head;
    while (aux != NULL)
    {
        printf("Universidade: %s\n", aux->nome);
        aux = aux->prox;
    }
}

void imprimeAlunos(Universidade *head)
{
    if (head == NULL || head->inicioAluno == NULL) {
        printf("Nenhum aluno cadastrado nesta universidade.\n");
        return;
    }

    Aluno *aluno = head->inicioAluno;
    printf("Alunos da Universidade %s:\n", head->nome);

    while (aluno != NULL) {
        printf("Nome: %s\n", aluno->nome);
        printf("Matrícula: %d\n", aluno->matricula);
        printf("Idade: %d\n", aluno->idade);
        printf("Número de disciplinas: %d\n", aluno->nroDisciplinas);
        printf("\n");
        aluno = aluno->prox;
    }
}

void FecharPrograma(Universidade *inicio) {
    salvaDados(inicio);
    printf("Programa encerrado.\n");
    exit(0);
}
