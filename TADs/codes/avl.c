#include "../headers/avl.h"
#include "../headers/paciente.h"
#include "../headers/avl.h"
#define max(a, b) ((a > b) ? a : b)

typedef struct no_ NO_AVL;

struct no_{
    NO_AVL *esq;
    NO_AVL *dir;
    int altura;
    Paciente *paciente;
};

struct avl{
    NO_AVL *raiz;
    int ultimoID; //Tornamos a inserção/criação mais fácil
};

AVL *avl_criar(){
    AVL *avl = (AVL *) malloc(sizeof(AVL));
    if(avl != NULL){
        avl->raiz = NULL;
        avl->ultimoID = 0;
    }

    return avl;
}

//Função auxiliar
void apagar_nos(NO_AVL *raiz){
    if(raiz != NULL){
        apagar_nos(raiz->esq);
        apagar_nos(raiz->dir);
        paciente_apagar(&raiz->paciente);
        free(raiz);
    }
}

void avl_apagar(AVL **avl){
    if(avl != NULL && *avl != NULL){
        apagar_nos((*avl)->raiz);
        free(*avl);
        *avl = NULL;
    }
}

int avl_altura_no(NO_AVL *raiz){
    if(raiz != NULL)
        return raiz->altura;
    else
        return -1;
}

NO_AVL *avl_criar_no(Paciente *p){
    NO_AVL *n = (NO_AVL *) malloc(sizeof(NO_AVL));
    if(n != NULL){ 
        n->esq = NULL;
        n->dir = NULL;
        n->altura = 0;
        n->paciente = p;
    }
    return n;
}

NO_AVL *rot_Direita(NO_AVL *a){
    NO_AVL *b = a->esq;
    a->esq = b->dir;
    b->dir = a;

    a->altura = max(avl_altura_no(a->esq), avl_altura_no(a->dir)) + 1;
    b->altura = max(avl_altura_no(b->esq), avl_altura_no(b->dir)) + 1;
    return b;
}

NO_AVL *rot_Esquerda(NO_AVL *a){
    NO_AVL *b = a->dir;
    a->dir = b->esq;
    b->esq = a;

    a->altura = max(avl_altura_no(a->esq), avl_altura_no(a->dir)) + 1;
    b->altura = max(avl_altura_no(b->esq), avl_altura_no(b->dir)) + 1;
    return b;
}

NO_AVL *rot_EsqDireita(NO_AVL *a){
    a->esq = rot_Esquerda(a->esq);
    return rot_Direita(a);
}

NO_AVL *rot_DirEsquerda(NO_AVL *a){
    a->dir = rot_Direita(a->dir);
    return rot_Esquerda(a);
}

NO_AVL *inserir_no(NO_AVL *raiz, Paciente *p){
    if(raiz == NULL){
        raiz = avl_criar_no(p);
    }
    else if (paciente_getID(p) < paciente_getID(raiz->paciente)){
        raiz->esq = inserir_no(raiz->esq, p);
    }
    else if (paciente_getID(p) > paciente_getID(raiz->paciente)){
        raiz->dir = inserir_no(raiz->dir, p);
    }

    raiz->altura = max(avl_altura_no(raiz->esq), avl_altura_no(raiz->dir)) + 1;
    int FB = avl_altura_no(raiz->esq) - avl_altura_no(raiz->dir);

    if(FB == -2){
        if((avl_altura_no(raiz->dir->esq) - avl_altura_no(raiz->dir->dir)) <= 0)
            raiz = rot_Esquerda(raiz);
        else{
            raiz = rot_DirEsquerda(raiz);
        }
    }
    if(FB == 2){
        if((avl_altura_no(raiz->esq->esq) - avl_altura_no(raiz->esq->dir)) >= 0)
            raiz = rot_Direita(raiz);
        else{
            raiz = rot_EsqDireita(raiz);
        }
    }
    return raiz;
}

