/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/main.cc to edit this template
 */

/* 
 * File:   imagem.cpp
 * Author: fl-via-gon-alves
 *
 * Created on 24 de junho de 2024, 18:48
 */

#include <cstdlib>
#include <time.h>
#include "imagem.h"

using namespace std;

/*
 * 
 */

// Função para ajustar o brilho da imagem
int ajustar_brilho(TMatriz entrada, TMatriz saida, int linha, int coluna, int *tomCinzaSaida, float modifica, bool clarear) {

    // static_cast garante que a multiplicação e divisão retorna um número inteiro
    // necessário, pois estamos trabalhando com pixels que devem ser inteiros

    int pixel = 0;  // Variável para armazenar o valor do pixel

    if (clarear == true) {  // Se for para clarear a imagem
        for (int i = 0; i < linha; i++) {
            for (int j = 0; j < coluna; j++) {
                pixel = entrada[i][j] + static_cast<int>(entrada[i][j] * modifica / 100); // Ajusta o brilho

                if (pixel > 255) {  // Garante que o valor do pixel não exceda 255
                    pixel = 255;
                }

                saida[i][j] = pixel;  // Define o valor do pixel na imagem de saída

                if (*tomCinzaSaida < pixel) {  // Atualiza o valor máximo do pixel (tomCinzaSaida)
                    *tomCinzaSaida = pixel;
                }
            }
        }
    } else {  // Se for para escurecer a imagem
        for (int i = 0; i < linha; i++) {
            for (int j = 0; j < coluna; j++) {
                pixel = entrada[i][j] - static_cast<int>(entrada[i][j] * modifica / 100); // Ajusta o brilho

                if (pixel < 0) {  // Garante que o valor do pixel não seja menor que 0
                    pixel = 0;
                }

                saida[i][j] = pixel;  // Define o valor do pixel na imagem de saída

                if (*tomCinzaSaida < pixel) {  // Atualiza o valor máximo do pixel (tomCinzaSaida)
                    *tomCinzaSaida = pixel;
                }
            }
        }
    }

    return 0;  // Retorna 0 indicando sucesso
}

// Função para criar a imagem negativa
int imagem_negativa(TMatriz entrada, TMatriz saida, int linha, int coluna, int tomCinza, int *tomCinzaSaida) {

    *tomCinzaSaida = tomCinza;  // Define o valor máximo do pixel (tomCinzaSaida)

    for (int i = 0; i < linha; i++) {
        for (int j = 0, pixel = 0; j < coluna; j++) {
            pixel = 255 - entrada[i][j];  // Calcula o valor do pixel negativo

            saida[i][j] = pixel;  // Define o valor do pixel na imagem de saída

            if (*tomCinzaSaida < pixel) {  // Atualiza o valor máximo do pixel (tomCinzaSaida)
                *tomCinzaSaida = pixel;
            }
        }
    }

    return 0;  // Retorna 0 indicando sucesso
}

// Função para binarizar a imagem
int imagem_binarizada(TMatriz entrada, TMatriz saida, int linha, int coluna, int tomCinza, int *tomCinzaSaida, int grau) {
    for (int i = 0; i < linha; ++i) {
        for (int j = 0; j < coluna; ++j) {
            if (entrada[i][j] > grau) {  // Se o pixel é maior que o grau, define como tomCinza
                saida[i][j] = tomCinza;
            } else {  // Caso contrário, define como 0
                saida[i][j] = 0;
            }
        }
    }

    *tomCinzaSaida = tomCinza;  // Define o valor máximo do pixel (tomCinzaSaida)

    return 0;  // Retorna 0 indicando sucesso
}

// Função para criar um ícone da imagem
int imagem_iconizada(TMatriz entrada, TMatriz saida, int linha, int coluna, int tomCinza, int *tomCinzaSaida) {

    int icon[64][64];  // Matriz para armazenar o ícone

    double escala_x = linha / 64.0;  // Calcula a escala na dimensão x
    double escala_y = coluna / 64.0;  // Calcula a escala na dimensão y

    *tomCinzaSaida = tomCinza;  // Define o valor máximo do pixel (tomCinzaSaida)

    for (int i = 0; i < 64; i++) {
        for (int j = 0; j < 64; j++) {
            icon[i][j] = entrada[static_cast<int>(i * escala_x)][static_cast<int>(j * escala_y)];  // Reduz a imagem para 64x64

            if (*tomCinzaSaida < icon[i][j]) {  // Atualiza o valor máximo do pixel (tomCinzaSaida)
                *tomCinzaSaida = icon[i][j];
            }
        }
    }

    for (int i = 0; i < linha; i++) {
        for (int j = 0; j < coluna; j++) {
            saida[i][j] = icon[i % 64][j % 64];  // Preenche a imagem de saída com o ícone
        }
    }

    return 0;  // Retorna 0 indicando sucesso
}

