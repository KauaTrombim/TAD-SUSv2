
#ifndef HISTORICO_H
    #define HISTORICO_H
    #include<stdbool.h>
    #include<stdlib.h>

    typedef struct historico_ HISTORICO;
    typedef struct procedimento_ PROCEDIMENTO;

    HISTORICO *historico_criar();
    bool historico_apagar(HISTORICO **);
    bool historico_inserir(HISTORICO *, char *);
    bool historico_retirar(HISTORICO *);
    bool historico_cheio(HISTORICO *);
    char **historico_consultar_procedimento(HISTORICO *);
    bool historico_vazio(HISTORICO *);
    int historico_getquantidade(HISTORICO *);
    PROCEDIMENTO *historico_getultimo(HISTORICO *);
    PROCEDIMENTO *procedimento_getanterior(PROCEDIMENTO *);
    char *procedimento_gettexto(PROCEDIMENTO *);
    void historico_inverter(HISTORICO *);

#endif