#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definicao da estrutura de dados do estudante (heterognea)
typedef struct {
    char nome[50];
    int matricula;
    float notas[3];
} Estudante;

// Definicao do "no" da lista encadeada
typedef struct Node {
    Estudante aluno;
    struct Node* proximo;
} Node;

// Funcao para criar um novo "no" na memoria heap
Node* criarNo(char* nome, int matricula, float* notas) {
    Node* novoNo = (Node*)malloc(sizeof(Node));
    if (novoNo == NULL) {
        printf("Erro: Falha crtica de alocao de memria.\n");
        exit(1);
    }
    
    strcpy(novoNo->aluno.nome, nome);
    novoNo->aluno.matricula = matricula;
    novoNo->aluno.notas[0] = notas[0];
    novoNo->aluno.notas[1] = notas[1];
    novoNo->aluno.notas[2] = notas[2];
    novoNo->proximo = NULL;
    
    return novoNo;
}

// Insercao dinamica no inicio da lista para maior eficiência
void inserirEstudante(Node** topo, char* nome, int matricula, float* notas) {
    Node* novo = criarNo(nome, matricula, notas);
    novo->proximo = *topo;
    *topo = novo;
    printf("Estudante %s cadastrado com sucesso!\n", nome);
}

// Funcao recursiva para exibir os alunos e calcular as medias
void exibirListaRecursiva(Node* atual) {
    // Caso base: se a lista chegou ao fim, para
    if (atual == NULL) {
        return;
    }
    
    float media = (atual->aluno.notas[0] + atual->aluno.notas[1] + atual->aluno.notas[2]) / 3.0;
    
    printf("Nome: %s | Matrcula: %d | Mdia: %.2f\n", 
           atual->aluno.nome, 
           atual->aluno.matricula, 
           media);
           
    // Chamada recursiva para o proximo elemento da lista
    exibirListaRecursiva(atual->proximo);
}

// Funcao recursiva para buscar um estudante pela matricula
Node* buscarRecursivo(Node* atual, int matricula) {
    // Caso base 1: Aluno nao encontrado ou lista vazia
    if (atual == NULL) {
        return NULL;
    }
    // Caso base 2: Aluno encontrado
    if (atual->aluno.matricula == matricula) {
        return atual;
    }
    // Passo recursivo: continua procurando no resto da lista
    return buscarRecursivo(atual->proximo, matricula);
}

// Remocao de elemento utilizando ponteiro para ponteiro
void removerEstudante(Node** topo, int matricula) {
    Node* atual = *topo;
    Node* anterior = NULL;
    
    while (atual != NULL && atual->aluno.matricula != matricula) {
        anterior = atual;
        atual = atual->proximo;
    }
    
    if (atual == NULL) {
        printf("Matrcula %d nao encontrada para remocao.\n", matricula);
        return;
    }
    
    if (anterior == NULL) {
        *topo = atual->proximo; // O primeiro elemento era o alvo
    } else {
        anterior->proximo = current->proximo; // Ignora o no atual na corrente
    }
    
    free(atual); // Libera a memoria para evitar memory leak
    printf("Registro com matrcula %d removido com sucesso.\n", matricula);
}

// Funcao para limpar toda a memoria antes de fechar o programa
void liberarLista(Node* atual) {
    if (atual == NULL) return;
    liberarLista(atual->proximo);
    free(atual);
}

int main() {
    Node* listaEstudantes = NULL;
    int opcao, mat;
    char nome[50];
    float notas[3];
    
    do {
        printf("\n=== SISTEMA DE GESTAO ACADeMICA ===\n");
        printf("1. Cadastrar Estudante\n");
        printf("2. Exibir Todos os Estudantes\n");
        printf("3. Buscar por Matrcula\n");
        printf("4. Remover Estudante\n");
        printf("5. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar(); // Limpa o buffer do teclado
        
        switch(opcao) {
            case 1:
                printf("Nome do aluno: ");
                fgets(nome, 50, stdin);
                nome[strcspn(nome, "\n")] = 0; // Remove a quebra de linha
                printf("Matrcula (apenas nmeros): ");
                scanf("%d", &mat);
                printf("Nota 1: "); scanf("%f", &notas[0]);
                printf("Nota 2: "); scanf("%f", &notas[1]);
                printf("Nota 3: "); scanf("%f", &notas[2]);
                inserirEstudante(&listaEstudantes, nome, mat, notas);
                break;
                
            case 2:
                printf("\n--- Lista de Alunos ---\n");
                if (listaEstudantes == NULL) {
                    printf("Nenhum aluno cadastrado.\n");
                } else {
                    exibirListaRecursiva(listaEstudantes);
                }
                break;
                
            case 3:
                printf("Digite a matrcula para busca: ");
                scanf("%d", &mat);
                Node* resultado = buscarRecursivo(listaEstudantes, mat);
                if (resultado != NULL) {
                    printf("Aluno Encontrado: %s | Matrcula: %d\n", resultado->aluno.nome, resultado->aluno.matricula);
                } else {
                    printf("Estudante com matrcula %d nao encontrado.\n", mat);
                }
                break;
                
            case 4:
                printf("Digite a matrcula para remover: ");
                scanf("%d", &mat);
                removerEstudante(&listaEstudantes, mat);
                break;
                
            case 5:
                printf("Finalizando o sistema e limpando a memria...\n");
                liberarLista(listaEstudantes);
                break;
                
            default:
                printf("Opcao invlida!\n");
        }
    } while(opcao != 5);
    
    return 0;
}