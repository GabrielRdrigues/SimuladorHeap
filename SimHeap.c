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
        aux->quantidade = aux->quantidade - qtd; // Quanto espaços temos
        if(aux->quantidade==0){
           head=remove_item(head,aux->inicial);
        }else{
            aux->inicial = aux->inicial+qtd; // Onde vai iniciar
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


/* -------------------------------------------------------------*/

// Função para ordenar a lista de áreas vazias usando Insertion Sort
areas_vazias* insertion_sort(areas_vazias* head) {
    if (head == NULL || head->next == NULL) {
        return head; // Lista vazia ou com um elemento, já está ordenada
    }

    areas_vazias* sorted = NULL; // Lista ordenada
    areas_vazias* current = head; // Nó atual da lista desordenada

    while (current != NULL) {
        areas_vazias* next = current->next; // Guarda o próximo nó
        areas_vazias* prev = NULL; // Nó anterior na lista ordenada
        areas_vazias* ptr = sorted; // Itera sobre a lista ordenada

        while (ptr != NULL && ptr->inicial < current->inicial) {
            prev = ptr;
            ptr = ptr->next;
        }

        // Insere o nó `current` na posição correta na lista ordenada
        if (prev == NULL) {
            current->next = sorted;
            sorted = current;
        } else {
            current->next = ptr;
            prev->next = current;
        }

        current = next; // Avança para o próximo nó na lista desordenada
    }

    return sorted; // Retorna a lista ordenada
}

/*-------------------------------------------------------------------------------*/


// Função aglutinadora de áreas vazias vzinhas

areas_vazias* aglutinacao(areas_vazias* head) {
    if (head == NULL || head->next == NULL) {
        return head;
    }

    areas_vazias* current = head;
    while (current->next != NULL) {
        if (current->inicial + current->quantidade == current->next->inicial) {
            // Agrupar as áreas
            current->quantidade += current->next->quantidade;
            areas_vazias* temp = current->next; // Guarde o próximo nó temporariamente
            current->next = temp->next; // Pule o nó que será liberado
            free(temp); // Liberar o nó que foi agrupado
        } else {
            current = current->next;
        }
    }

    return head;
}

// Função para ver qual nó da lista tem a maior quantidade disponível
int maior_qtd_lista(areas_vazias* a){
    int maior = a->quantidade;
    while(a!=NULL){
        if(a->quantidade>maior)
            maior = a->quantidade;
        a=a->next;
    }
    return maior;
}

/*-------------------------------------------------------------------*/
/*-------------------------------------------------------------------*/

                             /* Início da main() */
int main(){
    /*Declaração de variáveis */
    char* heap = calloc(10 , sizeof(char) ); // Criando um heap
    areas_vazias* head = NULL;
    head= new_node(head,0,10); // Inicializando a lista de espaços livres
    //(no início o heap está todo livre)
    id A[10]; // Identificadores
    for(int g=0;g<10;g++){ // Esse for serve para inicializar o ID com "nada" que no nosso código é um espaço
        A[g].id=' ';
    }
    int opcao=0;
    int qtd;
    char identificador;
    int i,j;
    int last_indice = 0; // Utilizado para o Next Fit
    int indice;
    areas_vazias* auxiliar,*auxiliar1;
    /*Fim da declaração de variáveis*/

    while(opcao!=6){
        /* Impressão do heap*/
        for(int z = 0;z<10;z++){
            printf("[%c] ",heap[z]);
        }

        // Leitura do teclado & Menu
        puts("\n1 - First Fit \n2 - Best Fit\n3 - Next Fit\n4 - Worst Fit\n5 - Delete\n6 - Sair");
        scanf("%d",&opcao);
        if(opcao==6)
            break;
        if(opcao!=5){

            if (head == NULL){
                printf("\n\nMemória Lotada, remova um espaço antes de alocar!\n\n");
                opcao=5;
            }
            else{
                puts("Digite a quantidade de memória que quer alocar:");
                scanf("%d",&qtd);

                if(qtd<=maior_qtd_lista(head)){
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
                }else{
                    puts("\nVocê quer alocar mais que a quantidade disponível!");
                    printf("\n");
                    opcao=20;
                }

            }


        }


        switch (opcao)
        {

        // First FIT
        case 1:
            auxiliar = head;
            while(auxiliar!=NULL){
                if(auxiliar->quantidade >= qtd){
                    A[j].inicial=auxiliar->inicial; // Guardando a posição do heap que o ID está
                    fit(A[j],auxiliar->inicial,qtd,heap);
                    last_indice = auxiliar->inicial; // Último indíce vai ser o atual
                    head = update_empty_memory(head,auxiliar->inicial,qtd);
                    break;
                }
                else
                    auxiliar=auxiliar->next;
            }
            break;

        // Best FIT
        case 2:
            auxiliar1=head;
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
            last_indice = indice; // Último indíce vai ser o atual
            head = update_empty_memory(head,indice,qtd);
            break;

        // Next Fit
        case 3:
            auxiliar = head;
            while (auxiliar != NULL && auxiliar->inicial < last_indice) {
                auxiliar = auxiliar->next;
            }

            if (auxiliar == NULL)
                auxiliar = head;

            areas_vazias* start = auxiliar;
            do {
                if (auxiliar->quantidade >= qtd) {
                    A[j].inicial = auxiliar->inicial;
                    fit(A[j], auxiliar->inicial, qtd, heap);
                    last_indice = auxiliar->inicial;
                    head = update_empty_memory(head, auxiliar->inicial, qtd);
                    break;
                }
                auxiliar = auxiliar->next;
                if (auxiliar == NULL)
                    auxiliar = head;

            } while (auxiliar != start);

            if (auxiliar == start && start->quantidade < qtd) {
                printf("Sem espaço pro next fit\n");
            }
            break;

        // Worst FIT
        case 4:
            auxiliar1=head;
            int maior = auxiliar1->quantidade;
            indice= auxiliar1->inicial;
            while(auxiliar1!=NULL){
                if(auxiliar1->quantidade >= qtd && auxiliar1->quantidade >= maior){
                    indice=auxiliar1->inicial;
                    maior=auxiliar1->quantidade;
                }
                auxiliar1=auxiliar1->next;
            }
            A[j].inicial=indice; // Guardando a posição do heap que o ID está
            fit(A[j],indice,qtd,heap);
            last_indice = indice; // Último indíce vai ser o atual
            head = update_empty_memory(head,indice,qtd);
            break;

        // Remoção do Heap
        case 5:
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
            head = insertion_sort(head); // Ordena o heap
            head = aglutinacao(head); /*Isso vai corrigir o erro de ter, por exemplo
        um nó com índice 0 até 3 e outro nó com indíce 4 até 6, essa função vai juntar isso em um
        nó só*/
            break;
        default:
            break;
        }

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
