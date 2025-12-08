#ifndef TAD_CADASTRO
    #define TAD_CADASTRO
    
    #include <stdbool.h>
    #include <stdlib.h>
    #include <stdio.h>
    typedef struct pac Paciente;// Necessário para evitar erros
    typedef struct avl AVL;

    AVL *avl_criar();
    void avl_apagar(AVL **avl);
    bool avl_inserir_paciente(AVL *avl, Paciente *p);
    bool avl_remover_paciente(AVL *avl, int id);
    void avl_listar(AVL *avl);
    Paciente *avl_buscar_paciente(AVL *avl, int id);
    int avl_gerar_id(AVL *avl);
#endif