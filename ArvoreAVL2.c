#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define max(a, b) ((a) > (b) ? (a) : (b))

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
Product *findMin(Product *);

// funcoes gerais
Product *createProduct(char nome[30], int code, float price, int in_stock);
void addProduct(Product **, Product *newProduct);
void findProduct(Product **, int); // busca por codigo
Product *removeProduct(Product *, int);
Product *recoverData(Product **root);
void spaces(int);
void printList(Product *, int);

void main ()
{
    Product *root = NULL; // Inicializa a raiz da árvore AVL

    // Adicionando alguns produtos para teste
    addProduct(&root, createProduct("Produto A", 50, 100.0, 10));
    addProduct(&root, createProduct("Produto B", 30, 75.0, 20));
    addProduct(&root, createProduct("Produto C", 70, 120.0, 5));
    addProduct(&root, createProduct("Produto D", 20, 90.0, 15));
    addProduct(&root, createProduct("Produto E", 10, 110.0, 25));

    // Imprime a árvore AVL
    printf("Arvore AVL:\n");
    printList(root, 0);

    // Remover um produto (exemplo: remover o produto com código 20)
    root = removeProduct(root, 20);

    // Imprime a árvore AVL após a remoção
    printf("\nArvore AVL apos a remocao do produto com codigo 20:\n");
    printList(root, 0);
}

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

// Função para remover um produto da árvore binária
Product *removeProduct(Product *root, int code) {
    if (root == NULL) {
        return root; // Se a árvore estiver vazia ou o produto não for encontrado, retorna a raiz original
    }

    // Procura pelo produto a ser removido
    if (code < root->code) {
        root->left = removeProduct(root->left, code); // Se o código for menor, vai para a subárvore esquerda
    } else if (code > root->code) {
        root->right = removeProduct(root->right, code); // Se for maior, vai para a subárvore direita
    } else {
        // Se o produto for encontrado, realiza a remoção
        if (root->left == NULL || root->right == NULL) {
            // Se o nó tiver no máximo um filho
            Product *temp = root->left ? root->left : root->right;

            // Caso sem filhos
            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else { // Caso com um filho
                *root = *temp; // Copia o conteúdo do filho não nulo para o nó atual
            }
            free(temp); // Libera a memória do nó removido
        } else {
            // Se o nó tiver dois filhos, encontra o sucessor na subárvore direita
            Product *temp = findMin(root->right); // Encontra o nó mais à esquerda na subárvore direita

            // Copia os dados do sucessor para este nó
            root->code = temp->code;
            strcpy(root->name, temp->name);
            root->price = temp->price;
            root->in_stock = temp->in_stock;

            // Remove o sucessor
            root->right = removeProduct(root->right, temp->code);
        }
    }

    // Se a árvore tinha apenas um nó, então retorna
    if (root == NULL) {
        return root;
    }

    // Atualiza a altura do nó atual
    root->height = 1 + max(height(root->left), height(root->right));

    // Calcula o fator de balanceamento do nó atual
    int balance = getBalance(root);

    // Verifica se o nó se tornou desbalanceado após a remoção
    // Se o nó estiver desbalanceado, realiza as rotações apropriadas
    if (balance > 1 && getBalance(root->left) >= 0) {
        return turnR(root); // Caso de rotação simples à direita
    }
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = turnL(root->left);
        return turnR(root); // Caso de rotação dupla esquerda-direita
    }
    if (balance < -1 && getBalance(root->right) <= 0) {
        return turnL(root); // Caso de rotação simples à esquerda
    }
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = turnR(root->right);
        return turnL(root); // Caso de rotação dupla direita-esquerda
    }

    return root; // Retorna a raiz atualizada
}

void spaces(int n)
{
    for(int i = 0; i < n; i++)
        printf(" ");
}

void printList(Product *root, int space)
{
    if(root == NULL) return;

    space += 5;

    printList(root->right, space);

    printf("\n");
    spaces(space);
    printf("%d (%s)\n", root->code, root->name);

    printList(root->left, space);
}

Product *findMin(Product *p)
{   
    // Só percorrendo a subárvore esquerda, nada de novo.
    while(p->left != NULL)
        p = p->left;

    return p;
}
