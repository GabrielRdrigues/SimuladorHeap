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


// Remove um nó da lista
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
// -------------------------------
//  Isso aqui é responsável por tirar áreas vazias da lista
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

int main(){
    char* heap = calloc(10 , sizeof(char) ); // Criando um heap
    areas_vazias* head= new_node(0,10); // Inicializando a lista de espaços livres 
    //(no início o heap está todo livre)
    id A[10]; // Identificadores
    int opcao=0;
    int qtd;
    char identificador;
    int i;
  
    while(opcao!=-1){
        puts("1 - First Fit \n2 - Best Fit");
        scanf("%d",&opcao); 
        if(opcao==-1)
            break;
        puts("Digite a quantidade de memória que quer alocar:");
        scanf("%d",&qtd);
        puts("Digite o ID:");
        scanf(" %c",&identificador);
        A[i].id=identificador;
        A[i].quantidade=qtd;
        switch (opcao)
        {
        case 1: // First FIT
            areas_vazias* auxiliar = head;
            while(auxiliar!=NULL){
                if(auxiliar->quantidade >= qtd){
                    fit(A[i],auxiliar->inicial,qtd,heap);
                    head = update_empty_memory(head,auxiliar->inicial,qtd);
                    break;
                }
                else
                    auxiliar=auxiliar->next;
            }
            if(auxiliar==NULL)
                puts("A área de memória que deseja alocar é muito grande");
            i++;
            break;
        case 2: // Best FIT
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
            fit(A[i],indice,qtd,heap);
            head = update_empty_memory(head,indice,qtd);
            break;
        case 3: // Remoção
            puts("Qual iD quer remover?");
            char aux3;
            scanf(" %c",&aux3);
            for(int j=0;j<10/*numeros de IDs do vetor Struct*/;j++){
                if(A[j].id==aux3){
                    // Função de remover
                }

            }
            break;
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
    while(head!=NULL){ // Imprimir a lista de espaços vazios
        printf("%d %d\n",head->quantidade,head->inicial);
        head=head->next;
    }


    free(aux5);
    free(heap);
    return 0;
}