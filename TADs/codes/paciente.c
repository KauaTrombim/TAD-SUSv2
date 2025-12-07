#include "../headers/setup.h"


#include "../headers/paciente.h"

struct pac{
    int id;
    char *nome; //Usamos ponteiro para alocar somente o espaço necessário no cadastro
    bool naFila;
};

Paciente *paciente_criar(char *nome, int id) {
    //Alocação do ponteiro para paciente
    Paciente *p = malloc(sizeof(Paciente));
    if (p == NULL) {
        printf("Paciente_criar: Erro ao alocar paciente\n");
        return NULL;
    }
    //Caso o id seja menor que 0 será gerado um novo id
    if(id<0){
        //p->id = registro_gerar_id(lista);
    }else{
        //O caso contrário é quando o paciente foi carregado da lista salva no JSON
        //Portanto não precisamos criar novos ids 
        p->id = id;
    }
    p->nome = nome;
    p->naFila = true; //Marca o paciente como na fila já na inserção
    return p;
}

void paciente_apagar(Paciente **p){
    if(p != NULL && *p != NULL){
        free((*p)->nome);
        free(*p);
        return;
    }
    printf("Paciente_apagar: Erro ao acessar o paciente\n");
    return;
}

void paciente_mudar_situacao_fila(Paciente *p, bool naFila){
    if(p != NULL){
        p->naFila = naFila;
        return;
    }
    printf("Paciente_situacao_fila: Erro ao acessar o paciente");
    return;
}

int paciente_getID(Paciente *p){
    if(p != NULL){
        return p->id;
    }
    printf("Paciente_getID: Erro ao acessar o paciente\n");
    return -1; //Código de erro
}

char *paciente_getNome(Paciente *p){
    if(p != NULL){
        return p->nome;
    }
    printf("Paciente_getNome: Erro ao acessar o paciente\n");
    return NULL;
}