/* Alunos: Eduardo Purkote e Guilherme Mota 
GRR's      20182960          20197268

Programa principal que trata a entrada padrão (stdin) e imprime o resultado da arvore AVl em um arquivo de saída.Imprime as chaves com as respectivas alturas de cada Nodo

*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avl.c"

int main()
{
    FILE *entrada, *saida;
    char l[6];
    int contLinhas, calcula_fb = 0;
    char op;
    int  chave;
    tNo *nodo = NULL;
    
    //define arquivo de entrada
    entrada = stdin;
    if(!entrada)
    {
        printf("Erro no arquivo de entrada!\n");
        exit(1);
    }

    //leitura e processamento do arquivo de entrada
    contLinhas = 0;
    while(!feof(entrada))
    {
        fgets(l, 6, entrada);
        sscanf(l, "%c %d", &op, &chave);
        if(op == 'i')
        {
            if(busca(nodo, chave) == NULL) //se não existir chave inclui
                nodo = inclui(nodo, chave);
        }
        if(op == 'r')
        {   
            
            if(busca(nodo, chave) != NULL)
            {                                //se existir chave exclui
                
                nodo = removeNo(nodo,chave);
            }
        }
    contLinhas++;   
    }
    
    //define e imprime no arquivo de saída
    saida = stdout;
    if(!saida)
    {
        printf("Erro no arquivo de saída!\n");
        exit(1);
    }
    else
    {
        inOrder(nodo, saida);
    }

    fclose(entrada);
    fclose(saida);
    libera(nodo);

	return 0;
}