// Função para adicionar ruído à imagem
int imagem_ruido(TMatriz entrada, TMatriz saida, int linha, int coluna, int tomCinza, int *tomCinzaSaida) {

    srand(time(0));  // Inicializa a semente para geração de números aleatórios

    *tomCinzaSaida = tomCinza;  // Define o valor máximo do pixel (tomCinzaSaida)

    for (int i = 0; i < linha; i++) {
        for (int j = 0, pixel = 0; j < coluna; j++) {
            pixel = entrada[i][j] + (rand() % 61 - 30);  // Adiciona ruído ao pixel

            // Garante que o valor do pixel esteja dentro do intervalo permitido
            if (pixel < 0) pixel = 0;
            if (pixel > *tomCinzaSaida) pixel = *tomCinzaSaida;

            saida[i][j] = pixel;  // Define o valor do pixel na imagem de saída
        }
    }

    return 0;  // Retorna 0 indicando sucesso
}

// Função para aplicar um filtro linear à imagem
int filtro_linear(TMatriz entrada, TMatriz saida, int linha, int coluna, int tomCinza, int *tomCinzaSaida) {
    
    int tam = 3;  // Tamanho do filtro
    int filtro_soma = 9;  // Soma dos elementos do filtro
    *tomCinzaSaida = tomCinza;  // Define o valor máximo do pixel (tomCinzaSaida)

    // Define o filtro 3x3
    int filtro[tam][tam] = {
        {1, 1, 1},
        {1, 1, 1},
        {1, 1, 1}
    };

    for (int i = 1; i < linha - 1; ++i) {
        for (int j = 1; j < coluna - 1; ++j) {
            int sum = 0;  // Variável para armazenar a soma dos produtos dos pixels pelo filtro

            for (int k = 0; k < tam; ++k) {
                for (int l = 0; l < tam; ++l) {
                    sum += entrada[i + k - 1][j + l - 1] * filtro[k][l];  // Aplica o filtro
                }
            }

            saida[i][j] = sum / filtro_soma;  // Normaliza a soma e define o valor do pixel na imagem de saída

            if (*tomCinzaSaida < saida[i][j]) {  // Atualiza o valor máximo do pixel (tomCinzaSaida)
                *tomCinzaSaida = saida[i][j];
            }
        }
    }
    
    return 0;  // Retorna 0 indicando sucesso
}

// Função de ordenação Bubble Sort para ordenar os valores dos pixels
void bubbleSort(int v[], int tam) {

    for (int i = tam; i > 0; i--) {
        for (int k = 0; k < i - 1; k++) {
            if (v[k] > v[k + 1]) {  // Se o valor atual é nmaior que o próximo, troca-os
                int aux = v[k];
                v[k] = v[k + 1];
                v[k + 1] = aux;
            }
        }
    }
}

// Função para aplicar um filtro não linear (filtro de mediana) à imagem
int filtro_naoLinear(TMatriz entrada, TMatriz saida, int linha, int coluna, int tomCinza, int *tomCinzaSaida){
    
    int tamanhoFiltro = 3;  // Tamanho do filtro
    int deslocamento = tamanhoFiltro / 2;  // Deslocamento para percorrer a vizinhança do pixel
    *tomCinzaSaida = tomCinza;  // Define o valor máximo do pixel (tomCinzaSaida)

    for (int i = deslocamento; i < linha - deslocamento; i++) {
        for (int j = deslocamento; j < coluna - deslocamento; j++) {
            
            int vizinhanca[9];  // Array para armazenar a vizinhança 3x3 dos pixels
            int v = 0;

            for (int k = -deslocamento; k <= deslocamento; k++) {
                for (int l = -deslocamento; l <= deslocamento; l++) {
                    vizinhanca[v++] = entrada[i + k][j + l];  // Coleta os pixels da vizinhança 3x3
                }
            }

            bubbleSort(vizinhanca, 9);  // Ordena os valores dos pixels da vizinhança
            saida[i][j] = vizinhanca[4];  // Define o pixel central como a mediana da vizinhança

            if (*tomCinzaSaida < saida[i][j]) {  // Atualiza o valor máximo do pixel (tomCinzaSaida)
                *tomCinzaSaida = saida[i][j];
            }
        }
    }
    
    return 0;  // Retorna 0 indicando sucesso
}