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

void salvarDominioNoArquivo(const char *dominio, const char *nome) {
    FILE *arquivo = fopen("dominios.txt", "a");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para salvar o dominio.\n");
        return;
    }

    fprintf(arquivo, "Dominio: %s, Responsavel: %s\n", dominio, nome);
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

    while (fgets(linha, sizeof(linha), arquivo)) {
        printf("%s", linha);
        encontrou = 1;
    }

    fclose(arquivo);

    if (!encontrou) {
        printf("Nenhum dominio registrado.\n");
    }
}

void apagarTodosDominiosDoArquivo() {
    FILE *arquivo = fopen("dominios.txt", "w");  // Modo "w" apaga o conteúdo
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

        printf("Menu\n");
        printf("1 Registrar um novo dominio\n");
        printf("2 Exibir todos os dominios registrados\n");
        printf("3 Apagar todos os dominios\n");
        printf("0 Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &escolha);
        getchar();  // Limpa o buffer do teclado

        switch (escolha) {
            case 1:
                printf("\nInsira o dominio que deseja registrar: ");
                fgets(dominio, sizeof(dominio), stdin);
                dominio[strcspn(dominio, "\n")] = 0;

                printf("Insira o nome do responsavel: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = 0;

                printf("\nDominio %s registrado com sucesso para %s\n", dominio, nome);
                salvarDominioNoArquivo(dominio, nome);
                break;

            case 2:
                exibirTodosDominiosDoArquivo();
                break;

            case 3:
                dominio[0] = '\0';
                nome[0] = '\0';
                apagarTodosDominiosDoArquivo();
                break;

            case 0:
                printf("\nEncerrando o programa\n");
                break;

            default:
                printf("\nOpcao invalida\n");
        }

        printf("\nPressione Enter para continuar...");
        getchar();
    }

    return 0;
}