bool avl_inserir_paciente(AVL *avl, Paciente *p){
    if(avl != NULL && p != NULL){
        avl->raiz = inserir_no(avl->raiz, p);
        avl->ultimoID++;
        return avl->raiz != NULL;
    }
    return false;
}

//poderia ser o min da direita
void troca_max_esq(NO_AVL *troca, NO_AVL *raiz, NO_AVL *ant){
    if(troca->dir != NULL){
        troca_max_esq(troca->dir, raiz, troca);
        return;
    }
    if(raiz == ant){
        ant->esq = troca->esq;
    }
    else{
        ant->dir = troca->esq;
    }

    Paciente *p = raiz->paciente;
    raiz->paciente = troca->paciente;
    paciente_apagar(&p);
    free(troca);
    troca = NULL;
}

NO_AVL *remover_no(NO_AVL *raiz, int id){
    NO_AVL *p;
    if(raiz == NULL){
        return NULL;
    }
    else if(id == paciente_getID(raiz->paciente)){
        p = raiz;
        //Caso tenha 1 ou nenhum filho
        if(raiz->esq == NULL || raiz->dir == NULL){
            p = raiz;
            if(raiz->esq == NULL){
                raiz = raiz->dir;
            }
            else{
                raiz = raiz->esq;
            }
            paciente_apagar(&p->paciente);
            free(p);
            p = NULL;
        }
        else{
            troca_max_esq(raiz->esq, raiz, (raiz));
        }
    }
    else if(id < paciente_getID(raiz->paciente)){
        raiz->esq = remover_no(raiz->esq, id);
    }
    else if(id > paciente_getID(raiz->paciente)){
        raiz->dir = remover_no(raiz->dir, id);
    }

    if(raiz != NULL){
        raiz->altura = max(avl_altura_no(raiz->esq), avl_altura_no(raiz->dir)) + 1;
        //Verificações de balancemento (caiu na prova)
        if(avl_altura_no(raiz->esq) - avl_altura_no(raiz->dir) == -2){
            if(avl_altura_no(raiz->dir->esq) - avl_altura_no(raiz->dir->dir) <= 0){
                raiz = rot_Esquerda(raiz);
            }
            else{
                rot_DirEsquerda(raiz);
            }
        }

        if(avl_altura_no(raiz->esq) - avl_altura_no(raiz->dir) == 2){
            if(avl_altura_no(raiz->dir->esq) - avl_altura_no(raiz->dir->dir) >= 0){
                raiz = rot_Direita(raiz);
            }
            else{
                rot_EsqDireita(raiz);
            }
        }
    }
    return raiz;
}

bool avl_remover_paciente(AVL *avl, int id){
    if(avl != NULL && id > -1){
        Paciente *p = avl_buscar_paciente(avl, id);
        if(p == NULL){
            printf("avl_remover_paciente: Paciente nao encontrado.\n");
            return false;
        }
        if(paciente_naFila(p)){
            printf("avl_remover_paciente: Nao e possivel remover um paciente que esta na fila de espera\n");
            return false;
        }
        avl->raiz = remover_no(avl->raiz, id);
        return true;
    }
    printf("avl_remover_paciente: erro ao acessar ponteiro ou id invalido.\n");
    return false;
}

void listar(NO_AVL *raiz){
    if(raiz != NULL){
        listar(raiz->esq);
        paciente_imprimir(raiz->paciente);
        printf("-----------------------\n");
        listar(raiz->dir);
    }
}

Paciente *busca(NO_AVL *raiz, int id){
    if(raiz != NULL){
        if(paciente_getID(raiz->paciente) == id){
            return raiz->paciente;
        }
        else{
            if(paciente_getID(raiz->paciente) > id){
                busca(raiz->dir, id);
            }
            else{
                busca(raiz->esq, id);
            }
        }
    }
    return NULL;
}   

Paciente *avl_buscar_paciente(AVL *avl, int id){
    if(avl != NULL){
        return busca(avl->raiz, id);
    }
    printf("AVL_buscar_paciente: erro ao acessar ponteiro ou ID invalido");
    return NULL;
}

