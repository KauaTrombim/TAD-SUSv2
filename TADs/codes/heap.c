#include "../headers/heap.h"

struct NO{
    Paciente* pac;
    int situacao;
    time_t horaInsercao;
};

struct HEAP{
    NO *arvore[100];
    int ultimo;
};

Heap *heap_criar(){
    Heap *heap = malloc(sizeof(Heap));
    if(heap != NULL){
        heap->ultimo = -1;
    }
    return heap;
}

void heap_apagar(Heap **heap){
    if(heap == NULL){
        return;
    }
    free(*heap);
    *heap = NULL;
}

bool heap_vazia(Heap *heap){
    if(heap->ultimo == -1){
        return true;
    }
    return false;
}

bool heap_cheia(Heap *heap){
    if(heap->ultimo == 99){
        return true;
    }
    return false;
}

void heap_fixdown(Heap *heap, int indice){
    if(heap==NULL){
        return;
    }
    int maior = indice;
    if(2*indice+1 <= heap->ultimo){
        if(heap->arvore[2*indice+1]->situacao == heap->arvore[maior]->situacao && difftime(heap->arvore[2*indice+1]->horaInsercao,heap->arvore[maior]->horaInsercao) > 0 || heap->arvore[2*indice+1]->situacao > heap->arvore[maior]->situacao)
            maior = 2*indice+1;
    }
    if(2*indice+2 <= heap->ultimo){
        if(heap->arvore[2*indice+2]->situacao == heap->arvore[maior]->situacao && difftime(heap->arvore[2*indice+2]->horaInsercao,heap->arvore[maior]->horaInsercao) > 0 || heap->arvore[2*indice+2]->situacao > heap->arvore[maior]->situacao)
            maior = 2*indice+2;
    }
    if(maior!=indice){
        NO* aux = heap->arvore[indice];
        heap->arvore[indice] = heap->arvore[maior];
        heap->arvore[maior] = aux;
        heap_fixdown(heap, maior);
    }
}

void heap_fixup(Heap *heap){
    if(heap == NULL){
        return;
    }
    int w = heap->ultimo;
    int maior = (w - 1)/2;
    while(w > 0 && (heap->arvore[w]->situacao >= heap->arvore[maior]->situacao)){
        if(heap->arvore[w]->situacao == heap->arvore[maior]->situacao && difftime(heap->arvore[w]->horaInsercao,heap->arvore[maior]->horaInsercao) < 0){
            continue;
        }
        NO* aux = heap->arvore[maior];
        heap->arvore[maior] = heap->arvore[w];
        heap->arvore[w] = aux;
        w = maior;
        maior = (maior-1)/2;
    }
}

NO* heap_remover(Heap *heap){
    if(heap == NULL){
        return NULL;
    }
    if(heap_vazia(heap)){
        printf("Não há registros na fila de espera.\n");
        return NULL;
    }
    NO* item = heap->arvore[0];
    heap->arvore[0] = heap->arvore[heap->ultimo--];
    heap_fixdown(heap, 0);
    return item;
}

bool heap_inserir(Heap *heap, Paciente *pac, int priori){
    if(heap == NULL || pac == NULL){
        return false;
    }
    if(heap_cheia(heap)){
        if(heap->arvore[heap->ultimo]->situacao < priori){
            heap->ultimo--;
        }else{
            printf("A fila de espera está lotada.\n");
            return false;
        }
    }
    NO* item = malloc(sizeof(NO));
    time_t t = time(NULL);
    item->horaInsercao = t;
    item->pac = pac;
    item->situacao = priori;
    heap->arvore[++heap->ultimo] = item;
    heap_fixup(heap);
    return true;
}

void heap_listar(Heap *heap){
    if(heap == NULL){
        return;
    }
    Heap* copia = heap_criar();
    if(copia == NULL){
        printf("Falha na listagem de pacientes.\n");
        return;
    }
    for(int i = 0; i<heap->ultimo+1;i++){
        copia->arvore[i] = heap->arvore[i];
    }
    copia->ultimo = heap->ultimo;
    while(!heap_vazia(copia)){
        printf("Id: %d\tPaciente: %s\t", paciente_getID(copia->arvore[0]->pac), paciente_getNome(copia->arvore[0]->pac));
        switch(copia->arvore[0]->situacao){
            case 0:
                printf("Prioridade: Emergência\n");
                break;
            case 1:
                printf("Prioridade: Muito urgente\n");
                break;
            case 2:
                printf("Prioridade: Urgente\n");            
                break;
            case 3:
                printf("Prioridade: Pouco urgente\n");
                break;
            case 4:
                printf("Prioridade: Não urgente\n");
                break;
        }
        heap_remover(copia);
    }
    heap_apagar(&copia);
}

Paciente *no_getPac(NO* item){
    if(item == NULL){
        return NULL;
    }
    return item->pac;
}