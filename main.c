#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Produto {
    int codigo;
    char nome[50];
    float preco;
    int quantidade;
};

struct Venda {
    int codigoProduto;
    char nome[50];
    int quantidade;
    float valorTotal;
};

int main() {
    struct Produto produtos[100];
    int totalProdutos = 0;
    int opcao = 0;
    float totalVendas = 0;

    struct Venda vendas[100];
    int totalVendasRegistradas = 0;

    while (opcao != 8) {
        system("cls");

        printf("=============================\n");
        printf("--- SISTEMA DE VENDAS ---\n");
        printf("=============================\n");
        printf("1 - Cadastrar produto\n");
        printf("2 - Listar produtos\n");
        printf("3 - Realizar venda\n");
        printf("4 - Total vendido\n");
        printf("5 - Historico de vendas\n");
        printf("6 - Buscar vendas por produto\n");
        printf("7 - Ranking de produtos\n");
        printf("8 - Sair\n");
        printf("=============================\n");

        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {

        case 1:
            printf("\nCadastro de produto\n");

            printf("Codigo: ");
            scanf("%d", &produtos[totalProdutos].codigo);

            printf("Nome: ");
            scanf("%49s", produtos[totalProdutos].nome);

            printf("Preco: R$ ");
            scanf("%f", &produtos[totalProdutos].preco);

            printf("Quantidade: ");
            scanf("%d", &produtos[totalProdutos].quantidade);

            totalProdutos++;

            printf("\n=== PRODUTO CADASTRADO COM SUCESSO ===\n");
            system("pause");
            break;

        case 2:
            printf("\n--- PRODUTOS ---\n");

            for (int i = 0; i < totalProdutos; i++) {
                printf("Codigo: %d | Nome: %s | Preco: R$ %.2f | Qtd: %d\n",
                    produtos[i].codigo,
                    produtos[i].nome,
                    produtos[i].preco,
                    produtos[i].quantidade);
            }
            system("pause");
            break;

        case 3: {
            int codigoBusca;
            int encontrado = 0;

            printf("\nDigite o codigo do produto: ");
            scanf("%d", &codigoBusca);

            if (totalProdutos == 0) {
                printf("\nNenhum produto cadastrado!\n");
                system("pause");
                break;
            }

            for (int i = 0; i < totalProdutos; i++) {
                if (produtos[i].codigo == codigoBusca) {

                    int quantidadeVenda;

                    printf("Quantidade para venda: ");
                    scanf("%d", &quantidadeVenda);

                    if (quantidadeVenda > 0 && quantidadeVenda <= produtos[i].quantidade) {

                        float valorVenda = quantidadeVenda * produtos[i].preco;

                        produtos[i].quantidade -= quantidadeVenda;
                        totalVendas += valorVenda;

                        vendas[totalVendasRegistradas].codigoProduto = produtos[i].codigo;
                        sprintf(vendas[totalVendasRegistradas].nome, "%s", produtos[i].nome);
                        vendas[totalVendasRegistradas].quantidade = quantidadeVenda;
                        vendas[totalVendasRegistradas].valorTotal = valorVenda;

                        totalVendasRegistradas++;

                        printf("\n=== VENDA REALIZADA COM SUCESSO ===\n");
                        printf("Valor da venda: R$ %.2f\n", valorVenda);
                    } else {
                        printf("\n=== ESTOQUE INSUFICIENTE ===\n");
                    }

                    encontrado = 1;
                    break;
                }
            }

            if (encontrado == 0) {
                printf("\n=== PRODUTO NAO ENCONTRADO ===\n");
            }

            system("pause");
            break;
        }

        case 4:
            printf("\nTotal vendido: R$ %.2f\n", totalVendas);
            system("pause");
            break;

        case 5:
            printf("\n--- HISTORICO DE VENDAS ---\n");

            for (int i = 0; i < totalVendasRegistradas; i++) {
                printf("\nProduto: %s\n", vendas[i].nome);
                printf("Codigo: %d\n", vendas[i].codigoProduto);
                printf("Quantidade: %d\n", vendas[i].quantidade);
                printf("Total: R$ %.2f\n", vendas[i].valorTotal);
            }

            if (totalVendasRegistradas == 0) {
                printf("\nNenhuma venda registrada!\n");
            }

            system("pause");
            break;

        case 6: {
            int codigoBusca;
            int encontrado = 0;

            printf("\nDigite o codigo do produto: ");
            scanf("%d", &codigoBusca);

            printf("\n--- VENDAS DO PRODUTO ---\n");

            for (int i = 0; i < totalVendasRegistradas; i++) {
                if (vendas[i].codigoProduto == codigoBusca) {
                    printf("\nProduto: %s\n", vendas[i].nome);
                    printf("Quantidade: %d\n", vendas[i].quantidade);
                    printf("Total: R$ %.2f\n", vendas[i].valorTotal);
                    encontrado = 1;
                }
            }

            if (encontrado == 0) {
                printf("\nNenhuma venda encontrada para esse produto.\n");
            }

            system("pause");
            break;
        }

        case 7: {
            int codigos[100];
            int quantidades[100];
            int totalUnicos = 0;

            for (int i = 0; i < 100; i++) {
                quantidades[i] = 0;
            }

            if (totalVendasRegistradas == 0) {
                printf("\nNenhuma venda realizada ainda!\n");
            } else {
                for (int i = 0; i < totalVendasRegistradas; i++) {
                    int encontrado = 0;

                    for (int j = 0; j < totalUnicos; j++) {
                        if (codigos[j] == vendas[i].codigoProduto) {
                            quantidades[j] += vendas[i].quantidade;
                            encontrado = 1;
                            break;
                        }
                    }

                    if (encontrado == 0) {
                        codigos[totalUnicos] = vendas[i].codigoProduto;
                        quantidades[totalUnicos] = vendas[i].quantidade;
                        totalUnicos++;
                    }
                }

                for (int i = 0; i < totalUnicos - 1; i++) {
                    for (int j = i + 1; j < totalUnicos; j++) {
                        if (quantidades[j] > quantidades[i]) {

                            int tempQ = quantidades[i];
                            quantidades[i] = quantidades[j];
                            quantidades[j] = tempQ;

                            int tempC = codigos[i];
                            codigos[i] = codigos[j];
                            codigos[j] = tempC;
                        }
                    }
                }

                printf("\n--- RANKING DE PRODUTOS ---\n");

                int limite = totalUnicos;
                if (limite > 3) limite = 3;

                for (int i = 0; i < limite; i++) {
                    for (int j = 0; j < totalVendasRegistradas; j++) {
                        if (vendas[j].codigoProduto == codigos[i]) {
                            printf("\n%dº Lugar\n", i + 1);
                            printf("Produto: %s\n", vendas[j].nome);
                            printf("Quantidade: %d\n", quantidades[i]);
                            break;
                        }
                    }
                }
            }

            system("pause");
            break;
        }

        case 8:
            printf("\nSaindo do sistema...\n");
            break;

        default:
            printf("\n=== OPCAO INVALIDA ===\n");
            system("pause");
        }
    }

    return 0;
}