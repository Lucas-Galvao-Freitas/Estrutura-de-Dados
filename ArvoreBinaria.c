#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Product
{
    int code;
    char name[30];
    float price;
    int in_stock;
    struct Product *left;
    struct Product *right;
} Product;

Product *createProduct(char nome[30], int code, float price, int in_stock);
void addProduct(Product **, Product *newProduct);
void findProduct(Product **, int); // busca por codigo
Product *recoverData(Product **root);

void main ()
{


}

// Função para criar um novo nó de produto com os dados fornecidos
Product *createProduct(char name[30], int code, float price, int in_stock)
{
    // Aloca espaço na memória para um novo produto
    Product *newProduct = (Product*)malloc(sizeof(Product));
    
    // Atribui os valores fornecidos para as propriedades do novo produto
    strcpy(newProduct->name, name);
    newProduct->code = code;
    newProduct->price = price;
    newProduct->in_stock = in_stock;
    
    // Inicializa os ponteiros left e right como NULL, indicando que este é um novo nó na árvore
    newProduct->left = newProduct->right = NULL;

    return newProduct; // Retorna o novo produto criado
}

// Função para adicionar um novo produto à árvore binária
void addProduct(Product **root, Product *newProduct)
{
    if(*root == NULL)
    {
        *root = newProduct; // Se a árvore estiver vazia, o novo produto se torna a raiz
        return;
    }

    // Compara o código do novo produto com o código do nó atual para decidir onde inserir na árvore
    if(newProduct->code < (*root)->code)
    {
        addProduct(&(*root)->left, newProduct); // Se o código for menor, vai para a subárvore esquerda
    }
    else
    {
        addProduct(&(*root)->right, newProduct); // Se for maior ou igual, vai para a subárvore direita
    }
}

























Product *recoverData(Product **root)
{
    FILE *file = fopen("data.csv", "r");

    if (file == NULL)
    {
        printf("Arquivo inexistente, sera criado. \n");
        return root;
    }
    else
    {
        printf("Erro ao carregar o arquivo!\n");
        return;
    }

    Product *auxProd = NULL;
    while(fscanf(arquivo_csv, "%[^;];%d;%f;%d", product.nome, &product.codigo,
&product.preco, &product.quant_estoque) == 4){
//implemente aqui o código para montar a árvore enviando a //struct produto
}
       

}

