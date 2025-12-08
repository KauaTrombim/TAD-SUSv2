//Arthur de Castro Dias - 16855302
//Gabriel Carraro Salzedas - 16827905
//Kaua Benjamin Trombim Silva - 16830893
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "TADs/headers/paciente.h"
#include "TADs/headers/avl.h" 
#include "TADs/headers/heap.h"
#include "TADs/headers/historico.h"
#include <string.h>


int main(void) {
    bool ok;
    //A lista é inicializada e os dados são carregados
    AVL *lista_pacientes;
    //lista_pacientes = avl_carregar_dados();
    lista_pacientes = avl_criar();
    //carregar_lista(lista_pacientes);

    if (lista_pacientes == NULL) {
        printf("ERRO ao criar lista de pacientes!\n");
        return 1;
    }

    //Inicialização e carregamento da triagem
    //Necessário depois da lista pois seu carregamento depende dela
    Heap *triagem;
    triagem = heap_criar();
    //carregar_fila(triagem, lista_pacientes);
    if(triagem == NULL){
        printf("Erro ao inicializar a triagem!");
        return 1;
    }
    printf("-------Bem vindo ao TAD SUS V2!-------\n");
    int op = 0;
    do {
        // Escolhemos adicionar mais uma opção, "3-Inserir paciente na fila", para o caso de querermos inserir um paciente já cadastrado na lista, sem ter que mudar o funcionamento do TAD lista_paciente.
        printf("\nMenu:\n1-Registrar paciente\n2-Remover paciente\n3-Lista de pacientes\n4-Buscar paciente\n5-Mostrar fila de espera\n6-Dar alta ao paciente\n7-Adiconar procedimento ao histórico\n8-Remover procedimento do histórico\n9-Sair\n");
        printf("Digite a opção desejada: ");
        scanf("%d",&op);
        Paciente *paciente;

        char a;
        while ((a = getchar()) != '\n' && a != EOF); //consome lixo

        int id;
        //Executa alguma das ações de aocrdo com a entrada do usuário
        switch (op) {
            case 1:
                //Registrar paciente
                //Agora precisamos verificar se o paciente já existe ou não
                //Entra na triagem de qualquer forma.
                printf("\n------------REGISTRO DE PACIENTE------------\n");
                char nome[100];
                printf("->Insira o nome do paciente (max: 99 caracteres): ");
                
                
                fgets(nome, 100, stdin);
                nome[strcspn(nome, "\n")] = '\0';
                //Cria paciente com o nome dado, id -1 para identificação de que
                //ele é um novo paciente
                paciente = paciente_criar(lista_pacientes, nome, -1);
                if(paciente == NULL) {
                    printf("ERRO ao criar paciente!\n");
                    printf("------------REGISTRO DE PACIENTE------------\n\n");
                    break;
                }
                //Paciente é guardado na lista geral
                ok = avl_inserir_paciente(lista_pacientes, paciente);
                if(!ok) {
                    printf("ERRO ao inserir paciente na lista de pacientes!\n");
                    printf("------------REGISTRO DE PACIENTE------------\n\n");
                    break;
                }
                //Paciente é inserido na fila de triagem para ser atendido
                char priori[15];

                bool flag = false;
                int prioridade = -1; //começa invalido
                while(!flag){
                    printf("->Digite a prioridade do paciente, \n");
                    printf("-->Emergencia, Muito urgente, Urgente, Pouco urgente, Nao urgencia: ");

                    //fgets(priori, 14, stdin);
                    //priori[strcspn(priori, "\n")] = '\0';
                    
                    if (fgets(priori,15, stdin) != NULL) {
                        priori[strcspn(priori, "\n")] = '\0'; // Remove o \n
                    }

                    if(!strcmp(priori, "Emergencia") || !strcmp(priori, "emergencia")){
                        prioridade = 0;
                        flag = 1;
                    }
                    else if(!strcmp(priori, "Muito urgente") || !strcmp(priori, "muito urgente")){
                        prioridade = 1;
                        flag = 1;
                    }
                    else if(!strcmp(priori, "Urgente") || !strcmp(priori, "urgente")){
                        prioridade = 2;
                        flag = 1;
                    }
                    else if(!strcmp(priori, "Pouco urgente") || !strcmp(priori, "pouco urgente")){
                        prioridade = 3;
                        flag = 1;
                    }
                    else if(!strcmp(priori, "Nao urgencia") || !strcmp(priori, "nao urgencia")){
                        prioridade = 4;
                        flag = 1;
                    }else{
                        printf("Erro ao interpretar a situação do paciente!\n");
                    }
                }
                id = paciente_getID(paciente);
                ok = heap_inserir(triagem, paciente, prioridade);
                if(!ok) {
                    printf("ERRO ao inserir paciente na triagem!\n");
                    printf("------------REGISTRO DE PACIENTE------------\n\n");
                    break;
                }

                printf("\n->Paciente de ID %d registrado e inserido na fila de espera com sucesso!\n", id);
                printf("------------REGISTRO DE PACIENTE------------\n\n");
                break;
            case 2:
            //Remover paciente
                printf("\n------------SISTEMA DE MORTE------------\n");
                
                printf("->Id do paciente: ");
                scanf("%d",&id);
                //Busca do paciente na lista para sua remoção
                paciente = avl_buscar_paciente(lista_pacientes, id);
                if(paciente == NULL) {
                    printf("ERRO ao procurar paciente!\n");
                    printf("------------SISTEMA DE MORTE------------\n\n");
                    break;
                }
                //Remoção do paciente da lista
                ok = avl_remover_paciente(lista_pacientes, id);
                if(!ok) {
                    printf("ERRO ao remover paciente da lista de pacientes!\n");
                    printf("------------SISTEMA DE MORTE------------\n\n");
                    break;
                }

                printf("Paciente removido com sucesso!\n");
                printf("------------SISTEMA DE MORTE------------\n\n");

                break;
            case 3:
                //Listar pacientes
                printf("\n----------USUARIOS CADASTRADOS----------\n");
                avl_listar(lista_pacientes);
                printf("----------USUARIOS CADASTRADOS----------\n");
                break;
            case 4:
                //Buscar por ID
                printf("\n------------BUSCA DE PACIENTE------------\n");
                printf("->ID do paciente: ");
                scanf("%d",&id);
                paciente = avl_buscar_paciente(lista_pacientes, id);
                if(paciente == NULL){
                    printf("Paciente nao encontrado\n");
                }
                else{
                    paciente_imprimir(paciente);
                }
                printf("\n------------BUSCA DE PACIENTE------------\n");
                break;
            case 5:
                //Mostra a triagem e os pacientes nela
                printf("------------FILA DE ESPERA------------\n");
                heap_listar(triagem);
                printf("------------FILA DE ESPERA------------\n\n");
                break;
            case 6:
                //Dar alta
                NO* removido = heap_remover(triagem);
                if(removido == NULL){
                    printf("Erro ao dar alta ao paciente!\n");
                    break;
                }
                printf("Paciente: %s recebeu alta\n", paciente_getNome(no_getPac(removido)));
                free(removido);
                removido = NULL;
                break;
            case 7:
                //Registro de procedimento ao histórico
                printf("------------ADIÇÃO DE PROCEDIMENTO AO HISTÓRICO------------\n");
                printf("Insira o id do paciente: ");
                scanf("%d",&id);
                //Busca pelo paciente
                paciente = avl_buscar_paciente(lista_pacientes, id);
                if(paciente == NULL) {
                    printf("ERRO ao procurar paciente!\n");
                    printf("------------ADIÇÃO DE PROCEDIMENTO AO HISTÓRICO------------\n\n");
                    break;
                }
                //Se o histórico do paciente estiver cheio o usuário recebe um aviso
                if(historico_cheio(paciente_gethistorico(paciente))) {
                    printf("ERRO ao inserir procedimento: histórico cheio!\n");
                    printf("------------ADIÇÃO DE PROCEDIMENTO AO HISTÓRICO------------\n\n");
                    break;
                }

                printf("Procedimento: ");
                char procedimento[100];
                //Lê o procedimento do usuário
                if(fscanf(stdin, " %99[^\n]", procedimento) != 1) {
                    printf("ERRO ao ler procedimento!\n");
                    printf("------------ADIÇÃO DE PROCEDIMENTO AO HISTÓRICO------------\n\n");
                    break;
                }
                //Avisa se houver erro na inserção
                if(!historico_inserir(paciente_gethistorico(paciente), procedimento)) {
                    printf("ERRO ao inserir histórico do paciente!\n");
                    printf("------------ADIÇÃO DE PROCEDIMENTO AO HISTÓRICO------------\n\n");
                    break;
                }

                printf("Procedimento adicionado ao histórico do paciente!\n");
                printf("------------ADIÇÃO DE PROCEDIMENTO AO HISTÓRICO------------\n\n");
                break;
            case 8:
                //O último procedimento do histórioc é desfeito
                printf("------------DESFAZER PROCEDIMENTO DO HISTÓRICO------------\n");
                printf("Id do paciente: ");
                scanf("%d",&id);
                //Procura o paciente que terá o histórico alterado
                paciente = avl_buscar_paciente(lista_pacientes, id);
                if(paciente == NULL) {
                    printf("ERRO ao procurar paciente!\n");
                    printf("------------DESFAZER PROCEDIMENTO DO HISTÓRICO------------\n\n");
                    break;
                }
                //Se o histórico estiver vazio não tem como retirar nada
                if(historico_vazio(paciente_gethistorico(paciente))) {
                    printf("ERRO ao retirar procedimento: histórico vazio!\n");
                    printf("------------DESFAZER PROCEDIMENTO DO HISTÓRICO------------\n\n");
                    break;
                }
                //Se falhar avisa ao usuário
                if(!historico_retirar(paciente_gethistorico(paciente))) {
                    printf("ERRO ao retirar procedimento do histórico do paciente!\n");
                    printf("------------DESFAZER PROCEDIMENTO DO HISTÓRICO------------\n\n");
                    break;
                }
                
                printf("Procedimento desfeito do histórico do paciente!\n");
                printf("------------DESFAZER PROCEDIMENTO DO HISTÓRICO------------\n\n");
                break;
            case 9:
            // Sair do loop e salvamento dos dados
                //A fila e a lista são salvas
                //salvar_fila(triagem);
                //salvar_lista(lista_pacientes);
                //Após seu salvamento a triagem e a lista de pacientes são apagadas
                //triagem_apagar(&triagem);
                //lista_paciente_apagar(&lista_pacientes);
                break;
            default:
            //Caso a opção digitada seja inválida nada acontece
                break;
        }
    }while(op != 7);
    return 0;
}