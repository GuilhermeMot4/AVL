/* Alunos: Eduardo Purkote e Guilherme Mota 
GRR's      20182960          20197268

Arquivo que contem a definição de todas as funções utilizadas para o funcionamento da arvore AVL e também a estrutura de dados que foi utilizada para desenvolver o Trabalho.



*/

#ifndef __AVL__
#define __AVL__


//Estrutura de dados que define a Árvore AVL

typedef struct tNo
{
	int chave;
	struct tNo *esq, *dir, *pai;
	int alt;
}tNo;

//Função que cria um novo Nodo
tNo * criaNo(int chave);

//Função que calcula a profundidade de cada nodo

int profundidade(tNo *no);

//Função que determina a altura dos Nodos

int altura(tNo *p);

//Função que calcula e retorna o Fator de balanceamento
int Calc_fb(tNo *Nodo);

//Função que realiza travessia em ordem na arvore

void inOrder(tNo *no, FILE *saida);

//Fução que remove Nó com filho a direita
tNo *removeNoDir(tNo *Nodo);

//FUnção que remove Nó com um Filho a esquerda
tNo *removeNoEsq(tNo *Nodo);

//Função que remove uma Folha e ajusta Fator de balanceamento
tNo *removeFolha(tNo *Nodo);

//Função que remove um Nó com dois filhos
tNo *removeNoDois(tNo *Nodo);

//Função que remove um Nodo através da busca
tNo *removeNo(tNo* Nodo, int chave);

//Função que realiza rotação para a esquerda
tNo * rotEsquerda(tNo *p);

//Função que realiza rotação para a direita

tNo * rotDireita(tNo *p);

//Função que realiza rotação dupla à Direita
tNo *rotDuplaDir(tNo *Nodo);

//Função que realiza rotação dupla à Esquerda
tNo* rotDuplaEsq(tNo *Nodo);

//Função que verifica balancemanto ao inserir um novo elemento
tNo * InserAvlBal(tNo *no, int chave);

//Função que faz a verificação após remoção de um elemento da árvore
tNo * RemoveAvlBal(tNo *no);

//Função que encontra o maior valor da esquerda da arvore para achar o antecessor
tNo * max(tNo *no);

//Função que realiza a busca binária na arvore

tNo * busca(tNo *no, int chave);

//Função de Exclusão de um Nodo
tNo * exclui(tNo *no);
 
//Função que realiza a inclusão com base no fator de balanceamento

tNo * inclui(tNo *no, int chave);

//Função que libera um Nó

void libera(tNo * no);


#endif
