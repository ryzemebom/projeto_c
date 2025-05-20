#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void limparTela() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

typedef struct No {
    char dominio[100];
    char responsavel[100];
    struct No *next;
} No;

No *listaDominios = NULL;

void registrarDominio(No **lista, const char *dominio, const char *responsavel) {
    No *novoNo = (No *)malloc(sizeof(No));
    if (novoNo == NULL) {
        printf("\nErro ao alocar memória para o novo domínio.\n");
        return;
    }
    strcpy(novoNo->dominio, dominio);
    strcpy(novoNo->responsavel, responsavel);
    novoNo->next = *lista;
    *lista = novoNo;
}

int dominioJaExiste(No *lista, const char *dominio) {
    No *noAtual = lista;
    while (noAtual != NULL) {
        if (strcmp(noAtual->dominio, dominio) == 0) {
            return 1;
        }
        noAtual = noAtual->next;
    }
    return 0;
}

void exibirTodosDominios(No *lista) {
    No *noAtual = lista;
    if (noAtual == NULL) {
        printf("\nNenhum dominio registrado.\n");
        return;
    }

    printf("\nDominios registrados:\n");
    printf("-------------------------------\n");
    while (noAtual != NULL) {
        printf("Dominio: %s\nResponsavel: %s\n", noAtual->dominio, noAtual->responsavel);
        printf("-------------------------------\n");
        noAtual = noAtual->next;
    }
}

void liberarLista(No *lista) {
    No *noAtual;
    while (lista != NULL) {
        noAtual = lista;
        lista = lista->next;
        free(noAtual);
    }
}

void carregarDominiosDoArquivo(No **lista) {
    FILE *arquivo = fopen("dominios.txt", "r");
    if (arquivo == NULL) {
        printf("Nenhum arquivo encontrado para carregar os domínios.\n");
        return;
    }

    char linhaArquivo[256];
    char dominioRegistro[100], responsavelDominio[100];

    while (fgets(linhaArquivo, sizeof(linhaArquivo), arquivo)) {
        if (strstr(linhaArquivo, "Dominio: ") == linhaArquivo) {
            sscanf(linhaArquivo, "Dominio: %99[^\n]", dominioRegistro);
            if (fgets(linhaArquivo, sizeof(linhaArquivo), arquivo)) {
                sscanf(linhaArquivo, "Responsavel: %99[^\n]", responsavelDominio);
                registrarDominio(lista, dominioRegistro, responsavelDominio);
            }
        }
    }

    fclose(arquivo);
}



void salvarDominioNoArquivo(const char *dominio, const char *nome) {
    FILE *arquivo = fopen("dominios.txt", "a");
    if (arquivo == NULL) {
        printf("\nErro ao abrir o arquivo para salvar o dominio.\n");
        return;
    }

    fprintf(arquivo, "Dominio: %s\n responsavel: %s\n", dominio, nome);
    fprintf(arquivo, "------------------------------\n");
    fclose(arquivo);
    printf("\nDominio salvo no arquivo com sucesso!\n");
}

int formatoDominioValido(const char *dominio) {
    const char *extensoesValidas[] = {".com", ".org", ".net", ".br", ".gov", ".edu", ".io"};
    int quantidadeExtensoes = sizeof(extensoesValidas) / sizeof(extensoesValidas[0]);

    int len = strlen(dominio);

    // Verificações básicas
    if (len == 0 || dominio[0] == '.' || dominio[len - 1] == '.') return 0;
    if (strstr(dominio, "..") != NULL) return 0; // impede partes vazias (como "".com)

    // Verifica se termina com uma extensão válida
    int extensaoValida = 0;
    for (int i = 0; i < quantidadeExtensoes; i++) {
        size_t lenExt = strlen(extensoesValidas[i]);
        if (len >= lenExt && strcmp(dominio + len - lenExt, extensoesValidas[i]) == 0) {
            extensaoValida = 1;
            break;
        }
    }
    if (!extensaoValida) return 0;

    // Verifica se o domínio contém pelo menos um nome válido antes da extensão
    char dominioCopia[100];
    strcpy(dominioCopia, dominio);
    char *token = strtok(dominioCopia, ".");

    int partesValidas = 0;
    while (token != NULL) {
        // Parte vazia ou só espaço? Inválida.
        if (strlen(token) == 0 || strspn(token, " ") == strlen(token)) {
            return 0;
        }

        // Verifica se é uma extensão
        int ehExtensao = 0;
        for (int i = 0; i < quantidadeExtensoes; i++) {
            if (strcmp(token, extensoesValidas[i] + 1) == 0) {
                ehExtensao = 1;
                break;
            }
        }

        if (!ehExtensao) partesValidas++;

        token = strtok(NULL, ".");
    }

    // Se não houver nenhuma parte válida antes da extensão, inválido
    return partesValidas >= 1;
}


