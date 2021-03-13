/* Alunos: Eduardo Purkote e Guilherme Mota 
GRR's      20182960          20197268

Arquivo que contem o funcionamento das funções utilizadas para o funcionamento da arvore AVL



*/

#include <stdio.h>
#include <stdlib.h>
#include "avl.h"

//Função que cria um novo Nodo
tNo * criaNo(int chave)
{
	tNo *no; 
	no = malloc(sizeof(tNo));
	no->esq = NULL;
	no->dir = NULL;
	no->pai = NULL;
	no->chave = chave;
	no->alt  = 0;

	return no;

}

//Função que calcula a profundidade de cada nodo. Usada na travessia em ordem

int profundidade(tNo *no)
{
	if(no->pai == NULL)
		return 0;
	else
		return 1 + profundidade(no->pai);
	
}

//Função que determina a altura dos Nodos

int altura(tNo *p) 
{
    
    if (p == NULL) return -1;

    int altura_esq, altura_dir;

    if(p->dir == NULL) altura_dir = 0;

    else altura_dir = 1 + (p->dir->alt);
    
    if(p->esq==NULL) altura_esq = 0;

    else altura_esq = 1 + (p->esq->alt);
    
    if (altura_esq > altura_dir)
    {
      return altura_esq;
    }
 
    else return altura_dir;
   
}

//Função que calcula e retorna o Fator de balanceamento
int Calc_fb(tNo *Nodo)
{
  if(Nodo == NULL) return -1;
  return altura(Nodo->esq) - altura(Nodo->dir);
  
}

//Função que realiza travessia em ordem na arvore

void inOrder(tNo *no, FILE *saida)
{
    if(no != NULL)
    { 
        inOrder(no->esq,saida);
        fprintf(saida, "%d,", no->chave); //Imprime A chave contida no Nodo na saida padrão
        fprintf(saida, "%d\n", profundidade(no));// Em seguida imprime a altura respectiva aquele Nodo
        inOrder(no->dir, saida);
    }
}

//Função que realiza rotação para a esquerda
tNo * rotEsquerda(tNo *p)
{
    tNo *q = p->dir;
    p->dir = q->esq;
    q->pai=p->pai;
    p->pai=q;

    if(q->esq != NULL)
       q->esq->pai=p;
    q->esq = p;


    p->alt=altura(p);
    q->alt=altura(q);

    
    return q;
}

//Função que realiza rotação para a direita

tNo * rotDireita(tNo *p)
{
    tNo *q = p->esq;
    p->esq = q->dir;
    q->pai = p->pai;
    p->pai = q;
    if (q->dir != NULL)
      q->dir->pai = p;
    q->dir = p;

    p->alt=altura(p);
    q->alt=altura(q);
   
    return q;
}

//Função que realiza rotação dupla à Direita
tNo *rotDuplaDir(tNo *Nodo)
{
  Nodo->esq = rotEsquerda(Nodo->esq);
  Nodo=rotDireita(Nodo);
  return Nodo;
}

//Função que realiza rotação dupla à Esquerda
tNo* rotDuplaEsq(tNo *Nodo)
{
  Nodo->dir = rotDireita(Nodo->dir);
  Nodo= rotEsquerda(Nodo);
  return Nodo;
}

//FUnção que remove Nó com um Filho a esquerda
tNo *removeNoEsq(tNo *Nodo)
{    
    
     tNo *novaRaiz=Nodo->esq;
     free(Nodo);
     return novaRaiz;
}

//Fução que remove Nó com filho a direita
tNo *removeNoDir(tNo *Nodo)
{   
   
    tNo *novaRaiz=Nodo->dir;
    free (Nodo); 
    return novaRaiz;
}

//Função que remove um Nodo Folha 
tNo *removeFolha(tNo *Nodo)
{ 
  free(Nodo);
  Nodo=NULL;
  return Nodo;     
}

//Função que remove um Nó com dois filhos
tNo *removeNoDois(tNo *Nodo)
{
    tNo* novaRaiz;
    int aux;
    novaRaiz= max(Nodo->esq);
    aux=novaRaiz->chave;
    Nodo=removeNo(Nodo,aux);
    Nodo->chave=aux;
    
    return Nodo;

}

