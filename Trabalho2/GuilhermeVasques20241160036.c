// #################################################
//  Instituto Federal da Bahia
//  Salvador - BA
//  Curso de Análise e Desenvolvimento de Sistemas http://ads.ifba.edu.br
//  Disciplina: INF029 - Laboratório de Programação
//  Professor: Renato Novais - renato@ifba.edu.br

//  ----- Dados do Aluno -----
//  Nome: Guilherme Cauê Andrade Vasques
//  email: guivasques90@gmail.com
//  Matrícula: 20241160036
//  Semestre: 2024.2

// #################################################


#include <stdio.h>
#include <stdlib.h>

// Estrutura Auxiliar
typedef struct {
    int *dados;
    int tamanho;
    int usados;
} EstruturaAuxiliar;

// Fun��o para inicializar as estruturas principais e auxiliares
void inicializarEstruturas(EstruturaAuxiliar **estruturas, int tamanhoPrincipal) {
    for (int i = 0; i < tamanhoPrincipal; i++) {
        estruturas[i] = NULL;
    }
}

// Fun��o para criar uma estrutura auxiliar
int criarEstruturaAuxiliar(EstruturaAuxiliar **estrutura, int tamanho) {
    *estrutura = (EstruturaAuxiliar *)malloc(sizeof(EstruturaAuxiliar));
    if (*estrutura == NULL) return 0;

    (*estrutura)->dados = (int *)malloc(tamanho * sizeof(int));
    if ((*estrutura)->dados == NULL) {
        free(*estrutura);
        *estrutura = NULL;
        return 0;
    }
    (*estrutura)->tamanho = tamanho;
    (*estrutura)->usados = 0;
    return 1;
}

// Fun��o para inserir um elemento
int inserirElemento(EstruturaAuxiliar *estrutura, int elemento) {
    if (estrutura == NULL || estrutura->usados == estrutura->tamanho) {
        return 0; // Sem espa�o ou estrutura inexistente
    }
    estrutura->dados[estrutura->usados++] = elemento;
    return 1;
}

// Fun��o para listar os elementos de todas as estruturas
void listarElementos(EstruturaAuxiliar **estruturas, int tamanhoPrincipal) {
    for (int i = 0; i < tamanhoPrincipal; i++) {
        printf("Posi��o %d: ", i + 1);
        if (estruturas[i] == NULL) {
            printf("(vazia)\n");
        } else {
            printf("Tamanho %d, Elementos: ", estruturas[i]->tamanho);
            for (int j = 0; j < estruturas[i]->usados; j++) {
                printf("%d ", estruturas[i]->dados[j]);
            }
            printf("\n");
        }
    }
}

// Fun��o para ordenar os elementos de uma estrutura auxiliar
void ordenarEstrutura(EstruturaAuxiliar *estrutura) {
    if (estrutura == NULL) return;
    for (int i = 0; i < estrutura->usados - 1; i++) {
        for (int j = i + 1; j < estrutura->usados; j++) {
            if (estrutura->dados[i] > estrutura->dados[j]) {
                int temp = estrutura->dados[i];
                estrutura->dados[i] = estrutura->dados[j];
                estrutura->dados[j] = temp;
            }
        }
    }
}

// Fun��o para listar os n�meros ordenados por estrutura
void listarOrdenadosPorEstrutura(EstruturaAuxiliar **estruturas, int tamanhoPrincipal) {
    for (int i = 0; i < tamanhoPrincipal; i++) {
        if (estruturas[i] != NULL) {
            ordenarEstrutura(estruturas[i]);
            printf("Posi��o %d (ordenada): ", i + 1);
            for (int j = 0; j < estruturas[i]->usados; j++) {
                printf("%d ", estruturas[i]->dados[j]);
            }
            printf("\n");
        }
    }
}

// Fun��o para listar todos os n�meros ordenados
void listarTodosOrdenados(EstruturaAuxiliar **estruturas, int tamanhoPrincipal) {
    int total = 0;
    for (int i = 0; i < tamanhoPrincipal; i++) {
        if (estruturas[i] != NULL) {
            total += estruturas[i]->usados;
        }
    }

    int *todos = (int *)malloc(total * sizeof(int));
    int index = 0;
    for (int i = 0; i < tamanhoPrincipal; i++) {
        if (estruturas[i] != NULL) {
            for (int j = 0; j < estruturas[i]->usados; j++) {
                todos[index++] = estruturas[i]->dados[j];
            }
        }
    }

    // Ordenar o array completo
    for (int i = 0; i < total - 1; i++) {
        for (int j = i + 1; j < total; j++) {
            if (todos[i] > todos[j]) {
                int temp = todos[i];
                todos[i] = todos[j];
                todos[j] = temp;
            }
        }
    }

    printf("Todos os elementos ordenados: ");
    for (int i = 0; i < total; i++) {
        printf("%d ", todos[i]);
    }
    printf("\n");
    free(todos);
}

