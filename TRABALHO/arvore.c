#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "arvore.h"


// Função para criar um novo nó e alocar espaço
struct no *novono(int chave)
{
    struct no *no = (struct no *)malloc(sizeof(struct no));
    no->chave = chave;
    no->esquerdo = no->direito = NULL;
    return no;
}

// Função para inserir um nó na árvore binária não balanceada
struct no *inserirNbalanceada(struct no *no, int chave)
{
    if (no == NULL)
    {
        return novono(chave);
    }
    if (chave < no->chave)
    {
        no->esquerdo = inserirNbalanceada(no->esquerdo, chave);
    }
    else
    {
        no->direito = inserirNbalanceada(no->direito, chave);
    }
    return no;
}



// Função para obter a altura de um nó
int altura(struct AVLno *N)
{
    if (N == NULL)
        return 0;
    return N->altura;
}

// Função para obter o máximo entre dois números
int max(int a, int b)
{
    return (a > b) ? a : b;
}

// Função para criar um novo nó da árvore AVL
struct AVLno *noAVLno(int chave)
{
    struct AVLno *no = (struct AVLno *)malloc(sizeof(struct AVLno));
    no->chave = chave;
    no->esquerdo = no->direito = NULL;
    no->altura = 1; // novo nó é inicialmente adicionado à altura 1
    return no;
}

// Função para realizar uma rotação à direita
struct AVLno *direitorotacao(struct AVLno *y)
{
    struct AVLno *x = y->esquerdo;
    struct AVLno *T2 = x->direito;

    // Realizar rotação
    x->direito = y;
    y->esquerdo = T2;

    // Atualizar alturas
    y->altura = max(altura(y->esquerdo), altura(y->direito)) + 1;
    x->altura = max(altura(x->esquerdo), altura(x->direito)) + 1;

    return x; // Retornar nova raiz
}

// Função para realizar uma rotação à esquerda
struct AVLno *esquerdorotacao(struct AVLno *x)
{
    struct AVLno *y = x->direito;
    struct AVLno *T2 = y->esquerdo;

    // Realizar rotação
    y->esquerdo = x;
    x->direito = T2;

    // Atualizar alturas
    x->altura = max(altura(x->esquerdo), altura(x->direito)) + 1;
    y->altura = max(altura(y->esquerdo), altura(y->direito)) + 1;

    return y; // Retornar nova raiz
}

// Função para obter o fator de balanceamento
int balanceamento(struct AVLno *N)
{
    if (N == NULL)
        return 0;
    return altura(N->esquerdo) - altura(N->direito);
}

// Função para inserir um nó na árvore AVL
struct AVLno *insereAVL(struct AVLno *no, int chave)
{
    if (no == NULL)
        return noAVLno(chave);

    if (chave < no->chave)
    {
        no->esquerdo = insereAVL(no->esquerdo, chave);
    }
    else
    {
        no->direito = insereAVL(no->direito, chave);
    }

    // Atualizar a altura do nó ancestral
    no->altura = 1 + max(altura(no->esquerdo), altura(no->direito));

    // Obter o fator de balanceamento
    int balance = balanceamento(no);

    // Se o nó se tornar desbalanceado, existem 4 casos

    // Caso à esquerda à esquerda
    if (balance > 1 && chave < no->esquerdo->chave)
    {
        return direitorotacao(no);
    }

    // Caso à direita à direita
    if (balance < -1 && chave > no->direito->chave)
    {
        return esquerdorotacao(no);
    }

    // Caso à esquerda à direita
    if (balance > 1 && chave > no->esquerdo->chave)
    {
        no->esquerdo = esquerdorotacao(no->esquerdo);
        return direitorotacao(no);
    }

    // Caso à direita à esquerda
    if (balance < -1 && chave < no->direito->chave)
    {
        no->direito = direitorotacao(no->direito);
        return esquerdorotacao(no);
    }

    return no; // Retornar o ponteiro do nó (inalterado)
}

int main()
{
    struct no *arvoreNbalanceada = NULL; // Raiz da árvore não balanceada
    struct AVLno *arvoreAVL = NULL;      // Raiz da árvore AVL

    // Abrindo o arquivo para leitura
    FILE *file = fopen("teste1.txt", "r"); // trocar o nome do file para teste2,teste3 ou testecurto para ler o arquivo diferente
    if (file == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    int chave;
    clock_t start, end;
    double cpu_time_used;

    // Inserindo na árvore não balanceada
    start = clock();
    for (int i = 0; i < 20000; i++)
    {                 // Repetir 20000 vezes para tamanho maximo to arquivo de entrada, para testes diminuir o loop
        rewind(file); // Reabrir o arquivo para cada iteração
        while (fscanf(file, "I %d", &chave) == 1)
        {
            arvoreNbalanceada = inserirNbalanceada(arvoreNbalanceada, chave);
        }
    }
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("%.6f - Tempo da arvore binaria nao balanceada(em segundos).\n", cpu_time_used); // Tempo da árvore não balanceada

    // Reabrindo o arquivo para inserções na árvore AVL
    rewind(file);

    // Inserindo na árvore AVL
    start = clock();
    for (int i = 0; i < 20000; i++)
    {                 // Repetir 20000 vezes para tamanho maximo to arquivo de entrada, para testes diminuir o loop
        rewind(file); // Reabrir o arquivo para cada iteração
        while (fscanf(file, "I %d", &chave) == 1)
        {
            arvoreAVL = insereAVL(arvoreAVL, chave);
        }
    }
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("%.6f - Tempo da arvore binaria balanceada(em segundos). \n", cpu_time_used); // Tempo da árvore balanceada

    fclose(file);
    return 0;
}