//Função que verifica balancemanto ao inserir um novo elemento
tNo *InserAvlBal(tNo * no, int chave)
{
   if(Calc_fb(no)>= 2)
   {
     if(chave<no->esq->chave)
       no=rotDireita(no);
     else
       no=rotDuplaDir(no);
   }
   if(Calc_fb(no)<=-2)
   {
      if(chave>no->dir->chave)
        no=rotEsquerda(no);
      else
        no=rotDuplaEsq(no);
   }
 return no;
}

//Função que faz a verificação após remoção de um elemento da árvore
tNo* RemoveAvlBal(tNo *no)
{
  if(Calc_fb(no)==2)
  {
     if(Calc_fb(no->esq)>-1)
       no=rotDireita(no);
     else
       no=rotDuplaDir(no);
  }
  if(Calc_fb(no)==-2)
  {
     if(Calc_fb(no->dir)<=0)
       no=rotEsquerda(no);
     else
       no=rotDuplaEsq(no);
  }
  return no;
}

//Função que encontra o maior valor da arvore para achar o antecessor e o retorna
tNo *max(tNo *Nodo)
{
    if (Nodo->dir == NULL) return Nodo;
    else
        return max(Nodo->dir);
}


//Função que realiza a busca binária na árvore

tNo *busca(tNo *no, int chave)
{
    if (no == NULL) return NULL;
    if (no->chave == chave) return no;
    if (chave < no->chave)
        return busca (no->esq, chave);
    else
        return busca (no->dir, chave);
}



/*Função de Exclusão de um Nodo
 Caso 1: Nodo Folha
 Caso 2: Nodo com Filho à Direita ou à Esquerda
 Caso 3: Nodo com dois filhos

*/
tNo *exclui(tNo *no) 
{
    tNo *NovaRaiz;
    if (no == NULL) 
    {
      NovaRaiz=NULL;
    }  
    

    //Caso 1
    if (no->esq == NULL && no->dir == NULL) //Exclui Folha
    { 
        NovaRaiz=removeFolha(no);
        
    } 


    //Caso 2
    else if (no->esq == NULL) //apenas um filho a direita
    {
     
      NovaRaiz=removeNoDir(no);
      
    } 

    else if (no->dir == NULL) // Nodo com um filho à esquerda
    {
      
      NovaRaiz=removeNoEsq(no);
    }

    //Caso 3
    else //Nodo com dois filhos
    {  
         
       NovaRaiz=removeNoDois(no);
    }
  
    return NovaRaiz;  
}

//Função que remove um Nodo através da busca
tNo *removeNo(tNo *Nodo, int chave)
{
  if(busca(Nodo,chave))
  {
     if(Nodo->chave == chave)
     {
       Nodo = exclui(Nodo);
     }
     else if(chave < Nodo->chave)
     {
       Nodo->esq = removeNo(Nodo->esq,chave);
     }     
     else if (chave > Nodo->chave)
     {
       Nodo->dir = removeNo(Nodo->dir,chave);
     }
      
      
     Nodo=RemoveAvlBal(Nodo);
      
  }
  
  else printf("Elemento não encontrado!\n");

  
  return Nodo;
}


//Função que realiza a inclusão com base no fator de balanceamento

tNo *inclui(tNo *no, int chave)
{
    if(busca(no,chave)) return no;

    if (no == NULL) 
    {
        no = criaNo(chave);        
        return no;    
    }
    
    else if(chave< no->chave)
    {
        no->esq=inclui(no->esq,chave);
        no->esq->pai = no;
    }
    else
    {
        no->dir=inclui(no->dir,chave);
        no->dir->pai = no;
    }
    no=InserAvlBal(no,chave);
    no->alt= altura(no);
    return no;
}

//Função que libera um Nó

void libera(tNo * no)
{
    if(no == NULL)
        return;
    libera(no->esq);
    libera(no->dir);
    free(no);
    no = NULL;
}