// Fun��o para excluir um elemento
int excluirElemento(EstruturaAuxiliar *estrutura, int elemento) {
    if (estrutura == NULL) return 0;
    for (int i = 0; i < estrutura->usados; i++) {
        if (estrutura->dados[i] == elemento) {
            for (int j = i; j < estrutura->usados - 1; j++) {
                estrutura->dados[j] = estrutura->dados[j + 1];
            }
            estrutura->usados--;
            return 1;
        }
    }
    return 0; // Elemento n�o encontrado
}

// Fun��o para aumentar o tamanho de uma estrutura auxiliar
int aumentarEstrutura(EstruturaAuxiliar *estrutura, int aumento) {
    if (estrutura == NULL) return 0;
    int *novoArray = (int *)realloc(estrutura->dados, (estrutura->tamanho + aumento) * sizeof(int));
    if (novoArray == NULL) return 0;

    estrutura->dados = novoArray;
    estrutura->tamanho += aumento;
    return 1;
}

int main() {
    const int TAMANHO_PRINCIPAL = 10;
    EstruturaAuxiliar *estruturas[TAMANHO_PRINCIPAL];

    inicializarEstruturas(estruturas, TAMANHO_PRINCIPAL);
    int opcao;

    do {
        printf("\nMenu:\n");
        printf("1. Inserir elemento\n");
        printf("2. Listar os n�meros de todas as estruturas\n");
        printf("3. Listar os n�meros ordenados por estrutura\n");
        printf("4. Listar todos os n�meros ordenados\n");
        printf("5. Excluir um elemento\n");
        printf("6. Aumentar o tamanho de uma estrutura auxiliar\n");
        printf("7. Sair\n");
        printf("Escolha uma op��o: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: {
                int posicao, elemento, tamanho;
                printf("Informe a posi��o (1 a %d): ", TAMANHO_PRINCIPAL);
                scanf("%d", &posicao);
                posicao--;

                if (posicao < 0 || posicao >= TAMANHO_PRINCIPAL) {
                    printf("Posi��o inv�lida.\n");
                    break;
                }

                if (estruturas[posicao] == NULL) {
                    printf("Informe o tamanho da nova estrutura auxiliar: ");
                    scanf("%d", &tamanho);
                    if (!criarEstruturaAuxiliar(&estruturas[posicao], tamanho)) {
                        printf("Erro ao criar estrutura auxiliar.\n");
                        break;
                    }
                }

                printf("Informe o elemento a ser inserido: ");
                scanf("%d", &elemento);
                if (!inserirElemento(estruturas[posicao], elemento)) {
                    printf("Sem espa�o na estrutura auxiliar ou erro.\n");
                }
                break;
            }
            case 2:
                listarElementos(estruturas, TAMANHO_PRINCIPAL);
                break;
            case 3:
                listarOrdenadosPorEstrutura(estruturas, TAMANHO_PRINCIPAL);
                break;
            case 4:
                listarTodosOrdenados(estruturas, TAMANHO_PRINCIPAL);
                break;
            case 5: {
                int posicao, elemento;
                printf("Informe a posi��o (1 a %d): ", TAMANHO_PRINCIPAL);
                scanf("%d", &posicao);
                posicao--;

                if (posicao < 0 || posicao >= TAMANHO_PRINCIPAL || estruturas[posicao] == NULL) {
                    printf("Posi��o inv�lida ou estrutura inexistente.\n");
                    break;
                }

                printf("Informe o elemento a ser exclu�do: ");
                scanf("%d", &elemento);
                if (!excluirElemento(estruturas[posicao], elemento)) {
                    printf("Elemento n�o encontrado.\n");
                }
                break;
            }
            case 6: {
                int posicao, aumento;
                printf("Informe a posi��o (1 a %d): ", TAMANHO_PRINCIPAL);
                scanf("%d", &posicao);
                posicao--;

                if (posicao < 0 || posicao >= TAMANHO_PRINCIPAL || estruturas[posicao] == NULL) {
                    printf("Posi��o inv�lida ou estrutura inexistente.\n");
                    break;
                }

                printf("Informe o tamanho adicional: ");
                scanf("%d", &aumento);
                if (!aumentarEstrutura(estruturas[posicao], aumento)) {
                    printf("Erro ao aumentar estrutura.\n");
                }
                break;
            }
            case 7:
                printf("Saindo...\n");
                break;
            default:
                printf("Op��o inv�lida.\n");
        }
    } while (opcao != 7);

    // Liberar mem�ria
    for (int i = 0; i < TAMANHO_PRINCIPAL; i++) {
        if (estruturas[i] != NULL) {
            free(estruturas[i]->dados);
            free(estruturas[i]);
        }
    }

    return 0;
}