void apagarDominioEspecifico(No **lista) {
    if (*lista == NULL) {
        printf("\nNenhum dominio registrado para apagar.\n");
        return;
    }

    printf("\nDominios registrados:\n");
    printf("-------------------------------\n");

    No *noAtual = *lista;
    int index = 1;
    while (noAtual != NULL) {
        printf("%d - Dominio: %s | Responsavel: %s\n", index, noAtual->dominio, noAtual->responsavel);
        noAtual = noAtual->next;
        index++;
    }
    printf("\nDigite o numero do dominio que deseja apagar(digite 0 para excluir nenhum dominio): ");

    char entrada[10];
    int escolha = 0;
    fgets(entrada, sizeof(entrada), stdin);
    sscanf(entrada, "%d", &escolha);

    if (escolha >= index) {
        printf("numero nao encontrado na lista, tente novamente\n");
        apagarDominioEspecifico(lista);
        return 0;
    }
    if (escolha == 0){

        printf("Nenhum dominio foi excluido");
        return;
    }
    No *anterior = NULL;
    noAtual = *lista;
    index = 1;
    while (noAtual != NULL && index < escolha) {
        anterior = noAtual;
        noAtual = noAtual->next;
        index++;
    }

    if (noAtual == NULL) {
        printf("Dominio nao encontrado.\n");
        return;
    }

    printf("\nDominio '%s' removido com sucesso!\n", noAtual->dominio);

    if (anterior == NULL) {
        *lista = noAtual->next;
    } else {
        anterior->next = noAtual->next;
    }

    free(noAtual);

    // Atualizar arquivo
    FILE *arquivo = fopen("dominios.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para atualizar.\n");
        return;
    }

    noAtual = *lista;
    while (noAtual != NULL) {
        fprintf(arquivo, "Dominio: %s\nResponsavel: %s\n", noAtual->dominio, noAtual->responsavel);
        fprintf(arquivo, "------------------------------\n");
        noAtual = noAtual->next;
    }

    fclose(arquivo);
}

void apagarTodosDominios(No **lista) {
    char confirmacao[4];
    printf("Tem certeza que deseja apagar todos os dominios? (sim/nao): ");
    fgets(confirmacao, sizeof(confirmacao), stdin);
    confirmacao[strcspn(confirmacao, "\n")] = 0;

    if (strcmp(confirmacao, "sim") != 0) {
        printf("Operacao cancelada.\n");
        return;
    }

    liberarLista(*lista);
    *lista = NULL;

    FILE *arquivo = fopen("dominios.txt", "w");
    if (arquivo == NULL) {
        printf("\nErro ao abrir o arquivo para apagar os dominios.\n");
        return;
    }
    fclose(arquivo);

    printf("\nTodos os dominios foram apagados com sucesso!\n");

    getchar();
}
int main() {
    int escolha = -1;
    char dominioRegistro[100] = "";
    char responsavelDominio[100] = "";

    carregarDominiosDoArquivo(&listaDominios);

    while (escolha != 0) {
        limparTela();

        printf("===================================\n");
        printf("       REGISTRO DE DOMINIOS\n");
        printf("===================================\n");
        printf("1 - Registrar um novo dominio\n");
        printf("2 - Exibir todos os dominios registrados\n");
        printf("3 - Verificar se um dominio esta registrado\n");
        printf("4 - Apagar um dominio especifico\n");
        printf("5 - Apagar todos os dominios\n");
        printf("0 - Sair\n");
        printf("-----------------------------------\n");
        printf("Escolha uma opcao: ");

        char entrada[10];
        fgets(entrada, sizeof(entrada), stdin);
        if (sscanf(entrada, "%d", &escolha) != 1) {
            printf("\nEntrada invalida! Digite apenas o numero da opcao.\n");
            escolha = -1;
            printf("\nPressione Enter para continuar...");
            getchar();
            continue;
        }

        if (escolha == 1) {
            printf("\nDigite o dominio que deseja registrar: ");
            fgets(dominioRegistro, sizeof(dominioRegistro), stdin);
            dominioRegistro[strcspn(dominioRegistro, "\n")] = 0;

            if (strlen(dominioRegistro) == 0) {
                printf("O dominio nao pode estar vazio!\n");
            } else if (!formatoDominioValido(dominioRegistro)) {
                printf("Formato de dominio invalido! Use algo como exemplo.com, site.org, etc.\n");
            } else if (dominioJaExiste(listaDominios, dominioRegistro)) {
                printf("Este dominio ja esta registrado!\n");
            } else {
                printf("Digite o nome do responsavel: ");
                fgets(responsavelDominio, sizeof(responsavelDominio), stdin);
                responsavelDominio[strcspn(responsavelDominio, "\n")] = 0;

                if (strlen(responsavelDominio) == 0) {
                    printf("O nome do responsavel e obrigatorio!\n");
                } else {
                    printf("\nDominio '%s' registrado com sucesso para '%s'!\n", dominioRegistro, responsavelDominio);
                    registrarDominio(&listaDominios, dominioRegistro, responsavelDominio);
                    salvarDominioNoArquivo(dominioRegistro, responsavelDominio);
                }
            }
        } else if (escolha == 2) {
            exibirTodosDominios(listaDominios);
        } else if (escolha == 3) {
            printf("\nDigite o dominio que deseja verificar: ");
            fgets(dominioRegistro, sizeof(dominioRegistro), stdin);
            dominioRegistro[strcspn(dominioRegistro, "\n")] = 0;

            if (dominioJaExiste(listaDominios, dominioRegistro)) {
                printf("O dominio '%s' esta registrado.\n", dominioRegistro);
                printf("O responsavel e: ",responsavelDominio);
            } else {
                printf("O dominio '%s' NAO esta registrado.\n", dominioRegistro);
            }
        } else if (escolha == 4) {
            apagarDominioEspecifico(&listaDominios);

                 } else if (escolha == 5) {
            apagarTodosDominios(&listaDominios);
        } else if (escolha == 0) {
            printf("\nEstamos te esperando novamente\n");

        }

        else {
            printf("\nOpcao invalida. Tente novamente.\n");
        }

        printf("\nPressione Enter para continuar...");
        getchar();
    }

    liberarLista(listaDominios);

    return 0;
}
