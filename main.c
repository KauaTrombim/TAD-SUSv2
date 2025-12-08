//Arthur de Castro Dias - 16855302
//Gabriel Carraro Salzedas - 16827905
//Kaua Benjamin Trombim Silva - 16830893
#include "TADs/headers/setup.h"
#include "TADs/headers/paciente.h"
#include "TADs/headers/heap.h"
#include <string.h>

int main(void) {
    bool ok;
    //A lista é inicializada e os dados são carregados
    AvL *lista_pacientes;
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
    printf("Bem vindo ao TAD SUS V2!\n");
    int op = 0;
    do {
        // Escolhemos adicionar mais uma opção, "3-Inserir paciente na fila", para o caso de querermos inserir um paciente já cadastrado na lista, sem ter que mudar o funcionamento do TAD lista_paciente.
        printf("\nMenu:\n1-Registrar paciente\n
            2-Remover paciente\n
            3-Lista de pacientes\n
            4-Buscar paciente\n
            5-Mistrar fila de espera\n
            6-Dar alta ao paciente\n
            7-Sair\n");
        printf("Digite a opção desejada: ");
        scanf("%d",&op);
        Paciente *paciente;
        int id;
        //Executa alguma das ações de aocrdo com a entrada do usuário
        switch (op) {
            case 1:
                //Registrar paciente
                //Agora precisamos verificar se o paciente já existe ou não
                //Entra na triagem de qualquer forma.
                printf("------------REGISTRO DE PACIENTE------------\n");
                char nome[100];
                printf("Insira o nome do paciente: ");
                scanf("%s", nome);
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
                char priori[14];
                bool flag = 0;
                int prioridade;
                while(!flag){
                    printf("Digite a prioridade do paciente: ");
                    scanf("%s", priori);
                    if(!strcmp(priori, "Emergência") || !strcmp(priori, "emergência")){
                        prioridade = 4;
                        flag = 1;
                    }
                    else if(!strcmp(priori, "Muito urgente") || !strcmp(priori, "muito urgente")){
                        prioridade = 3;
                        flag = 1;
                    }
                    else if(!strcmp(priori, "Urgente") || !strcmp(priori, "urgente")){
                        prioridade = 2;
                        flag = 1;
                    }
                    else if(!strcmp(priori, "Pouco urgente") || !strcmp(priori, "pouco urgente")){
                        prioridade = 1;
                        flag = 1;
                    }
                    else if(!strcmp(priori, "Não urgência") || !strcmp(priori, "não urgência")){
                        prioridade = 0;
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

                printf("Paciente de ID %d registrado e inserido na fila de espera com sucesso!\n", id);
                printf("------------REGISTRO DE PACIENTE------------\n\n");
                break;
            case 2:
            //Remover paciente
                printf("------------SISTEMA DE MORTE------------\n");
                
                printf("Id do paciente: ");
                scanf("%d",&id);
                //Busca do paciente na lista para sua remoção
                paciente = avl_buscar_paciente(lista_pacientes, id);
                if(paciente == NULL) {
                    printf("ERRO ao procurar paciente!\n");
                    printf("------------SISTEMA DE MORTE------------\n\n");
                    break;
                }
                //Remoção do paciente da lista
                ok = lista_paciente_remover(lista_pacientes, paciente);
                if(!ok) {
                    printf("ERRO ao remover paciente da lista de pacientes!\n");
                    printf("------------SISTEMA DE MORTE------------\n\n");
                    break;
                }
                //Apagar paciente para liberar memória para novo paciente
                ok = paciente_apagar(&paciente);
                if(!ok) {
                    printf("ERRO ao apagar paciente!\n");
                    printf("------------SISTEMA DE MORTE------------\n\n");
                    break;
                }

                printf("Paciente removido com sucesso!\n");
                printf("------------SISTEMA DE MORTE------------\n\n");

                break;
            case 3:
                //Listar pacientes
                break;
            case 4:
                //Buscar por ID
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
}