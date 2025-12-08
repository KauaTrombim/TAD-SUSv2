#include "../headers/avl.h"

#define max(a, b) ((a > b) ? a : b)

typedef struct no_ NO;

struct no_{
    NO *esq;
    NO *dir;
    int altura;
    Paciente *paciente;
};

struct avl{
    NO *raiz;
    int profundidade; //Nunca usada
    int ultimoID; //Tornamos a inserção/criação mais fácil
};

AVL *avl_criar(){
    AVL *avl = (AVL *) malloc(sizeof(AVL));
    if(avl != NULL){
        avl->raiz = NULL;
        avl->profundidade = -1; //Convenção
        avl->ultimoID = -1;
    }

    return avl;
}

//Função auxiliar
void apagar_nos(NO *raiz){
    if(raiz != NULL){
        apagar_nos(raiz->esq);
        apagar_nos(raiz->dir);
        paciente_apagar(raiz->paciente);
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

int avl_altura_no(NO *raiz){
    if(raiz != NULL)
        return raiz->altura;
    else
        return -1;
}

NO *avl_criar_no(Paciente *p){
    NO *n = (NO *) malloc(sizeof(NO));
    if(n != NULL){ 
        n->esq = NULL;
        n->dir = NULL;
        n->altura = 0;
        n->paciente = p;
    }
    return n;
}

NO *rot_Direita(NO *a){
    NO *b = a->esq;
    a->esq = b->dir;
    b->dir = a;

    a->altura = max(avl_altura_no(a->esq), avl_altura_no(a->dir)) + 1;
    b->altura = max(avl_altura_no(b->esq), avl_altura_no(b->dir)) + 1;
    return b;
}

NO *rot_Esquerda(NO *a){
    NO *b = a->dir;
    a->dir = b->esq;
    b->esq = a;

    a->altura = max(avl_altura_no(a->esq), avl_altura_no(a->dir)) + 1;
    b->altura = max(avl_altura_no(b->esq), avl_altura_no(b->dir)) + 1;
    return b;
}

NO *rot_EsqDireita(NO *a){
    a->esq = rot_Esquerda(a->esq);
    return rot_Direita(a);
}

NO *rot_DirEsquerda(NO *a){
    a->dir = rot_Direita(a->dir);
    return rot_Esquerda(a);
}

NO *inserir_no(NO *raiz, Paciente *p){
    if(raiz == NULL){
        raiz = avl_criar_no(p);
    }
    else if (paciente_getID(p) < paciente_getID(raiz->paciente)){
        raiz->esq = inserir_no(raiz->esq, p);
    }
    else if (paciente_getID(p) > paciente_getID(raiz->paciente)){
        raiz->dir = inserir_no(raiz->dir, p);
    }

    raiz->altura = max(avl_altura_no(raiz->esq, raiz->dir)) + 1;
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
}

//poderia ser o min da direita
void troca_max_esq(NO *troca, NO *raiz, NO *ant){
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

NO *remover_no(NO *raiz, int id){
    NO *p;
    if(raiz == NULL){
        return NULL;
    }
    else if(id == paciente_getID(raiz->paciente)){
        //Não podemos remover o paciente ainda esperando
        if(paciente_naFila(raiz->paciente)){
            printf("AVL_remover_paciente: Nao e possivel remover um paciente em espera\n");
            return NULL;
        }
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
        avl->raiz = remover_no(avl->raiz, id);
        return avl != NULL;
    }
}

//Lista os pacientes em ordem
void avl_listar(AVL *avl){
    if(avl != NULL){
        listar(avl->raiz);
    }
}

void listar(NO *raiz){
    if(raiz != NULL){
        avl_listar(raiz->esq);
        paciente_imprimir(raiz->paciente);
        avl_listar(raiz->dir);
    }
}

int avl_gerar_id(AVL *avl) {
    if(avl != NULL){
        return avl->ultimoID + 1; 
    }
}

Paciente *avl_buscar_paciente(AVL *avl, int id){
    if(avl != NULL && id > -1){
        return busca(avl->raiz, id);
    }
    printf("AVL_buscar_paciente: erro ao acessar ponteiro ou ID invalido");
    return NULL;
}

Paciente *busca(NO *raiz, int id){
    if(raiz != NULL){
        if(paciente_getID(raiz->paciente) == id){
            return raiz->paciente;
        }
        else{
            if(paciente_getID(raiz->paciente) > id){
                busca(raiz->dir);
            }
            else{
                busca(raiz->esq);
            }
        }
    }
}   