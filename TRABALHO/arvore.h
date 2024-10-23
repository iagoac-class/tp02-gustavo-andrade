#ifndef _H_ARVORES
#define _H_ARVORES

#include <time.h>

// Estrutura para um nó de árvore binária
struct no
{
    int chave;
    struct No *esquerdo;
    struct No *direito;
};
// Estrutura para um nó da árvore AVL(balanceada)
struct AVLno
{
    int chave;
    struct AVLno *esquerdo;
    struct AVLno *direito;
    int altura;
};

// Função que cria um novo nó e alocar espaço
struct no *novono(int chave);

// Função para inserir um nó na árvore binária não balanceada
struct no *inserirNbalanceada(struct no *no, int chave);

// Função para obter a altura de um nó
int altura(struct AVLno *N);

// Função para obter o máximo entre dois números
int max(int a, int b);

// Função para criar um novo nó da árvore AVL
struct AVLno *noAVLno(int chave);

// Função para realizar uma rotação à direita
struct AVLno *direitorotacao(struct AVLno *y);

// Função para realizar uma rotação à esquerda
struct AVLno *esquerdorotacao(struct AVLno *x);

// Função para obter o fator de balanceamento
int balanceamento(struct AVLno *N);

// Função para inserir um nó na árvore AVL
struct AVLno *insereAVL(struct AVLno *no, int chave);

#endif // _H_ARVORES