#include <stdio.h>
#include <stdlib.h>

typedef struct areas_vazias{ // Lista Encadeada de áreas vazias no heap
    int inicial; // Indice
    int quantidade;
    struct areas_vazias* next;
}areas_vazias;

typedef struct id{
    char id;
    int quantidade;
    int inicial;
}id;

areas_vazias* new_node(int endereco,int quantidade){ // Criação de um nó na lista
    areas_vazias* node = (areas_vazias*)malloc(sizeof(areas_vazias));
    node->inicial = endereco;
    node->quantidade = quantidade;
    node->next = NULL;
    return node;
}

void fit(id identificador,int endereco,int quantidade,char* heap){
    for(int i = endereco;i<endereco+quantidade;i++){
        heap[i]= identificador.id;
    }
}

int main(){
    char* heap = malloc(40 * sizeof(char) );
    areas_vazias* head= new_node(0,40);
    id A;
    int opcao=0;
    int qtd;
    char identificador;
    scanf("%d",&opcao);

    // Criando identificador (A,B,C,D,qualquer letra)
    scanf("%d",&qtd);
    scanf(" %c",&identificador);
    A.id=identificador;
    A.quantidade=qtd;

    // First Fit
    if(opcao==1){ 
        areas_vazias* auxiliar = head;
        while(auxiliar!=NULL){
            if(auxiliar->quantidade >= qtd){
                fit(A,auxiliar->inicial,qtd,heap);
                break;
            }
            else
                auxiliar=auxiliar->next;
        }
        if(auxiliar==NULL)
            puts("A área de memória que deseja alocar é muito grande");
    }


    // Só para imprimir o heap no final pra ver se funfou
    for(int z = 0;z<40;z++){
        printf("%c ",heap[z]);
    }

    return 0;
}