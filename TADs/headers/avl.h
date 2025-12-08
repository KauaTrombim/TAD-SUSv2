#ifndef TAD_CADASTRO
    #define TAD_CADASTRO
    
    typedef struct pac Paciente;// Necessário para evitar erros
    typedef struct avl AVL;

    AVL *avl_criar();
    void avl_apagar(AVL **avl);
    bool avl_inserir_paciente(AVL *avl, Paciente *p);
    bool avl_remover_paciente(AVL *avl, int id);
    void avl_listar(AVL *avl);
    int avl_gerar_id(AVL *avl);

#endif