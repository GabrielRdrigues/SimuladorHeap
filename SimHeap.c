#include <stdio.h>
#include <stdlib.h>

typedef struct areas_vazias{ // Lista Encadeada de áreas vazias no heap
    int inicial; // Indice
    int quantidade;
    struct areas_vazias* next;
}areas_vazias;

typedef struct id{ // Identificador (ex: A,B,E,D,F,G,Z,Y)
    char id;
    int quantidade; // Quantidade que está alocado para o identificador
    int inicial; // índice inicial
}id;

areas_vazias* new_node(int endereco,int quantidade){ // Criação de um nó na lista
    areas_vazias* node = (areas_vazias*)malloc(sizeof(areas_vazias));
    node->inicial = endereco;
    node->quantidade = quantidade;
    node->next = NULL;
    return node;
}

void fit(id identificador,int endereco,int quantidade,char* heap){ // Colocar no heap
    for(int i = endereco;i<endereco+quantidade;i++){
        heap[i]= identificador.id;
    }
}

areas_vazias* search_empty_memory(char* heap){ // Vasculhando no heap pra achar espaço livre
    areas_vazias* aux =NULL;
    areas_vazias* lista_retornada=NULL;
    int i = 0;
    int quantidade_memoria_livre = 0;
    
    while(i<10){ // 40 pois nosso,nesse exemplo,tem heap tem 10 espaços
        if(heap[i]==0)
            quantidade_memoria_livre++; // Se achou espaço livre incrementa 
        else{ // Se achou algum espaço ALOCADO, então vamos verificar se
            if(quantidade_memoria_livre>0){ // Se antes tinha algum espaço livre então temos que salvar
                if(aux==NULL){ // Se é o primeiro nó
                    aux=new_node(i-quantidade_memoria_livre,quantidade_memoria_livre);
                    lista_retornada = aux;
                } 
                else{
                    aux->next = new_node(i-quantidade_memoria_livre,quantidade_memoria_livre);
                    aux=aux->next;
                }
            }
            quantidade_memoria_livre=0;
        }
        i++;
    }
    // Quando i>10, pode ser que tenha uma área de memória no final do heap e precisamos salvar se tiver.
    if(quantidade_memoria_livre>0){
        aux = new_node(i-quantidade_memoria_livre,quantidade_memoria_livre);
        if(lista_retornada==NULL)
            lista_retornada=aux;
    }

    return lista_retornada; // Retornamos a lista encadeada
}

int main(){
    char* heap = calloc(10 , sizeof(char) ); // Criando um heap
    areas_vazias* head= new_node(0,10); // Inicializando a lista de espaços livres 
    //(no início o heap está todo livre)
    id A; // Identificador teste
    int opcao=0;
    int qtd;
    char identificador;
    scanf("%d",&opcao); // First Fit = 1

    // Criando identificador (A,B,C,D,qualquer letra e a quantidade que quer alocar)
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
                head = search_empty_memory(heap);
                break;
            }
            else
                auxiliar=auxiliar->next;
        }
        if(auxiliar==NULL)
            puts("A área de memória que deseja alocar é muito grande");
    }


    // Só para imprimir o heap no final pra ver se funfou
    for(int z = 0;z<10;z++){
        printf("%c ",heap[z]);
    }
    puts("");
    while(head!=NULL){ // Imprimir a lista de espaços vazios
        printf("%d %d\n",head->quantidade,head->inicial);
        head=head->next;
    }

    return 0;
}