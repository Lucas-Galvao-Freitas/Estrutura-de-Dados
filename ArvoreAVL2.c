#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Product
{
    int code;
    char name[30];
    float price;
    int in_stock;
    int height;
    struct Product *left;
    struct Product *right;
} Product;

// funcoes exclusivas da AVL
int height(Product *);
Product *turnR(Product *);
Product *turnL(Product *);
int getBalance(Product *);
Product *minValueProduct(Product *);

// funcoes gerais
Product *createProduct(char nome[30], int code, float price, int in_stock);
void addProduct(Product **, Product *newProduct);
void findProduct(Product **, int); // busca por codigo
Product *recoverData(Product **root);

// funcao da altura
int height(Product *P)
{
    if (P == NULL)
        return 0;

    return P->height;
}

// Função para criar um novo nó de produto com os dados fornecidos
Product *createProduct(char name[30], int code, float price, int in_stock)
{
    // Aloca espaço na memória para um novo produto
    Product *newProduct = (Product *)malloc(sizeof(Product));

    // Atribui os valores fornecidos para as propriedades do novo produto
    strcpy(newProduct->name, name);
    newProduct->code = code;
    newProduct->price = price;
    newProduct->in_stock = in_stock;

    // Inicializa os ponteiros left e right como NULL, indicando que este é um novo nó na árvore
    newProduct->left = newProduct->right = NULL;
    // Inicializa a altura
    newProduct->height = 1;

    return newProduct; // Retorna o novo produto criado
}

// rotacionando para a direita uma subarvore de raiz P
Product *turnR(Product *P)
{
    Product *x = P->left;
    Product *y = P->right;

    x->right = P;
    P->left = y;

    P->height = max(height(P->left), height(P->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x; // nova raiz
}

// rotacionando para a esquerda uma subarvore de raiz P
Product *turnL(Product *P)
{
    Product *x = P->right;
    Product *y = x->left;

    x->left = P;
    P->right = y;

    P->height = max(height(P->left), height(P->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x; // nova raiz
}

// Função para adicionar um novo produto à árvore binária
void addProduct(Product **root, Product *newProduct)
{
    if (*root == NULL)
    {
        *root = newProduct; // Se a árvore estiver vazia, o novo produto se torna a raiz
        return;
    }

    // Compara o código do novo produto com o código do nó atual para decidir onde inserir na árvore
    if (newProduct->code < (*root)->code)
    {
        addProduct(&(*root)->left, newProduct); // Se o código for menor, vai para a subárvore esquerda
    }
    else
    {
        addProduct(&(*root)->right, newProduct); // Se for maior ou igual, vai para a subárvore direita
    }

    // atualiza a altura do no atual apos insercao
    (*root)->height = 1 + max(height((*root)->left), height((*root)->right));

    // calcula o fator de balanceamento do no atual
    int balance = getBalance(*root);

    // Verifica se o nó se tornou desbalanceado após a inserção
    // Se o nó estiver desbalanceado, realizamos as rotações apropriadas
    if (balance > 1 && newProduct->code < (*root)->left->code)
    {
        // Caso de rotação simples à direita
        *root = turnR(*root);
    }
    else if (balance > 1 && newProduct->code > (*root)->left->code)
    {
        // Caso de rotação dupla esquerda-direita
        (*root)->left = turnL((*root)->left);
        *root = turnR(*root);
    }
    else if (balance < -1 && newProduct->code > (*root)->right->code)
    {
        // Caso de rotação simples à esquerda
        *root = turnL(*root);
    }
    else if (balance < -1 && newProduct->code < (*root)->right->code)
    {
        // Caso de rotação dupla direita-esquerda
        (*root)->right = turnR((*root)->right);
        *root = turnL(*root);
    }
}

int getBalance(Product *P)
{
    if (P == NULL)
        return 0;

    return height(P->left) - height(P->right);
}
