#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Aluno{
	char nome[30];
	int matricula;
	int idade; 
	int nroDisciplinas;
	struct Aluno *prox;
}Aluno;

typedef struct Universidade{
	char nome[30];
	int qtdAlunos;
	struct Universidade *prox;
	struct Aluno *inicioAluno;
}Universidade;


void insere_universidade(Universidade** inicio)
{
    char nome[30];

    printf("Insira a Universidade: ");
    fgets(nome, 30, stdin);

    fflush(stdin);

    Universidade* nova_uni = malloc(sizeof(Universidade));
    strcpy(nova_uni->nome, nome);
    nova_uni->qtdAlunos = 0;
    nova_uni->prox = NULL;
    nova_uni->inicioAluno = NULL;


    if (*inicio == NULL) {
        *inicio = nova_uni;
        return;
    }

    Universidade* aux = *inicio;
    while (aux->prox != NULL && strcmp(nova_uni->nome, aux->nome) > 0) {
        aux = aux->prox;
    }

    if(aux == *inicio)
    {
        nova_uni->prox = *inicio;
        *inicio = nova_uni;
        return;
    }

    nova_uni->prox = aux->prox;
    aux->prox = nova_uni;
}


void insere_aluno(Universidade **uni_inicio)
{
    int matricula, idade, disciplinas;
    char nome[30], nome_uni[30];

    printf("Insira o nome do aluno: ");
    fgets(nome, 30, stdin);
    fflush(stdin);

    printf("Em qual Universidade deseja cadastra-lo? ");
    fgets(nome_uni, 30, stdin);
    fflush(stdin);

    printf("Numero de matricula: ");
    scanf("%d", &matricula);

    printf("Idade: ");
    scanf("%d", &idade);

    printf("Numero de disciplinas: ");
    scanf("%d", &disciplinas);

    Aluno *novo_aluno = (Aluno*) malloc(sizeof(Aluno));
    strcpy(novo_aluno->nome, nome);
    novo_aluno->matricula = matricula;
    novo_aluno->idade = idade;
    novo_aluno->nroDisciplinas = disciplinas;
    novo_aluno->prox = NULL;

    Universidade *universidade = *uni_inicio;
    while(strcmp(universidade->nome, nome_uni) != 0)
    {
        universidade = universidade->prox;
    }

    if(universidade->inicioAluno == NULL)
    {
        universidade->inicioAluno = novo_aluno;
        return;
    }

    Aluno *aux = universidade->inicioAluno;
    while(aux->prox != NULL && novo_aluno->matricula > aux->matricula)
    {
        aux = aux->prox;
    }

    if(aux == universidade->inicioAluno)
    {
        novo_aluno->prox = universidade->inicioAluno;
        universidade->inicioAluno = novo_aluno;
        return;
    }

    novo_aluno->prox = aux->prox;
    aux->prox = novo_aluno;
}

