#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char nome[25];
    long int id;
    int estoque;
    float preco;
} cadastro_produtos;

int contadorProdutos = 0;
int tamanhoVetorProdts = 100;
cadastro_produtos *produtos = NULL;

void menuDeProdutos();
void exibirProdutos();
void cadastrarProdutos();
void atualizarProduto();
int excluirProduto();
void salvarProdutos();
void lerProdutos();
int procuraProduto(long int idDigitado);

int main() {
    produtos = (cadastro_produtos *)calloc(tamanhoVetorProdts, sizeof(cadastro_produtos));
    if (produtos == NULL) {
        printf("\aERRO");
        return 1;
    }

    menuDeProdutos();

    free(produtos);
    return 0;
}

void menuDeProdutos() {
    int flag = 1;
    int codigo = 0;
    char voltar = 'q';

    while (flag == 1) {
        while (codigo != 7) {
            system("cls");

            printf("\n\n=====\t\t||\t\t MENU DE PRODUTOS \t\t||\t\t=====\n\n");

            printf("\n \t Código  \t Opção              \t\n");
            printf("\n \t 1       \t Exibir             \t");
            printf("\n \t 2       \t Cadastrar          \t");
            printf("\n \t 3       \t Atualizar          \t");
            printf("\n \t 4       \t Excluir            \t");
            printf("\n \t 5       \t Salvar             \t");
            printf("\n \t 6       \t Ler                \t");
            printf("\n \t 7       \t Voltar             \t\n");

            printf("\nDigite o código para selecionar a opção: ");
            scanf("%d", &codigo);
            getchar();

            switch (codigo) {
            case 1:
                flag = 0;

                system("cls");

                if (contadorProdutos > 0) {
                    exibirProdutos();
                } else {
                    printf("\n\aAVISO: Você não possui produtos cadastrados.\n");
                }

                break;

            case 2:
                flag = 0;

                system("cls");

                int addProdutos = 0;

                printf("\n\n=====\t\t||\t\t CADASTRO DE PRODUTOS \t\t||\t\t=====\n\n");
                printf("\nDigite a quantidade de produtos que você quer cadastrar: ");
                scanf("%i", &addProdutos);
                getchar();

                for (int i = 0; i < addProdutos; i++) {
                    cadastrarProdutos();
                }
                contadorProdutos += addProdutos;

                break;

            case 3:
                flag = 0;

                system("cls");

                if (contadorProdutos > 0) {
                    exibirProdutos();
                    atualizarProduto();
                } else {
                    printf("\n\aAVISO: Você não possui produtos cadastrados.\n");
                }

                break;

            case 4:
                flag = 0;

                system("cls");

                if (contadorProdutos > 0) {
                    exibirProdutos();

                    if (excluirProduto() == 1) {
                        contadorProdutos = contadorProdutos - 1;
                    }
                } else {
                    printf("\n\aAVISO: Você não possui produtos cadastrados.\n");
                }

                break;

            case 5:
                flag = 0;

                if (contadorProdutos > 0) {
                    salvarProdutos();
                    printf("\nArquivo salvo com sucesso!");
                } else {
                    printf("\n\aAVISO: Você não possui produtos cadastrados.\n");
                }

                break;

            case 6:
                flag = 0;

                lerProdutos();
                printf("\nArquivo lido com sucesso!");

                break;

            case 7:
                flag = 0;

                printf("\nVocê será redirecionado ao menu principal. Aperte qualquer tecla para continuar.");
                scanf("%c", &voltar);

                system("cls");

                break;

            default:
                flag = 1;
                printf("\n\aCódigo inválido!");
                scanf("%c", &voltar);

                system("cls");

                break;
            }

            if (codigo != 7) {
                printf("\n\nVocê será redirecionado ao menu de produtos. Aperte qualquer tecla para continuar.");
                scanf("%c", &voltar);
            }
        }
    }
}

void exibirProdutos() {
    char voltar;

    printf("\n\n=====\t\t||\t\t PRODUTOS \t\t||\t\t=====\n\n");
    printf("\n\t ID      \t Produto \t Preço        \t Estoque \t\n");

    for (int i = 0; i < tamanhoVetorProdts; i++) {
        if (produtos[i].id > 0) {
            printf("\n\t %ld   \t\t %s      \t R$ %.2f      \t %d      \t",
                   produtos[i].id,
                   produtos[i].nome,
                   produtos[i].preco,
                   produtos[i].estoque);
        }
    }
}

void cadastrarProdutos() {
    for (int i = 0; i < tamanhoVetorProdts; i++) {
        if (produtos[i].id == 0) {
            long int id;
            char nome[25];
            float preco;

            do {
                printf("\nDigite o ID do produto sendo este maior que 0: ");
                scanf("%li", &id);
                getchar();
                if (id < 1 || procuraProduto(id) != -1) {
                    printf("\nCódigo inválido ou já existente!\n");
                } else {
                    produtos[i].id = id;
                }
            } while (id < 1);

            printf("\nDigite o nome do produto de ID %li com até 25 caracteres: ", produtos[i].id);
            scanf("%24s", nome);
            strcpy(produtos[i].nome, nome);

            do {
                printf("\nDigite o estoque do produto de ID %li sendo este valor maior ou igual a 0: ", produtos[i].id);
                scanf("%d", &produtos[i].estoque);
                getchar();
                if (produtos[i].estoque < 0) {
                    printf("Quantidade inválida!\n");
                }
            } while (produtos[i].estoque < 0);

            do {
                printf("\nDigite o preço do produto de ID %li sendo este valor maior ou igual a 0: ", produtos[i].id);
                scanf("%f", &preco);
                produtos[i].preco = preco;
                getchar();
                if (produtos[i].preco < 0) {
                    printf("Preço inválido!\n");
                }
            } while (produtos[i].preco < 0);

            break;
        }
    }
}

