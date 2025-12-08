#ifndef TAD_PACIENTE
    #define TAD_PACIENTE
    #include "historico.h"
    
    typedef struct pac Paciente;
    typedef struct avl AVL;

    Paciente *paciente_criar(AVL *avl, char *nome, int id);
    bool paciente_apagar(Paciente **p);
    bool paciente_mudar_situacao_fila(Paciente *p, bool naFila);
    int paciente_getID(Paciente *p);
    char *paciente_getNome(Paciente *p);
    bool paciente_naFila(Paciente *p);
    void paciente_listar(Paciente *p);
    HISTORICO *paciente_gethistorico(Paciente *);
#endif