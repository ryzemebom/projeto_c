# Sistema de Registro de Domínios

Este projeto é um sistema simples para registrar e gerenciar domínios e seus responsáveis, implementado em C. O sistema permite realizar operações como registrar novos domínios, verificar se um domínio está registrado, exibir todos os domínios registrados, apagar um domínio específico ou todos os domínios, além de salvar e carregar os dados de um arquivo.

## Funcionalidades

1. **Registrar um Novo Domínio**
   Permite registrar um novo domínio com o nome do responsável. O sistema valida se o formato do domínio está correto e se o domínio já está registrado.

2. **Exibir Todos os Domínios Registrados**
   Exibe todos os domínios e seus responsáveis armazenados.

3. **Verificar se um Domínio Está Registrado**
   Permite verificar se um domínio específico já está registrado.

4. **Apagar um Domínio Específico**
   Permite apagar um domínio da lista de domínios registrados.

5. **Apagar Todos os Domínios**
   Apaga todos os domínios registrados, tanto na lista quanto no arquivo de armazenamento.

6. **Armazenamento em Arquivo**
   Todos os dados de domínios registrados são salvos em um arquivo de texto (`dominios.txt`), que é carregado ao iniciar o programa.

## Estrutura do Código

O código é dividido em funções que tratam de cada operação específica, como registrar um domínio, exibir a lista de domínios, verificar se um domínio já existe, e apagar domínios. A estrutura `No` é usada para armazenar os domínios e seus respectivos responsáveis.

* **Função RegistrarDominio**: Registra um novo domínio na lista.

![image](https://github.com/user-attachments/assets/84eae39f-3049-4fa1-bc68-5d57193511d4)



* **Função DominioJaExiste**: Verifica se o domínio já está registrado.
* **Função ExibirTodosDominios**: Exibe todos os domínios registrados.
* **Função LimparTela**: Limpa a tela para uma melhor visualização da interface.
* **Função SalvarDominioNoArquivo**: Salva os domínios registrados no arquivo `dominios.txt`.
* **Função CarregarDominiosDoArquivo**: Carrega os domínios registrados a partir do arquivo `dominios.txt`.
