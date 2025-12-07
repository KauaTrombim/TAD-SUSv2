#ifndef TAD_PACIENTE
    #define TAD_PACIENTE
    
    typedef struct pac Paciente;

    Paciente *paciente_criar(char *nome, int id);
    void paciente_apagar(Paciente **p);
    int paciente_getID(Paciente *p);
    char *paciente_getNome(Paciente *p);
    void paciente_mudar_situacao_fila(Paciente *p, bool naFila);
#endif