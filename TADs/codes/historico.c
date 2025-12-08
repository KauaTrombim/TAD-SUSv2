#include "historico.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct procedimento_ {
    char texto[101];
    PROCEDIMENTO *anterior;
};

struct historico_ {
    PROCEDIMENTO *ultimoProcedimento;
    int quantidadeProcedimentos;
};

//Função para criar histórico
HISTORICO *historico_criar() {
    //Alocação do histórico
    HISTORICO *novo = malloc(sizeof(HISTORICO));
    if(novo == NULL) {
        return NULL;
    }
    //No incicio não há procedimentos, portanto quantidade nula
    novo->ultimoProcedimento = NULL;
    novo->quantidadeProcedimentos = 0;
    return novo;
}

//Inserir procedimento ao histórico
bool historico_inserir(HISTORICO *historico, char *procedimento) {
    if(historico == NULL) {
        historico = malloc(sizeof(HISTORICO));
        if(historico == NULL) {
            return false;
        }
    }
    //verifica se o histórico está cheio
    if(historico_cheio(historico)) {
        return false;
    }

    if(procedimento != NULL) {
        PROCEDIMENTO *novoProcedimento = malloc(sizeof(PROCEDIMENTO));
        if(novoProcedimento == NULL) {
            return false;
        }
        //O histórico é apenas uma sequência de caracteres, portanto copiamos na string
        strncpy(novoProcedimento->texto, procedimento, 100);
        novoProcedimento->texto[100] = '\0';
        //O procedimento é guardado como uma pilha, logo
        //novo procedimento deve apontar para o último da pilha
        novoProcedimento->anterior = historico->ultimoProcedimento;
        //Agora o novo é o último
        historico->ultimoProcedimento = novoProcedimento;
    }

    ++historico->quantidadeProcedimentos;

    return true;
}

//Remover procedimento do histórico
bool historico_retirar(HISTORICO *historico) {
    if (historico == NULL) {
        return false;
    }

    //Por se tratar de uma pilha o último elemento deve ser retirado primeiro
    PROCEDIMENTO *ultimo = historico->ultimoProcedimento;
    if (ultimo != NULL) {
        //Altera o ponteiro para o anterior do último antes de libetrar a memória
        historico->ultimoProcedimento = ultimo->anterior;
        free(ultimo);
        ultimo = NULL;
        --historico->quantidadeProcedimentos;
    }
    return true;
}

//Retorna todos os procedimentos de um certo histórico
char **historico_consultar_procedimento(HISTORICO *historico) {
    if(historico == NULL || historico_vazio(historico)) {
        return NULL;
    }
    
    char **procedimentos = malloc(10 * sizeof(char *));
    if(procedimentos == NULL) {
        return NULL;
    }
    //Primeiro limpa o vetor, podemos ter no máximo 10 procedimentos
    for(int i = 0; i < 10; ++i) {
        procedimentos[i] = NULL;
    }

    int i = 0;
    PROCEDIMENTO *atual = historico->ultimoProcedimento;
    //Armazena no vetor cada string
    while(atual != NULL && i < 10) {
        procedimentos[i] = atual->texto;
        atual = atual->anterior;
        ++i;
    }

    return procedimentos;
}

//Verifica se o histórico está cheio
bool historico_cheio(HISTORICO *historico) {
    if (historico == NULL) {
        return false;
    }

    return (historico->quantidadeProcedimentos >= 10);
}

//Verifica de o histórico está vazio
bool historico_vazio(HISTORICO *historico) {
    if (historico == NULL || historico->ultimoProcedimento == NULL || historico->quantidadeProcedimentos == 0) {
        return true;
    }
    
    return false;
}

//Função para apagar o histórico
bool historico_apagar(HISTORICO **historico) {
    if (historico == NULL || *historico == NULL) {
        return false;
    }
    //Vai retirando cada procedimento antes de liberar a memória
    //que aponta para o histórico
    while (!historico_vazio(*historico)) {
        if(!historico_retirar(*historico)) {
            return false;
        }
    }

    free(*historico);
    *historico = NULL;
    return true;
}

//Retorna a quantidade de quantidade de procedimentos no histórico
int historico_getquantidade(HISTORICO *historico){
    return historico->quantidadeProcedimentos;
}

//Retorna o último procedimento do histórico
PROCEDIMENTO *historico_getultimo(HISTORICO *historico){
    return historico->ultimoProcedimento;
}

//Retorna o procedimento anterior
PROCEDIMENTO *procedimento_getanterior(PROCEDIMENTO *proc){
    return proc->anterior;
}

//Retorna o texto de um certo procedimento
char *procedimento_gettexto(PROCEDIMENTO *proc){
    return proc->texto;
}

//Inverte a pilha de procedimentos
void historico_inverter(HISTORICO *historico){
    if(historico == NULL){
        return;
    }
    //Uso de dois ponteiros auxiliares para
    HISTORICO *aux = (HISTORICO *)malloc(sizeof(HISTORICO));
    HISTORICO *aux2 = (HISTORICO*)malloc(sizeof(HISTORICO));
    if(aux == NULL || aux2==NULL){
        return;
    }
    //Como a cada retirada a quantidade de procedimen tos diminui
    //É necessário uma variável para guardar o número de procediemntos
    int quantidade = historico->quantidadeProcedimentos;
    //Passa da pilha principal para a auxiliar(inverte a pilha)
    for(int i =0; i< quantidade; i++){
        historico_inserir(aux, historico->ultimoProcedimento->texto);
        historico_retirar(historico);
    }
    //Passa da auxiliar para a segunda auxiliar(desinverte a pilha)
    for(int i =0; i< quantidade; i++){
        historico_inserir(aux2, aux->ultimoProcedimento->texto);
        historico_retirar(aux);
    }
    //Passa da segunda auxiliar para a principal(Inverte de novo)
    for(int i =0; i< quantidade; i++){
        historico_inserir(historico, aux2->ultimoProcedimento->texto);
        historico_retirar(aux2);
    }
    free(aux);
    aux = NULL;
    free(aux2);
    aux2 = NULL;
}