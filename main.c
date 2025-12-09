//Arthur de Castro Dias - 16855302
//Gabriel Carraro Salzedas - 16827905
//Kaua Benjamin Trombim Silva - 16830893
//==== made in ICMC-USP====
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
lista_pacientes = avl_criar();
avl_carregar(lista_pacientes);

if (lista_pacientes == NULL) {
    printf("ERRO ao criar lista de pacientes!\n");
    return 1;
}

//Inicialização e carregamento da triagem
//Necessário depois da lista pois seu carregamento depende dela
Heap *triagem;
triagem = heap_criar();
if(triagem == NULL){
    printf("Erro ao inicializar a triagem!");
    return 1;
}
heap_carregar(triagem, lista_pacientes);
printf("-------Bem-vindo ao TAD SUS V2!-------\n");
int op = 0;
do {
    printf("\nMenu:\n1-Registrar paciente\n2-Remover paciente\n3-Lista de pacientes\n4-Buscar paciente\n5-Mostrar fila de espera\n6-Dar alta ao paciente\n7-Adiconar procedimento ao histórico\n8-Remover procedimento do histórico\n9-Sair\n");
    printf("Digite a opção desejada: ");
    scanf("%d",&op);
    Paciente *paciente;

    char a;

    int id;
    //Executa alguma das ações de acordo com a entrada do usuário
    switch (op) {
        case 1:
                //Registrar paciente
                //Agora precisamos verificar se o paciente já existe ou não
                //Entra na triagem de qualquer forma.
                printf("\n------------REGISTRO DE PACIENTE------------\n");
                char nome[100];
                id = -2;
                int priori = 0;
                while(id != -1 || avl_buscar_paciente(lista_pacientes, id) != NULL){
                    printf("->Insira o ID do paciente(-1 se for novo paciente): ");
                    scanf("%d", &id);
                    if(id != -1 || avl_buscar_paciente(lista_pacientes, id) != NULL){
                        printf("ID digitado inválido!\n");
                    }
                }
                paciente = avl_buscar_paciente(lista_pacientes, id);
                if(paciente != NULL){
                    priori = 0; //começa invalido
                    while(priori < 1 || priori > 5){
                        printf("->Digite a prioridade do paciente, \n");
                        printf("-->1-Nao urgencia, 2-Pouco urgente, 3-Urgente, 4-Muito urgente, 5-Emergencia: ");

                        scanf("%d",&priori);
                        if(priori < 1 || priori > 5){
                            printf("Prioridade inválida.\n");
                        }
                    }
                    if(paciente_naFila(paciente)){
                        printf("Paciente ja cadastrado na fila.\n");
                        break;
                    }
                    heap_inserir(triagem, paciente, priori);
                    break;
                }
                while ((a = getchar()) != '\n' && a != EOF); //consome lixo
                printf("->Insira o nome do paciente (max: 99 caracteres): ");
                
                if (fgets(nome, sizeof(nome), stdin) != NULL) {
                    char *p = strchr(nome, '\n');
                    if (p) {
                        *p = '\0';//Verificando se o texto coube inteiro
                    } else {
                        int c;
                        while ((c = getchar()) != '\n' && c != EOF); //limpando o resto da string se não couber
                    }
                }

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
                priori = 0; //começa invalido
                while(priori < 1 || priori > 5){
                    printf("->Digite a prioridade do paciente, \n");
                    printf("-->1-Nao urgencia, 2-Pouco urgente, 3-Urgente, 4-Muito urgente, 5-Emergencia: ");

                    scanf("%d",&priori);
                    if(priori < 1 || priori > 5){
                        printf("Prioridade inválida.\n");
                    }
                }
                id = paciente_getID(paciente);
                ok = heap_inserir(triagem, paciente, priori);
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
            //Dar alta, remove o paciente mais prioritário da heap
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
            //Salva os dados
            //Nota: se fechar o programa com ^C no terminal os dados não serão salvos
            avl_salvar(lista_pacientes);
            heap_salvar(triagem);
            heap_apagar(&triagem);
            avl_apagar(&lista_pacientes);
            break;
        default:
        //Caso a opção digitada seja inválida nada acontece
            break;
    }
}while(op != 9);
return 0;
}