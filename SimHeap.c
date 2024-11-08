/*  Gabriel Rodrigues Marques Valim && Nuno Martins do Couto && Breno Machado de Oliveira
    Simulador de Heap - Paradigmas de Programação 
*/

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

/*-----------------------------------------------------------------------*/
/* Cria um nó na lista encadeada*/
areas_vazias* new_node(areas_vazias* head,int endereco,int quantidade){ 
    areas_vazias* node = (areas_vazias*)malloc(sizeof(areas_vazias));
    node->inicial = endereco;
    node->quantidade = quantidade;
    node->next = head;
    return node;
}

/*-----------------------------------------------------------------------------*/
/* A função fit aloca no heap*/
void fit(id identificador,int endereco,int quantidade,char* heap){ // Colocar no heap
    for(int i = endereco;i<endereco+quantidade;i++){
        heap[i]= identificador.id;
    }
}

/*--------------------------------------------------------------------------------*/
/* As funções pop_front e remove_item removem um nó da lista encadeada*/
areas_vazias* pop_front(areas_vazias* head){
    if(head == NULL)
        return NULL;
    areas_vazias* new_head = head->next;
    free(head);
    return new_head;
}


areas_vazias* remove_item(areas_vazias* head, int c){
    if(head == NULL)
        return NULL;

    if(head->inicial == c)
        return pop_front(head);

    areas_vazias* p = head;
    areas_vazias* n = p->next;
    while(n != NULL && n->inicial != c){
        p = n;
        n = n->next;
    }

    if(n != NULL){
        p->next = n->next;
        free(n);
    }
    return head;
}
/*--------------------------------------------------------------*/

/*  A função update_empty_memory é responsável por atualizar 
a lista de areas vazias quando adicionamos no Heap*/
areas_vazias* update_empty_memory(areas_vazias* head,int indice,int qtd){ 
     areas_vazias* aux =head;
    while(aux->inicial!=indice){ 
        aux=aux->next;
    }
    if(aux!=NULL){
        aux->quantidade = aux->quantidade - qtd;
        if(aux->quantidade==0){
           head=remove_item(head,aux->inicial);
        }else{
            aux->inicial = aux->inicial+qtd;
        }
    }
    return head;
}
/*-------------------------------------------------------------------*/
// a função remove_from_heap remove um ID da memória heap
void remove_from_heap(char* heap,int endereco,int quantidade){
    for(int i = endereco;i<endereco+quantidade;i++){
        heap[i]= ' ';
    }
}
/*-------------------------------------------------------------------*/
// free_list dá free na lista encadeada
void free_list(areas_vazias* head){
   if(head){
       free_list(head->next);
       free(head);
   }
}

/*-------------------------------------------------------------------*/
/*-------------------------------------------------------------------*/

                                /* Início da main() */
int main(){
    char* heap = calloc(10 , sizeof(char) ); // Criando um heap
    areas_vazias* head = NULL;
    head= new_node(head,0,10); // Inicializando a lista de espaços livres 
    //(no início o heap está todo livre)
    id A[10]; // Identificadores
    for(int g=0;g<10;g++){
        A[g].id=' ';
    }
    int opcao=0;
    int qtd;
    char identificador;
    int i,j;
  
    while(opcao!=-1){
        // Menu
        puts("1 - First Fit \n2 - Best Fit\n3 - delete");
        scanf("%d",&opcao); 
        if(opcao==-1)
            break;
        if(opcao!=3){
            puts("Digite a quantidade de memória que quer alocar:");
            scanf("%d",&qtd);
            puts("Digite o ID:");
            scanf(" %c",&identificador);
        // Procurando espaço vazio no vetor de IDs
            for(j=0;j<10/*numeros de IDs do vetor Struct*/;j++){
                if(A[j].id==' '){
                    A[j].id=identificador;
                    A[j].quantidade=qtd;
                    break;
                            }
                                }
        }
        
        
        switch (opcao)
        {

        // First FIT
        case 1: 
            areas_vazias* auxiliar = head;
            while(auxiliar!=NULL){
                if(auxiliar->quantidade >= qtd){
                    A[j].inicial=auxiliar->inicial; // Guardando a posição do heap que o ID está
                    fit(A[j],auxiliar->inicial,qtd,heap);
                    head = update_empty_memory(head,auxiliar->inicial,qtd);
                    break;
                }
                else
                    auxiliar=auxiliar->next;
            }
            // Fazer um aviso se o usuário quiser alocar um área de memória muito grande
            break;

        // Best FIT
        case 2: 
            areas_vazias* auxiliar1=head;
            int menor = auxiliar1->quantidade;
            int indice= auxiliar1->inicial;
            while(auxiliar1!=NULL){
                if(auxiliar1->quantidade >= qtd && auxiliar1->quantidade <= menor){
                    indice=auxiliar1->inicial;
                    menor=auxiliar1->quantidade;
                }
                auxiliar1=auxiliar1->next;
            }
            A[j].inicial=indice; // Guardando a posição do heap que o ID está
            fit(A[j],indice,qtd,heap); 
            head = update_empty_memory(head,indice,qtd);
            // Fazer um aviso se o usuário quiser alocar um área de memória muito grande
            break;

        // Remoção do heap
        case 3: 
            puts("Qual ID quer remover?");
            char aux3; // Temporário apenas para salvar o char do ID do teclado
            scanf(" %c",&aux3);
            for(int k=0;k<10/*numeros de IDs do vetor Struct*/;k++){
                if(A[k].id==aux3){
                    remove_from_heap(heap,A[k].inicial,A[k].quantidade); // Função de remover do heap
                    A[k].id=' ';
                    head= new_node(head,A[k].inicial,A[k].quantidade); // Adicionar um nó na lista
                }
            }
            break;
        // Digitou número errado
        default:
            puts("numero errado");
            break;
        }
}
   
    // Só para imprimir o heap no final pra ver se funfou
    for(int z = 0;z<10;z++){
        printf("%c ",heap[z]);
    }
    puts("");
    areas_vazias* aux5 = head;
    while(aux5!=NULL){ // Imprimir a lista de espaços vazios
        printf("Quantidade disponível[%d] indíce[%d]\n",aux5->quantidade,aux5->inicial);
        aux5=aux5->next;
    }

    free_list(head);
    free(heap);
    return 0;
}