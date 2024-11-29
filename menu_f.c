#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int numero;
    char nome[50];
    char telefone[15];
} Cliente;

void cadastrarCliente() {
    Cliente cliente;
    FILE *arquivo = fopen("clientes.txt", "a");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }
    printf("Digite o número do cliente: ");
    scanf("%d", &cliente.numero);
    getchar(); // Limpa o buffer
    printf("Digite o nome do cliente: ");
    fgets(cliente.nome, 50, stdin);
    cliente.nome[strcspn(cliente.nome, "\n")] = '\0'; // Remove o '\n'
    printf("Digite o telefone do cliente: ");
    fgets(cliente.telefone, 15, stdin);
    cliente.telefone[strcspn(cliente.telefone, "\n")] = '\0'; // Remove o '\n'

    fprintf(arquivo, "%d;%s;%s\n", cliente.numero, cliente.nome, cliente.telefone);
    fclose(arquivo);
    printf("Cliente cadastrado com sucesso!\n");
}

void consultarCliente() {
    int numeroBusca;
    Cliente cliente;
    FILE *arquivo = fopen("clientes.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo ou arquivo vazio!\n");
        return;
    }
    printf("Digite o número do cliente para consulta: ");
    scanf("%d", &numeroBusca);

    int encontrado = 0;
    while (fscanf(arquivo, "%d;%49[^;];%14[^\n]\n", &cliente.numero, cliente.nome, cliente.telefone) == 3) {
        if (cliente.numero == numeroBusca) {
            printf("Cliente encontrado:\n");
            printf("Número: %d\n", cliente.numero);
            printf("Nome: %s\n", cliente.nome);
            printf("Telefone: %s\n", cliente.telefone);
            encontrado = 1;
            break;
        }
    }
    if (!encontrado) {
        printf("Cliente não encontrado.\n");
    }
    fclose(arquivo);
}

void gerarRelatorio() {
    Cliente cliente;
    FILE *arquivo = fopen("clientes.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo ou arquivo vazio!\n");
        return;
    }
    printf("Relatório de clientes cadastrados:\n");
    printf("=================================\n");
    while (fscanf(arquivo, "%d;%49[^;];%14[^\n]\n", &cliente.numero, cliente.nome, cliente.telefone) == 3) {
        printf("Número: %d | Nome: %s | Telefone: %s\n", cliente.numero, cliente.nome, cliente.telefone);
    }
    printf("=================================\n");
    fclose(arquivo);
}

void excluirCliente() {
    int numeroExclusao;
    Cliente cliente;
    FILE *arquivo = fopen("clientes.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    if (arquivo == NULL || temp == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }
    printf("Digite o número do cliente a ser excluído: ");
    scanf("%d", &numeroExclusao);

    int excluido = 0;
    while (fscanf(arquivo, "%d;%49[^;];%14[^\n]\n", &cliente.numero, cliente.nome, cliente.telefone) == 3) {
        if (cliente.numero == numeroExclusao) {
            excluido = 1;
            continue;
        }
        fprintf(temp, "%d;%s;%s\n", cliente.numero, cliente.nome, cliente.telefone);
    }

    fclose(arquivo);
    fclose(temp);

    remove("clientes.txt");
    rename("temp.txt", "clientes.txt");

    if (excluido) {
        printf("Cliente excluído com sucesso!\n");
    } else {
        printf("Cliente não encontrado.\n");
    }
}

int main() {
    int opcao;
    do {
        printf("\nMenu:\n");
        printf("1. Cadastro\n");
        printf("2. Consulta\n");
        printf("3. Gerar relatório\n");
        printf("4. Excluir\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrarCliente();
                break;
            case 2:
                consultarCliente();
                break;
            case 3:
                gerarRelatorio();
                break;
            case 4:
                excluirCliente();
                break;
            case 0:
                printf("Saindo do programa...\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}