//Lista os pacientes em ordem
void avl_listar(AVL *avl){
    if(avl != NULL){
        listar(avl->raiz);
    }
}

int avl_gerar_id(AVL *avl) {
    if(avl != NULL){
        return avl->ultimoID; 
    }
    return -1;
}

void salvar_nos_recursivo(NO_AVL *raiz, FILE *f, bool *primeiro) {
    if (raiz != NULL) {
        salvar_nos_recursivo(raiz->esq, f, primeiro);

        Paciente *p = raiz->paciente;
        
        if (!(*primeiro)) {
            fprintf(f, ",");
        }
        *primeiro = false;

        fprintf(f, "\n\t{");
        fprintf(f, "\n\t\t\"id\": %d,\n", paciente_getID(p));
        fprintf(f, "\t\t\"nome\": \"%s\",\n", paciente_getNome(p));
        fprintf(f, "\t\t\"naFila\": %d,\n", paciente_naFila(p) ? 1 : 0);

        fprintf(f, "\t\t\"histórico\": {");
        HISTORICO *h = paciente_gethistorico(p);
        PROCEDIMENTO *proc = historico_getultimo(h);
        int qtd = historico_getquantidade(h);

        for(int j = 0; j < qtd; ++j){
            if(j == 0){
                fprintf(f, "\n");
            }
            fprintf(f, "\t\t\t\"procedimento\": \"%s\"", procedimento_gettexto(proc));
            
            if(j < qtd - 1){
                fprintf(f, ",");
            }
            fprintf(f, "\n");
            
            proc = procedimento_getanterior(proc); 
            
            if(j == qtd - 1){
                fprintf(f, "\t\t");
            }
        }
        fprintf(f, "}\n");
        fprintf(f, "\t}");

        salvar_nos_recursivo(raiz->dir, f, primeiro);
    }
}

bool avl_salvar(AVL *avl) {
    if (avl == NULL) return false;

    FILE *f = fopen("lista.json", "w");
    if (f == NULL) {
        return false;
    }

    fprintf(f, "[");
    
    bool primeiro = true;
    salvar_nos_recursivo(avl->raiz, f, &primeiro);

    fprintf(f, "\n]");
    fclose(f);
    return true;
}

void avl_carregar(AVL *avl) {
    if (avl != NULL) {
        FILE *f = fopen("lista.json", "r");
        if (f == NULL) {
            return;
        }

        char buffer[256], nome[101], procedimentoTexto[101];
        int id;
        int naFilaInt;
        Paciente *paciente = NULL;

        while (fgets(buffer, 255, f) != NULL) {
            if (strstr(buffer, "\"id\":")) {
                sscanf(buffer, "%*[^:]: %d", &id);
            } 
            else if (strstr(buffer, "\"nome\":")) {
                sscanf(buffer, "%*[^:]: \"%[^\"]", nome);
                paciente = paciente_criar(avl, nome, id); 
                if(id > avl->ultimoID) {
                    avl->ultimoID = id;
                }
            }
            else if (strstr(buffer, "\"naFila\":")) {
                sscanf(buffer, "%*[^:]: %d", &naFilaInt);
                if (paciente != NULL) {
                    paciente_mudar_situacao_fila(paciente, (naFilaInt == 1));
                }
            }
            else if (strstr(buffer, "\"histórico\":")) {
                if(paciente != NULL){
                    while (fgets(buffer, 255, f) != NULL && !strstr(buffer, "}")) {
                        if (strstr(buffer, "\"procedimento\":")) {
                            sscanf(buffer, "%*[^:]: \"%[^\"]", procedimentoTexto);
                            historico_inserir(paciente_gethistorico(paciente), procedimentoTexto);
                        }
                    }
                    historico_inverter(paciente_gethistorico(paciente));
                    avl_inserir_paciente(avl, paciente);
                    paciente = NULL;
                }
            }
        }
        fclose(f);
    }
}