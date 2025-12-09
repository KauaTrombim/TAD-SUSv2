#include "../headers/heap.h"

struct NO{
    Paciente* pac;
    int situacao;
    time_t horaInsercao; //Usado para tornar a heap estável
};

struct HEAP{
    NO *arvore[100];
    int ultimo;
};


//Método de criação da Heap
Heap *heap_criar(){
    Heap *heap = malloc(sizeof(Heap));
    if(heap != NULL){
        //Caso inicial o último seria -1.
        heap->ultimo = -1;
    }
    return heap;
}


//Método para apagar a Heap
//Ponteiro para ponteiro para Heap
void heap_apagar(Heap **heap){
    if(*heap == NULL || heap ==NULL){
        return;
    }
    //Como cada nó é alocado dinamicamente ele libera todos os existentes.
    for(int i = 0; i<=(*heap)->ultimo; i++){
        free((*heap)->arvore[i]);
        (*heap)->arvore[i] = NULL;
    }
    //Liberação da estrutura.
    free(*heap);
    *heap = NULL;
}

//Verificação se a heap está vazia
bool heap_vazia(Heap *heap){
    if(heap->ultimo == -1){
        return true;
    }
    return false;
}

//Verificaçaõ se a heap está cheia
bool heap_cheia(Heap *heap){
    //Como a heap tem tamanho 100 ele vai de 0 a 99.
    if(heap->ultimo == 99){
        return true;
    }
    return false;
}

//Pós remoção correção da heap
//Vai descendo o primeiro nó até que ele entre na posição correta.
void heap_fixdown(Heap *heap, int indice){
    if(heap==NULL){
        return;
    }
    int maior = indice;
    //Comparação de acordo com a prioridade do filho esquerdo
    if(2*indice+1 <= heap->ultimo){
        //Se for a mesma prioridade quem entrou primeiro tem preferência
        if((heap->arvore[2*indice+1]->situacao == heap->arvore[maior]->situacao && difftime(heap->arvore[2*indice+1]->horaInsercao,heap->arvore[maior]->horaInsercao) < 0) || heap->arvore[2*indice+1]->situacao > heap->arvore[maior]->situacao)
            maior = 2*indice+1;
    }
    //Análogo para o filho direito
    if(2*indice+2 <= heap->ultimo){
        if((heap->arvore[2*indice+2]->situacao == heap->arvore[maior]->situacao && difftime(heap->arvore[2*indice+2]->horaInsercao,heap->arvore[maior]->horaInsercao) < 0) || heap->arvore[2*indice+2]->situacao > heap->arvore[maior]->situacao)
            maior = 2*indice+2;
    }
    //Se o maior foi trocado ele passa para o próximo até que o nó encontre sua posição correta
    if(maior!=indice){
        NO* aux = heap->arvore[indice];
        heap->arvore[indice] = heap->arvore[maior];
        heap->arvore[maior] = aux;
        heap_fixdown(heap, maior);
    }
}

//Pós inserção correção da heap
void heap_fixup(Heap *heap){
    if(heap == NULL){
        return;
    }
    int w = heap->ultimo;
    //Cálculo do pai
    int maior = (w - 1)/2;
    //Percorre a árvore subindo até encontrar a parte superior.
    while(w > 0 && (heap->arvore[w]->situacao >= heap->arvore[maior]->situacao)){
        //Atualização do pai a cada iteração.
        maior = (maior-1)/2;
        //Preferência para quem entrou primeiro na fila caso as prioridades sejam iguais
        if(heap->arvore[w]->situacao == heap->arvore[maior]->situacao && difftime(heap->arvore[w]->horaInsercao,heap->arvore[maior]->horaInsercao) > 0){
            break;
        }
        NO* aux = heap->arvore[maior];
        heap->arvore[maior] = heap->arvore[w];
        heap->arvore[w] = aux;
        w = maior;
    }
}

//Remoção de nó
NO* heap_remover(Heap *heap){
    if(heap == NULL){
        return NULL;
    }
    //Verificação se heap não está vazia
    if(heap_vazia(heap)){
        printf("Não há registros na fila de espera.\n");
        return NULL;
    }
    //Como é uma heap o primeiro será o próximo a ser chamado
    NO* item = heap->arvore[0];
    //Alteração do paciente como fora da fila de espera
    paciente_mudar_situacao_fila(heap->arvore[0]->pac, false);
    //Troca do primeiro elemento da heap com o último
    heap->arvore[0] = heap->arvore[heap->ultimo--];//Diminuição do último índice preenchido
    //Função para correção da heap
    heap_fixdown(heap, 0);
    //Retorno do item removido
    return item;
}

