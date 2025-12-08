#ifndef TAD_HEAP
    #define TAD_HEAP

    #include "paciente.h"
    #include <stdbool.h>
    #include <stdlib.h>
    #include <stdio.h>
    #include<time.h>

    typedef struct HEAP Heap;
    typedef struct NO NO;

    Heap *heap_criar();
    void heap_apagar(Heap **heap);
    bool heap_vazia(Heap *heap);
    bool heap_cheia(Heap *heap);
    void heap_fixdown(Heap *heap, int indice);
    void heap_fixup(Heap *heap);
    NO* heap_remover(Heap *heap);
    bool heap_inserir(Heap *heap, Paciente *pac, int priori);
    void heap_listar(Heap *heap); 
    Paciente *no_getPac(NO* item);

#endif