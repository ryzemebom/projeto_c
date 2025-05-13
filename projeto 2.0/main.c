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

int formatoDominioValido(const char *dominio) {
    const char *extensoesValidas[] = {".com", ".org", ".net", ".br", ".gov", ".edu", ".io"};
    int quantidadeExtensoes = sizeof(extensoesValidas) / sizeof(extensoesValidas[0]);

    if (strchr(dominio, '.') == NULL) return 0;

    for (int i = 0; i < quantidadeExtensoes; i++) {
        size_t lenDominio = strlen(dominio);
        size_t lenExt = strlen(extensoesValidas[i]);
        if (lenDominio >= lenExt && strcmp(dominio + lenDominio - lenExt, extensoesValidas[i]) == 0) {
            return 1;
        }
    }

    return 0;
}

int dominioJaExiste(const char *dominio) {
    FILE *arquivo = fopen("dominios.txt", "r");
    if (arquivo == NULL) return 0;

    char linha[256];
    while (fgets(linha, sizeof(linha), arquivo)) {
        if (strstr(linha, "Dominio: ") == linha) {
            char dominioLido[100];
            sscanf(linha, "Dominio: %99[^\n]", dominioLido);
            if (strcmp(dominioLido, dominio) == 0) {
                fclose(arquivo);
                return 1;
            }
        }
    }

    fclose(arquivo);
    return 0;
}

void salvarDominioNoArquivo(const char *dominio, const char *nome) {
    FILE *arquivo = fopen("dominios.txt", "a");
    if (arquivo == NULL) {
        printf("\nErro ao abrir o arquivo para salvar o dominio.\n");
        return;
    }

    fprintf(arquivo, "Dominio: %s\nResponsavel: %s\n", dominio, nome);
    fprintf(arquivo, "------------------------------\n");
    fclose(arquivo);
    printf("\nDominio salvo no arquivo com sucesso!\n");
}

void exibirTodosDominiosDoArquivo() {
    FILE *arquivo = fopen("dominios.txt", "r");
    if (arquivo == NULL) {
        printf("\nNenhum dominio registrado no arquivo.\n");
        return;
    }

    char linha[256];
    int encontrou = 0;

    printf("\nDominios registrados:\n");
    printf("-------------------------------\n");

    while (fgets(linha, sizeof(linha), arquivo)) {
        printf("%s", linha);
        encontrou = 1;
    }

    fclose(arquivo);

    if (!encontrou) {
        printf("Nenhum dominio encontrado.\n");
    }
}

void apagarTodosDominiosDoArquivo() {
    char confirmacao[4];
    printf("Tem certeza que deseja apagar todos os dominios? (sim/nao): ");
    fgets(confirmacao, sizeof(confirmacao), stdin);
    confirmacao[strcspn(confirmacao, "\n")] = 0;

    if (strcmp(confirmacao, "sim") != 0) {
        printf("Operacao cancelada.\n");
        return;
    }

    FILE *arquivo = fopen("dominios.txt", "w");
    if (arquivo == NULL) {
        printf("\nErro ao abrir o arquivo para apagar os dominios.\n");
        return;
    }
    fclose(arquivo);
    printf("\nTodos os dominios foram apagados do arquivo com sucesso!\n");
}

int main() {
    int escolha = -1;
    char dominio[100] = "";
    char nome[100] = "";

    while (escolha != 0) {
        limparTela();

        printf("===================================\n");
        printf("       REGISTRO DE DOMINIOS\n");
        printf("===================================\n");
        printf("1 - Registrar um novo dominio\n");
        printf("2 - Exibir todos os dominios registrados\n");
        printf("3 - Verificar se um dominio esta registrado\n");
        printf("4 - Apagar todos os dominios\n");
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
            fgets(dominio, sizeof(dominio), stdin);
            dominio[strcspn(dominio, "\n")] = 0;

            if (strlen(dominio) == 0) {
                printf("O dominio nao pode estar vazio!\n");
            } else if (!formatoDominioValido(dominio)) {
                printf("Formato de dominio invalido! Use algo como exemplo.com, site.org, etc.\n");
            } else if (dominioJaExiste(dominio)) {
                printf("Este dominio ja esta registrado!\n");
            } else {
                printf("Digite o nome do responsavel: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = 0;

                if (strlen(nome) == 0) {
                    printf("O nome do responsavel e obrigatorio!\n");
                } else {
                    printf("\nDominio '%s' registrado com sucesso para '%s'!\n", dominio, nome);
                    salvarDominioNoArquivo(dominio, nome);
                }
            }
        } else if (escolha == 2) {
            exibirTodosDominiosDoArquivo();
        } else if (escolha == 3) {
            printf("\nDigite o dominio que deseja verificar: ");
            fgets(dominio, sizeof(dominio), stdin);
            dominio[strcspn(dominio, "\n")] = 0;

            if (dominioJaExiste(dominio)) {
                printf("O dominio '%s' esta registrado.\n", dominio);
            } else {
                printf("O dominio '%s' NAO esta registrado.\n", dominio);
            }
        } else if (escolha == 4) {
            apagarTodosDominiosDoArquivo();
        } else if (escolha == 0) {
            printf("\nEstamos te esperando novamente\n");
        } else {
            printf("\nOpcao invalida. Tente novamente.\n");
        }


    }

    return 0;
}
