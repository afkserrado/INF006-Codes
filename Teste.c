/*
Instituto Federal da Bahia (IFBA)
Tecnólogo em Análise e Desenvolvimento de Sistemas (ADS)
Semestre 2025.1
INF006 - Estrutura de Dados e Algoritmos
Professor: José Dihego
Aluno: Anderson Serrado
*/

// ##################################################### //
// BIBLIOTECAS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

// ##################################################### //
// CONSTANTES

#define tamEntrada 501

// ##################################################### //
// STRCUTS

typedef struct {
    int x;
    int y;
    float distancia;
} ponto;

// ##################################################### //
// FUNÇÕES

// Elimina letras e parênteses da linha
void limparLinha(char linha[tamEntrada]) {
    int i, j = 0;  
    int len = strlen(linha); // Calcula o comprimento da linha
    for (i = 0; i < len; i++) {
        if (isdigit(linha[i]) || linha[i] == ',' || linha[i] == ' ' || linha[i] == '-') {
            linha[j] = linha[i];
            j++;
        }
    }
    linha[j] = '\0'; // Insere o terminador nulo
}

// Calcula as distâncias dos pontos até a origem
float calculaDistancia(int x1, int y1, int x2, int y2) {
    float distancia = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
    return distancia;
}

// Insertion sort
void insertionSort(ponto A[], int cont) {
    int i, j;
    ponto temp;
    for (j = 1; j < cont; j++) {
        temp = A[j];
        i = j - 1;

        while (i >= 0 && A[i].distancia > temp.distancia) {
            A[i + 1] = A[i];
            i--;
        }
        A[i + 1] = temp;
    }
}

int main() {
    // Declarações
    char linha[tamEntrada];
    char *token;
    char delimitador[] = ", ";
    ponto pontos[100]; // Supondo um máximo de 100 pontos

    // Leitura manual de linhas de entrada
    while (fgets(linha, tamEntrada, stdin) != NULL) {

        limparLinha(linha);

        // Resets
        int cont = 0; // Marca a posição do ponto no vetor de pontos
        float distance = 0; // Distância total entre os pontos
        float shortcut = 0; // Distância entre o primeiro e último pontos
        int erro = 0;

        token = strtok(linha, delimitador); // Pega o primeiro par

        // Lê a linha até o fim, quando strtok retorna NULL, e separa a string
        while (token != NULL && cont < 100) {

            pontos[cont].x = atoi(token); // Coordenada x do par atual
            token = strtok(NULL, delimitador);

            if (token == NULL) {
                erro = 1; // Número ímpar de valores
                break;
            }

            pontos[cont].y = atoi(token); // Coordenada y do par atual

            // Guarda a distância do ponto até a origem
            pontos[cont].distancia = calculaDistancia(0, 0, pontos[cont].x, pontos[cont].y);

            cont++; // Passa para o próximo par

            token = strtok(NULL, delimitador); // Busca os próximos pares
        }

        if (erro || cont == 0) continue; // Linha não lida. Passa para a próxima

        // Linha só tem 1 ponto
        if (cont <= 1) {
            distance = 0;
            shortcut = 0;
        }
        // Calcula a distância entre o primeiro e último pontos
        else {
            shortcut = calculaDistancia(pontos[0].x, pontos[0].y, pontos[cont - 1].x, pontos[cont - 1].y);

            distance = 0;
            for (int i = 1; i < cont; i++) {
                distance += calculaDistancia(pontos[i - 1].x, pontos[i - 1].y, pontos[i].x, pontos[i].y);
            }
        }

        insertionSort(pontos, cont);

        // Imprime os resultados no console
        printf("points ");
        for (int i = 0; i < cont; i++) {
            printf("(%d,%d) ", pontos[i].x, pontos[i].y);
        }
        printf("distance %.2f shortcut %.2f", distance, shortcut);
        printf("\n");
    }

    return EXIT_SUCCESS;
}
