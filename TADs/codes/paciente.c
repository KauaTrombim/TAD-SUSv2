#include "../headers/avl.h"
#include "../headers/historico.h"
#include "../headers/paciente.h"

struct pac{
    int id;
    char *nome; //Usamos ponteiro para alocar somente o espaço necessário no cadastro
    bool naFila;
    HISTORICO *historico;
};



Paciente *paciente_criar(AVL *avl, char *nome, int id) {
    //Alocação do ponteiro para paciente
    Paciente *p = malloc(sizeof(Paciente));
    if (p == NULL) {
        printf("Paciente_criar: Erro ao alocar paciente\n");
        return NULL;
    }
    //Caso o id seja menor que 0 será gerado um novo id
    if(id<0){
        p->id = avl_gerar_id(avl);
    }else{
        //O caso contrário é quando o paciente foi carregado da lista salva no JSON
        //Portanto não precisamos criar novos ids 
        p->id = id;
    }
    p->nome = nome;
    //p->historico = historico_criar(); //Temos que incluir essa função
    p->naFila = true; //Marca o paciente como na fila já na inserção
    p->historico = historico_criar();
    return p;
}

bool paciente_apagar(Paciente **p){
    if(p != NULL && *p != NULL){
        free((*p)->nome);
        historico_apagar(&(*p)->historico);
        free(*p);
        return true;
    }
    printf("Paciente_apagar: Erro ao acessar o paciente\n");
    return false;
}

bool paciente_mudar_situacao_fila(Paciente *p, bool naFila){
    if(p != NULL){
        p->naFila = naFila;
        return true;
    }
    printf("Paciente_situacao_fila: Erro ao acessar o paciente");
    return false;
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

bool paciente_naFila(Paciente *p){
    if(p != NULL){
        return p->naFila;
    }
    return true; //evita que possa ser removido
}

void paciente_imprimir(Paciente *p){
    if(p != NULL){  
        printf("ID: %d\n", p->id);
        printf("Nome: %s\n", p->nome);
        printf("------Histórico------\n");
        PROCEDIMENTO *procedimento = historico_getultimo(p->historico);
        for(int i = historico_getquantidade(p->historico); i>0; i--){
            printf("Procediemnto %d: %s\n", i, procedimento_gettexto(procedimento));
            procedimento = procedimento_getanterior(procedimento);
        }
        printf("------Histórico------\n");
        char *state = (p->naFila) ? "Sim" : "Nao";
        printf("Esta na fila: %s\n", state);
        printf("------------------------------------------");
    }
}

HISTORICO *paciente_gethistorico(Paciente *paciente) {
    if (paciente == NULL) {
        return NULL;
    }
    return paciente->historico;
}