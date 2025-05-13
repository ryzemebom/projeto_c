#include <stdio.h>
#include <string.h>

void salvarDominioEmArquivo(const char *dominio, const char *nome) {
    FILE *arquivo = fopen("dominios.txt", "a");  // Abre o arquivo no modo "append" (acrescentar)
    if (arquivo == NULL) {
        printf("\nErro ao abrir o arquivo para salvar o dominio.\n");
        return;
    }
    fprintf(arquivo, "Dominio: %s, Responsavel: %s\n", dominio, nome);  // Escreve no arquivo
    fclose(arquivo);  // Fecha o arquivo
    printf("\nDominio salvo no arquivo com sucesso!\n");
}

void carregarDominioDeArquivo(char *dominio, char *nome) {
    FILE *arquivo = fopen("dominios.txt", "r");
    if (arquivo == NULL) {
        printf("\nNenhum dominio registrado no arquivo.\n");
        return;
    }

    char linha[200];

    // Lê a primeira linha do arquivo
    if (fgets(linha, sizeof(linha), arquivo)) {
        // Tenta extrair dominio e nome da linha
        if (sscanf(linha, "Dominio: %99[^,], Responsavel: %99[^\n]", dominio, nome) == 2) {
            printf("\nDominio carregado do arquivo: %s, Responsavel: %s\n", dominio, nome);
        } else {
            printf("\nFormato de linha invalido no arquivo.\n");
        }
    } else {
        printf("\nNenhum dominio registrado no arquivo.\n");
    }

    fclose(arquivo);
}

void apagarDominioNoArquivo(const char *dominio) {
    FILE *arquivo = fopen("dominios.txt", "r");  // Abre o arquivo no modo "read"
    if (arquivo == NULL) {
        printf("\nErro ao abrir o arquivo para apagar o dominio.\n");
        return;
    }

    // Cria um arquivo temporário para armazenar os dados atualizados
    FILE *temp = fopen("temp.txt", "w");
    if (temp == NULL) {
        printf("\nErro ao criar arquivo temporário.\n");
        fclose(arquivo);
        return;
    }

    char linha[200];
    int encontrado = 0;

    // Copia as linhas para o arquivo temporário, exceto a linha com o domínio a ser apagado
    while (fgets(linha, sizeof(linha), arquivo)) {
        if (strstr(linha, dominio) == NULL) {
            fputs(linha, temp);
        } else {
            encontrado = 1;
        }
    }

    fclose(arquivo);
    fclose(temp);

    if (encontrado) {
        remove("dominios.txt");  // Apaga o arquivo original
        rename("temp.txt", "dominios.txt");  // Renomeia o arquivo temporário para o nome original
        printf("\nDominio apagado com sucesso do arquivo!\n");
    } else {
        printf("\nDominio nao encontrado no arquivo.\n");
        remove("temp.txt");  // Remove o arquivo temporário caso não tenha sido necessário
    }
}

int main() {
    int escolha = -1;
    char dominio[100] = "";  // Variável para armazenar o domínio
    char nome[100] = "";     // Variável para armazenar o nome do responsável

    // Carregar o domínio e o responsável do arquivo
    carregarDominioDeArquivo(dominio, nome);

    while (escolha != 0) {
        printf("\nMenu\n");
        printf("1 Registrar um novo dominio\n");
        printf("2 Exibir o dominio\n");
        printf("3 Apagar o dominio\n");
        printf("0 Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &escolha);
        getchar();  // Limpar o buffer do teclado

        if (escolha == 1) {
            printf("\nInsira o dominio que deseja registrar: ");
            fgets(dominio, sizeof(dominio), stdin);
            dominio[strcspn(dominio, "\n")] = 0;  // Remove a quebra de linha

            printf("Insira o nome do responsavel: ");
            fgets(nome, sizeof(nome), stdin);
            nome[strcspn(nome, "\n")] = 0;  // Remove a quebra de linha

            printf("\nDominio %s registrado com sucesso para %s\n", dominio, nome);

            // Salva o domínio no arquivo
            salvarDominioEmArquivo(dominio, nome);
        }
        else if (escolha == 2) {
            printf("\n");
            if (dominio[0] == '\0') {
                printf("Nenhum dominio registrado\n");
            } else {
                printf("Dominio registrado: %s\n", dominio);
                printf("Responsavel: %s\n", nome);
            }
        }
        else if (escolha == 3) {
            printf("\n");
            if (dominio[0] == '\0') {
                printf("Nenhum dominio para apagar\n");
            } else {
                apagarDominioNoArquivo(dominio);  // Apaga o domínio do arquivo
                dominio[0] = '\0';  // Limpa o domínio da memória
                nome[0] = '\0';     // Limpa o nome da memória
                printf("Dominio apagado com sucesso\n");
            }
        }
        else if (escolha == 0) {
            printf("\nEncerrando o programa\n");
        }
        else {
            printf("\nOpcao invalida\n");
        }
    }

    return 0;
}