void salvaDados(Universidade* inicio) {
    FILE* file = fopen("lista_uni.txt", "w");
    if (file == NULL) {
        printf("Criando arquivo.\n");
        return;
    }

    Universidade* auxUniv = inicio;
    while (auxUniv != NULL) {
        fprintf(file, "%s\n", auxUniv->nome);
        fprintf(file, "%d\n", auxUniv->qtdAlunos);

        Aluno* auxAluno = auxUniv->inicioAluno;
        while (auxAluno != NULL) {
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

Universidade* recuperaDados(Universidade **inicio) {
    FILE* file = fopen("lista_uni.txt", "r");
    if (file == NULL) {
        printf("Arquivo inexistente, sera criado.\n");
        return NULL;
    }

    Universidade* auxUniv = NULL;
    Aluno* auxAluno = NULL;
    char line[30];

    while (fgets(line, sizeof(line), file) != NULL) {
        line[strcspn(line, "\n")] = '\0';

        if (strlen(line) == 0) {
            auxUniv->prox = NULL;
            auxUniv = NULL;
            auxAluno = NULL;
        } else if (auxUniv == NULL) {
            // Create a new university entry
            Universidade* nova_uni = malloc(sizeof(Universidade));
            strcpy(nova_uni->nome, line);

            fgets(line, sizeof(line), file);
            nova_uni->qtdAlunos = atoi(line);

            nova_uni->prox = NULL;
            nova_uni->inicioAluno = NULL;

            if (*inicio == NULL) {
                *inicio = nova_uni;
            } else {
            	auxUniv = *inicio;
            	while(auxUniv->prox != NULL){
            		auxUniv = auxUniv->prox;
				}
                auxUniv->prox = nova_uni;
            }
            auxUniv = nova_uni;
        } else {
            // Create a new student entry
            Aluno* novo_aluno = malloc(sizeof(Aluno));
            strcpy(novo_aluno->nome, line);

            fgets(line, sizeof(line), file);
            novo_aluno->matricula = atoi(line);

            fgets(line, sizeof(line), file);
            novo_aluno->idade = atoi(line);

            fgets(line, sizeof(line), file);
            novo_aluno->nroDisciplinas = atoi(line);

            novo_aluno->prox = NULL;

            if (auxAluno == NULL) {
                auxUniv->inicioAluno = novo_aluno;
            } else {
                auxAluno->prox = novo_aluno;
            }
            auxAluno = novo_aluno;
        }
    }

    fclose(file);
    return *inicio;
}

void imprime(Universidade* head){
	if(head == NULL){
		printf("Lista vazia");
		return;
	}
	
	Universidade *aux = head;
	while(aux != NULL){
		printf("%s ", aux->nome);
		aux = aux->prox;
	}
}

void imprime_alunos(Universidade *inicio)
{
    Aluno *aux = inicio->inicioAluno;
    while(aux != NULL)
    {
        printf("Nome: %s\nMatricula: %d\nIdade: %d\nNum Disciplinas: %d\n\n", aux->nome, aux->matricula, aux->idade, aux->nroDisciplinas);
        aux = aux->prox;
    }
}

int main() {
    Universidade *inicio = NULL;
	int op = 10;
	//recuperaDados(&inicio);
	char nome[30];
    char nome_aluno[30];

    int qtd_alunos;
    int matricula, idade, disciplinas;

    if(inicio != NULL)
    {
        imprime(inicio);
        printf("\n\ndeseja inserir mais?");
        scanf("%d", &op);
    }
	
    while(op)
    {
        printf("----- MENU -----");
        printf("1) Insere Universidade\n");
        printf("2) Insere Aluno\n");
        printf("3) Busca Universidade\n");
        printf("4) Busca Aluno\n");
        printf("5) Remove Universidade\n");
        printf("6) Remove Aluno\n");
        printf("0) Fechar\n");

        scanf("%d", &op);

        switch (op)
        {
        case 1:
            insere_universidade(&inicio);
            break;

        case 2:
            insere_aluno(&inicio);
            break;

        case 3:
            printf("Digite o nome da Universidade: ");
            fgets(nome, 30, stdin);
            fflush(stdin);
            BuscaUniversidade(&inicio, nome);
            break;

        case 4:
            printf("Digite a matricula do aluno: ");
            scanf("%d", &matricula);
            BuscaAluno(&inicio, matricula);
            break;
        
        case 5:
            printf("Digite o nome da Universidade: ");
            fgets(nome, 30, stdin);
            fflush(stdin);
            RemoveUniversidade(&inicio, nome);
            break;
        
        case 6:
            printf("Digite o nome do aluno: ");
            fgets(nome_aluno, 30, stdin);
            fflush(stdin);
            RemoveAluno(&inicio, nome_aluno);
            break;

        default:
            printf("Opcao invalida! Digite novamente: ");
            scanf("%d", &op);
            break;
        }
    }

	while(op == 1){
		fflush(stdin);
    	printf("Insira uma universidade:");
    	fgets(nome, 30, stdin);
    	
    	fflush(stdin);
    	
    	insere_universidade(&inicio);
    	
    	printf("deseja inserir mais?");
    	scanf("%d", &op);
    	
	}


    while(op == 2)
    {
        fflush(stdin);
        printf("Insira um novo aluno: ");
        fgets(nome_aluno, 30, stdin);

        fflush(stdin);

        printf("Qual Universidade? ");
        fgets(nome, 30, stdin);

        fflush(stdin);

        printf("Matricula: ");
        scanf("%d", &matricula);

        printf("Idade: ");
        scanf("%d", &idade);

        printf("Numero de disciplinas: ");
        scanf("%d", &disciplinas);

        insere_aluno(&inicio);

        printf("Deseja inserir mais? ");
        scanf("%d", &op);
    }
	
	//imprime(inicio);
    imprime_alunos(inicio);
	
    //salvaDados(inicio);

    return 0;
}