void atualizarProduto() {
    printf("\n\n=====\t\t||\t\t ATUALIZAÇÃO DE PRODUTOS \t\t||\t\t=====\n\n");
    long int idDigitado = 0;
    int indice, quantidadeNova = -1;
    float valorNovo = -1;

    do {
        printf("\nDigite o ID do produto que você deseja alterar: ");
        scanf("%li", &idDigitado);
        getchar();
        indice = procuraProduto(idDigitado);

        if (indice == -1) {
            printf("\nProduto não encontrado!\n");
        }
    } while (indice == -1);

    int quantidadeAntiga = produtos[indice].estoque;
    float valorAntigo = produtos[indice].preco;

    do {
        printf("\nDigite o novo estoque do produto de ID %li sendo este valor maior ou igual a 0: ", produtos[indice].id);
        scanf("%d", &quantidadeNova);
        getchar();
        if (quantidadeNova < 0) {
            printf("Quantidade inválida!\n");
        }
    } while (quantidadeNova < 0);

    produtos[indice].estoque = quantidadeNova;

    do {
        printf("\nDigite o novo preço do produto de ID %li sendo este valor maior ou igual a 0: ", produtos[indice].id);
        scanf("%f", &valorNovo);
        getchar();
        if (valorNovo < 0) {
            printf("Preço inválido!\n");
        }
    } while (valorNovo < 0);

    produtos[indice].preco = valorNovo;

    system("cls");

    printf("\n\n=====\t\t||\t\t         ANTIGO          \t\t||\t\t=====\n\n");
    printf("\n\t ID     \t Produto \t Preço     \t Quantidade \t\n");
    printf("\n\t %d     \t %s      \t R$ %.2f   \t %d         \t", produtos[indice].id, produtos[indice].nome, valorAntigo, quantidadeAntiga);

    printf("\n\n=====\t\t||\t\t          NOVO           \t\t||\t\t=====\n\n");
    printf("\n\t %d     \t %s      \t R$ %.2f   \t %d         \t", produtos[indice].id, produtos[indice].nome, produtos[indice].preco, produtos[indice].estoque);
}

int excluirProduto() {
    long int idDigitado = 0;
    int indice, confirma, retorno = 0;
    printf("\n\n=====\t\t||\t\t EXCLUIR PRODUTOS \t\t||\t\t=====\n\n");

    do {
        printf("\nDigite o ID do produto que você deseja excluir: ");
        scanf("%li", &idDigitado);
        getchar();
        indice = procuraProduto(idDigitado);

        if (indice == -1) {
            printf("\nProduto não encontrado!\n");
        }
    } while (indice == -1);

    printf("\n\n=====\t\t||\t\t CONFIRMAR EXCLUSÃO \t\t||\t\t=====\n\n");
    printf("\n\t %d     \t %s      \t R$ %.2f   \t %d         \t", produtos[indice].id, produtos[indice].nome, produtos[indice].preco, produtos[indice].estoque);

    while (1) {
        printf("\n\nAperte 1 para confirmar e 2 para cancelar: ");
        scanf("%d", &confirma);
        getchar();

        if (confirma == 1) {
            produtos[indice].id = 0;
            printf("\nProduto excluído com sucesso.\n");
            retorno = 1;
            break;
        } else if (confirma == 2) {
            printf("\nAção cancelada.\n");
            break;
        } else {
            printf("Código inválido!\n");
        }
    }

    return retorno;
}

void salvarProdutos() {
    FILE *arquivo = fopen("produtos.txt", "w");

    if (arquivo == NULL) {
        printf("\nERRO NA ABERTURA DO ARQUIVO\n");
        exit(2);
    }

    fprintf(arquivo, "TamanhoVetorProdts: %d\n", contadorProdutos);

    for (int i = 0; i < contadorProdutos; i++) {
        fprintf(arquivo, "ID: %ld\n", produtos[i].id);
        fprintf(arquivo, "Produto: %s\n", produtos[i].nome);
        fprintf(arquivo, "Estoque: %d\n", produtos[i].estoque);
        fprintf(arquivo, "Valor: %.2f\n", produtos[i].preco);
    }

    fclose(arquivo);
}

void lerProdutos() {
    FILE *arquivo = fopen("produtos.txt", "r");

    if (arquivo == NULL) {
        printf("\nERRO NA ABERTURA DO ARQUIVO\n");
        exit(3);
    }

    fscanf(arquivo, "TamanhoVetorProdts: %d\n", &contadorProdutos);

    for (int i = 0; i < contadorProdutos; i++) {
        fscanf(arquivo, "ID: %ld", &produtos[i].id);
        fscanf(arquivo, "Produto: %s", produtos[i].nome);
        fscanf(arquivo, "Estoque: %d", &produtos[i].estoque);
        fscanf(arquivo, "Valor: %f", &produtos[i].preco);
    }

    fclose(arquivo);
}

int procuraProduto(long int idDigitado) {
    for (int i = 0; i < tamanhoVetorProdts; i++) {
        if (produtos[i].id == idDigitado) {
            if (produtos[i].id == 0) {
                return -1;
            } else {
                return i;
            }
        }
    }
    return -1;
}