//Função para inserção de um item
bool heap_inserir(Heap *heap, Paciente *pac, int priori){
    if(heap == NULL || pac == NULL){
        return false;
    }
    //Verificação inicial se eles está cheia
    if(heap_cheia(heap)){
        printf("A fila de espera está lotada.\n");
        return false;
    
    }
    //Criação do novo nó
    NO* item = malloc(sizeof(NO));
    if(item == NULL){
        return false;
    }
    //Pega o horário atual da inserção
    time_t t = time(NULL);
    item->horaInsercao = t;
    //Define a situação na fila para verdadeira
    paciente_mudar_situacao_fila(pac, true);
    item->pac = pac;
    item->situacao = priori;
    heap->arvore[++heap->ultimo] = item;//Insere no último nó
    //Função para correçaõ da heap
    heap_fixup(heap);
    return true;
}

//Função para listagem dos pacientes na heap
void heap_listar(Heap *heap){
    if(heap == NULL){
        return;
    }
    //Cria uma heap auxiliar
    Heap* copia = heap_criar();
    if(copia == NULL){
        printf("Falha na listagem de pacientes.\n");
        return;
    }
    //Copia todos os nós da heap original para a cópia
    for(int i = 0; i<heap->ultimo+1;i++){
        copia->arvore[i] = heap->arvore[i];
    }
    copia->ultimo = heap->ultimo;
    while(!heap_vazia(copia)){
        //Imprime sempre o primeiro item da heap
        printf("Id: %d\tPaciente: %s\t", paciente_getID(copia->arvore[0]->pac), paciente_getNome(copia->arvore[0]->pac));
        switch(copia->arvore[0]->situacao){
            case 5:
                printf("Prioridade: Emergência\n");
                break;
            case 4:
                printf("Prioridade: Muito urgente\n");
                break;
            case 3:
                printf("Prioridade: Urgente\n");            
                break;
            case 2:
                printf("Prioridade: Pouco urgente\n");
                break;
            case 1:
                printf("Prioridade: Não urgente\n");
                break;
        }
        //Remove o primeiro item da cópia e a arruma, assim o primeiro sempre será o próximo.
        copia->arvore[0] = copia->arvore[copia->ultimo--];
        heap_fixdown(copia, 0);
    }
    //Apaga a cópia criada
    heap_apagar(&copia);
}

//Retorna o paciente salvo em um certo nó
Paciente *no_getPac(NO* item){
    if(item == NULL){
        return NULL;
    }
    return item->pac;
}

// Salva os dados da heap em um arquivo de texto
bool heap_salvar(Heap *heap) {
    if (heap == NULL) {
        return false;
    }

    // Abrimos o arquivo "triagem.txt" em modo escrita
    FILE *arq = fopen("triagem.txt", "w");
    if (arq == NULL) {
        return false;
    }

    // Percorremos todos os elementos da heap até o último índice válido
    for (int i = 0; i <= heap->ultimo; ++i) {
        // Verificamos se o nó da heap e o paciente associado não são nulos
        // Em seguida, obtemos seu ID e sua situação e salvamos
        if (heap->arvore[i] != NULL && heap->arvore[i]->pac != NULL) {
            int id = paciente_getID(heap->arvore[i]->pac);
            int situacao = heap->arvore[i]->situacao;
            fprintf(arq, "%d %d\n", id, situacao);
        }
    }

    fclose(arq);
    return true;
}


// Carrega os dados da heap a partir do arquivo de texto
bool heap_carregar(Heap *heap, AVL *lista_pacientes) {
    // Abrimos o arquivo "triagem.txt" em modo leitura
    FILE *arq = fopen("triagem.txt", "r");
    if (arq == NULL) {
        return false;
    }

    int id, prioridade;
    // Lemos ID e prioridade até o fim do arquivo
    while (fscanf(arq, "%d %d", &id, &prioridade) == 2) {
        // Buscamos o paciente correspondente na árvore AVL usando o ID
        Paciente *p = avl_buscar_paciente(lista_pacientes, id);
        
        // Se o paciente foi encontrado, inserimos na heap com a prioridade lida
        if (p != NULL) {
            heap_inserir(heap, p, prioridade);
        }
    }

    fclose(arq);
    return true;
}
